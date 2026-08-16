<!-- doc-provenance: product-facts.yml reconciled 2026-07-19; source AKDB:plugins/BestPracticesJournal/architecture.md; release 1.1.2 -->
# Best Practices Journal 文档

Best Practices Journal 帮助团队直接在 Unreal Editor 内部治理可复用的工程实践。它将关于实践的知识、出处、评审状态、实现意图和结果历史存储在 BPJ 拥有的本地工件根目录下。

版本 1.1.2 支持 Unreal Engine 5.4 及更高版本。导入的证据和提供程序输出保持为待评审候选，直到人工明确提升；没有任何外部生成者可以自主接受某项实践。

BPJ 是独立运行的。可选的生态系统提供程序可以提供证据、候选、结果或交付目标，但日志、校验、搜索、导出和结果循环在没有任何可选提供程序的情况下也必须保持可用。

## 核心概念

- 实践记录（Practice records）：描述可复用的工程指南、上下文、权衡、适用性、失效模式和评审状态。
- 实践候选（Practice candidates）：来自提供程序且仍需评审的草案或提议。
- 证据记录（Evidence records）：将实践与项目本地证明、出处、权利说明和信任级别连接起来。
- 应用简报（Application briefs）：描述将已评审实践调整为特定目标的意图。
- 结果导入（Outcome imports）：记录下游工作是否验证、削弱、反驳、专门化或替代了某项实践。
- 脱敏与防护政策：保持共享记录的合规与审慎。
- 存储后端：允许 BPJ 作为 JSON 工件、本地 SQLite 或基于 Postgres 的工作室配置文件运行。

## 产品边界

BPJ 拥有实践记录、候选、证据引用、评审状态、应用简报、实现结果导入、确定性导出、模式校验、脱敏、防护栏和本地报告。它不拥有补丁计划、试运行/应用（dry-run/apply）、回滚、最终实现校验、AI 执行或源码/资产修改。

应用简报是仅限意图的交付工件。下游工具或人工工作流仍必须执行其自己的计划、审批、修改、校验和回滚步骤。

## 采纳契约

被接受的实践不应只是一个口号。在采纳或广泛复用之前，请记录：

- 问题、上下文和解决方案。
- 为何有效以及适用于何处。
- 前提条件、调整规则、权衡和失效模式。
- 证据引用、出处、权利说明和信任度。
- 评审状态、评审者说明以及可用的结果历史。

薄弱或缺失的字段应作为校验审查项处理，而非无害的格式问题。

## 简报与结果契约

应用简报可以包含实践标识、目标上下文、推荐调整、约束、允许与禁止的行动类别、校验要求、预期输出、证据引用、审批状态和兼容性说明。不得包含复制的实现代码或授予修改权限。

结果导入会更新实践的历史和信任度。失败或被拒绝的结果是有效数据：应该导入而不是隐藏，因为它可能会削弱、反驳、专门化或替代原始实践。

## 本工件与日志记录

BPJ 将项目本地工件写入 `Saved/BestPracticesJournal/`，包括 `practices`、`candidates`、`evidence`、`application_briefs`、`implementation_outcomes`、`reports`、`schemas`、`logs` 和 `provider_inbox`。Unreal 诊断使用 `LogBestPracticesJournal`；持久的操作者证据应来自保存的 JSON/Markdown 工件，而非临时日志行。

## 买家文档

- [快速入门](QUICKSTART.md)
- [用户手册](UserManual.md)
- [设置参考](SettingsReference.md)
- [故障排除](TROUBLESHOOTING.md)
- [常见问题 (FAQ)](FAQ.md)
- [第三方软件](THIRD_PARTY_SOFTWARE.md)
- [Storage Backends](StorageBackends.md)

## 操作界面

- 编辑器工作台：创建、评审、搜索、准备简报、导入结果以及检查集成状态。
- 保存的工件：`Saved/BestPracticesJournal/` 下的 JSON/Markdown 记录。
- Commandlet：用于自动化和发布检查的校验、工件导入和样例导出。
- 可选路由/提供程序：可替换的集成界面，不得成为首次使用的必需条件。

## 工作流

1. 打开 `Tools > Best Practices Journal`。
2. 创建或导入实践记录。
3. 附加证据和评审状态。
4. 在采纳前校验并评审记录。
5. 在明确实现上下文时生成仅限意图的应用简报。
6. 在下游工作完成后导入结果。

## 相关文件

- [../README.md](../README.md)：快速入门。
- [../CHANGELOG.md](../CHANGELOG.md)：版本历史。
- [StorageBackends.md](StorageBackends.md)：JSON、SQLite 和 Postgres 存储模式。
