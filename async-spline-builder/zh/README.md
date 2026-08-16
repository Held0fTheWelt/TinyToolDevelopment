<!-- doc-provenance: product-facts.yml reconciled 2026-07-15; source AKDB:plugins/AsyncSplineBuilder/architecture.md -->
# Async Spline Builder 文档

Async Spline Builder 生成道路、赛道、管道、轨道、墙壁和侧面对象的样条网格体，不会导致编辑器大幅卡顿。它支持同步构建、编辑器异步分批、运行时异步分批、按段网格体计划、可选的地面墙、特技间隙、落差墙、样条点数据资产，以及仅限编辑器的地形高度变形加叠加图层绘制。

本文件夹包含随插件 delivered 的文档。

## 从这里开始

- [BUYER_GUIDE.md](BUYER_GUIDE.md)：产品级概述、工作流、优势和限制。
- [UserManual.md](UserManual.md)：从首次 Actor 放置到重新构建的完整编辑器工作流。
- [FAQ.md](FAQ.md)：Fab 准备就绪的常见问题解答。

## 参考

- [SettingsReference.md](SettingsReference.md)：每个重要的 Actor 设置和推荐基线。
- [LandscapeAndWalls.md](LandscapeAndWalls.md)：吸附、高度变形、地面墙、间隙和落差墙。
- [TechnicalOverview.md](TechnicalOverview.md)：维护者级架构和构建流程。
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md)：常见设置、构建、追踪和几何体问题。

仅限维护者的审计、完成注释、自动化命令、遗留注释和发布检查清单可能存在于源存储库中，但已从买家软件包中排除。

## 快速工作流

1. 启用插件并在需要时重新启动编辑器。
2. 打开 **Tools > Track Tools > Async Spline Builder**。
3. 从工作流面板放置或选择一个 `ASplineGeneratingActor`。
4. 在面板设置区域指定 `MainMesh`。
5. 在视口中编辑 `TrackSpline` 点。
6. 使用 **Build Now** 进行立即构建，或使用 **Rebuild** 进行异步分批。
7. 在进行高级按段编辑之前，使用段助手创建按段行。
8. 可选：在 Details 面板中启用地面墙并配置追踪对象类型。
9. 可选：指定地形，运行 **Deform Height**，然后运行 **Paint Layer**（需要在 Actor 上设置 `PaintLayer`）以进行叠加权重绘制。

## 主要功能

- 沿样条线生成道路或轨道网格体。
- Track Shape Editor 用于原生路线/布局点创作，带有用于布局、锚点和段的设计师控件。
- Validate Layout Connectors 用于在信任路线关系之前审查被动 `PitEntry`、`PitExit`、`Link`、`ServiceAccess` 或自定义连接器元数据。
- Apply Layout Connector 用于添加或更新被动布局关系记录，而不创建隐藏的网格体分支。
- 具有 `SegmentsPerTick` 的编辑器异步重新构建。
- 使用下一 Tick 定时器泵的运行时异步重新构建。
- 按段网格体选择和网格体长度计划。
- 用于护栏、障碍物、栅栏、管道或细节网格体的起始、中间和结束附加网格体。
- 压制道路和侧面网格体的特技间隙。
- 高度阶梯之间的落差区域和程序化落差墙。
- 向下追踪到地形或其他配置的对象类型的程序化地面墙。
- 基于标签的生成组件清理，经得起陈旧数组和构建重新构建的考验。
- 通过 `USplinePointListAsset` 进行样条点保存/加载。
- 仅限编辑器的地形高度变形加叠加全局图层绘制。
- 针对最高风险行为的自动化测试。

## 支持的运行时定位

运行时模块包含 Actor、样条网格体生成、地面墙生成、落差墙生成、数据资产访问和运行时异步泵。

编辑器模块包含工作流面板、仅限编辑器的地形变形和图层绘制，以及编辑器选择助手。打包的游戏可以构建样条网格体和程序化墙壁，但地形高度/权重编辑和工作流面板仅限编辑器。

## 编辑器工作流面板

主要的编辑器界面是 **Tools > Track Tools > Async Spline Builder**。它将常见工作流分组到 **Build**、**Segments** 和 **Terrain** 选项卡中，使日常任务保持紧凑而不会隐藏验证状态。

当路线需要原生点/布局创作时使用 Track Shape Editor，当维修道、服务通道或替代路线需要显式关系元数据时使用布局连接器控件。

日常工作请使用面板。高级原始字段（例如按段附加网格体数组、详细墙壁 UV 设置、追踪对象数组、自定义碰撞设置和实验性字段）请使用 Unreal Details 面板。

## 重要限制

- 地形：当设置了 `PaintLayer` 时的高度变形加**叠加全局**图层权重绘制（`PaintLandscapeLayerNow` 或面板 **Paint Layer**）。未实现替换/清除绘制模式。
- 地形变形是一次性编辑器操作，不是每次轨道重新构建的自动步骤。
- 复杂的生产地形仍需要人工 QA，特别是在急弯、非常陡峭的地形和混合按段墙壁设置的情况下。
- 运行时异步自动化通过确定性测试钩子覆盖；仍建议对发布地图进行完整的 PIE 定时器世界集成测试。

## 验证

对于本地软件包验证测试，请为您项目构建编辑器目标，并从 Unreal 的 Automation 工具中运行 AsyncSplineBuilder 自动化组。请将维护者特定的命令路径保存在本地发布说明中，而不是交付的买家软件包中。

## 推荐的首次生产测试

首先使用较短的开放测试样条线，然后是闭合回路，最后是真实轨道。保持 `bUseAsyncBuild` 处于启用状态，从 `SegmentsPerTick = 2` 开始，仅在确认编辑器响应能力后提高它。在启用吸附或地面墙之前配置追踪对象类型，因为验证会意图明确地阻止那些会破坏旧几何体且无法生成有效替代品的构建。

## 法律声明

Async Spline Builder 根据产品分发中包含的许可条款提供。本插件不授予对与生成轨道一起使用的第三方网格体、材质、地形或内容的权利。
