<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/PerformancePresetWizard/architecture.md -->
# 故障排除

## 插件未出现在 Tools 菜单中

请检查插件是否已在 **Edit > Plugins** 中启用，并重启编辑器。

## 列表中未显示任何预设

在向导中使用 **Refresh**。确认资产确实是 `UPerformancePresetAsset` 数据资产。

## 无法应用预设

确保已选择预设。如果资产被删除或移动，请刷新列表。

## 某些 CVar 提示缺失（Missing）

CVar 名称无法在 Unreal 的控制台管理器中解析（拼写错误、插件未启用或引擎版本不同）。缺失的 CVar 不会阻止应用预设的其余部分。

## CVar 被统计为无效（Invalid）

无效条目的名称或值为空。请在批量编辑器中修正该行。

## "Restore Previous"不可用

恢复功能仅在当前编辑器会话中应用过预设后才可用。

## 启动预设未应用

请检查 **Apply Preset On Editor Startup** 是否已启用，且 **Startup Preset** 指向有效的资产。
