<!-- doc-provenance: AKDB:plugins/ProceduralGeneratedStructures/architecture.md; docs/architecture/plugins/ProceduralGeneratedStructures/product-facts.yml; reconciled 2026-06-21 -->
# 设置参考

每个面向用户的属性和数据资产字段及其用途。

## `AAsyncProceduralGeneratedActor`

| 属性 | 类别 | 类型 | 用途 |
| --- | --- | --- | --- |
| `InstancesPerFrame` | Procedural\|Performance | int32 (min 1) | 当启用异步构建时，所有构建任务跨 Tick 每 Tick 添加的实例数。 |
| `bAutoBuildOnConstruction` | Procedural\|Build | bool | 在 `OnConstruction` 期间触发构建。 |
| `bUseAsyncBuild` | Procedural\|Build | bool | 跨多个帧分散构建（非阻塞）；否则在一次 pass 中构建。 |
| `bCenterGeneratedTransforms` | Procedural\|Build | bool | 围绕局部 XY 原点居中**生成的行**变换。显式捕获的实例绝不重新居中。 |
| `ProceduralStructure` | Procedural | `UProceduralStructureDataAsset` | 定义要构建的内容的数据源。 |
| `ReadInComponentConfiguration` | Procedural | `FInstancedComponentConfiguration` 数组 | 将场景 `UInstancedStaticMeshComponent` 映射到数据资产条目（读取）。 |
| `ComponentConfiguration` | Procedural | `FInstancedComponentConfiguration` 数组 | 将数据资产条目映射到此 Actor 上的组件（重新构建）。 |
| `bClearProceduralStructureInformation` | Procedural\|Debug | bool | 清除 `ProceduralStructure` 数据（编辑器触发器）。 |
| `bReadInMeshComponentData` | Procedural\|Debug | bool | 将场景组件实例读取到数据资产中（编辑器触发器）。 |
| `EstimatedBuildInstanceCount` | Procedural\|Debug | int64 | 当前或最近重新构建的估计实例数。 |
| `AddedBuildInstanceCount` | Procedural\|Debug | int64 | 当前或最近重新构建添加的实例。 |

### Actor 助手函数

| 函数 | 用途 |
| --- | --- |
| `GetBuildPlan` | 包含目标组件、阻塞问题、修改意图和修剪后确切实例数的非修改性预览。 |
| `GetEstimatedBuildInstanceCount` | 返回当前或最近构建的估计实例数。 |
| `GetAddedBuildInstanceCount` | 返回当前或最近构建已添加的实例数。 |
| `GetBuildProgress` | 当有估计可用时返回 `0.0` 到 `1.0` 的构建进度。 |

## `FInstancedComponentConfiguration`

| 字段 | 类型 | 用途 |
| --- | --- | --- |
| `Name` | FName | Actor 上实例化网格体组件的名称。 |
| `StructureType` | `EStructureType` | 映射的结构分类。 |

## `EStructureType`

`None`、`Structure`、`Railing`、`Tribune`、`Stairs`。

## `UProceduralStructureDataAsset` → `FInstancedMeshInformation`

| 字段 | 类型 | 用途 |
| --- | --- | --- |
| `Name` | FName | 条目名称（与组件配置匹配）。 |
| `Type` | `EStructureType` | 结构分类。 |
| `Mesh` | `UStaticMesh` | 用于实例的网格体。 |
| `Instances` | `FTransform` 数组 | 精确重放的显式变换。 |
| `InstancedMeshRows` | `FInstancedMeshRowInformation` 数组 | 程序化行生成规则。 |

### DataAsset 助手函数

| 函数 | 用途 |
| --- | --- |
| `GetElementStats` | 返回具名条目的 `FProceduralStructureElementStats`。 |
| `GetAllElementStats` | 返回每个条目的统计数据。 |
| `GetTotalExplicitInstanceCount` | 统计所有条目中捕获的显式实例。 |
| `GetTotalPotentialGeneratedInstanceCount` | 统计修剪前的生成行容量。 |
| `GetTotalGeneratedInstanceCount` | 统计修剪后的生成行实例。 |
| `GetTotalInstanceCount` | 统计显式实例加修剪后生成实例的总和。 |

## `FProceduralStructureBuildPlan`

| 字段 | 类型 | 用途 |
| --- | --- | --- |
| `bHasDataAsset` / `bHasComponentConfiguration` / `bHasInstancedComponents` | bool | 高级就绪标志。 |
| `ConfiguredComponentCount` / `AvailableInstancedComponentCount` | int32 | 映射数量和发现的 Actor 拥有的 ISM 组件数量。 |
| `MutatingComponentCount` | int32 | 将被清除并重新构建的组件。 |
| `InstanceAddingComponentCount` | int32 | 将接收一个或多个实例的组件。 |
| `TotalExplicitInstanceCount` | int64 | 可构建条目中捕获的显式实例。 |
| `TotalPotentialGeneratedInstanceCount` | int64 | 修剪前的生成行容量。 |
| `TotalGeneratedInstanceCount` | int64 | 修剪后的生成行实例。 |
| `TotalInstanceCount` | int64 | 显式实例加修剪后生成实例的总和。 |
| `Entries` | `FProceduralStructureBuildPlanEntry` 数组 | 每个配置组件的预览条目。 |
| `Issues` | string 数组 | 阻塞问题代码。 |

## `FProceduralStructureElementStats`

| 字段 | 类型 | 用途 |
| --- | --- | --- |
| `Name` / `Type` / `Mesh` / `bHasMesh` | 混合 | 数据资产条目的身份和网格体就绪状态。 |
| `ExplicitInstanceCount` | int32 | 捕获的显式变换数量。 |
| `RowRuleCount` | int32 | 行生成规则数量。 |
| `PotentialGeneratedInstanceCount` | int64 | 修剪前的行容量。 |
| `GeneratedInstanceCount` | int64 | 修剪后的确切生成数量。 |
| `TotalInstanceCount` | int64 | 显式数加修剪后生成数的总和。 |

## `FInstancedMeshRowInformation`（行生成）

| 字段 | 类型 | 用途 |
| --- | --- | --- |
| `Transform` | FTransform | 行的基础变换。 |
| `RowCount_FirstDimension` / `_SecondDimension` / `_ThirdDimension` | int32 (min 0) | 每个维度的实例数量。 |
| `Movement_First_Dimension` / `_Second_Dimension` / `_Third_Dimension` | FTransform | 沿每个维度应用的步进变换。 |
| `MovementAdjustmentByRotation_First_Dimension` | FVector | 沿第一维度的旋转应用的移动调整。 |
| `DefinedSecondDimension` | FVector 数组 | 第二维度的显式放置。 |
| `PrunedInstances` / `PrunedFirstDimension` / `PrunedSecondDimension` / `PrunedThirdDimension` / `PrunedSecondDimensionInThirdDimension` | 数组 | 生成期间要跳过的索引/实例。 |
| `bApplyRowCountAdjust` | bool | 应用行数调整。 |
| `bUseDefinedPlacementMethod` | bool | 使用 `DefinedSecondDimension` 放置而不是移动步进。 |
