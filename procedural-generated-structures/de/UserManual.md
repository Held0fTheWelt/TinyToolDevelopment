<!-- doc-provenance: AKDB:plugins/ProceduralGeneratedStructures/architecture.md; docs/architecture/plugins/ProceduralGeneratedStructures/product-facts.yml; reconciled 2026-06-21 -->
# Benutzerhandbuch

Dieses Handbuch erklärt, wie Sie Procedural Generated Structures im Unreal Editor verwenden.

## Zweck

Procedural Generated Structures baut wiederverwendbare instanziierte Static-Mesh-Strukturen aus einem Data Asset. Der Laufzeit-Actor kann vorhandene `UInstancedStaticMeshComponent`-Instanzen in ein `UProceduralStructureDataAsset` einlesen und dann diese expliziten Instanzen neu bauen oder zusätzliche zeilenbasierte Strukturen generieren.

## Kernobjekte

- **`AAsyncProceduralGeneratedActor`** — besitzt den Build-Workflow und kann Komponenten synchron oder über Editor-/Spiel-Ticks hinweg neu bauen.
- **`UProceduralStructureDataAsset`** — speichert benannte Mesh-Einträge (`FInstancedMeshInformation`) mit expliziten Transformationen und optionalen Zeilengenerierungsregeln.
- **`FInstancedComponentConfiguration`** — ordnet eine benannte instanziierte Mesh-Komponente am Actor einem gespeicherten Data-Asset-Eintrag zu (`Name` + `StructureType`).
- **`FProceduralStructureBuildPlan`** — meldet, was ein Rebuild tun würde: Zielkomponenten, blockierende Probleme, Mutationsabsichten, asynchrone Zählungen und exakte Instanzsummen nach dem Beschneiden.
- **`FProceduralStructureElementStats`** — meldet explizite, generierte, potenziell generierte und Gesamtinstanzzahlen pro Eintrag.
- **`EStructureType`** — `None`, `Structure`, `Railing`, `Tribune`, `Stairs`.

## Workflow

1. Fügen Sie einen `AAsyncProceduralGeneratedActor` zu einem Level oder Blueprint hinzu.
2. Fügen Sie ein oder mehrere `UInstancedStaticMeshComponent`-Unterelemente mit **stabilen Komponentennamen** hinzu.
3. Weisen Sie ein `UProceduralStructureDataAsset` zu **ProceduralStructure** zu.
4. Konfigurieren Sie **ReadInComponentConfiguration**, um vorhandene Komponenteninstanzen im Asset zu erfassen (auslösen mit **bReadInMeshComponentData**).
5. Konfigurieren Sie **ComponentConfiguration**, um diese Einträge wieder auf die Komponenten neu zu bauen.
6. Überprüfen Sie **GetBuildPlan** (Blueprint/C++) oder die Vorschauroute, wenn Sie Automatisierung verwenden. Beheben Sie alle gemeldeten Probleme, bevor Sie einen Rebuild anwenden.
7. Verwenden Sie **bClearProceduralStructureInformation** (löschen), **bReadInMeshComponentData** (einlesen) und den Build (Construction / asynchron), um die Struktur zu iterieren.

## Bauhinweise

- Explizite Transformationen, die aus Szenenkomponenten gelesen werden, werden **exakt wiedergegeben** und beim Rebuild nicht neuzentriert.
- Generierte Zeilentransformationen können mit **bCenterGeneratedTransforms** um den lokalen XY-Ursprung zentriert werden.
- **InstancesPerFrame** begrenzt, wie viele Instanzen pro Tick hinzugefügt werden, wenn der asynchrone Build aktiviert ist.
- Zeilenzahlen werden vor der Generierung auf nicht-negative Werte begrenzt.
- Baupläne und DataAsset-Statistiken melden sowohl die unbeschnittene Zeilenkapazität als auch die exakte generierte Anzahl nach dem Beschneiden, sodass große Rebuilds vor der Mutation geschätzt werden können.
- **bAutoBuildOnConstruction** löst einen Build während `OnConstruction` aus (ähnlich dem Spline-Actor).
- **bUseAsyncBuild** verteilt den Build über Frames; andernfalls erfolgt der Build in einem Durchlauf.
- **GetBuildProgress**, **GetEstimatedBuildInstanceCount** und **GetAddedBuildInstanceCount** melden den asynchronen Build-Fortschritt für Editor-Tools und Blueprints.

## Bauplan und Validierung

`AAsyncProceduralGeneratedActor::GetBuildPlan` ist eine nicht-mutierende Vorschau. Verwenden Sie sie vor dem Rebuild großer oder gemeinsam genutzter Strukturen.

Der Bauplan meldet:

- Ob ein Data Asset, eine Komponentenkonfiguration und vom Actor besessene instanziierte Mesh-Komponenten vorhanden sind.
- Einen Eintrag pro konfigurierter Komponente, einschließlich Komponentenpfad, Mesh-Pfad, DataAsset-Elementstatistiken, Mutationsabsicht und Codes für blockierende Probleme.
- Summen für explizite Instanzen, potenziell generierte Instanzen vor dem Beschneiden, generierte Instanzen nach dem Beschneiden und die kombinierte Instanzzahl.

Häufige Codes für blockierende Probleme sind:

- `missing_procedural_structure_data_asset`
- `missing_component_configuration`
- `actor_has_no_instanced_static_mesh_components`
- `component_not_found:<Name>`
- `data_asset_element_not_found:<Name>`
- `data_asset_element_missing_mesh:<Name>`
- `data_asset_element_type_none:<Name>`

## Data-Asset-Einträge

Jeder `FInstancedMeshInformation`-Eintrag enthält:

- `Name`, `Type` (`EStructureType`), `Mesh` (`UStaticMesh`).
- `Instances` — explizite Transformationen (z. B. aus der Szene erfasst), wie besehen wiedergegeben.
- `InstancedMeshRows` — optionale prozedurale Zeilenregeln (Zeilenzahlen pro Dimension, Transformationsbewegungen pro Dimension, Beschneidungs-/definierte Platzierungsoptionen). Siehe [SettingsReference.md](SettingsReference.md) für jedes Feld.

## Was das Plugin nicht tut

- Es verfasst keine Static Meshes für Sie — Sie stellen Ihre eigenen bereit.
- Es zentriert explizit erfasste Instanzen nicht neu.
- Es ist kein vollständiges prozedurales Modellierungssystem; es platziert und regeneriert instanziierte Meshes aus Daten.
