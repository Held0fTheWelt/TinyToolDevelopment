<!-- doc-provenance: product-facts.yml reconciled 2026-07-15; source AKDB:plugins/AsyncSplineBuilder/architecture.md -->
# Einstellungsreferenz

Diese Referenz beschreibt die Einstellungen, die die meisten Benutzer bei der Konfiguration von `ASplineGeneratingActor` benötigen.

## Zuordnung im Workflow-Panel

Öffnen Sie **Tools > Track Tools > Async Spline Builder** für die aufgabenorientierte Benutzeroberfläche. Das Panel ist in die Registerkarten **Build**, **Segments** und **Terrain** unterteilt. Es deckt Actor-Auswahl, Mesh-Setup, Validierung, Build- und Rebuild-Befehle, asynchrones Batching, geschlossene Schleifen, Debug-Beschriftungen, Segment-Zeilen-Helfer, Sprunglücken, Stunt-Drops, Landschaftszuweisung, Layer-Paint-Einstellungen, Höhen-Deformation, Snapping-Schalter und Bodenwände auf Actor-Ebene ab.

Verwenden Sie diese Referenz, wenn eine Einstellung nur im Details-Panel verfügbar ist oder wenn Sie das exakte Feldverhalten benötigen. Zusatz-Mesh-Arrays pro Segment, detaillierte Bodenwand-Einstellungen, Trace-Objekt-Arrays, Kollisions-Flags, UV-Steuerungen und Data-Asset-Felder bleiben erweiterte Einstellungen des Details-Panels.

## Mesh-Setup

### StartMesh

Optionales Mesh, das für das erste generierte Straßenstück auf einer offenen Strecke verwendet wird. Wenn nicht gesetzt, wird das ausgewählte Segment-Straßen-Mesh verwendet.

### MainMesh

Erforderliches Fallback-Straßen-Mesh. Die Validierung blockiert die Generierung, wenn dieses Mesh fehlt.

### EndMesh

Optionales Mesh, das für das letzte generierte Straßenstück auf einer offenen Strecke verwendet wird. Wenn nicht gesetzt, wird das ausgewählte Segment-Straßen-Mesh verwendet.

## TrackTools

### bEditSpline

Wenn aktiviert, werden generierte Komponenten gelöscht und nur die Spline-/Debug-Bearbeitung bleibt während der Construction aktiv. Verwenden Sie dies beim Formen der Spline, ohne Meshes neu zu bauen.

### bShowSegmentNumbers / bShowPointNumbers

Erstellt Debug-Textkomponenten für Segment- oder Punktindizes. Diese werden getaggt und zusammen mit anderen generierten Komponenten bereinigt.

### bShowLayoutConnectorDebug

Boolean, Standard `false`. Das Kontrollkästchen **Show Connector Debug** im Bereich **Layout Connectors** des Panels steuert dieselbe Einstellung. Wenn aktiviert, zeigt der Editor eine Textmarkierung für jeden unabhängig auflösbaren Connector-Endpunkt an. Jede Beschriftung enthält den Connector-Index und die Art, die Rolle `From` oder `To`, die Layout-ID und die konfigurierte Distanz; ihre Größe folgt `DebugTextWorldSize`.

Fehlende Layouts und außerhalb des Bereichs liegende Distanzen werden übersprungen anstatt an einer falschen Position angezeigt zu werden. Das Umschalten oder Auffrischen von Connector-Beschriftungen ist rein visuell: Es baut die Strecke nicht neu, erstellt keine Connector-Straßengeometrie, ändert keine generierten Straßenanzahlen und erweitert nicht das Terrainverhalten. Das Deaktivieren der Einstellung entfernt nur Connector-Beschriftungen.

### bShowSplineVisualizationWidth / SplineVisualizationWidth

Steuert die Visualisierungsbreite der Editor-Spline.

### bSnapPointsToLandscape

Verschiebt Spline-Punkte auf Trace-Treffer. Erfordert `ObjectsToHitForLandscapeLineTrace`.

### bTangentPointsUpdate

Aktualisiert Tangenten nach dem Ausrichten der Punkte an der Landschaft.

### bMirrorExtraMesh

Spiegelt Zusatz-Meshes durch Umkehren ihrer X-Skalierung.

### SplinePointType

Der während Spline-Aktualisierungen angewendete Spline-Punkttyp. `CurveCustomTangent` ist ein guter Standardwert für Straßen.

### SplineZOffset

Wendet einen vertikalen Versatz auf die Spline-Komponente an.

### TrackSplineData

Daten pro Segment. Wenn für ein Segment kein Eintrag existiert, wird Eintrag `0` als Fallback verwendet.

### AdditionalLayouts

Optionale Routendatensätze für Boxengassen, Ausweichrouten, Servicestraßen und dekorative Splines. Die Legacy-Actor-Spline bleibt die Fassade des `Main`-Layouts.

### LayoutConnectors

Passive semantische Verbindungen zwischen zwei Layout-Distanzen. Jeder Connector speichert:

- `FromLayoutId` / `FromDistance`
- `ToLayoutId` / `ToDistance`
- `ConnectorKind`

Bekannte Arten sind `PitEntry`, `PitExit`, `Link` und `ServiceAccess`. `ConnectorKind` ist weiterhin ein offener `FName`; benutzerdefinierte nicht-leere Arten sind zulässig und werden als Warnung validiert. Leere Arten, fehlende Layouts, fehlerhafte Distanzen und nahe beieinander liegende Endpunkte auf demselben Layout sind Fehler im Connector-Bereich, die bei der Connector-Validierung gemeldet werden, aber Connector-Fehler blockieren keine Geometrie-Rebuilds.

Connector-Zeilen generieren keine Übergangs-Meshes, bauen nicht automatisch neu und ändern das Landschaftsdeformationsverhalten nicht.

## TrackSplineData

### RoadMesh

Optionales Straßen-Mesh für das Segment. Fällt auf `MainMesh` zurück.

### MeshInstances

Exakte Anzahl von Straßenstücken im Segment. Wenn größer als Null, überschreibt dies die automatische längenbasierte Anzahl.

### SegmentLength

Abstands-Fallback, wenn `RoadMeshLength` nicht gesetzt ist. Werte größer als `1` werden verwendet.

### RoadMeshLength

Explizite gewünschte Straßen-Mesh-Abdeckungslänge. Verwenden Sie dies, wenn die Mesh-Bounds nicht mit der visuellen Kachellänge übereinstimmen.

### ExtraMeshStart / ExtraMesh / ExtraMeshEnd

Optionale Arrays von Zusatz-Meshes für das erste, die mittleren und die letzten Stücke.

### ExtraMeshOffset

Seitlicher Versatz pro Zusatz-Mesh-Slot.

### GroundWallSettings

Wand-Generierungs-, Trace-, Breiten-, Kollisions- und UV-Einstellungen pro Segment.

## Options

### bClosedLoop

Verbindet den letzten Spline-Punkt zurück mit dem ersten.

### bEnableCollision

Aktiviert Kollision für generierte Straßen- und prozedurale Wandkomponenten.

### bCastShadow / bCastContactShadow

Steuert die Schatten-Flags generierter Spline-Meshes.

### bMirrorMesh

Spiegelt die Straßen-Mesh-Skalierung.

### bSnapMeshesToLandscape

Richtet Endpunkte von generierten Straßen- und Zusatz-Meshes an Trace-Treffern aus. Erfordert Trace-Objekttypen.

## Landscape

### Landscape

Landschafts-Proxy, der von der Editor-only Deformation verwendet wird.

### ActorsToIgnoreForGenerationTraces

Actors, die von Snap- und Wand-Traces ignoriert werden.

### bSnapTraceLandscapeOnly

Wenn wahr, akzeptieren Snap-Traces nur Landschaftstreffer.

### ObjectsToHitForLandscapeLineTrace

Objekttypen, die für Mesh- und Punkt-Snapping verwendet werden. Erforderlich, wenn Snapping aktiviert ist.

### FallOff

Distanz außerhalb der Straßenbreite, über die die Höhen-Deformation wieder in das bestehende Terrain übergeht.

### NumberOfSubdivisionsForDeform

Spline-Abtastauflösung für Landschaftsdeformation. Höhere Werte können die Passform verbessern, erhöhen aber die Kosten.

### bRaiseHeights / bLowerHeights

Steuert, ob die Deformation Landschafts-Samples anheben und/oder absenken kann.

### PaintHalfWidth

Halbe Breite mit vollem Gewicht für Layer-Painting (cm). `0` verwendet die halbe Straßenbreite bei jedem Deformation-Sample.

### PaintFallOff

Smoothstep-Falloff-Distanz für Layer-Painting (cm). Unabhängig vom Höhen-`FallOff`. `0` ergibt eine harte Kante ohne weiches Band außerhalb von `PaintHalfWidth`.

### PaintLayer

`ULandscapeLayerInfoObject`, das von `PaintLandscapeLayerNow` / Panel **Paint Layer** entlang der Straße gemalt wird. Muss auf der Ziel-Landschaft registriert sein. Wenn die Layer-Info `bNoWeightBlend` verwendet, kann der Ziel-Layer weiterhin Paint empfangen, aber es wird nicht garantiert, dass andere Material-Layer unter der Straße reduziert werden.

### LandscapeEditLayerName

Name der Edit-Ebene, die für Landschaftshöhenbearbeitungen verwendet wird, sofern von der Landschaftskonfiguration unterstützt.

### LineTraceLength

Trace-Tiefe für Landschafts-Snapping.

## Async Build

### bUseAsyncBuild

Aktiviert gebatchte Rebuilds.

### SegmentsPerTick

Anzahl asynchroner Arbeitseinheiten, die pro Tick verarbeitet werden. Eine Arbeitseinheit ist ein generiertes Straßen- oder Zusatz-Mesh-Stück, sodass ein langes Spline-Segment mit vielen Stücken über mehrere Ticks verteilt wird. Beginnen Sie niedrig für Reaktionsfähigkeit und erhöhen Sie nach dem Testen.

### bAutoRebuildOnConstruction

Plant Rebuilds nach Construction-Änderungen ein.

## Ground Walls

### bGenerateGroundWalls

Aktiviert die prozedurale Bodenwand-Generierung.

### GroundWallSubdivisions

Anzahl der Wand-Samples entlang der Spline. Höhere Werte erzeugen glattere Wände und mehr Geometrie.

### GroundWallOutset

Zusätzlicher horizontaler Versatz über die abgeleitete halbe Straßenbreite hinaus.

### GroundWallFallbackDepth

Tiefe, die verwendet wird, wenn ein Wand-Trace fehlschlägt.

### bGroundWallsDoubleSided

Fügt umgekehrte Dreiecke hinzu, sodass Wände von beiden Seiten gerendert werden.

### GroundWallObjectsToHitForLineTrace

Standard-Trace-Objekttypen für Bodenwände, wenn die Spurteinstellungen pro Segment leer sind.

## GroundWallSettings

### bGenerateGroundWalls

Wand-Aktivierung pro Segment.

### bGenerateBothSides

Wenn falsch, wird die linke Seite für dieses Segment unterdrückt.

### TrackHalfWidth

Manuelle Überschreibung der halben Breite. Lassen Sie `0`, um die Breite von den ausgewählten Straßen-Mesh-Bounds abzuleiten.

### MinWallHeight / MaxWallHeight

Überspringt winzige Wände und begrenzt sehr große Wände.

### bCreateCollision

Steuert die prozedurale Wandkollision, ebenfalls gesteuert durch den Actor `bEnableCollision`.

### TraceSettings

Trace-Objekttypen, Trace-Länge und Trace-Komplexität pro Segment.

### UVSettings

Wand-UV-Kachelung und Flips pro Segment.

## Drop Walls

### DropWallMaterial

Material, das auf generierte Drop-Wände angewendet wird.

### DropWallUVWorldUnitsU / DropWallUVWorldUnitsV

Welt-Einheiten-UV-Kachelung für Drop-Wände.

## Empfohlene Baseline

- `bUseAsyncBuild = true`
- `SegmentsPerTick = 24`
- `bAutoRebuildOnConstruction = true`
- `MainMesh` zugewiesen
- `RoadMeshLength = 0`, außer die Mesh-Bounds sind falsch
- `TrackHalfWidth = 0`, außer die Mesh-Bounds sind falsch
- Trace-Objekttypen für Bodenwände vor dem Aktivieren von Wänden konfiguriert
- Landschaftsdeformation manuell nach Stabilisierung der Straßenform ausgeführt
