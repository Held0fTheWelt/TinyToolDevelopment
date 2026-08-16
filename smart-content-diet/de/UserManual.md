<!-- doc-provenance: AKDB:plugins/SmartContentDiet/architecture.md; docs/architecture/plugins/SmartContentDiet/product-facts.yml; reconciled 2026-07-16 -->
# Benutzerhandbuch

Dieses Handbuch fasst den Editor-Workflow von Smart Content Diet zusammen und verweist auf die detaillierten Leitfäden.

## Einstiegspunkt

Öffnen Sie **Tools → Content Tools → Smart Content Diet**. Das Fenster ist eine rollenbewusste Shell.

## Rollen und Tabs

Legen Sie die Rolle (Anfänger / Ingenieur / Producer) und die Erklärungstiefe in den **Einstellungen** oder der Zielgruppenauswahl im Header fest. Die Sichtbarkeit der Tabs folgt der Rolle:

| Tab | Anfänger | Erweitert (Ingenieur / Producer) |
| --- | --- | --- |
| Übersicht, Optimieren, Ergebnisse, Einstellungen | ✓ | ✓ |
| Preset | — | ✓ |
| Governance (Trend, Schulden, Budget, Eigentümerschaft, Deep Scan) | — | ✓ |
| Redundanz | — | ✓ (nur mit externem Ähnlichkeitsanbieter) |

## Scan-Tiefen

Wählen Sie im Header: **Quick Safe** (Registry/Metadaten, kein Asset-Laden), **Full** (lädt Assets), **Deep** (tiefe Material-/Mesh-Metriken; Governance → Deep Scan). Jeder Analyzer-Lauf berücksichtigt die ausgewählte Tiefe; das Commandlet berücksichtigt `-QuickSafe` / `-FullScan` / `-DeepScan`.

Breite Scans nutzen eine AssetRegistry-zuerst-Pipeline. SCD sammelt Kandidaten einmal, liest günstige Textur-/Materialmetadaten wo möglich aus Tags, vergleicht zuerst tag-basiert und lädt nur die überlebende Kandidatenmenge tief, die Objektdaten benötigt. Phase 1 (schreibgeschützter Vergleich) kann parallel laufen; verändernde QuickFixes erfordern weiterhin explizite Benutzer- oder Commandlet-Aktionen.

Duplikat- und Alpha-Pfade teilen sich Hilfscode zwischen Scan-Ergebnissen und Reduktionen. Textur-/Material-Alpha-Prüfungen nutzen dieselbe Material-Instance-Deckkraftlogik, und Reduktions-Frühausstiege nutzen reduktionskonforme Duplikatschlüssel, sodass eine sichere Konsolidierung nicht übersprungen wird, nur weil der strengere Scan-Index die Assets nicht gruppiert hat.

## Kern-Workflow — Sicherer Optimierungszyklus (ohne KI)

1. Öffnen Sie das Werkzeug.
2. Wählen Sie die Scan-Tiefe (Quick Safe / Full / Deep).
3. Führen Sie den Scan über den Header aus.
4. Überprüfen Sie die **Übersicht**, dann **Optimieren → Sichere Optimierungswarteschlange**.
5. **Sichere Vorschau** → Backup / Quellcodeverwaltung → **Sicher anwenden**.
6. Die Shell führt nach einer erfolgreichen Anwendung oder einer Einzel-Asset-Korrektur automatisch einen erneuten Scan durch.
7. Vergleichen Sie Warteschlangenanzahlen und das Delta; JSON-Berichte werden unter `Saved/SmartContentDiet/OptimizationQueue/<timestamp>/` abgelegt.

## Allgemeiner Analyse-Workflow

1. Führen Sie einen Scan aus (Auswahl-, Ordner- oder Projektumfang).
2. Überprüfen Sie Ergebnisse nach Schweregrad, Auswirkung, Dimension und Erklärbarkeitskette.
3. Verwenden Sie **Preset** (erweitert), um zu sehen, wie sich Bewertungsgewichtungen auf die Ergebnisse auswirken.
4. Verwenden Sie **Governance** (erweitert) für Trend, Schulden, Budget, Eigentümerschaft und optionalen Deep Scan.
5. Wenden Sie QuickFixes erst nach Bestätigung von Backup/Quellcodeverwaltung an.
6. Scannen Sie erneut und validieren Sie im Zielprojektkontext.

## Sicherheit

Verändernde Aktionen modifizieren Projekt-Assets und sind standardmäßig genehmigungsgeschützt. Führen Sie sie nur in einem gesicherten, quellcodeverwalteten und wegwerfbaren Workspace aus. Siehe den Sicherheitshinweis in [QUICKSTART.md](QUICKSTART.md).

## Editor-Aufträge und UCM

Kürzliche Editor-Arbeiten werden als Auftragshistorie für Scans, Validierungen und Optimierungsaktionen aufgezeichnet. Wenn Unreal Capability Mesh aktiviert ist, stellt SCD schreibgeschützte Auftragsrouten bereit:

```text
scd.editor.jobs.list.v1
scd.editor.jobs.status.v1
```

Der Unified MCP Server kann diese Routen über `jobs_list` / `jobs_status` aggregieren; SCD selbst ist nicht von UMCP abhängig.

## Detaillierte Leitfäden

- Editor-Shell, Tabs, Ergebnisse, QuickFixes, Governance: [../Resources/UI_AND_BEHAVIOR.md](../Resources/UI_AND_BEHAVIOR.md).
- Sichere Optimierungswarteschlange (Buckets, Sicherheitsregeln, Berichtsschema): [../Resources/OPTIMIZATION_QUEUE.md](../Resources/OPTIMIZATION_QUEUE.md).
- Architektur: [../Resources/SMART_ANALYSIS_ARCHITECTURE.md](../Resources/SMART_ANALYSIS_ARCHITECTURE.md).
