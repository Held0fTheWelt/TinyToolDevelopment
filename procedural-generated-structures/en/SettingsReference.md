<!-- doc-provenance: AKDB:plugins/ProceduralGeneratedStructures/architecture.md; docs/architecture/plugins/ProceduralGeneratedStructures/product-facts.yml; reconciled 2026-06-21 -->
# Settings Reference

Every user-facing property and data-asset field, with its purpose.

## `AAsyncProceduralGeneratedActor`

| Property | Category | Type | Purpose |
| --- | --- | --- | --- |
| `InstancesPerFrame` | Procedural\|Performance | int32 (min 1) | Instances added per tick across all build tasks when async build is enabled. |
| `bAutoBuildOnConstruction` | Procedural\|Build | bool | Trigger a build during `OnConstruction`. |
| `bUseAsyncBuild` | Procedural\|Build | bool | Spread the build across multiple frames (non-blocking); otherwise build in one pass. |
| `bCenterGeneratedTransforms` | Procedural\|Build | bool | Center **generated row** transforms around the local XY origin. Explicit captured instances are never recentered. |
| `ProceduralStructure` | Procedural | `UProceduralStructureDataAsset` | Data source defining what is built. |
| `ReadInComponentConfiguration` | Procedural | array of `FInstancedComponentConfiguration` | Maps scene `UInstancedStaticMeshComponent`s → data-asset entries (read-in). |
| `ComponentConfiguration` | Procedural | array of `FInstancedComponentConfiguration` | Maps data-asset entries → components on this actor (rebuild). |
| `bClearProceduralStructureInformation` | Procedural\|Debug | bool | Clears the `ProceduralStructure` data (editor trigger). |
| `bReadInMeshComponentData` | Procedural\|Debug | bool | Reads scene component instances into the data asset (editor trigger). |
| `EstimatedBuildInstanceCount` | Procedural\|Debug | int64 | Estimated instance count for the current or most recent rebuild. |
| `AddedBuildInstanceCount` | Procedural\|Debug | int64 | Instances added by the current or most recent rebuild. |

### Actor Helper Functions

| Function | Purpose |
| --- | --- |
| `GetBuildPlan` | Non-mutating preview with target components, blocking issues, mutation intent, and exact post-prune instance counts. |
| `GetEstimatedBuildInstanceCount` | Returns the estimated instance count for the current or most recent build. |
| `GetAddedBuildInstanceCount` | Returns how many instances have been added by the current or most recent build. |
| `GetBuildProgress` | Returns build progress from `0.0` to `1.0` when an estimate is available. |

## `FInstancedComponentConfiguration`

| Field | Type | Purpose |
| --- | --- | --- |
| `Name` | FName | Name of the instanced mesh component on the actor. |
| `StructureType` | `EStructureType` | Structure classification for the mapping. |

## `EStructureType`

`None`, `Structure`, `Railing`, `Tribune`, `Stairs`.

## `UProceduralStructureDataAsset` → `FInstancedMeshInformation`

| Field | Type | Purpose |
| --- | --- | --- |
| `Name` | FName | Entry name (matches a component configuration). |
| `Type` | `EStructureType` | Structure classification. |
| `Mesh` | `UStaticMesh` | Mesh used for the instances. |
| `Instances` | array of `FTransform` | Explicit transforms, replayed exactly. |
| `InstancedMeshRows` | array of `FInstancedMeshRowInformation` | Procedural row-generation rules. |

### DataAsset Helper Functions

| Function | Purpose |
| --- | --- |
| `GetElementStats` | Returns `FProceduralStructureElementStats` for a named entry. |
| `GetAllElementStats` | Returns stats for every entry. |
| `GetTotalExplicitInstanceCount` | Counts captured explicit instances across all entries. |
| `GetTotalPotentialGeneratedInstanceCount` | Counts generated row capacity before pruning. |
| `GetTotalGeneratedInstanceCount` | Counts generated row instances after pruning. |
| `GetTotalInstanceCount` | Counts explicit plus post-prune generated instances. |

## `FProceduralStructureBuildPlan`

| Field | Type | Purpose |
| --- | --- | --- |
| `bHasDataAsset` / `bHasComponentConfiguration` / `bHasInstancedComponents` | bool | High-level readiness flags. |
| `ConfiguredComponentCount` / `AvailableInstancedComponentCount` | int32 | Mapping count and discovered actor-owned ISM component count. |
| `MutatingComponentCount` | int32 | Components that would be cleared and rebuilt. |
| `InstanceAddingComponentCount` | int32 | Components that would receive one or more instances. |
| `TotalExplicitInstanceCount` | int64 | Explicit captured instances in buildable entries. |
| `TotalPotentialGeneratedInstanceCount` | int64 | Generated row capacity before pruning. |
| `TotalGeneratedInstanceCount` | int64 | Generated row instances after pruning. |
| `TotalInstanceCount` | int64 | Explicit plus post-prune generated instances. |
| `Entries` | array of `FProceduralStructureBuildPlanEntry` | Per configured component preview entries. |
| `Issues` | array of string | Blocking issue codes. |

## `FProceduralStructureElementStats`

| Field | Type | Purpose |
| --- | --- | --- |
| `Name` / `Type` / `Mesh` / `bHasMesh` | mixed | Identity and mesh readiness for a data asset entry. |
| `ExplicitInstanceCount` | int32 | Count of captured explicit transforms. |
| `RowRuleCount` | int32 | Count of row-generation rules. |
| `PotentialGeneratedInstanceCount` | int64 | Row capacity before pruning. |
| `GeneratedInstanceCount` | int64 | Exact generated count after pruning. |
| `TotalInstanceCount` | int64 | Explicit plus post-prune generated count. |

## `FInstancedMeshRowInformation` (row generation)

| Field | Type | Purpose |
| --- | --- | --- |
| `Transform` | FTransform | Base transform for the row. |
| `RowCount_FirstDimension` / `_SecondDimension` / `_ThirdDimension` | int32 (min 0) | Instance counts per dimension. |
| `Movement_First_Dimension` / `_Second_Dimension` / `_Third_Dimension` | FTransform | Per-step transform applied along each dimension. |
| `MovementAdjustmentByRotation_First_Dimension` | FVector | Movement adjustment applied by rotation along the first dimension. |
| `DefinedSecondDimension` | array of FVector | Explicit second-dimension placements. |
| `PrunedInstances` / `PrunedFirstDimension` / `PrunedSecondDimension` / `PrunedThirdDimension` / `PrunedSecondDimensionInThirdDimension` | arrays | Indices/instances to skip during generation. |
| `bApplyRowCountAdjust` | bool | Apply row-count adjustment. |
| `bUseDefinedPlacementMethod` | bool | Use `DefinedSecondDimension` placement instead of movement stepping. |
