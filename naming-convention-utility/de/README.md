<!-- doc-provenance: product-facts.yml reconciled 2026-07-04; source AKDB:plugins/NamingConventionUtility/architecture.md -->
# Naming Convention Utility Dokumentation

Naming Convention Utility ist ein Unreal Engine-Editor-Plugin zur Anwendung konsistenter Asset-Präfixe und -Suffixe über ausgewählte Content Browser-Ordner hinweg. Es erkennt Asset-Typen, erstellt einen Umbenennungsplan, validiert Zielnamen, zeigt geplante Änderungen in einer andockbaren Workbench als Vorschau an und wendet ausgewählte Unreal-Asset-Umbenennungen über die Asset-Tools des Editors an.

Dieser Ordner enthält die vollständige Dokumentation, die mit dem Plugin geliefert wird.

## Hier beginnen

- [BUYER_GUIDE.md](BUYER_GUIDE.md): käuferfreundliche Übersicht, Anwendungsfälle und Eignung.
- [QUICKSTART.md](QUICKSTART.md): kurzer Leitfaden von der Installation bis zum Ergebnis.
- [UserManual.md](UserManual.md): vollständiger Workflow für Konfiguration, Scannen, Bearbeiten, Berichterstellung und Anwenden von Konventionen.
- [FAQ.md](FAQ.md): Fab-bereite Fragen und Antworten für Käufer.

## Referenz

- [SettingsReference.md](SettingsReference.md): Einstellungen, DataAsset-Felder und empfohlene Grundstandards.
- [TechnicalOverview.md](TechnicalOverview.md): Architektur und Sicherheitsmodell für Maintainer.
- [CodeDocumentation.md](CodeDocumentation.md): Quellcode-Layout, Verträge und Erweiterungspunkte.
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md): häufige Probleme und Lösungen.
- [ReleaseChecklist.md](ReleaseChecklist.md): Validierungscheckliste vor dem Versand.

## Enthaltene Assets

- `../Readme.pdf`: klassische verpackte Readme.
- `../Content/Editor/Data/DA_NamingConvention.uasset`: Standard-Konventions-DataAsset.
- `../Content/Editor/Data/DT_NamingConvention.uasset`: DataTable-Beispiel/Quell-Asset.
- `../Resources/NamingConvention.csv`: CSV-Importreferenz.
- `../Resources/NamingConvention.json`: JSON-Importreferenz.
- `../Resources/NamingConvention_EpicRecommended.csv`: Epic-konforme Profil-Importreferenz.
- `../Resources/NamingConvention_TinyLegacy.csv`: abwärtskompatible 1.0.x-Profil-Importreferenz.
- `../Resources/FileTypeValues.txt`: Dateityp-Enum-Referenz.
- `../Resources/ToolTypeValues.txt`: DataTable-Werkzeugtyp-Referenz.

## Schneller Workflow

1. Aktivieren Sie das Plugin und starten Sie den Editor neu, falls erforderlich.
2. Öffnen Sie die Project Settings und überprüfen Sie das konfigurierte Naming Conventions DataAsset.
3. Öffnen Sie die Workbench über das Plugin-Menü oder eine Ordner-Kontextaktion.
4. Wählen Sie **Epic Recommended**, **Tiny Legacy** oder **Project Custom**.
5. Scannen Sie den Ordner, prüfen Sie Konformität, Überspringungsgründe und Zielpfade.
6. Wählen Sie die akzeptierten Zeilen aus, die Sie anwenden möchten, und exportieren Sie einen Bericht oder wenden Sie die Änderungen nach der Überprüfung an.
7. Speichern Sie betroffene Assets/Pakete, nachdem Unreal die Umbenennung abgeschlossen hat.

## Sicherheitsmodell

Das Plugin behandelt Umbenennungsoperationen als folgenschwer. Vor dem Aufruf der Unreal-Asset-Umbenennungswerkzeuge erstellt es einen Plan und überspringt risikoreiche Einträge.

Der Plan prüft:

- Nicht unterstützte Asset-Typen.
- Fehlende Konventionseinträge.
- Generierte Namen, die leer oder ungültig sind.
- Ziel-Objektpfade, die ungültig sind.
- Bereits vorhandene Ziel-Assets.
- Bereits vorhandene Zielpakete auf der Festplatte.
- Doppelte Ziele innerhalb desselben Stapeleintrags.
- Doppelte Quell-Assets, die über überlappende Ordner ausgewählt wurden.

Die Workbench zeigt vor dem Anwenden des Plans eine Vorschau an, schützt das Anwenden mit einem überprüften Plan-Hash und schreibt JSON/Markdown-Berichte unter `Saved/NamingConventionUtility/Reports/`.

## Was das Tool ändert

Das Plugin benennt Unreal-Assets über `IAssetTools::RenameAssets` um.

Es tut Folgendes nicht:

- Rohdateien außerhalb des Asset-Systems umbenennen.
- Importierte Quelldateien bearbeiten.
- Klassennamen in C++ ändern.
- Blueprint-Klassennamen innerhalb von generiertem Code ändern.
- Die Namenskonvention Ihres Studios für Sie festlegen.

## Standard-Namensfamilien

Das Standard-DataAsset enthält gängige Unreal-Präfixe wie:

- `T_`, `T_N_`, `T_D_` für Texturen.
- `M_`, `MI_`, `MF_` für Materialien.
- `SM_`, `SK_`, `SKEL_` für Meshes und Skelette.
- `BP_`, `BPI_`, `BPF_`, `WB_` für Blueprints und Widgets.
- `NS_`, `NE_`, `PS_` für Effekte.
- `DT_`, `CT_`, `CF_`, `CV_`, `CLC_` für Daten und Kurven.

Die Workbench umfasst außerdem:

- `epic_recommended`: Epic-konforme Präfixe mit dokumentierten Kollisionszuordnungen.
- `tiny_legacy`: den abwärtskompatiblen Standardstil der Version 1.0.x.
- `project_custom`: Ihre konfigurierten DataAsset-Regeln.

Sie können das DataAsset bearbeiten oder ersetzen, um es an Ihren Studio-Standard anzupassen. Die Workbench kann auch ein integriertes Profil in das konfigurierte Projekt-DataAsset kopieren.

## Wichtige Einschränkungen

- Die Textur-Untertyperkennung nutzt eine Kombination aus Komprimierungseinstellungen und Namenstokens. Sie ist eine Hilfe, keine Hellseherei.
- Vom Plugin nicht erkannte Asset-Typen werden übersprungen.
- Unreal zeigt möglicherweise weiterhin Umbenennungsdialoge an oder lässt Umbenennungen aufgrund von Referenzen, Quellcodeverwaltung oder gesperrten Paketen fehlschlagen.
- Umbenennungen großer Ordner sollten sorgfältig geprüft werden.

## Rechtlicher Hinweis

Naming Convention Utility ist ein Produktivitätswerkzeug für den Editor. Es hilft bei der Anwendung von Namensstandards, garantiert jedoch nicht, dass ein Namensstandard für jedes Studio, jeden Marketplace oder jede Projekt-Pipeline korrekt ist.
