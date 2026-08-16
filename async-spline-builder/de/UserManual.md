<!-- doc-provenance: product-facts.yml reconciled 2026-07-15; source AKDB:plugins/AsyncSplineBuilder/architecture.md -->
# Benutzerhandbuch

Dieses Handbuch erklärt, wie Sie Async Spline Builder im Unreal Editor verwenden und wie die Hauptfunktionen zusammenwirken.

## Zweck

Async Spline Builder erstellt generierte Komponenten aus einer bearbeitbaren Spline. Die typische Ausgabe ist eine Straße oder Strecke aus `USplineMeshComponent`-Abschnitten mit optionalen zusätzlichen Spline-Meshes und prozeduralen Wand-Meshes.

Der Actor kann synchron oder in Batches neu bauen. Batching hält den Editor bei langen Strecken reaktionsfähig und ist auch zur Laufzeit über einen Next-Tick-Timer-Pump verfügbar.

## Öffnen und Aktivieren

1. Öffnen Sie **Edit > Plugins**.
2. Aktivieren Sie **AsyncSplineBuilder**.
3. Starten Sie den Editor neu, falls Sie dazu aufgefordert werden.
4. Öffnen oder erstellen Sie ein Level.
5. Öffnen Sie **Tools > Track Tools > Async Spline Builder**.

Das Plugin enthält sowohl Laufzeit- als auch Editor-Module. Der Actor ist laufzeitfähig; das Workflow-Panel und die Landschaftsdeformations-Tools sind Editor-only.

## Workflow-Panel

Das Async Spline Builder Panel ist die empfohlene Methode zur Konfiguration normaler Strecken. Es verhindert das Verstreuen des gewöhnlichen Workflows über mehrere Details-Kategorien.

Das Panel ist in Registerkarten organisiert:

- **Build**: Actor-Auswahl, Mesh-Setup, Validate/Build/Rebuild/Cancel, asynchrones Batching, geschlossene Schleife, Debug-Punkt- oder Segment-Beschriftungen und optionale Layout-Connector-Endpunkt-Beschriftungen.
- **Segments**: `TrackSplineData` pro Segment, Erstellung von Segmentzeilen, Sprunglücken und Stunt-Drops.
- **Terrain**: Ausrichtung an Landschaft, Landschaftszuweisung, Layer-Paint-Einstellungen, Höhen-Deformation, additives Layer-Paint und Bodenwände.

Verwenden Sie das Details-Panel für erweiterte Arrays und seltene Einstellungen, die im Workflow-Panel absichtlich nicht dupliziert werden.

## Grundlegendes Actor-Setup

1. Drücken Sie im Workflow-Panel auf **Create Actor** oder wählen Sie einen vorhandenen `ASplineGeneratingActor` aus und drücken Sie **Use Selection**.
2. Weisen Sie unter **Setup** `MainMesh` zu.
3. Weisen Sie optional `StartMesh` und `EndMesh` zu.
4. Verschieben Sie Spline-Punkte im Viewport.
5. Drücken Sie **Validate**.
6. Drücken Sie **Build Now** oder **Rebuild**.

`MainMesh` ist erforderlich. Die Validierung blockiert Builds ohne dieses Mesh, damit vorhandene generierte Geometrie nicht gelöscht und durch nichts ersetzt wird.

## Erwartungen an das Mesh-Authoring

Straßen-Meshes sollten:

- Entlang der lokalen X-Achse kacheln.
- Eine sinnvolle Y-Ausdehnung haben, da Mesh-Bounds verwendet werden, um die halbe Straßenbreite abzuleiten.
- Konsistente Pivots verwenden.
- Versteckte Kollisionskomplexität vermeiden, es sei denn, Kollision wird benötigt.

Wenn die Mesh-Bounds nicht repräsentativ sind, stellen Sie `GroundWallSettings.TrackHalfWidth` manuell ein.

## Bearbeiten der Spline

Verwenden Sie die Standard-Spline-Bearbeitungstools von Unreal. Nützliche Felder:

- `bClosedLoop`: Verbindet den letzten Punkt mit dem ersten Punkt.
- `SplinePointType`: Steuert das Punktinterpolationsverhalten.
- `SplineZOffset`: Versetzt die Spline-Komponente vertikal.
- `bShowPointNumbers`: Zeigt Punktindizes an.
- `bShowSegmentNumbers`: Zeigt Segmentindizes an.
- `bShowSplineVisualizationWidth`: Zeigt eine breitere Editor-Spline an.

Punkt- und Segmentnummern sind generierte Debug-Komponenten und werden durch dasselbe Tag-System bereinigt, das für generierte Geometrie verwendet wird.

## Track Shape Editor

Öffnen Sie **Tools > Track Tools > Track Shape Editor**, wenn Sie eine kompakte Multi-Layout-Erstellungsoberfläche benötigen, anstatt nur die Roh-Spline-Punkte des Actors zu bearbeiten. Der Editor arbeitet auf einem nativen `track_shape.v1`-Dokument und kann kompilierte Haupt-, Boxengassen-, Alternativ- oder Service-Straßen-Layouts auf den ausgewählten `ASplineGeneratingActor` anwenden.

Der Bereich **Designer Tools** bietet die alltäglichen Bearbeitungssteuerungen:

- Boxengassen-, Alternativ- oder Service-Straßen-Layouts hinzufügen
- Das ausgewählte Nicht-Haupt-Layout duplizieren oder löschen
- Layout-Art und den Zustand der geschlossenen Schleife ändern
- Vorheriges oder nächstes Layout, Anker oder Segment auswählen
- X/Y-Koordinaten des ausgewählten Ankers bearbeiten
- Anker hinzufügen, einfügen oder löschen, während eine gültige Mindestanzahl an Ankern erhalten bleibt
- Explizite Segmente hinzufügen oder löschen, ausgewählte Segmente zwischen Linie und Bezier umschalten oder sequenzielle Segmente für das ausgewählte Layout neu bauen

Der Viewport unterstützt die direkte Anker-Auswahl und das Ziehen. Die Layout-Liste und der Inspektor spiegeln dieselbe Auswahl wider, und der JSON-Bereich kann weiterhin das zugrunde liegende Dokument zur Überprüfung oder Quellcodeverwaltung importieren oder exportieren.

Verwenden Sie **Validate** vor der Anwendung komplexer Bearbeitungen. Verwenden Sie **Apply** erst nach Auswahl oder Erstellung des Ziel-Actors, da das Anwenden den editierbaren Spline-/Layout-Zustand des Actors verändert.

## Bauen

Verwenden Sie:

- **Build Now** / `BuildTrack`: synchroner vollständiger Build.
- **Rebuild** / `RebuildTrack`: asynchron, wenn `bUseAsyncBuild` wahr ist, andernfalls synchron.
- **Cancel** / `CancelAsyncBuild`: bricht einen aktiven oder ausstehenden asynchronen Build ab.

Der Actor baut auf Basis eines berechneten `FTrackBuildPlan` neu auf. Der Plan entscheidet über Segmentbereiche, Stückzahlen, Drop-Status, Sprunglücken, ausgewähltes Straßen-Mesh und Zusatz-Mesh-Anzahl, bevor die Generierung beginnt.

## Asynchroner Build

Einstellungen:

- `bUseAsyncBuild`: Aktiviert Batch-Building.
- `SegmentsPerTick`: Anzahl generierter Straßen-/Zusatz-Mesh-Stücke, die pro Tick verarbeitet werden.
- `bAutoRebuildOnConstruction`: Plant Rebuilds ein, wenn Construction-Änderungen auftreten.

Editor-Welten entprellen Construction-Änderungen vor dem Löschen oder Vorbereiten generierter Komponenten, wodurch vorhandene Spline-Geometrie bearbeitbar bleibt, während Sie Punkte ziehen. Laufzeit-Welten verwenden einen Next-Tick-Timer-Pump. Beide Pfade rufen denselben Builder auf Stückebene auf, sodass das Verhalten ausgerichtet bleibt, ohne dass ein langes Spline-Segment einen Frame monopolisiert.

## Daten pro Segment

`TrackSplineData` konfiguriert jedes Segment. Wenn weniger Einträge als Spline-Segmente vorhanden sind, wird Index `0` als Fallback verwendet.

Wichtige Felder:

- `RoadMesh`: optionales segment-spezifisches Straßen-Mesh.
- `MeshInstances`: exakte Anzahl von Mesh-Stücken für das Segment.
- `RoadMeshLength`: gewünschte Straßenstücklänge.
- `SegmentLength`: Fallback-Abstand, wenn `RoadMeshLength` nicht gesetzt ist.
- `ExtraMeshStart`, `ExtraMesh`, `ExtraMeshEnd`: zusätzliche Spline-Meshes.
- `ExtraMeshOffset`: seitliche Versätze für Zusatz-Mesh-Slots.
- `GroundWallSettings`: Bodenwand-Verhalten pro Segment.

## Zusatz-Meshes

Zusatz-Meshes folgen demselben Spline-Stückintervall wie das Straßenstück. Sie sind nützlich für Leitplanken, Bordsteine, Zäune und dekorative Seitenobjekte.

Start-, Mittel- und End-Arrays ermöglichen unterschiedliche Meshes an Segmentgrenzen. Zusatz-Meshes sind mit `AsyncSplineBuilder.ExtraMesh` getaggt, nicht mit `AsyncSplineBuilder.RoadMesh`.

## Lücken

Fügen Sie Einträge zu `JumpGapsByPoints` hinzu, um die Generierung von Straßen- und Zusatz-Meshes für Punktindex-Bereiche zu unterdrücken.

Bereiche sind Segmentbereiche:

```text
[StartPointIndex, EndPointIndex)
```

Beispiel: `StartPointIndex = 2`, `EndPointIndex = 4` unterdrückt die Segmente `2` und `3`.

## Drops

Fügen Sie Einträge zu `StuntDropsByPoints` hinzu, um Segmentbereiche nach unten oder auf ein konstantes Welt-Z zu verschieben.

Felder:

- `DropHeight`: relativer Z-Versatz. Negative Werte bewegen die Straße nach unten.
- `bUseConstantGapHeight`: verwendet absolutes Welt-Z anstelle des Versatzes.
- `ConstantGapWorldZ`: absolute Höhe, wenn aktiviert.

Wenn zwei benachbarte Nicht-Lücken-Segmente auf unterschiedlichen Höhen aufeinandertreffen, erzeugt der Actor eine Drop-Wand zwischen ihnen.

## Bodenwände

Aktivieren Sie `bGenerateGroundWalls`, um prozedurale Wandstreifen von der Straßenkante nach unten zu generieren.

Bodenwände:

- Verwenden vom Mesh abgeleitete oder überschriebene Straßenbreiten.
- Beachten Wand-Einstellungen pro Segment.
- Teilen Streifen an Sprunglücken und ungültigen Samples.
- Können einseitig oder zweiseitig sein.
- Verwenden UVs basierend auf Distanz und realer Wandhöhe.

Siehe [LandscapeAndWalls.md](LandscapeAndWalls.md) für detailliertes Setup.

## Ausrichtung an Landschaft

Mesh-Snapping:

- `bSnapMeshesToLandscape`
- `ObjectsToHitForLandscapeLineTrace`
- `LineTraceLength`

Punkt-Snapping:

- `bSnapPointsToLandscape`
- `bTangentPointsUpdate`

Verwenden Sie `ActorsToIgnoreForGenerationTraces`, um Hilfs-Meshes oder temporäre Objekte von Trace-Abfragen auszuschließen.

## Landschaftsdeformation

Editor-only Deformation wird mit `DeformLandscapeNow` ausgeführt.

Anforderungen:

- `Landscape` zugewiesen.
- Eine gültige Spline.
- Sinnvolle Werte für `FallOff` und `NumberOfSubdivisionsForDeform`.
- `bRaiseHeights` und/oder `bLowerHeights` aktiviert.

Höhe: `DeformLandscapeNow` oder Panel **Deform Height**. Layer-Paint: Weisen Sie `PaintLayer` zu, stellen Sie `PaintHalfWidth` / `PaintFallOff` im Panel ein, dann `PaintLandscapeLayerNow` oder Panel **Paint Layer**. Paint ist additiv; es löscht keine vorherigen breiteren Bänder, wenn Sie den Falloff verkleinern. `PaintFallOff = 0` erzeugt eine harte Kante. Wenn die ausgewählte Layer-Info `bNoWeightBlend` verwendet, warnt das Panel/die Validierung, dass andere Landschafts-Layer unter der Straße nicht garantiert reduziert werden.

## Wann das Details-Panel zu verwenden ist

Das Workflow-Panel ist absichtlich fokussiert. Verwenden Sie das Details-Panel, wenn Sie folgendes bearbeiten müssen:

- Arrays für `ExtraMeshStart`, `ExtraMesh`, `ExtraMeshEnd` und `ExtraMeshOffset` pro Segment
- Detaillierte `FGroundWallSettings`, einschließlich Trace-, UV-, Material-, Kollisions- und Breite-Überschreibungen
- Trace-Objekt-Arrays für Landschafts-Snapping und Wand-Generierung
- Lese-/Schreibfelder für Spline-Punkt-Data-Assets
- Erweiterte Debug- und Construction-Einstellungen

## Layout Connectors

Die Registerkarte Build enthält einen Bereich **Layout Connectors** für passive Routen-Metadaten. Ein Connector verbindet ein Quell-Layout/eine Quell-Distanz mit einem Ziel-Layout/einer Ziel-Distanz und speichert eine semantische Art wie `PitEntry`, `PitExit`, `Link` oder `ServiceAccess`. Sie können auch eine benutzerdefinierte Art eingeben; benutzerdefinierte nicht-leere Arten werden als Warnungen statt als Fehler validiert.

Verwenden Sie **Pit Entry**, um einen Standard-Connector von `Main` zum ersten Boxengassen-Layout hinzuzufügen. Verwenden Sie **Pit Exit**, um einen Standard-Connector vom ersten Boxengassen-Layout zurück zu `Main` hinzuzufügen. **Validate** in diesem Bereich führt eine Connector-only-Validierung aus.

Connector-Bearbeitungen bauen die Straße nicht neu und löschen keine generierte Geometrie. Sie erstellen auch keine automatischen Übergangs-Meshes, schneiden keine Splines, erweitern keine Terrain-Deformation auf Boxengassen oder aktivieren einen speziellen Boxengassen-Renderer.

Aktivieren Sie **Show Connector Debug**, um visuelle Textmarkierungen an gültigen Connector-Endpunkten zu platzieren. Eine Markierung identifiziert den Connector-Index und die Art, ob es der `From`- oder `To`-Endpunkt ist, seine Layout-ID und seine Distanz. Jeder Endpunkt wird unabhängig aufgelöst, sodass ein gültiger Endpunkt sichtbar bleiben kann, wenn der andere ungültig ist. Fehlende Layouts und Distanzen außerhalb des Bereichs einer Spline werden übersprungen; verwenden Sie **Validate**, um diese Connector-Probleme zu untersuchen.

Die Markierungen verwenden `UTextRenderComponent`-Debug-Ausgaben und fügen keine Straßen-, Zusatz-Mesh-, Bodenwand- oder Drop-Wand-Geometrie hinzu. Das Bearbeiten von Connectors frischt die Markierungen auf, während das Kontrollkästchen aktiviert ist. Deaktivieren Sie **Show Connector Debug**, um nur die Connector-Beschriftungen zu entfernen. Das Umschalten oder Auffrischen dieser Beschriftungen baut die Strecke nicht neu, ändert keine Straßenkomponentenanzahl, erweitert nicht das Terrainverhalten und beeinflusst nicht das Build-Validierungstor.

## Data-Asset-Workflow

Weisen Sie ein `USplinePointListAsset` zu `SplinePointList` zu.

Verwenden Sie:

- `WriteSplineToDataAsset`: speichert aktuelle Spline-Punkte.
- `ReadSplineFromDataAsset`: lädt Spline-Punkte.

Dies ist nützlich, um Strecken-Layouts getrennt von generierten Komponenten zu bewahren.

## Empfohlener Produktions-Workflow

1. Bauen Sie eine kurze Test-Spline.
2. Validieren Sie Straßen-Mesh-Bounds und Kachelung.
3. Fügen Sie Segmentdaten hinzu.
4. Fügen Sie Zusatz-Meshes hinzu.
5. Fügen Sie Lücken und Drops hinzu.
6. Konfigurieren Sie das Tracing von Bodenwänden.
7. Führen Sie Landschaftsdeformation erst aus, wenn die Straßenform stabil ist.
8. Führen Sie vor dem Release Automatisierungstests aus.
9. Testen Sie das Level im PIE und im paketierten Runtime.

## Was das Plugin nicht tut

- Es bietet keine Ersetzungs-/Lösch- oder segmentweisen Landschafts-Paint-Modi.
- Es verfasst keine Meshes für Sie.
- Es garantiert keine perfekten Terrain-Schultern auf jeder Landschaft.
- Es generiert keine Connector-Übergangs-Straßen-Meshes automatisch.
- Es ersetzt nicht die manuelle künstlerische Regie für den finalen Feinschliff der Strecke.
