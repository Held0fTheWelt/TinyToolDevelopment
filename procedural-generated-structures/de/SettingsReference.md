<!-- doc-provenance: AKDB:plugins/ProceduralGeneratedStructures/architecture.md; docs/architecture/plugins/ProceduralGeneratedStructures/product-facts.yml; reconciled 2026-06-21 -->
# Einstellungsreferenz

Jede benutzerseitige Eigenschaft und jedes Data-Asset-Feld mit ihrem Zweck.

## `AAsyncProceduralGeneratedActor`

| Eigenschaft | Kategorie | Typ | Zweck |
| --- | --- | --- | --- |
| `InstancesPerFrame` | Procedural\|Performance | int32 (min 1) | Pro Tick über alle Build-Aufgaben hinzugefügte Instanzen, wenn der asynchrone Build aktiviert ist. |
| `bAutoBuildOnConstruction` | Procedural\|Build | bool | Löst einen Build während `OnConstruction` aus. |
| `bUseAsyncBuild` | Procedural\|Build | bool | Verteilt den Build über mehrere Frames (nicht-blockierend); andernfalls Build in einem Durchlauf. |
| `bCenterGeneratedTransforms` | Procedural\|Build | bool | Zentriert **generierte Zeilen**-Transformationen um den lokalen XY-Ursprung. Explizit erfasste Instanzen werden niemals neuzentriert. |
| `ProceduralStructure` | Procedural | `UProceduralStructureDataAsset` | Datenquelle, die definiert, was gebaut wird. |
| `ReadInComponentConfiguration` | Procedural | Array von `FInstancedComponentConfiguration` | Ordnet Szenen-`UInstancedStaticMeshComponent`s → Data-Asset-Einträgen zu (Einlesen). |
| `ComponentConfiguration` | Procedural | Array von `FInstancedComponentConfiguration` | Ordnet Data-Asset-Einträge → Komponenten an diesem Actor zu (Rebuild). |
| `bClearProceduralStructureInformation` | Procedural\|Debug | bool | Löscht die `ProceduralStructure`-Daten (Editor-Auslöser). |
| `bReadInMeshComponentData` | Procedural\|Debug | bool | Liest Szenenkomponenteninstanzen in das Data Asset ein (Editor-Auslöser). |
| `EstimatedBuildInstanceCount` | Procedural\|Debug | int64 | Geschätzte Instanzzahl für den aktuellen oder jüngsten Rebuild. |
| `AddedBuildInstanceCount` | Procedural\|Debug | int64 | Durch den aktuellen oder jüngsten Rebuild hinzugefügte Instanzen. |

### Actor-Hilfsfunktionen

| Funktion | Zweck |
| --- | --- |
| `GetBuildPlan` | Nicht-mutierende Vorschau mit Zielkomponenten, blockierenden Problemen, Mutationsabsicht und exakten Instanzzahlen nach dem Beschneiden. |
| `GetEstimatedBuildInstanceCount` | Gibt die geschätzte Instanzzahl für den aktuellen oder jüngsten Build zurück. |
| `GetAddedBuildInstanceCount` | Gibt zurück, wie viele Instanzen durch den aktuellen oder jüngsten Build hinzugefügt wurden. |
| `GetBuildProgress` | Gibt den Build-Fortschritt von `0.0` bis `1.0` zurück, wenn eine Schätzung verfügbar ist. |

## `FInstancedComponentConfiguration`

| Feld | Typ | Zweck |
| --- | --- | --- |
| `Name` | FName | Name der instanziierten Mesh-Komponente am Actor. |
| `StructureType` | `EStructureType` | Strukturklassifizierung für die Zuordnung. |

## `EStructureType`

`None`, `Structure`, `Railing`, `Tribune`, `Stairs`.

## `UProceduralStructureDataAsset` → `FInstancedMeshInformation`

| Feld | Typ | Zweck |
| --- | --- | --- |
| `Name` | FName | Eintragsname (stimmt mit einer Komponentenkonfiguration überein). |
| `Type` | `EStructureType` | Strukturklassifizierung. |
| `Mesh` | `UStaticMesh` | Für die Instanzen verwendetes Mesh. |
| `Instances` | Array von `FTransform` | Explizite Transformationen, exakt wiedergegeben. |
| `InstancedMeshRows` | Array von `FInstancedMeshRowInformation` | Prozedurale Zeilengenerierungsregeln. |

### DataAsset-Hilfsfunktionen

| Funktion | Zweck |
| --- | --- |
| `GetElementStats` | Gibt `FProceduralStructureElementStats` für einen benannten Eintrag zurück. |
| `GetAllElementStats` | Gibt Statistiken für jeden Eintrag zurück. |
| `GetTotalExplicitInstanceCount` | Zählt erfasste explizite Instanzen über alle Einträge hinweg. |
| `GetTotalPotentialGeneratedInstanceCount` | Zählt die generierte Zeilenkapazität vor dem Beschneiden. |
| `GetTotalGeneratedInstanceCount` | Zählt generierte Zeileninstanzen nach dem Beschneiden. |
| `GetTotalInstanceCount` | Zählt explizite plus generierte Instanzen nach dem Beschneiden. |

## `FProceduralStructureBuildPlan`

| Feld | Typ | Zweck |
| --- | --- | --- |
| `bHasDataAsset` / `bHasComponentConfiguration` / `bHasInstancedComponents` | bool | Bereitschafts-Flags auf hoher Ebene. |
| `ConfiguredComponentCount` / `AvailableInstancedComponentCount` | int32 | Zuordnungszahl und gefundene vom Actor besessene ISM-Komponentenanzahl. |
| `MutatingComponentCount` | int32 | Komponenten, die gelöscht und neu gebaut würden. |
| `InstanceAddingComponentCount` | int32 | Komponenten, die eine oder mehrere Instanzen erhalten würden. |
| `TotalExplicitInstanceCount` | int64 | Explizit erfasste Instanzen in baubaren Einträgen. |
| `TotalPotentialGeneratedInstanceCount` | int64 | Generierte Zeilenkapazität vor dem Beschneiden. |
| `TotalGeneratedInstanceCount` | int64 | Generierte Zeileninstanzen nach dem Beschneiden. |
| `TotalInstanceCount` | int64 | Explizite plus generierte Instanzen nach dem Beschneiden. |
| `Entries` | Array von `FProceduralStructureBuildPlanEntry` | Vorschaueinträge pro konfigurierter Komponente. |
| `Issues` | Array von string | Codes für blockierende Probleme. |

## `FProceduralStructureElementStats`

| Feld | Typ | Zweck |
| --- | --- | --- |
| `Name` / `Type` / `Mesh` / `bHasMesh` | gemischt | Identität und Mesh-Bereitschaft für einen Data-Asset-Eintrag. |
| `ExplicitInstanceCount` | int32 | Anzahl erfasster expliziter Transformationen. |
| `RowRuleCount` | int32 | Anzahl von Zeilengenerierungsregeln. |
| `PotentialGeneratedInstanceCount` | int64 | Zeilenkapazität vor dem Beschneiden. |
| `GeneratedInstanceCount` | int64 | Exakte generierte Anzahl nach dem Beschneiden. |
| `TotalInstanceCount` | int64 | Explizite plus generierte Anzahl nach dem Beschneiden. |

## `FInstancedMeshRowInformation` (Zeilengenerierung)

| Feld | Typ | Zweck |
| --- | --- | --- |
| `Transform` | FTransform | Basistransformation für die Zeile. |
| `RowCount_FirstDimension` / `_SecondDimension` / `_ThirdDimension` | int32 (min 0) | Instanzzahlen pro Dimension. |
| `Movement_First_Dimension` / `_Second_Dimension` / `_Third_Dimension` | FTransform | Entlang jeder Dimension angewendete Schritttransformation. |
| `MovementAdjustmentByRotation_First_Dimension` | FVector | Durch Rotation entlang der ersten Dimension angewendete Anpassung. |
| `DefinedSecondDimension` | Array von FVector | Explizite Platzierungen der zweiten Dimension. |
| `PrunedInstances` / `PrunedFirstDimension` / `PrunedSecondDimension` / `PrunedThirdDimension` / `PrunedSecondDimensionInThirdDimension` | Arrays | Indizes/Instanzen, die während der Generierung übersprungen werden sollen. |
| `bApplyRowCountAdjust` | bool | Zeilenzahlanpassung anwenden. |
| `bUseDefinedPlacementMethod` | bool | Verwende `DefinedSecondDimension`-Platzierung anstelle von Schrittbewegungen. |
