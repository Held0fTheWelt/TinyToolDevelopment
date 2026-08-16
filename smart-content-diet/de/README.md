<!-- doc-provenance: AKDB:plugins/SmartContentDiet/architecture.md; docs/architecture/plugins/SmartContentDiet/product-facts.yml; reconciled 2026-07-16 -->
# SmartContentDiet Dokumentation

SmartContentDiet scannt Unreal Engine Projekt-Assets, erklärt Optimierungsergebnisse im Kontext, stellt Governance-Ansichten bereit und bietet geprüfte QuickFix / Reduktions-Workflows. Der Standard-Produktzyklus ist **Scannen → Prüfen → Sichere Fixes anwenden → Erneut scannen → Verbesserung messen** — ohne KI oder externe Werkzeuge.

## Sicherheitshinweis

SmartContentDiet kann Projekt-Assets verändern, wenn QuickFixes, Mesh-Reduktionen, Textur-/Materialänderungen, Asset-Review-Verschiebungen/-Löschungen, Baseline-Updates oder Governance-Schreibvorgänge angewendet werden. Verwenden Sie es nur in einem gesicherten, quellcodeverwalteten und wegwerfbaren Branch oder Workspace. Führen Sie es niemals auf ungeschütztem Quellcode aus. Die Nutzung erfolgt auf eigenes Risiko.

Die Funktionalität ist im angegebenen Umfang sorgfältig implementiert, ersetzt jedoch keine Backups, Quellcodeverwaltung, Code-/Inhaltsprüfungen oder projektspezifische Validierungen.

## Dokumentationsübersicht

| Dokument | Zielgruppe | Inhalt |
|----------|------------|--------|
| [UI_AND_BEHAVIOR.md](../Resources/UI_AND_BEHAVIOR.md) | Artists, Tech Artists, Producer | Editor-Shell, Tabs, Scan-Workflow, Ergebnisse, QuickFixes, Governance |
| [OPTIMIZATION_QUEUE.md](../Resources/OPTIMIZATION_QUEUE.md) | Alle Editor-Benutzer | Sichere Optimierungswarteschlange, Buckets, Anwenden/Vorschau, Vorher/Nachher-Delta |
| [SMART_ANALYSIS_ARCHITECTURE.md](../Resources/SMART_ANALYSIS_ARCHITECTURE.md) | Ingenieure, Integratoren | Analyzer, Presets, Auswirkungen, Reduktion, Trend, Governance-Architektur |
| [DIMENSION_INTEGRATION_STATUS.md](../Resources/DIMENSION_INTEGRATION_STATUS.md) | Ingenieure | FindingType, Dimensionszuordnung, Konverter, UI-Integrationsstatus |
| [SmartAnalysisResult_Usage.md](../Resources/SmartAnalysisResult_Usage.md) | Ingenieure | Ergebnismodellnutzung, Auto-Fix-Metadaten |
| [CHANGELOG.md](../CHANGELOG.md) | Release-Operators | Versionshistorie |

**Neu hier?** Beginnen Sie mit [QUICKSTART.md](QUICKSTART.md) für Installation und den sicheren Scan→Fix-Zyklus.

## Paket für installierte Engine

Verwenden Sie ein Smart Content Diet BuildPlugin-Paket, das für die installierte Engine-Version erstellt wurde. Das Paket enthält generierte Binärdateien und Präkompilierungsmetadaten, die von installierten Builds benötigt werden. Entfernen Sie diese Dateien beim Kopieren oder Archivieren des Plugins nicht.

> **Für Maintainer:** Das SCD-Release-Gate und die Release/Runbook-Dokumente befinden sich im Entwicklungs-Repository und sind **nicht** Teil des Fab-Pakets; Sie benötigen diese nicht zur Installation oder Nutzung von SCD.

## Editor-Einstiegspunkt

Öffnen Sie **Tools → Content Tools → Smart Content Diet**.

### Rollenbewusste Shell

Das Hauptfenster verwendet Zielgruppeneinstellungen (Anfänger / Ingenieur / Producer), um die Erklärungstiefe und die sichtbaren Tabs zu steuern.

| Tab | Anfänger | Erweitert (Ingenieur / Producer + erweiterter Modus) |
|-----|----------|--------------------------------------------------|
| Übersicht | ✓ | ✓ |
| Optimieren | ✓ | ✓ |
| Ergebnisse | ✓ | ✓ |
| Preset | — | ✓ |
| Governance | — | ✓ (Trend, Schulden, Budget, Eigentümerschaft, Deep Scan als Unter-Tabs) |
| Redundanz | — | ✓ nur wenn ein externer Ähnlichkeitsanbieter registriert ist |
| Einstellungen | ✓ | ✓ |

Ändern Sie Rolle und Erklärungstiefe in den **Einstellungen** oder über die Zielgruppenauswahl im Header.

### Scan-Tiefen (Header)

| Tiefe | Lädt Assets? | Typische Nutzung |
|-------|--------------|------------------|
| **Quick Safe** (Standard) | Nein — Registry/Metadaten-Pfad | Erster Lauf, schnelles „Was kann ich sicher verbessern?“ |
| **Full** | Ja — Vollständige Analyzer-Pipeline | Handlungsrelevante Mesh-/Textur-/Material-Ergebnisse |
| **Deep** | Ja — Beinhaltet tiefe Material-/Static-Mesh-Metriken | Langsamste Tiefe; Shader-Statistik und tiefe Mesh-Arbeit |

Das Header-Kombinationsfeld aktualisiert die Beschriftung der Haupt-Scan-Schaltfläche (`Quick Safe Scan` / `Full Scan` / `Deep Scan`) und zeigt einen Tiefenhinweis unter den Steuerelementen.

Die ausgewählte Tiefe wird von **jedem** Analyzer-Lauf berücksichtigt: Editor-Analyseläufe (Ergebnisse / Governance → Analyse ausführen) übergeben sie an `FSmartAnalysisOrchestrator`, und die Governance-Statuszeile nennt die verwendete Tiefe. **Commandlet und CI** berücksichtigen `-QuickSafe`, `-FullScan` und `-DeepScan` wie bisher. Die tiefen Material-/Mesh-Metriken nutzen zusätzlich den Governance Deep Scan-Workflow (`Governance → Deep Scan`), analog zum Commandlet.

## Schnelle Workflows

### UCM-Ökosystem-Routen

Wenn Unreal Capability Mesh (UCM) aktiviert ist, kann SmartContentDiet über konfigurationsdeklarierte Routen anstelle direkter Provider-Brücken verwendet werden. SCD verlinkt niemals ein Peer-Plugin und listet keines in `required_plugin_names` oder `Build.cs`; plattformübergreifender Mehrwert entsteht durch JSON-Routen, nicht durch Code-Abhängigkeiten. Das aktive Projektprofil macht **12 SCD-Funktionen** verfügbar:

| Funktion | Art | Richtlinie |
| --- | --- | --- |
| `scd.migration.advice_from_handoff` | Beratung | Schreibgeschützt |
| `scd.scan.run` | Anbieter | Schreibgeschützt |
| `scd.findings.get` | Anbieter | Schreibgeschützt |
| `scd.findings.explain` | Anbieter | Schreibgeschützt |
| `scd.health.snapshot` | Anbieter | Schreibgeschützt |
| `scd.health.evidence` | Anbieter | Schreibgeschützt |
| `scd.governance.snapshot` | Anbieter | Schreibgeschützt |
| `scd.similarity.groups` | Ähnlichkeit | Schreibgeschützt |
| `scd.similarity.ingest_groups` | Ähnlichkeit | Schreibgeschützt |
| `scd.optimize.preview_safe` | Optimierung | Schreibgeschützt |
| `scd.optimize.apply_safe` | Optimierung | **Verändernd — erfordert Genehmigung** |
| `scd.optimize.apply_fix` | Optimierung | **Verändernd — erfordert Genehmigung** |

**Degradierungsvertrag.** Jede Funktion gibt den gemeinsamen Umschlag `smart_content_diet.capability_mesh_endpoint.v1` zurück (`status` ist `ok`/`degraded`/`error`). Funktionen reduzieren ihren Funktionsumfang, anstatt fehlzuschlagen, wenn eine Vorbedingung fehlt: Die Optimierungs-/Ergebnisrouten geben einen `error`-Umschlag zurück, der auffordert, zuerst `scd.scan.run` auszuführen; `scd.optimize.apply_fix` gibt einen `degraded`-Umschlag (keine Mutation) zurück, wenn eine destruktive Korrektur ohne `allow_destructive: true` angefordert wird. Die Verbindung von SCD mit einem Peer wird niemals vorausgesetzt — eine Route, die auf ein anderes Plugin verweist (z. B. das Beispiel `scd_ingest_from_iis.v1`, `iis.search.hybrid → scd.similarity.ingest_groups`), wird von der UCM-Ermittlung als *verfügbar, aber Plugin nicht geladen* gemeldet, wenn dieser Peer fehlt, während jede reine SCD-Funktion *verfügbar* bleibt.

**Genehmigungsgate (und Option 3).** Die zwei verändernden Routen tragen `requires_user_approval: true`, sodass UCM sie mit `ApprovalRequired` blockiert, bis ein Mensch den Lauf genehmigt — vorher wird kein Asset verändert. Operatoren, die eine unbeaufsichtigte sichere Anwendung wünschen, können die Routenrichtlinie ändern, um die Genehmigungsanforderung aufzuheben (Option 3); der Standard wird genehmigungsgeschützt ausgeliefert.

PRS-Platzierungs-Workflows bleiben PRS-eigene UCM-Routen. Freebie-Brücken bleiben nur für Teams ohne UCM und als Referenzimplementierungen für direkte Adapter verfügbar; sie sind im Hauptprojekt nicht erforderlich.

### Eigenständiger sicherer Optimierungszyklus (ohne KI)

### Scan-Korrektheit und Leistung

Der aktuelle Analyzer-Pfad arbeitet AssetRegistry-zuerst. Er erstellt die Kandidatenmenge einmal, liest Tag-Metadaten vor dem Laden von Assets, parallelisiert schreibgeschützte Vergleichsarbeiten und lädt nur endgültige Kandidaten tief. Ein Metadaten-Cache pro Asset mit Zeitstempel-/Versionsungültigerklärung vermeidet das Wiederholen unveränderter Arbeiten.

Duplikat- und Alpha-Analysen teilen sich Hilfsprogramme mit der Reduktionsengine. Reduktions-Frühausstiege nutzen reduktionskonforme Duplikatschlüssel (`DuplicateTextureReduction`, `DuplicateStaticMeshReduction`), sodass sichere Konsolidierungsprüfungen mit der Fingerabdrucklogik des eigentlichen Reduzierers übereinstimmen. Textur-Alpha-Heuristiken sind in `SCDMaterialAlpha` zentralisiert, um das Verhalten von Analyzer und Reduktion auszurichten.

Die Editor-Auftragshistorie ist über UCM-Routen (`scd.editor.jobs.list.v1`, `scd.editor.jobs.status.v1`) für die UMCP-Aggregation verfügbar, ohne eine UMCP-Abhängigkeit zu SCD hinzuzufügen.

1. Öffnen Sie Smart Content Diet.
2. Belassen Sie die Scan-Tiefe auf **Quick Safe** oder wählen Sie **Full** / **Deep**.
3. Führen Sie den Scan über den Header aus.
4. Überprüfen Sie die **Übersicht** und öffnen Sie dann **Optimieren** → Sichere Optimierungswarteschlange.
5. **Sichere Vorschau** → **Sicher anwenden** (Backup / Quellcodeverwaltung zuerst).
6. Nach erfolgreicher Anwendung oder Korrektur eines einzelnen Assets in den Details der **Ergebnisse** führt die Shell automatisch einen erneuten Scan durch.
7. Vergleichen Sie die Warteschlangenanzahlen und die Delta-Zusammenfassung im Optimieren-Panel; JSON-Anwendungsberichte werden unter `Saved/SmartContentDiet/OptimizationQueue/<timestamp>/` abgelegt.

Siehe [OPTIMIZATION_QUEUE.md](../Resources/OPTIMIZATION_QUEUE.md) für Bucket-Definitionen, Sicherheitsregeln und Berichtsschemata.

### Allgemeiner Analyse-Workflow

1. Führen Sie einen Scan aus (Auswahl-, Ordner- oder Projektumfang).
2. Überprüfen Sie Ergebnisse nach Schweregrad, Auswirkung, Dimension und Erklärbarkeitskette.
3. Verwenden Sie **Preset** (erweitert), um zu verstehen, wie sich Beweistungsfaktoren auf die Bewertungen auswirken.
4. Verwenden Sie **Governance** (erweitert) für Trend, Schulden, Budget, Eigentümerschaft und optionalen Deep Scan.
5. Wenden Sie QuickFixes erst nach Bestätigung von Backup/Quellcodeverwaltung an.
6. Scannen Sie erneut und validieren Sie im Zielprojektkontext.

## Commandlet (CI / headless)

```powershell
UnrealEditor-Cmd.exe "<Project>.uproject" -run=SmartContentDiet `
  -QuickSafe -OptimizationQueueReport -Path=/Game -Limit=50 `
  -NoFail -unattended -nop4 -nosplash
```

Sichere Warteschlangenzeilen anwenden (nur im gesicherten Projekt):

```powershell
UnrealEditor-Cmd.exe "<Project>.uproject" -run=SmartContentDiet `
  -QuickSafe -ApplySafeQueue -OptimizationQueueReport -Path=/Game `
  -NoFail -unattended -nop4 -nosplash
```

| Flagge | Wirkung |
|--------|---------|
| `-QuickSafe` | Registry/Abhängigkeitsscan; lädt keine Assets |
| `-FullScan` | Lädt Assets und führt Analyzer aus (Standard, wenn `-QuickSafe` fehlt) |
| `-DeepScan` | Langsamste Tiefe; tiefe Material-/Mesh-Metriken |
| `-OptimizationQueueReport` | Schreibt Warteschlangen-JSON/Markdown (automatisch aktiviert bei `-QuickSafe`) |
| `-ApplySafeQueue` | Wendet nur **Safe Now**-Zeilen an; destruktive Zeilen werden abgelehnt |
| `-Path=/Game/...` | Scan-Umfang |
| `-NoFail` | Beendet mit 0, selbst wenn Richtlinienwarnungen vorliegen (in CI mit Vorsicht verwenden) |

Das Commandlet gibt die Sicherheitswarnung bei Verwendung und Ausführungsstart aus. Baseline-Updates und Berichtsschreibvorgänge sind den Workspace verändernde Operationen.

## Artefakt-Pfade (gitignored)

| Artefakt | Pfad |
|----------|------|
| Anwendungsbericht der Optimierungswarteschlange | `Saved/SmartContentDiet/OptimizationQueue/<timestamp>/apply_report.json` |
| Commandlet-Warteschlangenbericht | `-ReportDir` / Standard unter `Saved/SmartContentDiet/` |
| Release-Validierungsausgabe | `Saved/SCDValidation/`, wenn Maintainer-Validierung ausgeführt wird |

## Implementierter QuickFix-Umfang (Zusammenfassung)

SmartContentDiet bietet geprüfte QuickFixes für Textur-, Static/Skeletal Mesh-, Material-, Animations-, Audio/VFX-Hygiene sowie Asset-Prüfung/Konsolidierung. Destruktive oder übergreifende Aktionen erfordern eine explizite Bestätigung und sind standardmäßig nicht stapelverarbeitungssicher.

Vollständiger Katalog: [UI_AND_BEHAVIOR.md § Optimization Packs](../Resources/UI_AND_BEHAVIOR.md#71-optimization-packs).

## Release-Validierung

Die Release-Validierung ist ein Maintainer-Workflow. Die Käufernutzung erfordert keine lokalen Gate-Skripte, Host-Projekt-Testmodule oder repositoryspezifische Pfade.
