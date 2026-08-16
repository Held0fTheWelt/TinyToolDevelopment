<!-- doc-provenance: AKDB:plugins/ProceduralGeneratedStructures/architecture.md; docs/architecture/plugins/ProceduralGeneratedStructures/product-facts.yml; reconciled 2026-06-21 -->
# 疑难解答

## 我启用了插件但什么也没发生

该插件添加了 `AAsyncProceduralGeneratedActor` 类和 `UProceduralStructureDataAsset`。
将 Actor 放置在关卡中（Place Actors → *Async Procedural Generated Actor*）；没有菜单 —
工作流保存在 Actor 的 Details 面板中。

## 构建未产生实例

- 确认 Actor 至少具有一个带**稳定名称**的 `UInstancedStaticMeshComponent` 子组件。
- 确认 **ComponentConfiguration** 具有一个 **Name** 与该组件匹配的条目。
- 确认向数据资产条目指定了有效的 **Mesh**。
- 如果使用读取，请确保您首先进行了捕获 (**bReadInMeshComponentData**)，且带有匹配的 **ReadInComponentConfiguration** 条目。
- 检查 **GetBuildPlan**。它会报告精确的问题代码，例如 `component_not_found:<Name>`、`data_asset_element_not_found:<Name>` 和 `data_asset_element_missing_mesh:<Name>`。

## 预览报告了非常高的实例数

构建计划报告了修剪前潜在生成的实例数以及修剪后的确切生成数量。如果两者都太高，请减少行数、添加修剪 (pruning)，或启用 **bUseAsyncBuild** 并降低 **InstancesPerFrame**。

## 捕获的实例发生了意外移动/重新居中

捕获的显式实例将精确重放，且绝不重新居中。只有**生成的行**变换会受到 **bCenterGeneratedTransforms** 的影响。

## 构建在大结构上使编辑器/游戏卡顿

启用 **bUseAsyncBuild** 并降低 **InstancesPerFrame**，以便跨多个 Tick 添加实例，而不是在单次阻塞 pass 中添加。

## 读取捕获了错误的组件

`ReadInComponentConfiguration` 通过组件 **Name** 进行匹配。请确保组件名称稳定且唯一，并且配置条目的 `Name` 完全匹配。

## 生成的网格有缝隙

检查行信息上的 `Pruned*` 数组 — 修剪后的索引/实例会被意图明确地跳过。清除它们以生成完整的网格。
