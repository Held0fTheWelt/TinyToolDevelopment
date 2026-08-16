<!-- doc-provenance: AKDB:plugins/ProceduralGeneratedStructures/architecture.md; docs/architecture/plugins/ProceduralGeneratedStructures/product-facts.yml; reconciled 2026-06-21 -->
# ProceduralGeneratedStructures 文档

ProceduralGeneratedStructures 根据数据资产构建可重用的实例化静态网格体结构。运行时 Actor 可以将现有 `UInstancedStaticMeshComponent` 实例读取到 `UProceduralStructureDataAsset` 中，然后重新构建这些显式实例或生成额外的基于行的结构。它还公开构建计划和统计数据，以便您可以在应用重新构建之前检查目标组件、阻塞问题、修改意图、异步进度和修剪后的确切实例数。

## 文档

- [QUICKSTART.md](QUICKSTART.md)：安装 → 放置 Actor → 捕获并重新构建，包含预期结果。
- [UserManual.md](UserManual.md)：完整工作流、核心对象和构建说明。
- [SettingsReference.md](SettingsReference.md)：每个 Actor 属性和数据资产字段。
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md) · [FAQ.md](FAQ.md)
- [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md)：第三方声明（无捆绑）。

## 核心资产

- `AAsyncProceduralGeneratedActor` 拥有构建工作流，可以同步或跨编辑器/游戏 Tick 重新构建组件。
- `UProceduralStructureDataAsset` 存储包含显式变换和可选行生成规则的具名网格体条目。
- `FInstancedComponentConfiguration` 将 Actor 上的具名实例化网格体组件映射到存储的数据资产条目。
- `FProceduralStructureBuildPlan` 和 `FProceduralStructureElementStats` 为工具、Blueprint 和 UCM 路线公开确切的预览数据。

## 构建说明

- 从场景组件读取的显式变换将精确重放，且在重新构建期间不会重新居中。
- 生成的行变换可以通过 `bCenterGeneratedTransforms` 围绕局部 XY 原点居中。
- 当启用异步构建时，`InstancesPerFrame` 限制每个 Tick 添加的实例数。
- 行数在生成前被限制为非负值。
- 构建计划报告修剪前的生成行容量以及修剪后的确切生成数量。

## 推荐工作流

1. 将 `AAsyncProceduralGeneratedActor` 添加到关卡或 Blueprint 中。
2. 添加一个或多个具有稳定组件名称的 `UInstancedStaticMeshComponent` 子组件。
3. 指定 `UProceduralStructureDataAsset`。
4. 配置 `ReadInComponentConfiguration` 以捕获现有组件实例。
5. 配置 `ComponentConfiguration` 以重新构建这些条目。
6. 检查 `GetBuildPlan` 或预览路线，然后使用编辑器中可调用的读取、清除和构建操作来迭代结构。
