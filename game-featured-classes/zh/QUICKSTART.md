---
lang: zh
title: GameFeaturedClasses Quick Start
audience: [end_user]
owner_ref: plugin:GameFeaturedClasses
applies_to:
  component: GameFeaturedClasses
preconditions:
  - Unreal Engine project open with the plugin package available
  - Edit > Plugins can enable GameFeaturedClasses
expected_result:
  text: GameFeaturedClasses runtime module is enabled and loads after editor restart.
version:
  since: "1.0"
---
# 快速入门

本指南介绍如何安装并启用 **GameFeaturedClasses**，并验证运行时模块是否成功加载。版本 `1.0.1` 是一个**模块外壳**：它包含描述符、打包元数据、图标和更新日志。它尚未提供游戏玩法类、Game Feature 操作或编辑器工作台。

## 完成本指南后您将拥有

项目中启用了该插件，且在编辑器重启后的模块列表中出现了 `GameFeaturedClasses` 运行时模块。

## 要求

- Unreal Engine 5.4–5.8（打包发布矩阵）。
- 外壳无需其他 Tiny Tool 插件。
- 无需第三方软件、账户或外部运行时。请参阅 [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md)。

## 1. 安装并启用

1. 从 Fab 获取 **GameFeaturedClasses** 并将其添加到项目中（或安装至引擎的 Plugins 目录下）。
2. 打开 **编辑 → 插件**，搜索 **GameFeaturedClasses**，启用它，并在提示时重启。

## 2. 确认模块边界

重启后，验证运行时模块已加载（输出日志 / 模块管理器）。公共模块接口为 `FGameFeaturedClassesModule`，位于 `Source/GameFeaturedClasses/Public/GameFeaturedClasses.h`，仅包含 `StartupModule` / `ShutdownModule`。

## 3. 示例：外壳冒烟测试

1. 创建或打开一个基于 Unreal Engine 5.4+ 的项目。
2. 按上述步骤启用插件并重启。
3. 在输出日志中，过滤加载后 `GameFeaturedClasses` 的模块启动噪音。

此包版本中没有特色类注册表 UI，也没有可运行的示例 Game Feature 操作。调用不存在的工作台菜单预计会失败，因为这些界面**尚不可用**。

## 预期结果

- 插件在 **编辑 → 插件** 中显示为已启用。
- 运行时模块启动和关闭无需依赖对等的 Tiny Tool 插件。
- 从此包中不会在 Content Browser 中出现游戏玩法特色类资产（未提供）。

## 后续步骤

- 阅读 [UserManual.md](UserManual.md) 了解当前与目标边界。
- 阅读 [FAQ.md](FAQ.md) 了解范围相关问题。
- 在后续包提供这些类和编辑器界面之前，将高级 GameFeature Workbench 行为视为目标架构。

## 需牢记的边界

- 不要将项目游戏玩法类添加到此插件文件夹中，期望它们在 1.0.1 中作为 GFC 内容发布。
- 不要仅为了“解锁”尚未打包的工作台而启用对等插件。
- 当后续版本提供特色类时，请在此快速入门指南中更新真实的类名，并提供来自该版本的示例。
