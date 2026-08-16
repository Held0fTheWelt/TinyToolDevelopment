<!-- doc-provenance: product-facts.yml reconciled 2026-07-19; source AKDB:plugins/BestPracticesJournal/architecture.md; release 1.1.2 -->
# 用户手册

Best Practices Journal 是一个用于基于证据的工程实践治理的编辑器工作台。它是决策支持和评审记忆，而非补丁计划器、源码编辑器、AI 执行器或资产修改工具。

## 核心工作流

1. 从手动说明、证据引用或可选提供程序捕获实践或候选。
2. 添加适用性、权衡、失效模式、出处、权利说明和评审元数据。
3. 在接受或导出前校验记录。
4. 在为任务或评审选择指南时搜索实践。
5. 为已评审实践或明确候选创建应用简报。
6. 将简报交付给人工工作流、UCI、PRS 或其他获批的执行者。
7. 导入实现结果报告，记录实践是被验证、削弱、反驳、专门化还是替代。

## 实践记录质量

将 BPJ 用于能够通过评审的实践。一份有用的记录包括：

- 具体问题和目标上下文。
- 表述为可复用指南而非复制实现代码的解决方案。
- 指南为何有效、适用于何处以及在何处失效。
- 权衡、前提条件、调整规则和失效模式。
- 证据引用、出处、权利说明、信任度和评审状态。

如果这些字段未知，请将该项保持为候选或草案。不要仅因概述看起来合理就将其提升为已被接受的指南。

## 公共操作

- **Create practice record**：保存包含证据、上下文、权衡和评审状态的已评审或草案实践。
- **Create practice candidate**：保存来自提供程序的草案或提议，直到被明确评审。
- **Attach evidence**：链接本地/手动/提供程序证明，无需复制受受限的实现代码。
- **Search practices**：从 BPJ 拥有的工件存储中返回匹配的实践记录。
- **Create application brief**：为特定目标上下文导出仅限意图的交付物。
- **Import implementation outcome**：在实现或拒绝后完成循环。

## 应用简报 (Application Briefs)

简报应当帮助另一个工作流安全地制定计划。它可以包含目标项目/模块/范围、推荐调整、理由、约束、允许与禁止的行动类别、校验要求、预期输出、证据引用、审批状态和兼容性说明。

简报不得作为授权 BPJ 修改文件的凭据。如果下游工具应用修改，该工具必须拥有范围解析、试运行计划、审批、修改关卡、校验、回滚及其自身的结果报告。

## 结果导入 (Outcome Imports)

导入所有有意义的结果，包括失败、被拒绝、部分成功和无操作（no-op）的结果。结果会更新实践的历史、信任度、评审说明和演进链接。它们不会将原始实践重写为普遍正确。

将结果字段用于修改后的文件引用、校验报告路径、教训、推荐的日志更新、警告、错误以及指向外部计划或报告的链接。

## 可选提供程序

可选的证据、候选、结果、交付、索引、路由或实现提供程序可以丰富 BPJ。它们必须保持可替换。如果缺失提供程序，请使用手动记录、本地证据、JSON/Markdown 工件和 BPJ 校验继续进行。

## Capability Mesh (MCP)

无文件访问权限的 Agent 可以通过 UMCP 完成以评审为中心的日志生命周期：

- `bpj.gather_candidates.v1` — 扫描提供程序收件箱文件夹（包括来自 PIO 交付的 `project_intelligence_orchestrator`）。
- `bpj.repository.list.v1` — 列出实践、候选、证据、简报和结果的 ID。
- `bpj.practice.read.v1` — 内联读取单个序列化记录。
- `bpj.candidate.promote.v1` — 提升已评审候选（需要在路径上获得用户批准）。
- `bpj.import_artifacts.v1` — 导入 PIO 候选信封（以 `bpj.implementation_intent_candidates.` 开头的 `schema` / `schema_version`）。

提供程序收件箱路径：`Saved/BestPracticesJournal/provider_inbox/candidates/<provider_id>/`。

## Commandlet

Commandlet 用于校验、工件导入和样例导出非常方便，但不是首次使用的必需步骤。请使用保存于 `Saved/BestPracticesJournal/reports/` 中的报告作为自动化的持久证明。日志概括发生的事件；保存的工件始终是官方记录。

## 边界

BPJ 记录知识和意图。它不会修改源码文件、资产、Build.cs 文件、项目描述符或外部插件代码。下游执行拥有者必须实施其自己的预览、审批、校验和回滚关卡。

## 本地证据与日志

BPJ 将持久的评审证据存储在 `Saved/BestPracticesJournal/` 下。在共享或审计工作流时，请使用 `reports`、`application_briefs`、`implementation_outcomes` 和 `schemas` 中的 JSON/Markdown 文件。Unreal 日志类别 `LogBestPracticesJournal` 用于操作者诊断和 Commandlet 摘要；它不是已被接受实践的官方记录。
