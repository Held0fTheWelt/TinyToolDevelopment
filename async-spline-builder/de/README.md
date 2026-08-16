<!-- doc-provenance: product-facts.yml reconciled 2026-07-15; source AKDB:plugins/AsyncSplineBuilder/architecture.md -->
# Async Spline Builder Dokumentation

Async Spline Builder generiert Straßen-, Rennstrecken-, Rohr-, Schienen-, Wand- und Nebenobjekt-Spline-Meshes, ohne große Editor-Stalls zu verursachen. Es unterstützt synchrone Builds, asynchrones Batching im Editor, asynchrones Batching zur Laufzeit, Mesh-Pläne pro Segment, optionale Bodenwände, Stunt-Lücken, Drop-Wände, Spline-Punkt-Data-Assets sowie editor-only Landschaftshöhen-Deformation plus additives Layer-Paint.

Dieser Ordner enthält die mit dem Plugin gelieferte Dokumentation.

## Erste Schritte

- [BUYER_GUIDE.md](BUYER_GUIDE.md): Überblick auf Produktebene, Workflows, Stärken und Einschränkungen.
- [UserManual.md](UserManual.md): vollständiger Editor-Workflow von der ersten Actor-Platzierung bis zu Rebuilds.
- [FAQ.md](FAQ.md): Fab-bereite Fragen und Antworten.

## Referenz

- [SettingsReference.md](SettingsReference.md): jede wichtige Actor-Einstellung und empfohlene Baseline.
- [LandscapeAndWalls.md](LandscapeAndWalls.md): Snapping, Höhen-Deformation, Bodenwände, Lücken und Drop-Wände.
- [TechnicalOverview.md](TechnicalOverview.md): Architektur und Build-Flow auf Betreuer-Ebene.
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md): häufige Setup-, Build-, Trace- und Geometrie-Probleme.

Nur für Betreuer bestimmte Audits, Fertigstellungsnotizen, Automatisierungsbefehle, Legacy-Notizen und Release-Checklisten können im Quell-Repository existieren, werden aber aus dem Käuferpaket ausgeschlossen.

## Schneller Workflow

1. Aktivieren Sie das Plugin und starten Sie den Editor neu, falls erforderlich.
2. Öffnen Sie **Tools > Track Tools > Async Spline Builder**.
3. Platzieren oder wählen Sie einen `ASplineGeneratingActor` im Workflow-Panel.
4. Weisen Sie `MainMesh` im Setup-Bereich des Panels zu.
5. Bearbeiten Sie die `TrackSpline`-Punkte im Viewport.
6. Verwenden Sie **Build Now** für einen sofortigen Build oder **Rebuild** für asynchrones Batching.
7. Nutzen Sie die Segment-Helfer, um Zeilen pro Segment zu erstellen, bevor Sie erweiterte Bearbeitungen pro Segment vornehmen.
8. Optional: Aktivieren Sie Bodenwände und konfigurieren Sie Trace-Objekttypen im Details-Panel.
9. Optional: Weisen Sie eine Landschaft zu, führen Sie **Deform Height** aus und anschließend **Paint Layer** (erfordert `PaintLayer` am Actor) für additives Gewichtsmalen.

## Hauptfunktionen

- Straßen- oder Strecken-Mesh-Generierung entlang einer Spline.
- Track Shape Editor für natives Erstellen von Routen-/Layout-Punkten mit Designer-Steuerungen für Layouts, Anker und Segmente.
- Validate Layout Connectors zur Überprüfung passiver `PitEntry`-, `PitExit`-, `Link`-, `ServiceAccess`- oder benutzerdefinierter Connector-Metadaten vor dem Vertrauen auf Routenbeziehungen.
- Apply Layout Connector zum Hinzufügen oder Aktualisieren passiver Layout-Beziehungsdatensätze ohne Erstellung versteckter Mesh-Zweige.
- Asynchrone Editor-Rebuilds mit `SegmentsPerTick`.
- Asynchrone Laufzeit-Rebuilds über einen Next-Tick-Timer-Pump.
- Mesh-Auswahl pro Segment und Mesh-Längenplanung.
- Start-, Mittel- und End-Zusatz-Meshes für Leitplanken, Barrieren, Zäune, Rohre oder Detail-Meshes.
- Stunt-Lücken, die Straßen- und Seiten-Meshes unterdrücken.
- Drop-Regionen und prozedurale Drop-Wände zwischen Höhenstufen.
- Prozedurale Bodenwände, die bis zum Terrain oder anderen konfigurierten Objekttypen nach unten tracen.
- Tag-basierte Bereinigung generierter Komponenten, die veraltete Arrays und Construction-Rebuilds übersteht.
- Speichern/Laden von Spline-Punkten über `USplinePointListAsset`.
- Editor-only Landschaftshöhen-Deformation plus additives globales Layer-Paint.
- Automatisierungstests für die risikoreichsten Verhaltensweisen.

## Unterstützte Laufzeit-Position

Das Laufzeit-Modul enthält den Actor, die Spline-Mesh-Generierung, Bodenwand-Generierung, Drop-Wand-Generierung, Data-Asset-Zugriff und den Laufzeit-Async-Pump.

Das Editor-Modul enthält das Workflow-Panel, Editor-only Landschaftsdeformation und Layer-Paint sowie Editor-Auswahlhelfer. Paketierte Spiele können die Spline-Meshes und prozeduralen Wände bauen, aber Landschaftshöhen-/Gewichtsbearbeitungen und das Workflow-Panel sind Editor-only.

## Editor-Workflow-Panel

Die primäre Editor-Oberfläche ist **Tools > Track Tools > Async Spline Builder**. Sie gruppiert den gewöhnlichen Workflow in die Registerkarten **Build**, **Segments** und **Terrain**, damit alltägliche Aufgaben kompakt bleiben, ohne den Validierungsstatus zu verbergen.

Verwenden Sie den Track Shape Editor, wenn eine Route native Punkt-/Layout-Erstellung benötigt, und nutzen Sie Layout-Connector-Steuerungen, wenn Boxengassen, Servicezugänge oder alternative Routen explizite Beziehungsmetadaten benötigen.

Verwenden Sie das Panel für die tägliche Arbeit. Verwenden Sie das Unreal-Details-Panel für erweiterte Rohfelder wie Zusatz-Mesh-Arrays pro Segment, detaillierte Wand-UV-Einstellungen, Trace-Objekt-Arrays, benutzerdefinierte Kollisionseinstellungen und experimentelle Felder.

## Wichtige Einschränkungen

- Landschaft: Höhen-Deformation plus **additives globales** Layer-Gewichtsmalen, wenn `PaintLayer` gesetzt ist (`PaintLandscapeLayerNow` oder Panel **Paint Layer**). Der Ersetzungs-/Lösch-Malmodus ist nicht implementiert.
- Landschaftsdeformation ist eine einmalige Editor-Operation und kein automatischer Bestandteil jedes Strecken-Rebuilds.
- Komplexe Produktionslandschaften benötigen weiterhin manuelles QS, insbesondere bei engen Kurven, sehr steilem Gelände und gemischten Wand-Einstellungen pro Segment.
- Die asynchrone Laufzeit-Automatisierung wird durch einen deterministischen Test-Hook abgedeckt; ein vollständiger PIE-Timer-World-Integrationslauf wird weiterhin für Release-Maps empfohlen.

## Validierung

Für einen lokalen Paket-Validierungslauf bauen Sie das Editor-Target für Ihr Projekt und führen Sie die AsyncSplineBuilder-Automatisierungsgruppe in Unreals Automation-Tools aus. Halten Sie betreuer-spezifische Befehlspfade in lokalen Release-Notizen anstatt im ausgelieferten Käuferpaket.

## Empfohlener erster Durchlauf in der Produktion

Verwenden Sie zuerst eine kurze offene Test-Spline, dann eine geschlossene Schleife und schließlich die reale Strecke. Lassen Sie `bUseAsyncBuild` aktiviert, beginnen Sie mit `SegmentsPerTick = 2` und erhöhen Sie dies erst nach Bestätigung der Editor-Reaktionsfähigkeit. Konfigurieren Sie Trace-Objekttypen vor dem Aktivieren von Snapping oder Bodenwänden, da die Validierung beabsichtigt Builds blockiert, die andernfalls alte Geometrie zerstören und keinen gültigen Ersatz erzeugen würden.

## Rechtlicher Hinweis

Async Spline Builder wird unter den in der Produktverteilung enthaltenen Lizenzbedingungen bereitgestellt. Das Plugin gewährt keine Rechte an Drittanbieter-Meshes, Materialien, Landschaften oder Inhalten, die mit generierten Strecken verwendet werden.
