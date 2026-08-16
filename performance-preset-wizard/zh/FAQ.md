<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/PerformancePresetWizard/architecture.md -->
# 常见问题（FAQ）

## Performance Preset Wizard 是自动优化器吗？

不是。它是一个预设编写和应用工具，不会自动对硬件进行基准测试。

## 它能在运行时工作吗？

可以。打包后的游戏可以通过 `UPerformancePresetRuntimeSubsystem`、Blueprint、C++ 或附带的 UMG 控件手动应用预设。

## 应用预设会保存项目设置吗？

不会。它通过 Scalability 和 CVar API 更改当前的引擎/运行时状态，不会修改项目配置文件。

## 我可以撤销应用吗？

在编辑器向导中，使用 **Restore Previous**。在运行时，使用 `RestoreLatestBackup` 或 `RestoreBackupById`。

## 如果 CVar 不存在会怎样？

插件会将其记录并统计为缺失，然后继续应用预设的其余部分。

## 为什么 CVar 值存储为字符串？

CVar 可以是整数、浮点数、布尔值或文本。字符串可以统一覆盖所有这些类型。

## "Editor Only" 是什么意思？

仅编辑器有效的覆盖仅在编辑器环境中应用，在打包后的游戏中会被跳过。

## 该插件会替代 Device Profiles 吗？

不会。Device Profiles 仍然是配置平台策略的正确场所。
