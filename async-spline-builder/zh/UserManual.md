<!-- doc-provenance: product-facts.yml reconciled 2026-07-15; source AKDB:plugins/AsyncSplineBuilder/architecture.md -->
# 用户手册

本手册解释如何在 Unreal Editor 中使用 Async Spline Builder 以及主要功能如何结合在一起。

## 目的

Async Spline Builder 从可编辑样条线创建生成组件。典型输出是由 `USplineMeshComponent` 段组成的道路或轨道，包含可选的额外样条网格体和程序化墙壁网格体。

Actor 可以同步重新构建或分批重新构建。分批处理使长轨道上的编辑器保持响应，并且也可以在运行时通过下一 Tick 定时器泵使用。

## 打开与启用

1. 打开 **Edit > Plugins**。
2. 启用 **AsyncSplineBuilder**。
3. 如果收到提示，请重新启动编辑器。
4. 打开或创建一个关卡。
5. 打开 **Tools > Track Tools > Async Spline Builder**。

该插件包含运行时和编辑器模块。Actor 具备运行时能力；工作流面板和地形变形工具仅限编辑器。

## 工作流面板

Async Spline Builder 面板是配置正常轨道的推荐方式。它避免了将常见工作流分散在多个 Details 类别中。

面板按选项卡组织：

- **Build**：Actor 选择、网格体设置、验证/构建/重新构建/取消、异步分批、闭合回路、调试点或段标签，以及可选的布局连接器端点标签。
- **Segments**：按段 `TrackSplineData`、段行创建、跳跃间隙和特技落差。
- **Terrain**：地形吸附、地形指定、图层绘制设置、高度变形、叠加图层绘制和地面墙。

对于工作流面板中意图明确未重复的高级数组和不常用设置，请使用 Details 面板。

## 基本 Actor 设置

1. 在工作流面板中，按 **Create Actor** 或选择现有的 `ASplineGeneratingActor` 并按 **Use Selection**。
2. 在 **Setup** 中指定 `MainMesh`。
3. 可选指定 `StartMesh` 和 `EndMesh`。
4. 在视口中移动样条点。
5. 按 **Validate**。
6. 按 **Build Now** 或 **Rebuild**。

`MainMesh` 是必需的。验证会阻止没有它的构建，因此现有的生成几何体不会被清除并替换为空。

## 网格体创作期望

道路网格体应该：

- 沿局部 X 轴平铺。
- 具有合理的 Y 范围，因为网格体边界用于派生道路半宽。
- 使用一致的轴心。
- 避免隐藏的碰撞复杂性，除非需要碰撞。

如果网格体边界没有代表性，请手动设置 `GroundWallSettings.TrackHalfWidth`。

## 编辑样条线

使用标准 Unreal 样条线编辑工具。有用字段：

- `bClosedLoop`：将最后一个点连接到第一个点。
- `SplinePointType`：控制点插值行为。
- `SplineZOffset`：垂直偏移样条组件。
- `bShowPointNumbers`：显示点索引。
- `bShowSegmentNumbers`：显示段索引。
- `bShowSplineVisualizationWidth`：显示更宽的编辑器样条线。

点和段编号是生成的调试组件，并由用于生成几何体的相同标签系统进行清理。

## Track Shape Editor

当您需要紧凑的多布局创作界面而不是仅编辑 Actor 的原始样条点时，请打开 **Tools > Track Tools > Track Shape Editor**。该编辑器在原生 `track_shape.v1` 文档上工作，并可以将编译的主布局、维修道布局、替代布局或服务道路布局应用于选定的 `ASplineGeneratingActor`。

**Designer Tools** 区域提供日常编辑控件：

- 添加维修道、替代或服务道路布局
- 复制或删除选定的非主布局
- 更改布局种类和闭合回路状态
- 选择上一个或下一个布局、锚点或段
- 编辑选定锚点的 X/Y 坐标
- 添加、插入或删除锚点，同时保持有效的最小锚点数
- 添加或删除显式段、在直线和贝塞尔曲线之间切换选定段，或为选定布局重新构建顺序段

视口支持直接锚点选择和拖动。布局列表和检查器反映相同的选择，JSON 区域仍可以导入或导出底层文档以供审查或源代码控制。

在应用复杂编辑之前使用 **Validate**。仅在选择或创建目标 Actor 后使用 **Apply**，因为应用会修改 Actor 的可编辑样条线/布局状态。

## 构建

使用：

- **Build Now** / `BuildTrack`：同步完全构建。
- **Rebuild** / `RebuildTrack`：如果 `bUseAsyncBuild` 为真则为异步，否则为同步。
- **Cancel** / `CancelAsyncBuild`：取消活动或挂起的异步构建。

Actor 根据计算出的 `FTrackBuildPlan` 重新构建。在生成开始之前，计划决定段范围、件数、落差状态、跳跃间隙、选定的道路网格体和附加网格体数量。

## 异步构建

设置：

- `bUseAsyncBuild`：启用分批构建。
- `SegmentsPerTick`：每个 Tick 处理的生成道路/附加网格体件数。
- `bAutoRebuildOnConstruction`：在发生构建更改后安排重新构建。

编辑器世界在清除或准备生成组件之前对构建更改进行防抖动，这使您在拖动点时现有的样条几何体保持可编辑。运行时世界使用下一 Tick 定时器泵。两条路径调用相同的件级构建器，因此行为保持一致，而不会让一个长样条段独占一个帧。

## 按段数据

`TrackSplineData` 配置每个段。如果条目少于样条段，则使用索引 `0` 作为备用。

重要字段：

- `RoadMesh`：可选的段特定道路网格体。
- `MeshInstances`：段的网格体件数的精确数量。
- `RoadMeshLength`：期望的道路网格体覆盖长度。
- `SegmentLength`：未设置 `RoadMeshLength` 时的备用间距。
- `ExtraMeshStart`、`ExtraMesh`、`ExtraMeshEnd`：附加样条网格体。
- `ExtraMeshOffset`：附加网格体插槽的横向偏移。
- `GroundWallSettings`：按段地面墙行为。

## 附加网格体

附加网格体遵循与道路件相同的样条件间隔。它们对于护栏、马路牙子、栅栏和装饰性侧面对象很有用。

起始、中间和结束数组允许在段边界处使用不同的网格体。附加网格体被标记为 `AsyncSplineBuilder.ExtraMesh`，而不是 `AsyncSplineBuilder.RoadMesh`。

## 间隙 (Gaps)

将条目添加到 `JumpGapsByPoints` 以压制点索引范围的道路和附加网格体生成。

范围是段范围：

```text
[StartPointIndex, EndPointIndex)
```

例如，`StartPointIndex = 2`、`EndPointIndex = 4` 压制段 `2` 和 `3`。

## 落差 (Drops)

将条目添加到 `StuntDropsByPoints` 以向下移动段范围或移动到恒定的世界 Z。

字段：

- `DropHeight`：相对 Z 偏移。负值将道路向下移动。
- `bUseConstantGapHeight`：使用绝对世界 Z 而不是偏移。
- `ConstantGapWorldZ`：启用时的绝对高度。

如果两个相邻的无间隙段在不同的高度相遇，Actor 会在它们之间创建一个落差墙。

## 地面墙

启用 `bGenerateGroundWalls` 以从道路边缘向下生成程序化墙条。

地面墙：

- 使用网格体派生或覆盖的道路宽度。
- 遵循按段墙壁设置。
- 在跳跃间隙和无效采样处拆分墙条。
- 可以是单面或双面。
- 使用基于距离和实际墙壁高度的 UV。

详细设置请参阅 [LandscapeAndWalls.md](LandscapeAndWalls.md)。

## 地形吸附

网格体吸附：

- `bSnapMeshesToLandscape`
- `ObjectsToHitForLandscapeLineTrace`
- `LineTraceLength`

点吸附：

- `bSnapPointsToLandscape`
- `bTangentPointsUpdate`

使用 `ActorsToIgnoreForGenerationTraces` 从追踪查询中排除辅助网格体或临时对象。

## 地形变形

仅限编辑器的变形通过 `DeformLandscapeNow` 运行。

要求：

- 指定了 `Landscape`。
- 有效的样条线。
- 合理的 `FallOff` 和 `NumberOfSubdivisionsForDeform`。
- 启用了 `bRaiseHeights` 和/或 `bLowerHeights`。

高度：`DeformLandscapeNow` 或面板 **Deform Height**。图层绘制：指定 `PaintLayer`，在面板中调整 `PaintHalfWidth` / `PaintFallOff`，然后运行 `PaintLandscapeLayerNow` 或面板 **Paint Layer**。绘制是叠加性的；当您缩小衰减时，它不会清除先前较宽的区域。`PaintFallOff = 0` 是硬边缘。如果选定的图层信息使用 `bNoWeightBlend`，面板/验证会警告其他地形图层不保证在道路下方被减少。

## 何时使用 Details 面板

工作流面板是意图明确地保持聚焦的。当您需要编辑以下内容时，请使用 Details 面板：

- 按段 `ExtraMeshStart`、`ExtraMesh`、`ExtraMeshEnd` 和 `ExtraMeshOffset` 数组
- 详细的 `FGroundWallSettings`，包括追踪、UV、材质、碰撞和宽度覆盖
- 用于地形吸附和墙壁生成的追踪对象数组
- 样条点数据资产读/写字段
- 高级调试和构建设置

## 布局连接器

Build 选项卡包含用于被动路线元数据的 **Layout Connectors** 区域。连接器将源布局/距离链接到目标布局/距离，并存储语义种类，例如 `PitEntry`、`PitExit`、`Link` 或 `ServiceAccess`。您也可以键入自定义种类；自定义非空种类验证为警告而不是错误。

使用 **Pit Entry** 添加从 `Main` 到第一个维修道布局的默认连接器。使用 **Pit Exit** 添加从第一个维修道布局返回 `Main` 的默认连接器。该区域中的 **Validate** 运行仅限连接器的验证。

连接器编辑不会重新构建道路，也不会删除生成的几何体。它们也不会自动创建过渡网格体、剪切样条线、将地形变形扩展到维修道，或启用特殊的维修道渲染器。

启用 **Show Connector Debug** 以在有效的连接器端点处放置仅限视觉的文本标记。标记标识连接器索引和种类、是 `From` 还是 `To` 角色、其布局 id 以及其配置的距离；其大小遵循 `DebugTextWorldSize`。

缺失的布局和超出样条线范围的距离会被忽略；使用 **Validate** 检查这些连接器问题。

标记使用 `UTextRenderComponent` 调试输出，不添加道路、附加网格体、地面墙或落差墙几何体。在启用复选框时编辑连接器会刷新标记。禁用 **Show Connector Debug** 仅删除连接器标签。切换或刷新这些标签不会重新构建轨道、更改生成的道路数量、扩展地形行为或影响构建验证门。

## 数据资产工作流

将 `USplinePointListAsset` 指定给 `SplinePointList`。

使用：

- `WriteSplineToDataAsset`：保存当前样条点。
- `ReadSplineFromDataAsset`：加载样条点。

这对于独立于生成组件保留轨道布局非常有用。

## 推荐的生产工作流

1. 构建一条短测试样条线。
2. 验证道路网格体边界和平铺。
3. 添加段数据。
4. 添加附加网格体。
5. 添加间隙和落差。
6. 配置地面墙追踪。
7. 仅在道路形状稳定后运行地形变形。
8. 在发布前运行自动化测试。
9. 在 PIE 和打包的运行时中测试关卡。

## 本插件不做的事项

- 它不提供替换/清除或按段地形绘制模式。
- 它不会为您创作网格体。
- 它不保证在每个地形上都有完美的地形路肩。
- 它不会自动生成连接器过渡道路网格体。
- 它不能替代最终轨道修饰的手工艺术指导。
