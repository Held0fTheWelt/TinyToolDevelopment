<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/PerformancePresetWizard/architecture.md -->
# Performance Preset Wizard 文档

Performance Preset Wizard 用于创建可在 Unreal Editor 中编写和复核的运行时目标性能预设，然后通过编辑器向导、C++、Blueprint 或附带的运行时选择器控件手动应用。预设将引擎的可扩展性级别（Scalability）与可选的控制台变量（CVar）覆盖结合起来，使团队能够在硬件分级、VR 预算、截图设置、笔记本电脑开发设置以及项目特定的质量目标之间快速切换。

本文件夹包含随插件附带的完整文档。

## 从这里开始

- [BUYER_GUIDE.md](BUYER_GUIDE.md)：面向买家的概述、包含的价值以及常见的生产工作流程。
- [UserManual.md](UserManual.md)：打开向导、应用预设、恢复先前设置以及配置启动预设的完整编辑器工作流程。
- [RuntimeUsage.md](RuntimeUsage.md)：运行时子系统、Blueprint API、备份历史记录、存储提供程序和选择器控件。
- [FAQ.md](FAQ.md)：针对 Fab 买家、设计师和技术美术的实用解答。

## 参考指南

- [PresetAuthoringGuide.md](PresetAuthoringGuide.md)：如何设计可靠的预设、选择可扩展性级别以及编写 CVar 覆盖。
- [RuntimeUsage.md](RuntimeUsage.md)：打包后的游戏如何手动应用和恢复预设资产。
- [SettingsReference.md](SettingsReference.md)：每个插件设置和资产字段的默认值与推荐用法。
- [SamplePresetsReference.md](SamplePresetsReference.md)：包含的 `DA_*` 示例预设以及如何调整它们。
- [CodeDocumentation.md](CodeDocumentation.md)：源码结构、公共契约、实现说明和扩展点。
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md)：常见的设置、资产、CVar 和构建问题及解决方案。

## 包含的资源

- [Screenshots/](Screenshots)：轻量级文档图解，展示向导工作流程、预设编写以及恢复/启动行为。
- `../Content/DA_*.uasset`：示例预设数据资产，涵盖桌面、VR、类主机、移动端原型、笔记本电脑开发和电影级展示等使用场景。
- `../PerformancePresetWizard_Changelog.txt`：随插件附带的发行说明。

## 快速编辑器工作流程

1. 启用插件，并在 Unreal 提示时重启编辑器。
2. 打开 **Tools > Performance > Performance Preset Wizard**。
3. 从列表中选择一个预设。如果刚创建或导入了新的预设资产，请使用 **Refresh** 刷新列表。
4. 复核显示名称、描述、目标平台、可扩展性摘要和 CVar 覆盖。
5. 点击 **Apply Preset**。向导会先应用可扩展性设置，然后再应用有效的 CVar 覆盖。
6. 如果需要返回到紧接上次应用前捕获的设置，请点击 **Restore Previous**。
7. 如果希望在打开编辑器时自动应用某个预设，请在 Project Settings 中启用 **Apply on Editor Startup**。

## 快速运行时工作流程

1. 在编辑器中编写和复核 `UPerformancePresetAsset` 预设。
2. 将运行时预设添加到 **Project Settings > Plugins > Performance Preset Wizard Runtime**，或直接传递给运行时子系统。
3. 在 C++ 或 Blueprint 中，从当前的 `GameInstance` 获取 `UPerformancePresetRuntimeSubsystem`。
4. 调用 `ApplyRuntimePreset` 执行显式的用户或项目操作。
5. 当项目需要撤销功能时，使用 `GetBackupHistory`、`RestoreLatestBackup` 或 `RestoreBackupById`。
6. 使用 `UPerformancePresetRuntimeSelectorWidget` 作为测试菜单或选项屏幕的可替换 UMG 选择器控件。

## 快速 CVar 格式

批量 CVar 编辑器每行接受一个覆盖项：

```text
r.ScreenPercentage=85
r.Nanite=1
r.Lumen.Reflections.Allow=0
r.Shadow.Virtual.Enable=1,editor
```

规则：

- 忽略空行。
- 以 `#` 或 `//` 开头的行被视为注释。
- `Name=Value` 创建普通覆盖。
- `Name=Value,editor` 将覆盖标记为仅编辑器有效（editor-only）。
- 未知的 CVar 会被报告，但不会阻止应用预设的其余部分。
- 空名称或空值将被跳过。

## 可扩展性级别（Scalability）

Performance Preset Wizard 遵循 Unreal Engine 的标准质量分级：

- `0`：Low
- `1`：Medium
- `2`：High
- `3`：Epic
- `4`：Cinematic

本插件涵盖了 UE5 当前的可扩展性类别，包括可视距离、抗锯齿、阴影、全局光照、反射、后期处理、纹理、特效、植物、着色和地形。

## 重要范围说明

Performance Preset Wizard 不是基准测试框架、硬件检测器、自动优化器，也不能替代 Device Profiles。在将预设作为生产默认值之前，应在目标项目、地图和目标平台上进行验证。
