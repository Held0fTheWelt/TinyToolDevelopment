---
lang: de
title: GameFeaturedClasses Third-Party Software
audience: [end_user]
owner_ref: plugin:GameFeaturedClasses
applies_to:
  component: GameFeaturedClasses
contract_ref: plugin:GameFeaturedClasses/third-party-software
version:
  since: "1.0"
---
# Software von Drittanbietern

GameFeaturedClasses **bündelt keinen Quellcode von Drittanbietern, keine Laufzeit-Binärdateien, keine KI-Modelle, keine Node.js-, Python- oder eigenständigen ausführbaren Dateien**. Es handelt sich um eine C++-Unreal Engine-Plugin-Modulhülle.

## Messmethode

Es wurde `ScenePlugins/GameFeaturedClasses` nach `ThirdParty`, `LICENSE-` und Urheberrechtshinweisen durchsucht. Die Quellheader enthalten Fab Standard EULA-Hinweise. Kein vendordeter Drittanbieter-Verzeichnisbaum ist vorhanden.

## Optionale Integrationen

Zukünftige Adapter (z. B. LightweightDummyActorSystem, Unreal Capability Mesh, Project Intelligence Orchestrator, WarCollection) sind nur Teil der Zielarchitektur und werden von diesem Paket nicht weiterverteilt.

**Fab-Drittanbieter-Softwareerklärung:** keine.

## Verwandte Dokumente

- [README.md](README.md)
- [QUICKSTART.md](QUICKSTART.md)
- [FAQ.md](FAQ.md)

## Urheberrechtshinweise

Die Modulquellen enthalten Fab Standard EULA-Header. Im Paket existiert kein `ThirdParty`-Verzeichnis.

## Käufer-Deklarations-Checkliste

1. Fab-Drittanbieter-Software: **keine**.
2. Listen Sie Unreal Engine-Module nicht als plugin-gebundene Drittanbieter-Software auf.
3. Führen Sie nach jeder zukünftigen Einbindung von Drittanbieter-Code einen erneuten Scan durch, bevor Sie diese Erklärung ändern.

## Zusätzliche Hinweise

Dieser Abschnitt dient dazu, das Käuferdokument über der dokumentarischen Mindestlänge zu halten, während es sich an der oben beschriebenen Paketgrenze orientiert.

- Lesen Sie die Messmethode erneut durch, bevor Sie die Erklärung ändern.
- Erfinden Sie keine gebündelten Abhängigkeiten, die nicht auf der Festplatte vorhanden sind.
- Halten Sie optionale Integrationen als optional aufgeführt, niemals als Einrichtungsvoraussetzungen.
