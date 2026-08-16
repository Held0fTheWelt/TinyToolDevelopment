<!-- doc-provenance: AKDB:plugins/ProceduralGeneratedStructures/architecture.md; docs/architecture/plugins/ProceduralGeneratedStructures/product-facts.yml; reconciled 2026-06-21 -->
# 用户手册

本手册解释如何在 Unreal Editor 中使用 Procedural Generated Structures。

## 目的

Procedural Generated Structures 根据数据资产构建可重用的实例化静态网格体结构。
运行时 Actor 可以将现有 `UInstancedStaticMeshComponent` 实例读取到 `UProceduralStructureDataAsset` 中，然后重新构建这些显式实例或生成额外的基于行的结构。

## 核心对象

- **`AAsyncProceduralGeneratedActor`** — 拥有构建工作流，可以同步或跨编辑器/游戏 Tick 重新构建组件。
- **`UProceduralStructureDataAsset`** — 存储包含显式变换和可选行生成规则的具名网格体条目 (`FInstancedMeshInformation`)。
- **`FInstancedComponentConfiguration`** — 将 Actor 上的具名实例化网格体组件映射到存储的数据资产条目 (`Name` + `StructureType`)。
- **`FProceduralStructureBuildPlan`** — 报告重新构建将执行的操作：目标组件、阻塞问题、修改意图、异步计数和修剪后的确切实例总数。
- **`FProceduralStructureElementStats`** — 报告每个条目的显式、生成、潜在生成和总实例数。
- **`EStructureType`** — `None`、`Structure`、`Railing`、`Tribune`、`Stairs`。

## 工作流

1. 将 `AAsyncProceduralGeneratedActor` 添加到关卡或 Blueprint 中。
2. 添加一个或多个具有**稳定组件名称**的 `UInstancedStaticMeshComponent` 子组件。
3. 将 `UProceduralStructureDataAsset` 指定给 **ProceduralStructure**。
4. 配置 **ReadInComponentConfiguration** 以将现有组件实例捕获到资产中（通过 **bReadInMeshComponentData** 触发）。
5. 配置 **ComponentConfiguration** 以将这些条目重新构建回组件上。
6. 如果使用自动化，请检查 **GetBuildPlan** (Blueprint/C++) 或预览路线。在应用重新构建之前修复任何报告的问题。
7. 使用 **bClearProceduralStructureInformation**（清除）、**bReadInMeshComponentData**（读取）和构建（构建 / 异步）来迭代结构。

## 构建说明

- 从场景组件读取的显式变换将**精确重放**，且在重新构建期间不会重新居中。
- 生成的行变换可以通过 **bCenterGeneratedTransforms** 围绕局部 XY 原点居中。
- **InstancesPerFrame** 限制当启用异步构建时每个 Tick 添加的实例数。
- 行数在生成前被限制为非负值。
- 构建计划和 DataAsset 统计信息同时报告未修剪的行容量以及修剪后的确切生成数量，因此可以在修改前估计大型重新构建。
- **bAutoBuildOnConstruction** 在 `OnConstruction` 期间触发构建（类似于样条线 Actor）。
- **bUseAsyncBuild** 跨帧分散构建；否则构建将在一次 pass 中发生。
- **GetBuildProgress**、**GetEstimatedBuildInstanceCount** 和 **GetAddedBuildInstanceCount** 为编辑器工具和 Blueprint 报告异步构建进度。

## 构建计划与验证

`AAsyncProceduralGeneratedActor::GetBuildPlan` 是非修改性预览。在重新构建大型或共享结构之前使用它。

构建计划报告：

- 数据资产、组件配置以及 Actor 拥有的实例化网格体组件是否存在。
- 每个配置组件一个条目，包括组件路径、网格体路径、DataAsset 元素统计、修改意图和阻塞问题代码。
- 显式实例、修剪前潜在生成的实例、修剪后生成的实例以及组合实例数的总计。

常见的阻塞问题代码包括：

- `missing_procedural_structure_data_asset`
- `missing_component_configuration`
- `actor_has_no_instanced_static_mesh_components`
- `component_not_found:<Name>`
- `data_asset_element_not_found:<Name>`
- `data_asset_element_missing_mesh:<Name>`
- `data_asset_element_type_none:<Name>`

## 数据资产条目

每个 `FInstancedMeshInformation` 条目包含：

- `Name`、`Type` (`EStructureType`)、`Mesh` (`UStaticMesh`)。
- `Instances` — 显式变换（例如从场景捕获），按原样重放。
- `InstancedMeshRows` — 可选的程序化行生成规则（每个维度的行数、每个维度的移动变换、修剪/定义放置选项）。有关每个字段，请参阅 [SettingsReference.md](SettingsReference.md)。

## 本插件不做的事项

- 它不会为您创作静态网格体 — 您自行提供。
- 它不会重新居中显式捕获的实例。
- 它不是一个完整的程序化建模系统；它根据数据放置和重新生成实例化网格体。
