<!-- doc-provenance: AKDB:plugins/ProceduralGeneratedStructures/architecture.md; docs/architecture/plugins/ProceduralGeneratedStructures/product-facts.yml; reconciled 2026-06-21 -->
# Schnellstartanleitung

Diese Anleitung führt Sie von der Installation zu einem **sichtbaren Ergebnis**: einem `AAsyncProceduralGeneratedActor`, der instanziierte Mesh-Strukturen aus einem Data Asset neu baut. Das Plugin funktioniert eigenständig — es ist kein anderes Plugin erforderlich.

## Was Sie nach dieser Anleitung haben werden

Einen Actor in Ihrem Level, dessen instanziierte Static-Mesh-Instanzen in einem Data Asset erfasst und daraus neu gebaut werden, sodass die Struktur wiederverwendbar und regenerierbar ist.

## Anforderungen

- Unreal Engine 5 Editor und ein geöffnetes Level.
- Ein `UStaticMesh` aus Ihrem Projekt zum Instanziieren (z. B. ein Wand- oder Säulen-Mesh).
- Keine Software von Drittanbietern, Konten oder Laufzeiten. Siehe [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## 1. Installieren und aktivieren

1. Fügen Sie **ProceduralGeneratedStructures** aus Ihrer Fab-Bibliothek zum Projekt hinzu (oder installieren Sie es in der Engine).
2. Öffnen Sie **Edit → Plugins**, aktivieren Sie **ProceduralGeneratedStructures** und starten Sie nach Aufforderung neu.

## 2. Actor platzieren (Erstes Ergebnis)

1. Suchen Sie im Panel **Place Actors** nach **Async Procedural Generated Actor** und ziehen Sie ihn in das Level (oder fügen Sie `AAsyncProceduralGeneratedActor` aus der Klassenliste hinzu).
2. Fügen Sie dem Actor ein oder mehrere **Instanced Static Mesh Component**-Unterelemente hinzu und geben Sie jedem einen **stabilen Komponentennamen** (z. B. `Walls`). Weisen Sie Ihr Static Mesh zu und platzieren Sie einige Instanzen.

## 3. Ein reales Beispiel: Erfassen und Neu bauen

1. Erstellen Sie ein **Procedural Structure Data Asset** (`UProceduralStructureDataAsset`) im Content Browser und weisen Sie es der Eigenschaft **ProceduralStructure** des Actors zu.
2. Fügen Sie in **ReadInComponentConfiguration** einen Eintrag hinzu, dessen **Name** mit Ihrer Komponente (`Walls`) übereinstimmt, und wählen Sie einen **StructureType** (z. B. `Structure`).
3. Setzen Sie **bReadInMeshComponentData**, um die aktuellen Instanzen der Komponente im Data Asset zu erfassen.
4. Fügen Sie in **ComponentConfiguration** einen Eintrag hinzu, der denselben **Name** (`Walls`) wieder dem Data-Asset-Eintrag zuordnet.
5. Führen Sie eine Vorschau mit **GetBuildPlan** aus Blueprint/C++ oder der automatisierten Vorschauroute durch. Ein sauberer Plan weist keine blockierenden Probleme auf und meldet die exakte Instanzsumme, die neu gebaut wird.
6. Neu bauen — aktivieren Sie **bAutoBuildOnConstruction** (baut bei der Construction neu) oder verschieben/bearbeiten Sie den Actor, um einen Build auszulösen.

**Erwartetes Ergebnis:** Die instanziierten Meshes werden aus dem Data Asset neu gebaut. Explizit erfasste Transformationen werden exakt wiedergegeben (niemals neuzentriert). Um zu iterieren, setzen Sie **bClearProceduralStructureInformation**, um die gespeicherten Daten zu löschen, und erfassen Sie erneut.

## 4. Leistung / Asynchron

- **bUseAsyncBuild**: Verteilt den Build über Frames anstelle eines einzelnen blockierenden Durchlaufs.
- **InstancesPerFrame**: Wie viele Instanzen pro Tick hinzugefügt werden, wenn der asynchrone Build aktiviert ist.
- **GetBuildProgress** / **GetAddedBuildInstanceCount**: Verfolgt den asynchronen Build-Fortschritt für Tools.
- **bCenterGeneratedTransforms**: Zentriert *generierte Zeilen*-Transformationen um den lokalen XY-Ursprung (explizit erfasste Instanzen werden niemals neuzentriert).

## 5. Zeilenbasierte Strukturen generieren (Optional)

Über das erneute Abspielen erfasster Instanzen hinaus kann ein Data-Asset-Eintrag **InstancedMeshRows** definieren, um Raster/Zeilen prozedural zu generieren (Zeilenzahlen pro Dimension mit Transformationsbewegungen pro Dimension). Siehe [SettingsReference.md](SettingsReference.md) für jedes Feld.

## 6. Nächste Schritte

- Vollständiger Workflow und Bauhinweise: [UserManual.md](UserManual.md).
- Jede Actor-Eigenschaft und jedes Data-Asset-Feld: [SettingsReference.md](SettingsReference.md).
- Probleme: [TROUBLESHOOTING.md](TROUBLESHOOTING.md) und [FAQ.md](FAQ.md).
