<!-- doc-provenance: product-facts.yml reconciled 2026-07-15; source AKDB:plugins/AsyncSplineBuilder/architecture.md -->
# FAQ

## Wofür wird Async Spline Builder verwendet?

Es baut Spline-folgende Meshes wie Straßen, Rennstrecken, Schienen, Rohre, Barrieren und prozedurale Stützwände. Sein Hauptvorteil ist asynchrones Batching, sodass lange Splines ohne großen Editor-Stall neu gebaut werden können.

## Funktioniert es zur Laufzeit?

Ja. Straßen-Meshes, Zusatz-Meshes, Bodenwände, Drop-Wände und der asynchrone Laufzeit-Pump befinden sich im Laufzeit-Modul. Editor-only Landschaftshöhen-Deformation ist in paketierten Builds nicht verfügbar.

## Welche Mesh-Richtung sollte mein Straßen-Mesh verwenden?

Erstellen Sie wiederholbare Straßen-Meshes entlang der lokalen X-Achse. Der Builder verwendet Mesh-Bounds auf X für Längen-Fallback und Bounds auf Y für Breiten-Fallback.

## Kann ich unterschiedliche Meshes pro Segment verwenden?

Ja. Fügen Sie Einträge zu `TrackSplineData` hinzu und stellen Sie `RoadMesh`, `RoadMeshLength`, `SegmentLength`, `MeshInstances` und Zusatz-Mesh-Arrays pro Segment ein. Fehlende Segmentdaten fallen auf Eintrag `0` zurück.

## Wo konfiguriere ich das Plugin?

Verwenden Sie **Tools > Track Tools > Async Spline Builder** für den normalen Workflow. Es bietet Ihnen Actor-Auswahl, Mesh-Setup, Validierung, Build-Steuerung, asynchrone Einstellungen, Spline-Anzeige-Schalter, Segment-Helfer, Landschafts-Aktionen und Bodenwand-Aktivierung in einem Panel. Verwenden Sie das Details-Panel für erweiterte Arrays pro Segment und detaillierte Trace-, Wand-, Kollisions-, UV- und Data-Asset-Felder.

## Was ist der Unterschied zwischen BuildTrack und RebuildTrack?

`BuildTrack` ist synchron und sofort. `RebuildTrack` verwendet asynchrones Batching, wenn `bUseAsyncBuild` aktiviert ist.

## Verwendet die asynchrone Generierung Worker-Threads?

Nein. Es batcht die Arbeit über Ticks hinweg. Dies hält die Erstellung von Unreal-Komponenten auf dem Game-Thread, was der richtige Ort für die Registrierung von `UActorComponent`-Instanzen ist.

## Kann es Leitplanken oder Seiten-Meshes erstellen?

Ja. Verwenden Sie `ExtraMeshStart`, `ExtraMesh`, `ExtraMeshEnd` und `ExtraMeshOffset` in `FTrackSplineData`.

## Kann es Sprünge oder fehlende Straßenabschnitte erstellen?

Ja. Verwenden Sie `JumpGapsByPoints`. Lücken unterdrücken Straßen- und Zusatz-Meshes für Segmentbereiche.

## Kann es Höhendrops erstellen?

Ja. Verwenden Sie `StuntDropsByPoints`. Benachbarte Nicht-Lücken-Segmente auf unterschiedlichen Höhen erzeugen Drop-Wände.

## Kann es Wände bis zum Boden erstellen?

Ja. Aktivieren Sie `bGenerateGroundWalls` und konfigurieren Sie Trace-Objekttypen. Die prozeduralen Wandstreifen tracen von den Straßenkanten nach unten zu konfigurierten Objekttypen.

## Deformiert es Landschaften?

Ja, im Editor. Verwenden Sie `DeformLandscapeNow` für Höhe und `PaintLandscapeLayerNow` (oder Panel **Paint Layer**) für additives Gewichtsmalen, wenn `PaintLayer` zugewiesen ist.

## Malt es Landschafts-Layer?

Ja, für ein einzelnes globales `PaintLayer` unter Verwendung von additivem `max`-Malen. Stellen Sie `PaintLayer` am Actor ein, weisen Sie die Landschaft zu und führen Sie **Paint Layer** aus. Gewichtsgemischte Layer-Infos reduzieren andere Ebenen unter der Straße. `bNoWeightBlend`-Layer-Infos können die Ziel-Ebene malen, garantieren aber nicht, dass andere Ebenen reduziert werden. Nicht unterstützt: Ersetzungs-/Löschmodus, segmentweise Layer oder automatisches Löschen alter Gewichte beim Verkleinern des Malbands.

## Warum hat die Validierung meinen Build blockiert?

Der Actor blockiert Builds bei destruktiver Fehlkonfiguration, wie z. B. fehlendem `MainMesh` oder aktivierten trace-basierten Funktionen ohne Trace-Objekttypen. Dies schützt bestehende generierte Geometrie vor dem Löschen, bevor ein gültiger Ersatz erstellt werden kann.

## Warum fehlen meine Wände?

Häufige Ursachen sind fehlende Trace-Objekttypen, keine Trace-Treffer, zu hohe `MinWallHeight`, Sprunglücken, die den Streifen schneiden, oder deaktivierte `bGenerateGroundWalls` in den Einstellungen pro Segment.

## Bereinigt es generierte Komponenten sicher?

Ja. Generierte Komponenten erhalten stabile Tags und die Bereinigung scannt Tags, anstatt nur transienten Arrays zu vertrauen.

## Kann ich das Spline-Layout speichern?

Ja. Weisen Sie `SplinePointList` zu und verwenden Sie `WriteSplineToDataAsset` / `ReadSplineFromDataAsset`.

## Kann ich es für Fab-Produkte oder kommerzielle Spiele verwenden?

Ja, vorbehaltlich der Produktlizenz. Das Plugin gewährt keine Rechte an Drittanbieter-Meshes, Materialien oder Inhalten, die Sie damit verwenden.
