---
lang: de
title: EditorExtensionBase Third-Party Software
audience: [end_user]
owner_ref: plugin:EditorExtensionBase
applies_to:
  component: EditorExtensionBase
contract_ref: plugin:EditorExtensionBase/third-party-software
version:
  since: "1.0"
---
# Software von Drittanbietern

Editor Extension Base **bündelt keinen Quellcode von Drittanbietern, keine Laufzeit-Binärdateien, keine KI-Modelle, kein Node.js, keinen Python-Code oder eigenständige ausführbare Dateien**. Es handelt sich um ein C++-Unreal Engine-Plugin, das auf Unreal-Editor-Modulen und Editor Scripting Utilities aufbaut.

## Messmethode

Es wurde nach `ThirdParty`, `LICENSE-` und Urheberrechtshinweisen in `GovernanceDevelopmentPlugins/EditorExtensionBase` gesucht. Die Header-Dateien verweisen auf die Tiny Tool Development / Fab EULA. Es ist kein eingebetteter Drittanbieter-Codebaum vorhanden.

## Engine-Abhängigkeiten (nicht gebündelt)

| Abhängigkeit | Gebündelt? | Anmerkungen |
| --- | --- | --- |
| Unreal Engine Editor-Module | Nein | Wird durch die Engine-Installation bereitgestellt. |
| Editor Scripting Utilities | Nein | Aktiviert über den `.uplugin`-Eintrag `Plugins`; Plugin im Besitz von Epic. |

## Optionale Integrationen

Feature-Plugins können Editor Extension Base für gemeinsam genutzte Widgets abhängig machen. Diese Konsumenten sind separate Pakete und werden hier nicht neu verteilt.

**Fab-Deklaration zu Software von Drittanbietern:** keine.

## Verwandte Dokumente

- [README.md](README.md)
- [QUICKSTART.md](QUICKSTART.md)
- [FAQ.md](FAQ.md)

## Urheberrechtshinweise

Editor- und Laufzeitquellen verwenden die Header der Tiny Tool Development / Fab Standard EULA. Es wurden keine zusätzlichen Lizenzdateien in einem `ThirdParty`-Verzeichnis gefunden.

## Checkliste für die Käufererklärung

1. Deklarieren Sie **keine** gebündelte Software von Drittanbietern für Fab.
2. Editor Scripting Utilities bleibt eine Abhängigkeit des Epic-Engine-Plugins und kein gebündelter Drittanbieter-Codebaum.
3. Führen Sie die Suche nach jeder zukünftigen Änderung an eingebetteten Komponenten erneut durch, bevor Sie diese Datei aktualisieren.
