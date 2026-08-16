<!-- doc-provenance: product-facts.yml reconciled 2026-07-15; source AKDB:plugins/AsyncSplineBuilder/architecture.md -->
# 设置参考

本参考描述了大多数用户在配置 `ASplineGeneratingActor` 时需要的设置。

## 工作流面板映射

打开 **Tools > Track Tools > Async Spline Builder** 以获得以任务为中心的 UI。面板分为 **Build**、**Segments** 和 **Terrain** 选项卡。它涵盖 Actor 选择、网格体设置、验证、构建和重新构建命令、异步分批、闭合回路状态、调试标签、段行助手、跳跃间隙、特技落差、地形指定、图层绘制设置、高度变形、吸附切换和 Actor 级地面墙。

当某个设置仅在 Details 面板中公开或当您需要确切的字段行为时，请使用本参考。按段附加网格体数组、详细地面墙设置、追踪对象数组、碰撞标志、UV 控件和数据资产字段仍属于 Details 面板的高级设置。

## 网格体设置

### StartMesh

用于开放轨道上第一个生成的道路件的可选网格体。如果未设置，则使用选定的段道路网格体。

### MainMesh

必需的备用道路网格体。如果缺失，验证会阻止生成。

### EndMesh

用于开放轨道上最后一个生成的道路件的可选网格体。如果未设置，则使用选定的段道路网格体。

## TrackTools

### bEditSpline

启用时，生成的组件会被清除，且在构建期间仅样条线/调试编辑保持活动状态。在不重新构建网格体的情况下塑造样条线形状时使用此功能。

### bShowSegmentNumbers / bShowPointNumbers

为段或点索引创建调试文本组件。这些组件被标记并与其他生成的组件一起被清理。

### bShowLayoutConnectorDebug

布尔值，默认 `false`。面板 **Layout Connectors** 区域中的 **Show Connector Debug** 复选框控制相同的设置。启用时，编辑器为每个独立可解析的连接器端点显示文本标记。每个标签包括连接器索引和种类、`From` 或 `To` 角色、布局 id 和配置的距离；其大小遵循 `DebugTextWorldSize`。

缺失的布局和超出范围的距离会被忽略，而不是显示在错误位置。切换或刷新连接器标签纯粹是视觉上的：它不会重新构建轨道、创建连接器道路几何体、更改生成的道路数量或扩展地形行为。禁用该设置仅删除连接器标签。

### bShowSplineVisualizationWidth / SplineVisualizationWidth

控制编辑器样条线可视化宽度。

### bSnapPointsToLandscape

将样条点移动到追踪命中位置。需要 `ObjectsToHitForLandscapeLineTrace`。

### bTangentPointsUpdate

将点吸附到地形后更新切线。

### bMirrorExtraMesh

通过翻转其 X 缩放来镜像附加网格体。

### SplinePointType

在样条线更新期间应用的样条点类型。`CurveCustomTangent` 是道路的好默认值。

### SplineZOffset

对样条组件应用垂直偏移。

### TrackSplineData

按段数据。如果某个段不存在条目，则使用条目 `0` 作为备用。

### AdditionalLayouts

维修道、替代路线、服务道路和装饰样条线的可选路线记录。遗留 Actor 样条线仍是 `Main` 布局外观。

### LayoutConnectors

两个布局距离之间的被动语义链接。每个连接器存储：

- `FromLayoutId` / `FromDistance`
- `ToLayoutId` / `ToDistance`
- `ConnectorKind`

已知种类为 `PitEntry`、`PitExit`、`Link` 和 `ServiceAccess`。`ConnectorKind` 仍是开放的 `FName`；允许使用自定义非空种类并验证为警告。空种类、缺失的布局、错误的距离以及同一布局上近乎相等的端点是由连接器验证报告的连接器范围错误，但连接器错误不会阻止几何体重新构建。

连接器行不生成过渡网格体、不自动重新构建，也不更改地形变形行为。

## TrackSplineData

### RoadMesh

段的可选道路网格体。回退到 `MainMesh`。

### MeshInstances

段中道路件数的精确数量。当大于零时，它会覆盖基于长度的自动计数。

### SegmentLength

未设置 `RoadMeshLength` 时的间距备用。使用大于 `1` 的值。

### RoadMeshLength

显式期望的道路网格体覆盖长度。当网格体边界与视觉平铺长度不匹配时使用此功能。

### ExtraMeshStart / ExtraMesh / ExtraMeshEnd

第一件、中间件和最终件的可选附加网格体数组。

### ExtraMeshOffset

每个附加网格体插槽的横向偏移。

### GroundWallSettings

按段墙壁生成、追踪、宽度、碰撞和 UV 设置。

## Options

### bClosedLoop

将最后一个样条点连接回第一个点。

### bEnableCollision

为生成的道路和程序化墙壁组件启用碰撞。

### bCastShadow / bCastContactShadow

控制生成的样条网格体阴影标志。

### bMirrorMesh

镜像道路网格体缩放。

### bSnapMeshesToLandscape

将生成的道路和附加网格体端点吸附到追踪命中位置。需要追踪对象类型。

## Landscape

### Landscape

仅限编辑器的变形所使用的地形代理。

### ActorsToIgnoreForGenerationTraces

吸附和墙壁追踪所忽略的 Actor。

### bSnapTraceLandscapeOnly

如果为真，吸附追踪仅接受地形命中。

### ObjectsToHitForLandscapeLineTrace

网格体和点吸附所使用的对象类型。启用吸附时必需。

### FallOff

道路宽度之外的距离，高度变形在该距离内平滑过渡回现有地形。

### NumberOfSubdivisionsForDeform

地形变形的样条线采样分辨率。较高的值可以改善拟合，但会增加开销。

### bRaiseHeights / bLowerHeights

控制变形是否可以抬高和/或降低地形采样。

### PaintHalfWidth

图层绘制的全权重半宽 (cm)。`0` 在每个变形采样处使用道路半宽。

### PaintFallOff

图层绘制的平滑阶梯衰减距离 (cm)。独立于高度 `FallOff`。`0` 在 `PaintHalfWidth` 之外给出没有软边缘的硬边缘。

### PaintLayer

由 `PaintLandscapeLayerNow` / 面板 **Paint Layer** 沿道路绘制的 `ULandscapeLayerInfoObject`。必须在目标地形上注册。如果图层信息使用 `bNoWeightBlend`，目标图层仍可接收绘制，但不保证道路下方的其他材质图层被减少。

### LandscapeEditLayerName

在地形配置支持的情况下用于地形高度编辑的编辑图层名称。

### LineTraceLength

地形吸附的追踪深度。

## Async Build

### bUseAsyncBuild

启用分批重新构建。

### SegmentsPerTick

每个 Tick 处理的异步工作单元数量。一个工作单元是一个生成的道路或附加网格体件，因此具有许多件的长样条段分布在多个 Tick 中，而不是一次性全部生成。为了保持响应性，请从低值开始，并在测试后增加。

### bAutoRebuildOnConstruction

在构建更改后安排重新构建。

## Ground Walls

### bGenerateGroundWalls

启用程序化地面墙生成。

### GroundWallSubdivisions

沿样条线的墙壁采样数。较高的值生成更平滑的墙壁和更多的几何体。

### GroundWallOutset

超出派生道路半宽的额外水平偏移。

### GroundWallFallbackDepth

当墙壁追踪未命中时使用的深度。

### bGroundWallsDoubleSided

添加反向三角形，使墙壁从两侧渲染。

### GroundWallObjectsToHitForLineTrace

当按段追踪设置为空时，地面墙的默认追踪对象类型。

## GroundWallSettings

### bGenerateGroundWalls

按段墙壁启用。

### bGenerateBothSides

如果为假，则为该段压制左侧。

### TrackHalfWidth

手动半宽覆盖。留 `0` 以从选定的道路网格体边界派生宽度。

### MinWallHeight / MaxWallHeight

跳过微小的墙壁并限制非常大的墙壁。

### bCreateCollision

控制程序化墙壁碰撞，也由 Actor `bEnableCollision` 门控。

### TraceSettings

按段追踪对象类型、追踪长度和追踪复杂性。

### UVSettings

按段墙壁 UV 平铺和翻转。

## Drop Walls

### DropWallMaterial

应用于生成的落差墙的材质。

### DropWallUVWorldUnitsU / DropWallUVWorldUnitsV

落差墙的世界单位 UV 平铺。

## 推荐基线

- `bUseAsyncBuild = true`
- `SegmentsPerTick = 24`
- `bAutoRebuildOnConstruction = true`
- 指定了 `MainMesh`
- 除非网格体边界错误，否则 `RoadMeshLength = 0`
- 除非网格体边界错误，否则 `TrackHalfWidth = 0`
- 在启用墙壁之前配置了地面墙追踪对象类型
- 在道路形状稳定后手动运行地形变形
