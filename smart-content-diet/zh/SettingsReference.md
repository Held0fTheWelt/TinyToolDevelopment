<!-- doc-provenance: AKDB:plugins/SmartContentDiet/architecture.md; docs/architecture/plugins/SmartContentDiet/product-facts.yml; reconciled 2026-07-16 -->
# 设置参考

## 角色 / 受众

在 **Settings** 或标头受众选择器中设置。控制解释深度和标签页可见性：

- **Beginner** — Overview、Optimize、Findings、Settings。
- **Engineer / Producer (advanced)** — 添加 Preset 和 Governance（Trend、Debt、Budget、Ownership、Deep Scan）；Redundancy 仅在注册了外部相似性提供程序时出现。

## 扫描深度（标头）

| 深度 | 是否加载资产？ | 备注 |
| --- | --- | --- |
| `Quick Safe` （默认） | 否 | 注册表/元数据路径；快速首次通过。 |
| `Full` | 是 | 完整分析器管道；可操作的网格/纹理/材质发现。 |
| `Deep` | 是 | 深入材质/静态网格指标；使用 Governance → Deep Scan；最慢。 |

所选深度会得到每次分析器运行（编辑器和 Commandlet）的尊重。

Quick Safe 是 AssetRegistry 优先路径：广泛扫描避免硬加载资产，除非候选通过了廉价的元数据检查。Full 和 Deep 可能会加载资产以获得可操作的分析器细节。

## 输出位置

```text
Saved/SmartContentDiet/OptimizationQueue/<timestamp>/   ← 安全队列应用报告
```

## 批准 / 安全性

修改能力（`scd.optimize.apply_safe`、`scd.optimize.apply_fix`）**默认带有批准门控**。破坏性修复需要显式的 `allow_destructive: true`。仅在已备份、受版本控制且可弃用的工作区中运行修改。

## Commandlet （CI / 无界面）

开关：`-QuickSafe`、`-FullScan`、`-DeepScan`、`-OptimizationQueueReport`、`-ApplySafeQueue`、`-Path=`、`-Limit=`、`-NoFail`，以及标准 `-unattended -nop4 -nosplash`。应用开关应仅针对已备份的项目。

## 可选生态系统路由

启用 **Unreal Capability Mesh (UCM)** 时，SCD 通过 JSON 声明的 UCM 路由公开只读提供程序能力和两个需要批准的修改优化路由。SCD 从不在代码中链接同伴插件；此集成完全可选。请参阅[文档索引](README.md)和 [../Resources/SMART_ANALYSIS_ARCHITECTURE.md](../Resources/SMART_ANALYSIS_ARCHITECTURE.md)。

SCD 还公开只读编辑器作业路由（`scd.editor.jobs.list.v1`、`scd.editor.jobs.status.v1`），以便通过 UCM 进行 UMCP 聚合。

有关更深入的分析器/预设/治理设置，请参阅 [../Resources/SMART_ANALYSIS_ARCHITECTURE.md](../Resources/SMART_ANALYSIS_ARCHITECTURE.md)。
