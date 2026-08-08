# 编辑器扩展基础文档

编辑器扩展基础（Editor Extension Base）是为 Tiny Tool Development UI 插件提供的共享 Unreal 编辑器基础架构。它提供可复用的编辑器实用工具组件（Editor Utility widgets）、内容浏览器（Content Browser）选择/检出/保存辅助功能、撤销准备工具以及轻量级运行时宏模块。

目标受众：需要一致编辑器用户体验而无需复制组件和选择样板代码的插件作者及团队。本包属于支持层，不注册任何自己的 Tiny Tools 产品菜单。

## 功能

- 共享编辑器实用工具组件（标题栏、按钮、选项卡按钮、双窗格布局）。
- `UEditorManagerUtilityLibrary` 的选择、检出/保存及编辑器世界辅助功能。
- 撤销准备及可撤销资产操作工具。
- 运行时模块（`EditorExtensionRuntimeBase`），为非编辑器使用者提供共享宏。

## 入门指南

1. 启用该插件（以及编辑器脚本工具）——请参阅 [QUICKSTART.md](QUICKSTART.md)。
2. 从编辑器实用工具或 C++ 编辑器工具中调用 `GetSelectedAssetsForAction`。
3. 阅读 [UserManual.md](UserManual.md) 和 [SettingsReference.md](SettingsReference.md) 以获取完整目录。

## 相关文件

- [../README.md](../README.md) — 产品概述。
- [../CHANGELOG.md](../CHANGELOG.md) — 发布历史。
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md) · [FAQ.md](FAQ.md) · [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md)
