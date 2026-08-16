<!-- doc-provenance: AKDB:plugins/SmartContentDiet/architecture.md; docs/architecture/plugins/SmartContentDiet/product-facts.yml; reconciled 2026-07-16 -->
# 快速入门指南

本指南将带您从安装到获得**实际成果**：扫描项目资产以获取优化发现，并（可选）应用带有前后对比报告的已审查安全修复。Smart Content Diet 的核心循环独立工作 — **无需 AI、同伴插件或外部工具**。

> **⚠ 安全第一。** 应用修复、缩减、资产移动/删除、基线更新或治理写入**会修改项目资产**。请仅在**已备份、受版本控制且可弃用**的工作区中执行此操作 — 切勿在未受保护的源代码上执行。扫描和预览是只读且安全的。

## 完成本指南后您将获得什么

在您选择的角色中打开工具，完成带有发现的 Quick Safe 扫描，并了解如何预览和应用安全优化以及读取前后增量。

## 要求

- 带有包含内容资产的项目的 Unreal Engine 5.4+ 编辑器。
- 无需第三方软件、帐户、AI 模型或外部运行时。参见 [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md)。

## 1. 安装与启用

1. 从 Fab 库将 **SmartContentDiet** 添加到项目（或安装到引擎）。
2. 打开 **Edit → Plugins**，启用 **SmartContentDiet**，并在收到提示时重新启动。

## 2. 打开工具并选择角色（首次成果）

1. 打开 **Tools → Content Tools → Smart Content Diet**。
2. 在标头受众选择器（或 **Settings**）中，选择您的角色：
   - **Beginner** — Overview、Optimize、Findings、Settings；更多解释。
   - **Engineer / Producer (advanced)** — 添加 Preset 和 Governance（Trend、Debt、Budget、Ownership、Deep Scan），并在注册了外部相似性提供程序时添加 Redundancy。
3. 将 **扫描深度** 保持为 **Quick Safe**（默认 — 仅注册表/元数据，无资产加载；快速）。
4. 单击标头中的 **Quick Safe Scan**。

**预期输出：** 扫描完成，**Overview** 标签页汇总发现（可以安全改进的内容）。这是只读的。

## 3. 实际操作示例：预览并应用安全修复

> 请先备份 / 提交您的项目（参见上面的安全须知）。

1. 打开 **Optimize** 标签页 → **Safe Optimization Queue**。
2. 单击 **Preview Safe** 查看队列中的安全优化和预测的前后增量（仍为只读）。
3. 单击 **Apply Safe** 应用安全队列。应用成功（或从 **Findings** 细节中修复单个资产）后，Shell 会**自动重新扫描**。
4. 在 Optimize 面板中比较队列计数和增量摘要。

**预期输出：** 应用安全优化并在以下位置写入 JSON 应用报告：

```text
Saved/SmartContentDiet/OptimizationQueue/<timestamp>/
```

## 4. 扫描深度

| 深度 | 是否加载资产？ | 用途 |
| --- | --- | --- |
| **Quick Safe** （默认） | 否 | 快速了解“我可以安全改进什么？” |
| **Full** | 是 | 可操作的网格/纹理/材质发现 |
| **Deep** | 是 | 最慢；深入的材质/静态网格指标（Governance → Deep Scan） |

标头按钮标签和提示随所选深度更新，每次分析器运行都会遵循该深度。

## 5. 后续步骤

- 编辑器 Shell、标签页、发现、治理: [../Resources/UI_AND_BEHAVIOR.md](../Resources/UI_AND_BEHAVIOR.md)。
- 安全优化队列（桶、安全规则、报告 Schema）: [../Resources/OPTIMIZATION_QUEUE.md](../Resources/OPTIMIZATION_QUEUE.md)。
- 设置和角色: [SettingsReference.md](SettingsReference.md)。
- 疑难解答: [TROUBLESHOOTING.md](TROUBLESHOOTING.md) 和 [FAQ.md](FAQ.md)。

> **可选 / 高级：** SCD 还为 CI 提供无界面 Commandlet（`-QuickSafe`、`-FullScan`、`-DeepScan`、`-OptimizationQueueReport`、`-ApplySafeQueue`），并且 — 仅当您还拥有 **Unreal Capability Mesh (UCM)** 时 — 提供可选的配置声明生态系统路由。上述编辑器工作流不需要这两者；请参阅[文档索引](README.md)。
