<!-- doc-provenance: product-facts.yml reconciled 2026-07-15; source AKDB:plugins/AsyncSplineBuilder/architecture.md -->
# 疑难解答

## Actor 没有构建任何内容

检查：

- 指定了 `MainMesh`。
- 样条线至少有两个点。
- 验证没有阻止构建。
- `bEditSpline` 没有意图明确地清除生成的组件。
- 生成的网格体没有被关卡可见性或 Actor 可见性隐藏。

## 构建被验证阻止

验证会阻止破坏性的错误构建。常见原因：

- 缺失 `MainMesh`。
- 启用了地面墙，但未配置地面墙追踪对象类型。
- 启用了地形吸附，但未配置地形追踪对象类型。
- 跳跃间隙或落差范围无效。

修复设置并再次运行 `RebuildTrack`。

## 连接器验证报告问题

当被动布局连接器指向缺失的 Actor、未知的布局 id、无效的样条线距离或不完整的连接器元数据时，会发生 Connector Validation Reports Issues。

在工作流面板或 Details 面板中修复连接器记录，然后再次运行 `Validate Layout Connectors`。连接器验证与几何体生成是分开的：连接器记录描述路线意图，本身不创建过渡网格体。

## 缺失连接器端点标签

在面板的 **Layout Connectors** 区域中启用 **Show Connector Debug**。如果仅出现连接器的一侧，请运行 **Validate Layout Connectors** 并纠正针对隐藏端点报告的缺失布局或超出范围的距离。端点是独立解析的，无效位置会被意图明确地忽略。

连接器标签仅限视觉。您无需重新构建轨道即可创建或刷新它们，纠正标签不会添加连接器道路几何体，也不会更改地形行为。

## 工作流面板打不开

通过 **Tools > Track Tools > Async Spline Builder** 打开它。如果菜单条目缺失：

- 重新构建编辑器目标
- 确认启用了 `AsyncSplineBuilderEditor` 模块
- 启用插件后重新启动编辑器
- 检查 Output Log 中的 `AsyncSplineBuilderEditor` 启动错误

面板仅限编辑器，在打包构建中不可用。

## 编辑器在 Rebuild 期间冻结

使用异步设置：

- `bUseAsyncBuild = true`
- 降低 `SegmentsPerTick`
- 在迭代时禁用昂贵的墙壁碰撞
- 减少 `GroundWallSubdivisions`

非常大的组件数量仍可能很昂贵，因为 Unreal 组件注册发生在游戏线程上。

## 附加网格体出现在错误的位置

检查：

- 网格体轴心和局部轴
- `ExtraMeshOffset`
- `bMirrorExtraMesh`
- 段数据回退到索引 `0`
- 起始/中间/结束数组是否包含不同的网格体

附加网格体使用与道路件相同的样条线间隔。

## 道路网格体过度拉伸

设置以下字段之一：

- `MeshInstances` 用于精确数量
- `RoadMeshLength` 用于显式件长
- `SegmentLength` 用于从期望间距自动计数

如果均未设置，则使用网格体边界 X。

## 闭合回路有不良缝隙

检查：

- 第一个和最后一个样条点的位置/切线
- 网格体轴心和平铺长度
- 闭合回路上 `StartMesh` 的使用
- 切线平滑设置

闭合回路构建到样条线长度的包裹段。

## 地面墙未出现

检查：

- 在 Actor 上启用了 `bGenerateGroundWalls`
- 按段 `GroundWallSettings.bGenerateGroundWalls`
- `GroundWallObjectsToHitForLineTrace`
- 按段 `TraceSettings.ObjectsToHit`
- 追踪长度
- `MinWallHeight`
- 跳跃间隙

如果追踪未命中，则使用备用深度。如果墙壁高度仍低于 `MinWallHeight`，则不创建任何切片。

## 地面墙跨越间隙

它们不应该跨越。如果您看到这种情况，请确认间隙范围使用段语义：

```text
[StartPointIndex, EndPointIndex)
```

另外运行自动化套件；`GroundWallGapStripValid` 涵盖了基本的墙条拆分行为。

## 地面墙宽度错误

宽度是从选定的道路网格体在 Y 上的边界派生的，除非 `TrackHalfWidth` 大于零。如果网格体边界没有代表性，请手动设置 `TrackHalfWidth`。

## 落差墙未出现

检查：

- 两个相邻段都有道路
- 边界不在跳跃间隙内
- 相邻段解析为不同的世界 Z 值
- 一侧设置了 `DropHeight` 或恒定 Z

针对基本落差墙行为运行 `AsyncSplineBuilder.DropWallCount`。

## 地形吸附不起作用

检查：

- 启用了 `bSnapMeshesToLandscape` 或 `bSnapPointsToLandscape`
- `ObjectsToHitForLandscapeLineTrace` 具有对象类型
- 地形碰撞对象类型与查询匹配
- `ActorsToIgnoreForGenerationTraces` 不包含目标
- 追踪长度到达表面

## 地形变形不起作用

检查：

- 指定了 `Landscape`
- 加载了编辑器模块
- 样条线具有有效点
- `NumberOfSubdivisionsForDeform` 大于零
- 至少启用了 `bRaiseHeights` 或 `bLowerHeights` 之一
- 道路与地形区域重叠

记住：变形是通过 `DeformLandscapeNow` 进行的手动编辑器操作。

## 地形材质图层未绘制

高度变形 (`DeformLandscapeNow`) 和图层权重绘制 (`PaintLandscapeLayerNow`) 是独立的操作。图层绘制需要在地形上注册有效的 `PaintLayer`。撤销由变形器事务所有；在面板上、CallInEditor 中以及使用活动的地形编辑图层测试撤销。

如果选定的图层信息使用 `bNoWeightBlend`，该操作应该警告。在那种设置下，目标图层可以接收绘制，但不保证道路下方的其他图层被减少。

## 生成的几何体在 Rebuild 后重复

生成的组件进行了标签清理。如果出现重复：

- 检查自定义代码是否创建了没有 `GeneratedTag` 的组件
- 检查修改后的组件是否被手动复制
- 运行 `CleanupRemovesAllTagged` 自动化

## 运行时异步未完成

检查：

- `bUseAsyncBuild = true`
- 世界定时器管理器正在 Tick
- Actor 有效且未被销毁
- `SegmentsPerTick` 至少为 `1`
- 验证在开始前没有中止

运行时泵在构建时使用 `SetTimerForNextTick` 重新装备自身。

## BuildPlugin 或编译失败并出现 Unity 碰撞

某些模块在匿名命名空间中定义了类似名称的助手。如果 Unity 分组组合了这些文件，MSVC 可能会报告重复定义。受影响的模块应该使用非 Unity 构建设置，例如 `bUseUnity = false`。

## 自动化未找到测试

检查：

- 构建了编辑器目标
- 启用了开发自动化测试
- 命令使用 `Automation RunTests AsyncSplineBuilder`
- 测试已编译到编辑器模块中

## 日志噪音太大

在日志中搜索：

```text
AsyncSplineBuilder
Result={Fail}
Result={Success}
TEST COMPLETE
```
