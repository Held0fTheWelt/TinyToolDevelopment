<!-- doc-provenance: AKDB:plugins/SmartContentDiet/architecture.md; docs/architecture/plugins/SmartContentDiet/product-facts.yml; reconciled 2026-07-16 -->
# Schnellstart

Dieser Guide führt Sie von der Installation zu einem **echten Ergebnis**: einem Scan der Assets Ihres Projekts mit Optimierungsergebnissen und (optional) einem geprüften, sicheren Fix, der mit Vorher-Nachher-Berichten angewendet wird.
Der Kernprozess von Smart Content Diet funktioniert eigenständig — **keine KI, kein Peer-Plugin und kein externes Tool erforderlich**.

> **⚠ Sicherheit geht vor.** Das Anwenden von Fixes, Reduzierungen, Asset-Verschiebungen/-Löschungen, Baseline-Aktualisierungen oder Governance-Schreibungen **ändert Projekt-Assets**. Führen Sie diese Aktionen nur in einem **gesicherten, quellcodeverwalteten, disposableen** Workspace durch — niemals auf ungeschützten Quelldaten. Scans und Vorschauen sind schreibgeschützt und sicher.

## Was Sie nach diesem Guide haben

Das Tool in Ihrer gewählten Rolle, einen abgeschlossenen Quick Safe-Scan mit Ergebnissen und das Verständnis, wie Sie sichere Optimierungen vorschauen und anwenden sowie das Vorher-Nachher-Delta lesen.

## Anforderungen

- Unreal Engine 5.4+ Editor mit einem Projekt, das Content-Assets enthält.
- Keine Drittanbieter-Software, kein Konto, kein KI-Modell und keine externe Laufzeit. Siehe
  [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## 1. Installation und Aktivierung

1. Fügen Sie **SmartContentDiet** aus Ihrer Fab-Bibliothek zum Projekt hinzu (oder installieren Sie es in der Engine).
2. Öffnen Sie **Edit → Plugins**, aktivieren Sie **SmartContentDiet** und starten Sie neu, wenn dazu aufgefordert wird.

## 2. Öffnen Sie das Tool und wählen Sie eine Rolle (Erstes Ergebnis)

1. Öffnen Sie **Tools → Content Tools → Smart Content Diet**.
2. Wählen Sie in der Header-Rollen-Auswahl (oder **Settings**) Ihre Rolle:
   - **Beginner** — Übersicht, Optimize, Findings, Settings; mehr Erklärungen.
   - **Engineer / Producer (fortgeschritten)** — fügt Preset und Governance (Trend, Debt, Budget,
     Ownership, Deep Scan) hinzu sowie Redundanz, wenn ein externer Ähnlichkeitsanbieter registriert ist.
3. Lassen Sie die **Scan-Tiefe** auf **Quick Safe** (Standard — nur Registry/Metadaten, kein Asset-Laden; schnell).
4. Klicken Sie im Header auf **Quick Safe Scan**.

**Erwartete Ausgabe:** Der Scan wird abgeschlossen, und der Tab **Overview** fasst die Ergebnisse zusammen (was sicher verbessert werden kann). Dies ist schreibgeschützt.

## 3. Ein echtes Beispiel: Vorschau und Anwendung eines sicheren Fixes

> Sichern / committen Sie Ihr Projekt zuerst (siehe Sicherheitshinweis oben).

1. Öffnen Sie den Tab **Optimize** → **Safe Optimization Queue**.
2. Klicken Sie auf **Preview Safe**, um die geplanten sicheren Optimierungen und das projizierte Vorher-Nachher-Delta zu sehen (immer noch schreibgeschützt).
3. Klicken Sie auf **Apply Safe**, um die sichere Warteschlange anzuwenden. Nach einer erfolgreichen Anwendung (oder einem einzelnen Asset-Fix aus den Details von **Findings**) **scant die Shell automatisch neu**.
4. Vergleichen Sie die Warteschlangenzahlen und die Delta-Zusammenfassung im Optimize-Panel.

**Erwartete Ausgabe:** Sichere Optimierungen werden angewendet, und ein JSON-Anwendungsbericht wird unter folgendem Pfad geschrieben:

```text
Saved/SmartContentDiet/OptimizationQueue/<timestamp>/
```

## 4. Scan-Tiefen

| Tiefe | Lädt Assets? | Verwendung |
| --- | --- | --- |
| **Quick Safe** (Standard) | Nein | Schnelles „Was kann ich sicher verbessern?“ |
| **Full** | Ja | Umsetzbare Mesh-/Texture-/Material-Ergebnisse |
| **Deep** | Ja | Langsamste; tiefe Material-/Static-Mesh-Metriken (Governance → Deep Scan) |

Die Beschriftung und der Hinweis der Header-Schaltfläche aktualisieren sich mit der gewählten Tiefe, die jeder Analyzer-Lauf berücksichtigt.

## 5. Nächste Schritte

- Editor-Shell, Tabs, Findings, Governance: [../Resources/UI_AND_BEHAVIOR.md](../Resources/UI_AND_BEHAVIOR.md).
- Safe Optimization Queue (Buckets, Sicherheitsregeln, Berichts-Schema):
  [../Resources/OPTIMIZATION_QUEUE.md](../Resources/OPTIMIZATION_QUEUE.md).
- Einstellungen und Rollen: [SettingsReference.md](SettingsReference.md).
- Probleme: [TROUBLESHOOTING.md](TROUBLESHOOTING.md) und [FAQ.md](FAQ.md).

> **Optional / fortgeschritten:** SCD bietet auch ein headless Commandlet für CI (`-QuickSafe`, `-FullScan`,
> `-DeepScan`, `-OptimizationQueueReport`, `-ApplySafeQueue`) und — nur wenn Sie auch **Unreal Capability Mesh (UCM)** besitzen — optionale, in der Setup-Deklaration angegebene Ökosystem-Routen. Beides ist für den oben beschriebenen Editor-Workflow nicht erforderlich; siehe [Dokumentationsindex](README.md).
