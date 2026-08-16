<!-- doc-provenance: product-facts.yml reconciled 2026-07-15; source AKDB:plugins/AsyncSplineBuilder/architecture.md -->
# 常见问题解答 (FAQ)

## Async Spline Builder 用于什么？

它构建遵循样条线的网格体，例如道路、赛道、轨道、管道、障碍物和程序化支撑墙。其主要优势是异步分批，因此长样条线可以重新构建而不会导致编辑器大幅卡顿。

## 它在运行时有效吗？

有效。道路网格体、附加网格体、地面墙、落差墙和异步运行时泵均位于运行时模块中。仅限编辑器的地形高度变形在打包构建中不可用。

## 我的道路网格体应该使用什么方向？

沿局部 X 轴创作可重复的道路网格体。构建器在 X 上使用网格体边界作为长度备用，在 Y 上使用网格体边界作为宽度备用。

## 我可以按段使用不同的网格体吗？

可以。将条目添加到 `TrackSplineData` 并按段设置 `RoadMesh`、`RoadMeshLength`、`SegmentLength`、`MeshInstances` 和附加网格体数组。缺失的段数据回退到条目 `0`。

## 我在哪里配置本插件？

对于正常工作流，请使用 **Tools > Track Tools > Async Spline Builder**。它在一个面板中为您提供 Actor 选择、网格体设置、验证、构建控件、异步设置、样条线显示切换、段助手、地形操作和地面墙启用。对于按段的高级数组以及详细的追踪、墙壁、碰撞、UV 和数据资产字段，请使用 Details 面板。

## BuildTrack 和 RebuildTrack 有什么区别？

`BuildTrack` 是同步且立即的。当启用 `bUseAsyncBuild` 时，`RebuildTrack` 使用异步分批。

## 异步生成是否使用工作线程 (worker threads)？

不使用。它将工作分批在多个 Tick 中。这使 Unreal 组件创建保持在游戏线程上，这是注册 `UActorComponent` 实例的合适位置。

## 它可以创建护栏或侧面网格体吗？

可以。在 `FTrackSplineData` 中使用 `ExtraMeshStart`、`ExtraMesh`、`ExtraMeshEnd` 和 `ExtraMeshOffset`。

## 它可以创建跳跃或缺失的道路切片吗？

可以。使用 `JumpGapsByPoints`。间隙会压制段范围的道路和附加网格体。

## 它可以创建高度落差吗？

可以。使用 `StuntDropsByPoints`。不同高度的相邻无间隙段会创建落差墙。

## 它可以创建一直到地面的墙壁吗？

可以。启用 `bGenerateGroundWalls` 并配置追踪对象类型。程序化墙条从道路边缘向下追踪到配置的对象类型。

## 它会使地形变形吗？

会，在编辑器中。当指定了 `PaintLayer` 时，将 `DeformLandscapeNow` 用于高度，将 `PaintLandscapeLayerNow`（或面板 **Paint Layer**）用于叠加权重绘制。

## 它会绘制地形图层吗？

会，使用叠加 `max` 绘制针对单个全局 `PaintLayer` 进行绘制。在 Actor 上设置 `PaintLayer`，指定地形，然后运行 **Paint Layer**。权重混合的图层信息会减少道路下方的其他图层。使用 `bNoWeightBlend` 的图层信息可以绘制目标图层，但不保证减少其他图层。不支持：替换/清除模式、按段绘制图层，或在缩小绘制带时自动清除旧权重。

## 为什么验证阻止了我的构建？

对于破坏性的错误配置，例如缺失 `MainMesh` 或在没有追踪对象类型的情况下启用基于追踪的功能，Actor 会阻止构建。这可以保护现有的生成几何体不会在创建有效替代品之前被清除。

## 为什么我的墙壁缺失了？

常见原因是缺少追踪对象类型、没有追踪命中、`MinWallHeight` 太高、跳跃间隙切断了墙条，或在按段设置中禁用了 `bGenerateGroundWalls`。

## 它能安全地清理生成的组件吗？

能。生成的组件获得稳定的标签，清理过程扫描标签，而不是仅信任临时数组。

## 我可以保存样条线布局吗？

可以。指定 `SplinePointList` 并使用 `WriteSplineToDataAsset` / `ReadSplineFromDataAsset`。

## 我可以将它用于 Fab 产品或商业游戏吗？

可以，须遵守产品许可条款。本插件不授予您对与其一起使用的第三方网格体、材质或内容的权利。
