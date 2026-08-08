# 用户手册

Editor Extension Base 包提供了共享的 Unreal Editor UI 基元和辅助库，以便功能插件能够保持统一的选中、签出、保存和撤销行为。

## 目标受众

- 构建 Editor Utility Widget 或编辑器工具的插件作者。
- 在不复制 Widget 样板代码的情况下，统一 Tiny Tool Development 编辑器用户体验的团队。

本插件**不是**具有其自身 Tiny Tools 菜单条目的最终用户工具。

## 模块

| 模块 | 加载时机 | 内容 |
| --- | --- | --- |
| `EditorExtensionBase` | Editor / Default | Widgets、`UEditorManagerUtilityLibrary`、撤销/资产操作工具。 |
| `EditorExtensionRuntimeBase` | Runtime / Default | 共享宏 (`UsefulMacros.h`) 和模块入口。 |

## 共享 Widgets

<!-- image slot: eeb-widget-overview -->

| 类 | 用途 |
| --- | --- |
| `UEditorToolHeaderWidget` | 带有标题/副标题 BindWidget 插槽和可编辑显示文本的标题行。 |
| `UEditorUtilityButtonWidget` | 带有文本块 BindWidgets 和点击委托的样式化按钮。 |
| `UEditorUtilityTabButtonWidget` | 带有选中/未选中图标插槽的选项卡样式按钮。 |
| `UTwoPaneUserWidget` | 用于编辑器 Utility 屏幕的双窗格布局容器。 |

Widget Blueprint 子类必须绑定声明的 BindWidget 插槽；缺失的绑定将在 `LogEditorExtensionBase` 下记录警告。

## Editor Manager Utility Library

`UEditorManagerUtilityLibrary` 扩展了 `UEditorUtilityLibrary`，提供了选中和持久化辅助功能：

| 函数 | 行为 |
| --- | --- |
| `GetSelectedAssetsForAction` | 返回当前选中项，可选择性地由主对象锚定。 |
| `CheckoutAndSaveAssets` | 尝试源控制签出和保存；通过输出参数报告成功状态。 |
| `GetEditorWorld` | 在可用时返回当前编辑器世界。 |
| `BeginTransactionAndGetSelectedAssets` | **在 5.4 中已弃用** — 调用方应自行管理 `FScopedTransaction`。 |

## 撤销和资产操作

| 类 | 行为 |
| --- | --- |
| `UEditorUtilityTask_PrepareUndo` | 为选中的事务性资产准备撤销选项的编辑器 Utility 任务；对于空、无效或非事务性对象，将跳过并记录警告。 |
| `UUndoableAssetActionUtility` | 编码可撤销的资产操作结果，包括在成功伴随签出警告时的 `SucceededWithCheckoutWarning`。 |

## 设计规则

1. 将特定于功能的业务逻辑保留在消费插件中。
2. 不要将此插件视为无关场景或 AI 插件的设置要求。
3. 优先使用调用方拥有的事务，而非已弃用的 begin-transaction 辅助函数。

## 可选集成

消费 Tiny Tool 编辑器插件可能依赖 Editor Extension Base 以实现 UI 一致性。这些集成由消费者拥有；当未启用时，本包仅降级为“辅助功能不可用”——它不会替代其他插件的行为。

## 相关文档

- [QUICKSTART.md](QUICKSTART.md)
- [SettingsReference.md](SettingsReference.md)
- [FAQ.md](FAQ.md)
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md)
