<!-- doc-provenance: AKDB:plugins/SmartContentDiet/architecture.md; docs/architecture/plugins/SmartContentDiet/product-facts.yml; reconciled 2026-07-16 -->
# Fehlerbehebung

## Ich habe das Plugin aktiviert, sehe es aber nicht

Öffnen Sie **Tools → Content Tools → Smart Content Diet**. Wenn der Menüeintrag fehlt, bestätigen Sie unter *Bearbeiten → Plugins*, dass das Plugin aktiviert ist, und dass Sie den Editor neu gestartet haben.

## Ein erwarteter Tab (Preset / Governance / Redundanz) ist nicht sichtbar

Die Tab-Sichtbarkeit ist rollenbewusst. **Preset** und **Governance** erscheinen für **Ingenieur / Producer** (erweiterter Modus); **Redundanz** erscheint nur, wenn ein externer Ähnlichkeitsanbieter registriert ist. Ändern Sie Ihre Rolle/Erklärungstiefe in den **Einstellungen** oder der Zielgruppenauswahl im Header.

## Der Scan liefert wenig oder nichts zurück

**Quick Safe** nutzt nur den Registry/Metadaten-Pfad (kein Asset-Laden), daher benötigen einige Ergebnisse einen schwereren Durchgang. Schalten Sie die Header-Tiefe auf **Full** (lädt Assets) oder **Deep** (tiefe Material-/Mesh-Metriken) um und führen Sie den Scan erneut aus.

## „Zuerst Scan ausführen“ / leere Ergebnisse oder Optimieren

Ergebnisse und Optimierungsaktionen erfordern einen abgeschlossenen Scan. Führen Sie zuerst einen Scan über den Header aus und öffnen Sie dann **Ergebnisse** oder **Optimieren**.

## Anwendung ist blockiert oder bittet um Genehmigung

Verändernde Aktionen sind standardmäßig genehmigungsgeschützt und müssen in einem gesicherten, quellcodeverwalteten und wegwerfbaren Workspace ausgeführt werden. Bestätigen Sie Ihr Backup / Ihre Quellcodeverwaltung und genehmigen Sie dann die Aktion. Destruktive Korrekturen erfordern zusätzlich ein explizites Opt-in (`allow_destructive: true` auf der entsprechenden Route).

## Wo befinden sich die Anwendungsberichte?

```text
Saved/SmartContentDiet/OptimizationQueue/<timestamp>/
```

## Eine pluginübergreifende Route zeigt „verfügbar, aber Plugin nicht geladen“

Das ist zu erwarten und sicher: SCD setzt niemals zwingend ein Peer-Plugin voraus. Routen, die auf ein anderes Plugin verweist (z. B. eine IIS-Ähnlichkeitserfassung), werden als *verfügbar, aber Plugin nicht geladen* gemetdet, wenn dieser Peer fehlt, während jede reine SCD-Funktion verfügbar bleibt.
