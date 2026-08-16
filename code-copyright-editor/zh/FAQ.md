<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/CodeCopyrightEditor/architecture.md -->
# 常见问题 (FAQ)

## Code Copyright Editor 是做什么用的？

Code Copyright Editor 帮助 Unreal Engine 开发者在 Project Settings 和源码文件中保持一致的版权声明。它可以从单个编辑器工作流中扫描、预览、更新和报告源码文件标头。

## 插件会影响运行时的游戏代码吗？

不会。Code Copyright Editor 是仅限编辑器使用的工具。它专用于开发、审查、文档记录和 CI 工作流。

## 它能自动更新整个代码库吗？

可以，但仅限于扫描和审查之后。编辑器会在应用更改前展示哪些文件可以修改、哪些文件受保护，以及提议的替换样式。

## 它会保护第三方或 Epic 的声明吗？

是的。扫描器旨在保护外部、Epic 和第三方的声明免受自动重写。受保护的文件和存在冲突的文件应手动审查。

## 我可以自定义版权模板吗？

可以。您可以编辑源码文件声明模板和 Project Settings 声明模板。可以自动渲染产品名称、文件路径、年份、许可证标识符和单文件描述等标记。

## 它支持 SPDX 或 REUSE 工作流吗？

插件提供了面向 REUSE/SPDX 的模板和报告。这些报告旨在支持审查和 CI 工作流，但不构成法律认证。

## 有用于 CI 的 Commandlet 吗？

有。附带的 `CodeCopyrightCheck` Commandlet 可以扫描项目、选择性地修复可更改的文件、写入报告，并在版权声明不同步时使 CI 失败。

## 它能替代法律咨询吗？

不能。它旨在帮助一致地应用和审查声明文本。它不会决定法律所有权、验证第三方许可证或提供法律咨询。
