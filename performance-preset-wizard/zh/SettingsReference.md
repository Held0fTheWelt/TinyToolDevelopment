<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/PerformancePresetWizard/architecture.md -->
# 设置参考

本参考列出了插件设置与预设资产字段。

## 项目设置

打开 **Edit > Project Settings > Plugins > Performance Preset Wizard**。

| 设置项 | 类型 | 默认值 | 描述 |
| --- | --- | --- | --- |
| Apply Preset On Editor Startup | Boolean | `false` | 启用后，选定的启动预设将在编辑器初始化完成后应用。 |
| Startup Preset | Soft object pointer | 空 | 编辑器启动时要应用的 `UPerformancePresetAsset`。 |

## 运行时项目设置

打开 **Edit > Project Settings > Plugins > Performance Preset Wizard Runtime**。

| 设置项 | 类型 | 默认值 | 描述 |
| --- | --- | --- | --- |
| Max Backup History | Integer | `10` | 保存的运行时备份条目的最大数量。限制在 `1..100`。 |
| Runtime Preset Library | Array of soft object pointers | 空 | 默认运行时选择器控件展示的预设资产列表。 |
| Storage Provider Class | Class | `PerformancePresetGameUserSettingsStorage` | 运行时子系统使用的存储提供程序。 |

## 预设资产字段

预设资产使用 `UPerformancePresetAsset` 类。

| 字段 | 类型 | 默认值 | 描述 |
| --- | --- | --- | --- |
| Display Name | `FText` | 空 | 向导中显示的易读名称。 |
| Description | `FText` | 空 | 目标设备或使用场景的简短说明。 |
| Target Platform | Enum | Desktop Mid Range | 分组和排序提示。 |
| View Distance Quality | Integer | `2` | 可视距离的可扩展性级别。 |
| Anti-Aliasing Quality | Integer | `2` | 抗锯齿的可扩展性级别。 |
| Shadow Quality | Integer | `2` | 阴影的可扩展性级别。 |
| Global Illumination Quality | Integer | `2` | 全局光照的可扩展性级别。 |
| Reflection Quality | Integer | `2` | 反射的可扩展性级别。 |
| Post Process Quality | Integer | `2` | 后期处理的可扩展性级别。 |
| Texture Quality | Integer | `2` | 纹理的可扩展性级别。 |
| Effects Quality | Integer | `2` | 特效的可扩展性级别。 |
| Foliage Quality | Integer | `1` | 植物的可扩展性级别。 |
| Shading Quality | Integer | `2` | 着色的可扩展性级别。 |
| Landscape Quality | Integer | `2` | 地形的可扩展性级别。 |
| CVar Overrides | Array | 空 | 额外的控制台变量覆盖。 |

所有质量字段均限制在 `0..4` 范围内：

- `0`：Low
- `1`：Medium
- `2`：High
- `3`：Epic
- `4`：Cinematic

## CVar 覆盖字段

每个 `FPerformanceCVarOverride` 包含：

| 字段 | 类型 | 描述 |
| --- | --- | --- |
| Name | `FString` | 控制台变量名称，例如 `r.ScreenPercentage`。 |
| Value | `FString` | 传递给 CVar 的值。 |
| Editor Only | Boolean | 为 true 时，该覆盖仅在编辑器环境中应用。 |
