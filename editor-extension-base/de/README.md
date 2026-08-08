# Dokumentation zur Basis der Editor-Erweiterung

Editor Extension Base ist eine gemeinsame Unreal-Editor-Grundlage für UI-Plugins zur Tiny Tool Development. Es stellt wiederverwendbare Editor Utility Widgets, Hilfsfunktionen zur Auswahl / zum Checkout / zum Speichern im Content Browser, Undo-Vorbereitungshilfen sowie ein leichtgewichtiges Runtime-Makromodul bereit.

Zielgruppe: Plugin-Autoren und Teams, die eine konsistente Editor-UX benötigen, ohne Widget- und Auswahl-Boilerplate zu kopieren. Dieses Paket ist eine Unterstützungsschicht – es registriert kein eigenes Tiny Tools-Produktmenü.

## Funktionen

- Gemeinsame Editor Utility Widgets (Header, Schaltfläche, Registerkartenschaltfläche, Zwei-Spalten-Layout).
- `UEditorManagerUtilityLibrary` für Auswahl, Checkout/Speichern und Editor-Welt-Hilfsfunktionen.
- Undo-Vorbereitung und undoierbare Asset-Aktions-Hilfsfunktionen.
- Runtime-Modul (`EditorExtensionRuntimeBase`) mit gemeinsamen Makros für Nicht-Editor-Konsumenten.

## Erste Schritte

1. Aktivieren Sie das Plugin (und Editor Scripting Utilities) – siehe [QUICKSTART.md](QUICKSTART.md).
2. Rufen Sie `GetSelectedAssetsForAction` aus einem Editor Utility oder einem C++-Editor-Tool auf.
3. Lesen Sie [UserManual.md](UserManual.md) und [SettingsReference.md](SettingsReference.md) für den vollständigen Katalog.

## Verwandte Dateien

- [../README.md](../README.md) — Produktübersicht.
- [../CHANGELOG.md](../CHANGELOG.md) — Versionshistorie.
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md) · [FAQ.md](FAQ.md) · [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md)
