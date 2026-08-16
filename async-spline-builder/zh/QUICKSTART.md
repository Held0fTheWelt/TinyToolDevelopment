<!-- doc-provenance: product-facts.yml reconciled 2026-07-15; source AKDB:plugins/AsyncSplineBuilder/architecture.md -->
# 快速入门指南

本指南带您从安装到获得**直观成果**：沿您控制的样条线生成道路/轨道网格体。Async Spline Builder 独立工作 — 无需其他插件。

## 完成本指南后您将获得什么

关卡中的 `Spline Generating Actor` 包含一条由样条网格体段构建的道路，您可以通过移动样条点来重新塑形并根据需要重新构建。

## 要求

- Unreal Engine 5 编辑器和打开的关卡。
- 至少一个沿其局部 X 轴平铺的**道路网格体**（参阅用户手册中的步骤 3 / 网格体创作）。您可以从项目中使用任何平铺网格体开始。
- 无第三方软件、帐户或运行时。参阅 [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md)。

## 1. 安装与启用

1. 从 Fab 库将 **AsyncSplineBuilder** 添加到项目（或安装到引擎）。
2. 打开 **Edit → Plugins**，启用 **AsyncSplineBuilder**，并在收到提示时重新启动。

## 2. 打开面板（首个成果）

1. 打开或创建一个关卡。
2. 打开 **Tools → Track Tools → Async Spline Builder**。面板包含 **Build**、**Segments** 和 **Terrain** 选项卡。

## 3. 实际操作示例：构建轨道

1. 在 **Build** 选项卡上，单击 **Create Actor**（这将生成一个 `ASplineGeneratingActor`），或选择现有 Actor 并单击 **Use Selection**。
2. 在 **Setup** 中，将平铺网格体指定给 **MainMesh**（必需）。可选指定 **StartMesh** 和 **EndMesh**。
3. 在视口中，移动 Actor 的样条点以塑造路径。
4. 单击 **Validate**（这将检查是否设置了 `MainMesh` 以及样条线是否可构建）。
5. 单击 **Build Now**。

**预期输出：** Actor 沿样条线生成 `USplineMeshComponent` 道路段。移动一个样条点并单击 **Rebuild** 以查看道路更新。

> 对于长轨道，启用 **Use Async Build** 并设置 **SegmentsPerTick**，以便跨 Tick 分批生成并保持编辑器响应。使用 **Cancel** 停止正在进行的异步构建。

## 4. 进阶（可选）

- **Segments** 选项卡：按段网格体、跳跃间隙 (`JumpGapsByPoints`) 和特技落差。
- **Terrain** 选项卡：吸附到地形、高度变形和程序化**地面墙** (`bGenerateGroundWalls`)。参阅 [LandscapeAndWalls.md](LandscapeAndWalls.md)。
- **数据资产：** 通过 `WriteSplineToDataAsset` / `ReadSplineFromDataAsset` 保存/加载布局。

## 5. 后续步骤

- 完整工作流、按段数据、间隙、落差、墙壁、地形变形: [UserManual.md](UserManual.md)。
- 设置参考: [SettingsReference.md](SettingsReference.md)。
- 疑难解答与修复: [TROUBLESHOOTING.md](TROUBLESHOOTING.md) 和 [FAQ.md](FAQ.md)。
