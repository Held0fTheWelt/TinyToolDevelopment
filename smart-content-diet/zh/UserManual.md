<!-- doc-provenance: AKDB:plugins/SmartContentDiet/architecture.md; docs/architecture/plugins/SmartContentDiet/product-facts.yml; reconciled 2026-07-16 -->
# 用户手册

本手册总结了 Smart Content Diet 编辑器工作流并指向详细指南。

## 入口点

打开 **Tools → Content Tools → Smart Content Diet**。该窗口是一个角色感知 Shell。

## 角色与标签页

在 **Settings** 或标头受众选择器中设置角色（Beginner / Engineer / Producer）和解释级别。标签页可见性遵循角色：

| 标签页 | Beginner | Advanced (Engineer / Producer) |
| --- | --- | --- |
| Overview, Optimize, Findings, Settings | ✓ | ✓ |
| Preset | — | ✓ |
| Governance (Trend, Debt, Budget, Ownership, Deep Scan) | — | ✓ |
| Redundancy | — | ✓ （仅限带外部相似性提供程序时） |

## 扫描深度

在标头中选择：**Quick Safe**（注册表/元数据，无资产加载）、**Full**（加载资产）、**Deep**（深入材质/网格指标；Governance → Deep Scan）。每次分析器运行都遵循所选深度；Commandlet 遵循 `-QuickSafe` / `-FullScan` / `-DeepScan`。

广泛扫描使用 AssetRegistry 优先管道。SCD 收集一次候选，尽可能从标签读取廉价的纹理/材质元数据，优先比较标签，并仅深入加载需要对象数据的幸存候选集。只读比较阶段可以并行运行；修改性 QuickFix 仍需要显式的人工或 Commandlet 操作。

重复和 Alpha 路径在扫描发现和缩减之间共享助手代码。纹理/材质 Alpha 检查使用相同的材质实例不透明度逻辑，缩减早期退出使用与缩减对齐的重复键，因此不会仅仅因为更严格的扫描索引未对资产进行分组而跳过安全整合。

## 核心工作流 — 安全优化循环（无 AI）

1. 打开工具。
2. 选择扫描深度（Quick Safe / Full / Deep）。
3. 从标头运行扫描。
4. 审查 **Overview**，然后打开 **Optimize → Safe Optimization Queue**。
5. **Preview Safe** → 备份 / 版本控制 → **Apply Safe**。
6. 应用成功或修复单个资产后，Shell 会自动重新扫描。
7. 比较队列计数和增量；JSON 报告保存在 `Saved/SmartContentDiet/OptimizationQueue/<timestamp>/` 下。

## 一般分析工作流

1. 运行扫描（选择、文件夹或项目范围）。
2. 按严重性、影响、维度和可解释性链审查发现。
3. 使用 **Preset** （高级）查看评估权重如何影响得分。
4. 使用 **Governance** （高级）查看趋势、债务、预算、所有权、可选的 Deep Scan。
5. 仅在确认备份/版本控制后应用 QuickFix。
6. 重新扫描并在目标项目上下文中验证。

## 安全性

修改性操作会更改项目资产，默认情况下需要批准门控。请仅在已备份、受版本控制且可弃用 solace 的工作区中运行它们。请参阅 [QUICKSTART.md](QUICKSTART.md) 中的安全须知。

## 编辑器作业和 UCM

最近的编辑器工作将记录为扫描、验证和优化操作的作业历史记录。启用 Unreal Capability Mesh 时，SCD 会公开只读作业路由：

```text
scd.editor.jobs.list.v1
scd.editor.jobs.status.v1
```

Unified MCP Server 可以通过 `jobs_list` / `jobs_status` 聚合这些路由；SCD 本身不依赖于 UMCP。

## 详细指南

- 编辑器 Shell、标签页、发现、QuickFix、治理: [../Resources/UI_AND_BEHAVIOR.md](../Resources/UI_AND_BEHAVIOR.md)。
- 安全优化队列（桶、安全规则、报告 Schema）: [../Resources/OPTIMIZATION_QUEUE.md](../Resources/OPTIMIZATION_QUEUE.md)。
- 架构: [../Resources/SMART_ANALYSIS_ARCHITECTURE.md](../Resources/SMART_ANALYSIS_ARCHITECTURE.md)。
