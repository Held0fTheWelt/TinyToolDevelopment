---
lang: de
title: GameFeaturedClasses Troubleshooting
audience: [end_user]
owner_ref: plugin:GameFeaturedClasses
applies_to:
  component: GameFeaturedClasses
symptom: Buyer expects a GameFeature workbench or featured classes that are not shipped in 1.0.1.
recovery:
  steps:
    - Confirm the plugin is enabled under Edit > Plugins and restart the editor
    - Re-read the matching troubleshooting entry and apply the documented fix
    - Re-run the quick start smoke check
version:
  since: "1.0"
---
# Fehlerbehebung

Format: Symptom → Ursache → Lösung.

## 0. Ich habe es aktiviert, aber es ist nichts passiert

**Symptom:** Nach dem Aktivieren von `GameFeaturedClasses` und dem Neustart gibt es kein Tiny-Tools-Menü, keine neuen Assets im Content Browser und keine Workbench-Benutzeroberfläche.  
**Ursache:** Die Version `1.0.1` liefert nur die Runtime-Modul-Shell. Featured Classes und Editor-Oberflächen sind noch nicht verfügbar.  
**Lösung:** Stellen Sie sicher, dass das Plugin unter **Bearbeiten → Plugins** aktiviert ist, und überprüfen Sie, ob das Modul `GameFeaturedClasses` geladen wird (siehe [QUICKSTART.md](QUICKSTART.md)). Erwarten Sie kein Produktmenü, bis ein späteres Paket es bereitstellt.

## 1. Suche nach einem fehlenden GameFeature Workbench-Menü

**Symptom:** Nach dem Aktivieren des Plugins erscheint kein Eintrag für Tiny Tools / Workbench.  
**Ursache:** Die Version 1.0.1 liefert nur die Runtime-Modul-Shell; Editor-Workbench-Oberflächen sind noch nicht verfügbar.  
**Lösung:** Verwenden Sie das Plugin ausschließlich als Modul-Grenze. Erwarten Sie keine Workbench-Benutzeroberfläche, bis ein späteres Paket diese explizit bereitstellt.

## 2. Keine Featured Classes im Content Browser

**Symptom:** Das Aktivieren des Plugins fügt keine Gameplay-Class-Assets hinzu.  
**Ursache:** Das Paket enthält keine Featured-Class- oder Feature-Set-Inhalte.  
**Lösung:** Behalten Sie Ihre Projekt-Klassen in Ihren eigenen Modulen; betrachten Sie das Ausliefern von Featured Classes als zukünftige Paketarbeit.

## 3. Plugin erscheint nicht unter Bearbeiten → Plugins

**Symptom:** Die Suche nach `GameFeaturedClasses` liefert keine Ergebnisse.  
**Ursache:** Das Plugin wurde nicht in den Projekt- oder Engine-Plugins-Ordner kopiert, oder der Descriptor wurde gefiltert.  
**Lösung:** Stellen Sie sicher, dass `GameFeaturedClasses.uplugin` im Projekt-`Plugins`-Baum (oder in den Engine-Plugins) vorhanden ist, und starten Sie den Editor neu.

## 4. Modul lädt auf einer nicht unterstützten Engine fehl

**Symptom:** Die Aktivierung in der Benutzeroberfläche gelingt, aber das Runtime-Modul schlägt beim Kompilieren/Laden fehl.  
**Ursache:** Die Engine-Version liegt außerhalb der verpackten Matrix 5.4–5.8 oder es liegt ein Binärdatei-Mismatch vor.  
**Lösung:** Verwenden Sie eine unterstützte Engine-Version, die mit dem Fab-Build übereinstimmt, oder erstellen Sie aus dem Quellcode auf dieser Engine neu.

## 5. Erwarten von `LightweightDummyActorSystem` oder PIO als feste Abhängigkeit

**Symptom:** Einrichtungsanleitungen anderer Produkte deuten darauf hin, dass GFC LDAS/UCM/PIO erfordert.  
**Ursache:** Diese Integrationen sind optionale Zielarchitekturen, keine Laufzeitanforderungen für die Shell.  
**Lösung:** Aktivieren Sie nur `GameFeaturedClasses` für den Shell-Smoke-Check. Fügen Sie Peers erst später hinzu, wenn eine ausgelieferte Integration vorhanden ist.

## 6. Wo ist die Online-Dokumentation?

**Symptom:** Der DocsURL im Fab-/Descriptor sollte zu einer Browserseite auflösen.  
**Ursache:** Online-Landingpages befinden sich außerhalb des Fab-Pakets.  
**Lösung:** Öffnen Sie `https://docs.tiny-tool-development.com/game-featured-classes/` (Descriptor `DocsURL`) oder verwenden Sie das im Paket enthaltene `Documentation/`-Set, das mit diesem Plugin ausgeliefert wird.

## Verwandte Dokumente

- [QUICKSTART.md](QUICKSTART.md)
- [UserManual.md](UserManual.md)
- [FAQ.md](FAQ.md)
- [SettingsReference.md](SettingsReference.md)
