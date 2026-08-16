<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/PerformancePresetWizard/architecture.md -->
# 快速入门指南

本指南将带您从安装一步步获得**实际结果**：将性能预设应用到您的编辑器（可扩展性 + 控制台变量），并且您可以通过一次点击完全恢复。Performance Preset Wizard 可独立运行。

## 完成本指南后您将获得

打开的向导并列出检测到的预设、应用的一个预设（可扩展性级别 + CVar 覆盖），以及恢复先前设置的能力。

## 前提条件

- Unreal Engine 5 编辑器。打包游戏中的运行时应用是可选的。
- 无需第三方软件、账户或额外的运行时环境。请参阅 [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md)。

## 1. 安装与启用

1. 从 Fab 库将 **Performance Preset Wizard** 添加到项目中（或安装到引擎中）。
2. 打开 **Edit → Plugins**，启用 **Performance Preset Wizard**，并在提示时重启。

## 2. 打开向导

1. 打开 **Tools → Performance → Performance Preset Wizard**。
2. 向导扫描资产注册表中的 `UPerformancePresetAsset` 资产，并按显示名称、目标平台和路径列出它们。
3. 点击某个预设以加载其详细信息面板。

## 3. 实际示例：应用与恢复

1. 选择一个自带的示例预设。
2. 点击 **Apply Preset**。

**预期结果：** 向导捕获一个恢复点，将可扩展性限制在 Unreal 的 `0..4` 范围内并应用，然后应用各个 CVar 覆盖。

3. 点击 **Restore Previous**。

**预期结果：** 可扩展性结构以及预设修改的特定 CVar 将恢复为紧接应用前捕获的值。

## 4. 编写您自己的预设

在 Content Browser 中打开任意 `PerformancePresetAsset`。Details 面板为您提供每个可扩展性类别的质量下拉菜单和**批量 CVar 编辑器**：

```text
# 允许注释行
r.ScreenPercentage=85
r.Nanite=1
r.Shadow.Virtual.Enable=1,editor
```

`,editor` 将覆盖标记为仅编辑器有效。使用 **Export** 将当前数组导出到文本编辑器，使用 **Apply** 将其重新解析回资产中。请参阅 [PresetAuthoringGuide.md](PresetAuthoringGuide.md)。

## 5. 可选：启动时与运行时使用

- **编辑器启动时：** *Project Settings → Plugins → Performance Preset Wizard* → **Apply Preset On Editor Startup** + **Startup Preset**。
- **打包游戏：** 通过 `UPerformancePresetRuntimeSubsystem.ApplyRuntimePreset` 和 `RestoreLatestBackup` 应用预设，或使用附带的 `UPerformancePresetRuntimeSelectorWidget`。请参阅 [RuntimeUsage.md](RuntimeUsage.md)。

## 6. 后续步骤

- 完整工作流程和备份历史：[UserManual.md](UserManual.md)。
- 附带预设：[SamplePresetsReference.md](SamplePresetsReference.md)。
- 设置选项：[SettingsReference.md](SettingsReference.md)。问题排查：[TROUBLESHOOTING.md](TROUBLESHOOTING.md)、[FAQ.md](FAQ.md)。
