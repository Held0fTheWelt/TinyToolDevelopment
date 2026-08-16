<!-- doc-provenance: product-facts.yml reconciled 2026-07-19; source AKDB:plugins/BestPracticesJournal/architecture.md; release 1.1.2 -->
# 快速入门

## 目标

创建一个独立的、项目本地的实践日志，捕获证据，评审实践，导出实现意图简报，并导入结果，而无需修改项目的源码或资产。

## 首次运行

1. 在 Unreal Editor 插件浏览器中启用 **Best Practices Journal**。
2. 根据提示重启编辑器。
3. 打开 **Tools > Best Practices Journal**。
4. 如果指南尚未评审，请先创建一个实践候选。
5. 填写问题、上下文、解决方案、适用性、权衡、前提条件和失效模式。
6. 附加本地证据或包含出处和权利说明的手动证据说明。
7. 在将其作为已被接受的指南之前，校验记录并添加评审者说明。
8. 使用 **Search practices** 按主题、标签（tag）或证据说明重新找到该记录。
9. 为特定目标创建应用简报，并检查 JSON/Markdown 导出。
10. 下游工作完成后导入实现结果。

BPJ 是独立的：可选的证据提供程序、UCM 路由、IIS、SDA、UCI 或 PRS 可以丰富工作流，但核心日志、评审、导出和结果循环在没有任何其他 Tiny Tool 插件的情况下也能正常工作。

## 验证结果

首次运行后，检查保存于 `Saved/BestPracticesJournal/` 下的工件：

- `practices/` 包含实践记录。
- `application_briefs/` 包含仅限意图的交付文件。
- `implementation_outcomes/` 包含导入的结果记录。
- `reports/` 包含校验、导入和操作者报告。

这些文件构成了用于评审和交付的持久证明。Unreal 日志输出对诊断很有帮助，但不是官方记录。

## 边界检查

应用简报应描述意图、目标上下文、约束、所需的校验和审批状态。不应包含复制的实现代码、补丁指令、回滚步骤，也不得授权 BPJ 修改项目文件。

## 第一个良好实践

从具有真实证据的小型实践开始，例如特定于项目的日志记录规范或评审检查清单。避免编写诸如“编写更好的代码”之类的泛泛规则，除非您能添加上下文、失效模式、证据示例和校验要求。

## 第一个良好结果

在下游工作流试用简报后，即使没有发生任何更改也请导入结果。`rejected`、`failed`、`partial` 和 `no_op` 结果均有价值，因为它们能防止 BPJ 将过于概括的实践误展示为已验证实践。
