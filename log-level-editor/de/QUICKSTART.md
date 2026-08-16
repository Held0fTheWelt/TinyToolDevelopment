<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/LogLevelEditor/architecture.md -->
# Schnellanleitung

Diese Anleitung führt Sie von der Installation bis zu einem **konkreten Ergebnis**: Die Ausführlichkeit (Verbosity) einer Log-Kategorie wurde geändert und als dauerhafte Überschreibung gespeichert, die Editor-Neustarts übersteht. Log Level Editor funktioniert eigenständig – es ist kein anderes Plugin erforderlich.

## Was Sie nach dieser Anleitung haben

Das Tool ist geöffnet mit Ihren Projekt-Logkategorien aufgelistet, die Ausführlichkeit einer Kategorie wurde geändert und diese Überschreibung wurde im Plugin-DataAsset gespeichert.

## Anforderungen

- Unreal Engine 5 Editor.
- Keine Software von Drittanbietern, Konten oder Zusatz-Runtimes erforderlich. Siehe [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## 1. Installieren und Aktivieren

1. Fügen Sie **LogLevelEditor** aus Ihrer Fab-Bibliothek zum Projekt hinzu (oder installieren Sie es in der Engine).
2. Öffnen Sie **Edit → Plugins**, aktivieren Sie **LogLevelEditor** und starten Sie den Editor neu, wenn Sie dazu aufgefordert werden.

## 2. Tool öffnen (Erstes Ergebnis)

1. Öffnen Sie **Tools → Log Tools → Log Level Editor**. Ein andockbarer Tab öffnet sich und scannt den Quellcode Ihres Projekts (und Ihrer Projekt-Plugins) nach Log-Kategorien.
2. Jede Zeile zeigt den **Kategorienamen** (z. B. `LogTemp`), den **erkannten Standardwert**, die **aktuelle Stufe** und den **Quellcode-Pfad** (falls verfügbar).

Sie sehen nun jede entdeckte Log-Kategorie und ihre Live-Ausführlichkeit.

## 3. Ein konkretes Beispiel: Ausführlichkeit einer Kategorie ändern

1. Nutzen Sie das Suchfeld, um `LogTemp` zu finden.
2. Klicken Sie in dieser Zeile auf die Schaltfläche **Warning**.

**Erwartetes Ergebnis:** Das Plugin führt den passenden Unreal-Konsolenbefehl aus, die Zeile aktualisiert sich auf `Warning` und die Änderung wird als dauerhafte Überschreibung im Plugin-DataAsset gespeichert (sodass sie beim nächsten Editor-Start erneut angewendet wird).

3. Zum Rückgängigmachen: Wählen Sie den **erkannten Standardwert** der Zeile. Wenn der ausgewählte Wert dem erkannten Standard entspricht, entfernt das Plugin die dauerhafte Überschreibung automatisch, damit das DataAsset auf echte Überschreibungen fokussiert bleibt.

## 4. Wo Überschreibungen gespeichert werden

Dauerhafte Überschreibungen werden im konfigurierten `ULogLevelDataAsset` gespeichert (eingestellt über **LogLevelDataAsset** in den Einstellungen). Gespeicherte Überschreibungen werden beim Editor-Start erneut angewendet, sobald die Engine Konsolenbefehle akzeptieren kann.

## 5. Einstellungen

Öffnen Sie die Plugin-Einstellungen (Project/Editor settings → Log Level Editor), um Folgendes zu steuern:

- `LogLevelDataAsset`, `bAutoSaveLogLevelDataAsset`
- `bShowToolbarButton`
- `bAlsoListEnginePluginChannels`, `bAlsoListEngineSourceChannels` (Engine-Scans sind aufwendig)
- `LogChannelsToHide`, `LogChannelsToHideTemporary`

Siehe [SettingsReference.md](SettingsReference.md).

## 6. Nächste Schritte

- Vollständiger Workflow (dauerhaftes vs. temporäres Ausblenden, Team-Workflow, Start-Anwendung):
  [UserManual.md](UserManual.md).
- Probleme: [TROUBLESHOOTING.md](TROUBLESHOOTING.md) und [FAQ.md](FAQ.md).
