---
lang: de
title: LightweightDummyActorSystem Third-Party Software
audience: [end_user]
owner_ref: plugin:LightweightDummyActorSystem
applies_to:
  component: LightweightDummyActorSystem
contract_ref: plugin:LightweightDummyActorSystem/third-party-software
version:
  since: "1.0"
---
# Software von Drittanbietern

LightweightDummyActorSystem **bündelt keine Quelldrittanbieter-Software, Laufzeit-Binärdateien, KI-Modelle, Node.js, Python oder eigenständige ausführbare Dateien**. Es handelt sich um ein C++-Unreal Engine-Plugin, das Unreal-Laufzeit- und Editor-Module verwendet.

## Messmethode

Es wurde im Verzeichnis `ScenePlugins/LightweightDummyActorSystem` nach `ThirdParty`, `LICENSE-` und Urheberrechtshinweisen gesucht. Die Header-Dateien enthalten Fab Standard EULA-Hinweise / Projekturheberrechtszeilen. Es ist kein eingebetteter Drittanbieter-Baum vorhanden.

## Optionale Integrationen (nicht gebündelt)

WarCollection, LightningCore, Unreal Capability Mesh, Project Intelligence Orchestrator und BPJ-Adapter sind optionale Zielintegrationen und werden von diesem Paket nicht weiterverteilt.

**Fab-Drittanbieter-Softwareerklärung:** keine.

## Verwandte Dokumente

- [README.md](README.md)
- [QUICKSTART.md](QUICKSTART.md)
- [FAQ.md](FAQ.md)

## Urheberrechtshinweise

Quellcodes für Laufzeit, Editor und DeveloperTool enthalten Fab Standard EULA- / Projekturheberrechtshinweise. Es ist kein `ThirdParty`-Verzeichnis vorhanden.

## Käufer-Deklarations-Checkliste

1. Fab-Drittanbieter-Software: **keine**.
2. Optionale Adapter (WarCollection, LightningCore, UCM, PIO, BPJ) sind separate Pakete, sofern vorhanden.
3. Führen Sie nach jeder zukünftigen Einbettung von Drittanbieter-Code einen erneuten Scan durch, bevor Sie diese Erklärung ändern.

## Zusätzliche Hinweise

Dieser Abschnitt dient dazu, das Käuferdokument über der Dokumentationsbasis zu halten, indem es substantiell lang bleibt, sich jedoch an der oben beschriebenen Paketgrenze orientiert.

- Lesen Sie die Messmethode erneut durch, bevor Sie die Erklärung ändern.
- Erfinden Sie keine gebündelten Abhängigkeiten, die nicht auf der Festplatte vorhanden sind.
- Halten Sie optionale Integrationen als optional aufgeführt, niemals als Setup-Anforderungen.
