<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/PerformancePresetWizard/architecture.md -->
# 用户手册

本手册说明 Performance Preset Wizard 的常规编辑器工作流程。

## 打开向导

1. 在 **Edit > Plugins** 中启用 **Performance Preset Wizard**。
2. 如果提示，请重启 Unreal Editor。
3. 打开 **Tools > Performance > Performance Preset Wizard**。

向导扫描资产注册表中的 `UPerformancePresetAsset` 资产，并列出检测到的预设。

## 主面板

向导包含两个主要区域：

- 预设列表：所有检测到的性能预设资产。
- 详细信息面板：选定预设的名称、描述、可扩展性级别、CVar 覆盖、状态文本和操作按钮。

如果新创建、重命名、移动或导入了预设资产，请使用 **Refresh** 刷新。

## 选择预设

点击列表中的预设以加载其摘要。

## 应用预设

1. 选择一个预设。
2. 复核摘要。
3. 点击 **Apply Preset**。

操作按以下顺序执行：

1. 捕获恢复点（Restore Point）。
2. 将可扩展性数值限制在 Unreal 支持的 `0..4` 质量范围内。
3. 通过 `Scalability::SetQualityLevels` 应用可扩展性。
4. 遍历 CVar 覆盖项。
5. 跳过无效或格式错误的条目。
6. 在非编辑器环境下跳过 `editor-only` 条目。
7. 在状态栏和通知区域报告结果。

## 恢复先前设置

点击 **Restore Previous** 以返回到紧接上次成功应用预设前捕获的设置。

恢复内容包括：

- 应用前完整的可扩展性结构。
- 被预设重写的特定 CVar 的先前数值。

应用另一个预设会替换先前的恢复点。

## 编辑器启动预设

打开 **Edit > Project Settings > Plugins > Performance Preset Wizard**。

可用的设置项：

- **Apply Preset On Editor Startup**：启用或禁用启动时自动应用。
- **Startup Preset**：对要在编辑器初始化完成后应用的预设资产的软引用。

## 运行时预设

运行时预设使用相同的 `UPerformancePresetAsset` 资产。打包后的游戏通过 `UPerformancePresetRuntimeSubsystem` 手动应用它们。

典型的 Blueprint 流程：

1. 获取当前的 `GameInstance`。
2. 获取 `Performance Preset Runtime Subsystem`。
3. 将预设资产传递给 `ApplyRuntimePreset`。
4. 在需要撤销时调用 `RestoreLatestBackup`。

## 运行时选择器控件

`UPerformancePresetRuntimeSelectorWidget` 作为 UMG 的起步组件附带提供。它可以列出配置的预设、应用选定的预设并恢复最新的备份。

默认控件展示的运行时预设可在 **Project Settings > Plugins > Performance Preset Wizard Runtime** 下进行配置。

## 批量 CVar 编辑器

使用 CVar 文本编辑器从文档或控制台会话中复制覆盖项。

支持的语法：

```text
# 允许注释行
r.ScreenPercentage=85
r.Nanite=1
r.Shadow.Virtual.Enable=1,editor
```

使用 **Export** 将当前数组导出到文本编辑器，使用 **Apply** 将文本重新解析回资产中。

## 推荐的命名

使用清晰明确的名称：

- `Laptop Dev`
- `Desktop Mid Range 60 FPS`
- `Console Like Review`
- `VR Mobile Stable`
- `Cinematic Capture 4k`

## 移动或删除预设

如果启动预设不再生效，请在 Project Settings 中重新选择资产并保存设置。
