<!-- doc-provenance: AKDB:plugins/ProceduralGeneratedStructures/architecture.md; docs/architecture/plugins/ProceduralGeneratedStructures/product-facts.yml; reconciled 2026-06-21 -->
# 快速入门指南

本指南带您从安装到获得**直观成果**：从数据资产重新构建实例化网格体结构的 `AAsyncProceduralGeneratedActor`。本插件独立工作 — 无需其他插件。

## 完成本指南后您将获得什么

关卡中的一个 Actor，其实例化静态网格体实例被捕获到数据资产中并从中重新构建，使结构可重用和可再生。

## 要求

- Unreal Engine 5 编辑器和打开的关卡。
- 来自您项目的要实例化的 `UStaticMesh`（例如墙壁或柱子网格体）。
- 无第三方软件、帐户或运行时。参阅 [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md)。

## 1. 安装与启用

1. 从 Fab 库将 **ProceduralGeneratedStructures** 添加到项目（或安装到引擎）。
2. 打开 **Edit → Plugins**，启用 **ProceduralGeneratedStructures**，并在收到提示时重新启动。

## 2. 放置 Actor（首个成果）

1. 在 **Place Actors** 面板中，搜索 **Async Procedural Generated Actor** 并将其拖入关卡（或从类列表中添加 `AAsyncProceduralGeneratedActor`）。
2. 向 Actor 添加一个或多个 **Instanced Static Mesh Component** 子组件，并为每个子组件指定一个**稳定的组件名称**（例如 `Walls`）。指定您的静态网格体并放置几个实例。

## 3. 实际操作示例：捕获与重新构建

1. 在 Content Browser 中创建 **Procedural Structure Data Asset** (`UProceduralStructureDataAsset`) 并将其指定给 Actor 的 **ProceduralStructure** 属性。
2. 在 **ReadInComponentConfiguration** 中，添加一个 **Name** 与您的组件 (`Walls`) 匹配的条目，并选择一个 **StructureType**（例如 `Structure`）。
3. 设置 **bReadInMeshComponentData** 以将组件的当前实例捕获到数据资产中。
4. 在 **ComponentConfiguration** 中，添加一个将相同 **Name** (`Walls`) 映射回数据资产条目的条目。
5. 从 Blueprint/C++ 或自动化预览路线中使用 **GetBuildPlan** 进行预览。干净的计划没有阻塞问题，并报告将要重新构建的确切实例总数。
6. 重新构建 — 启用 **bAutoBuildOnConstruction**（在构建时重新构建）或移动/编辑 Actor 以触发构建。

**预期输出：** 实例化网格体从数据资产重新构建。捕获的显式变换将精确重放（绝不重新居中）。要进行迭代，请设置 **bClearProceduralStructureInformation** 以清除存储的数据，然后再次捕获。

## 4. 性能 / 异步

- **bUseAsyncBuild**：跨帧分散构建，而不是单次阻塞 pass。
- **InstancesPerFrame**：当启用异步构建时每个 Tick 添加多少个实例。
- **GetBuildProgress** / **GetAddedBuildInstanceCount**：为工具跟踪异步构建进度。
- **bCenterGeneratedTransforms**：围绕局部 XY 原点居中*生成的行*变换（显式捕获的实例绝不重新居中）。

## 5. 生成基于行的结构（可选）

除了重放捕获的实例之外，数据资产条目还可以定义 **InstancedMeshRows** 以程序化生成网格/行（每个维度的行数以及每个维度的移动变换）。有关每个字段，请参阅 [SettingsReference.md](SettingsReference.md)。

## 6. 后续步骤

- 完整工作流和构建说明: [UserManual.md](UserManual.md)。
- 每个 Actor 属性和数据资产字段: [SettingsReference.md](SettingsReference.md)。
- 疑难解答与修复: [TROUBLESHOOTING.md](TROUBLESHOOTING.md) 和 [FAQ.md](FAQ.md)。
