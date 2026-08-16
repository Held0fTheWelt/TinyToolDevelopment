<!-- doc-provenance: product-facts.yml reconciled 2026-07-15; source AKDB:plugins/AsyncSplineBuilder/architecture.md -->
# Fehlerbehebung

## Der Actor baut nichts

Prüfen Sie:

- `MainMesh` ist zugewiesen.
- Die Spline hat mindestens zwei Punkte.
- Die Validierung hat den Build nicht blockiert.
- `bEditSpline` löscht nicht absichtlich generierte Komponenten.
- Die generierten Meshes werden nicht durch Level-Sichtbarkeit oder Actor-Sichtbarkeit verborgen.

## Build wird durch Validierung blockiert

Die Validierung blockiert destruktive schlechte Builds. Häufige Ursachen:

- `MainMesh` fehlt.
- Bodenwände sind aktiviert, aber es sind keine Bodenwand-Trace-Objekttypen konfiguriert.
- Landschafts-Snapping ist aktiviert, aber es sind keine Landschafts-Trace-Objekttypen konfiguriert.
- Sprunglücken- oder Drop-Bereiche sind ungültig.

Korrigieren Sie die Einstellung und führen Sie `RebuildTrack` erneut aus.

## Connector-Validierung meldet Probleme

Connector Validation Reports Issues tritt auf, wenn ein passiver Layout-Connector auf einen fehlenden Actor, eine unbekannte Layout-ID, eine ungültige Spline-Distanz oder unvollständige Connector-Metadaten zeigt.

Korrigieren Sie den Connector-Datensatz im Workflow-Panel oder Details-Panel und führen Sie `Validate Layout Connectors` erneut aus. Die Connector-Validierung ist getrennt von der Geometriegenerierung: Connector-Datensätze beschreiben die Routenabsicht und erstellen nicht von selbst Übergangs-Meshes.

## Eine Connector-Endpunkt-Beschriftung fehlt

Aktivieren Sie **Show Connector Debug** im Bereich **Layout Connectors** des Panels. Wenn nur eine Seite eines Connectors angezeigt wird, führen Sie **Validate Layout Connectors** aus und korrigieren Sie das fehlende Layout oder die Distanz außerhalb des Bereichs, die für den verborgenen Endpunkt gemeldet wird. Endpunkte werden unabhängig aufgelöst und ungültige Positionen werden absichtlich übersprungen.

Connector-Beschriftungen sind rein visuell. Sie müssen die Strecke nicht neu bauen, um sie zu erstellen oder aufzufrischen, und das Korrigieren einer Beschriftung fügt keine Connector-Straßengeometrie hinzu und ändert nicht das Landschaftsverhalten.

## Workflow-Panel öffnet sich nicht

Öffnen Sie es über **Tools > Track Tools > Async Spline Builder**. Wenn der Menüeintrag fehlt:

- Bauen Sie das Editor-Target neu
- Bestätigen Sie, dass das Modul `AsyncSplineBuilderEditor` aktiviert ist
- Starten Sie den Editor nach dem Aktivieren des Plugins neu
- Überprüfen Sie das Output Log auf Startfehler von `AsyncSplineBuilderEditor`

Das Panel ist Editor-only und in paketierten Builds nicht verfügbar.

## Der Editor friert während des Rebuilds ein

Verwenden Sie asynchrone Einstellungen:

- `bUseAsyncBuild = true`
- verringern Sie `SegmentsPerTick`
- deaktivieren Sie teure Wandkollisionen während der Iteration
- reduzieren Sie `GroundWallSubdivisions`

Sehr große Komponentenzahlen können weiterhin teuer sein, da die Registrierung von Unreal-Komponenten im Game-Thread erfolgt.

## Zusatz-Meshes erscheinen an der falschen Stelle

Prüfen Sie:

- Mesh-Pivot und lokale Achsen
- `ExtraMeshOffset`
- `bMirrorExtraMesh`
- Segmentdaten-Fallback auf Index `0`
- ob Start-/Mittel-/End-Arrays unterschiedliche Meshes enthalten

Zusatz-Meshes verwenden dasselbe Spline-Intervall wie das Straßenstück.

## Straßen-Meshes dehnen sich zu stark

Stellen Sie eines der folgenden Felder ein:

- `MeshInstances` für exakte Anzahl
- `RoadMeshLength` für explizite Stücklänge
- `SegmentLength` für automatische Anzahl basierend auf gewünschtem Abstand

Wenn alle nicht gesetzt sind, wird das X der Mesh-Bounds verwendet.

## Die geschlossene Schleife hat eine schlechte Nahtstelle

Prüfen Sie:

- Positionen/Tangenten des ersten und letzten Spline-Punkts
- Mesh-Pivot und Kachellänge
- Verwendung von `StartMesh` bei geschlossenen Schleifen
- Einstellungen zur Tangentenglättung

Geschlossene Schleifen bauen ein Wickelsegment auf die Splinelänge.

## Bodenwände erscheinen nicht

Prüfen Sie:

- `bGenerateGroundWalls` am Actor aktiviert
- `GroundWallSettings.bGenerateGroundWalls` pro Segment
- `GroundWallObjectsToHitForLineTrace`
- `TraceSettings.ObjectsToHit` pro Segment
- Trace-Länge
- `MinWallHeight`
- Sprunglücken

Wenn Traces fehlschlagen, wird die Fallback-Tiefe verwendet. Wenn die Wandhöhe immer noch unter `MinWallHeight` liegt, wird kein Abschnitt erstellt.

## Bodenwände überbrücken Lücken

Das sollten sie nicht. Wenn Sie dies sehen, bestätigen Sie, dass der Lückenbereich Segment-Semantik verwendet:

```text
[StartPointIndex, EndPointIndex)
```

Führen Sie auch die Automatisierungssuite aus; `GroundWallGapStripValid` deckt das grundlegende Verhalten der Streifentrennung ab.

## Bodenwandbreite ist falsch

Die Breite wird vom ausgewählten Straßen-Mesh auf Y abgeleitet, es sei denn, `TrackHalfWidth` ist größer als Null. Wenn die Mesh-Bounds nicht repräsentativ sind, stellen Sie `TrackHalfWidth` manuell ein.

## Drop-Wände erscheinen nicht

Prüfen Sie:

- beide benachbarten Segmente haben eine Straße
- die Grenze liegt nicht innerhalb einer Sprunglücke
- die angrenzenden Segmente lösen sich zu unterschiedlichen Welt-Z-Werten auf
- `DropHeight` oder konstantes Z ist auf einer Seite eingestellt

Führen Sie `AsyncSplineBuilder.DropWallCount` für das grundlegende Drop-Wand-Verhalten aus.

## Landschafts-Snapping tut nichts

Prüfen Sie:

- `bSnapMeshesToLandscape` oder `bSnapPointsToLandscape` ist aktiviert
- `ObjectsToHitForLandscapeLineTrace` enthält Objekttypen
- der Kollisionsobjekttyp der Landschaft entspricht der Abfrage
- `ActorsToIgnoreForGenerationTraces` enthält nicht das Ziel
- Trace-Länge erreicht die Oberfläche

## Landschaftsdeformation tut nichts

Prüfen Sie:

- `Landscape` ist zugewiesen
- Editor-Modul ist geladen
- Spline hat gültige Punkte
- `NumberOfSubdivisionsForDeform` ist größer als Null
- mindestens eines von `bRaiseHeights` oder `bLowerHeights` ist aktiviert
- die Straße überlappt den Landschaftsbereich

Denken Sie daran: Deformation ist eine manuelle Editor-Aktion über `DeformLandscapeNow`.

## Landschaftsmaterial-Ebene wird nicht gemalt

Höhen-Deformation (`DeformLandscapeNow`) und Layer-Gewichtsmalen (`PaintLandscapeLayerNow`) sind getrennte Aktionen. Layer-Paint erfordert ein gültiges `PaintLayer`, das auf der Landschaft registriert ist. Rückgängigmachen wird von der Deformationstransaktion verwaltet; testen Sie Undo im Panel, CallInEditor und mit einer aktiven Landschafts-Edit-Ebene.

Wenn die ausgewählte Layer-Info `bNoWeightBlend` verwendet, sollte die Operation warnen. In dieser Konfiguration kann die Ziel-Ebene Paint empfangen, aber das übliche Verhalten "andere Ebenen werden unter der Straße reduziert" ist nicht garantiert.

## Generierte Geometrie dupliziert sich nach Rebuild

Generierte Komponenten sind Tag-bereinigt. Wenn Duplikate erscheinen:

- überprüfen Sie, ob benutzerdefinierter Code Komponenten ohne `GeneratedTag` erzeugt
- prüfen Sie, ob eine veränderte Komponente manuell dupliziert wurde
- führen Sie die Automatisierung `CleanupRemovesAllTagged` aus

## Laufzeit-Async wird nicht fertig

Prüfen Sie:

- `bUseAsyncBuild = true`
- World Timer Manager tickt
- Actor ist gültig und nicht zerstört
- `SegmentsPerTick` ist mindestens `1`
- Validierung wurde vor dem Start nicht abgebrochen

Der Laufzeit-Pump reaktiviert sich selbst mit `SetTimerForNextTick` während des Baus.

## BuildPlugin oder Build schlägt mit Unity-Kollisionen fehl

Einige Module definieren ähnlich benannte Helfer in anonymen Namespaces. Wenn die Unity-Gruppierung diese Dateien kombiniert, kann MSVC doppelte Definitionen melden. Das betroffene Modul sollte Nicht-Unity-Build-Einstellungen wie `bUseUnity = false` verwenden.

## Automatisierung findet keine Tests

Prüfen Sie:

- Editor-Target wurde gebaut
- Development Automation Tests sind aktiviert
- Befehl verwendet `Automation RunTests AsyncSplineBuilder`
- Tests sind im Editor-Modul kompiliert

## Logs sind zu laut

Suchen Sie im Log nach:

```text
AsyncSplineBuilder
Result={Fail}
Result={Success}
TEST COMPLETE
```
