# 常见问题解答

## EditorExtensionBase 的用途是什么？

它是用于 Tiny Tool Development 编辑器 UI 插件的共享基础架构，包括可复用的编辑器实用工具小部件、选择/签出/保存辅助函数、撤销准备工具以及轻量级运行时宏模块。

## 这是一个面向最终用户的工具吗？

不是。它不会注册自己的 Tiny Tools 产品菜单。功能插件将其作为依赖项进行消费。

## 它加载哪些 Unreal 模块？

`EditorExtensionBase`（编辑器）和 `EditorExtensionRuntimeBase`（运行时），如 `EditorExtensionBase.uplugin` 中所声明。

## 它是否需要其他 Tiny Tool 插件？

不需要。它需要 Unreal 的 **Editor Scripting Utilities** 插件（在描述符中启用）。场景、AI 或其他 Tiny Tool 插件是可选的消费者，而非设置要求。

## 如何读取当前 Content Browser 的选择？

启用插件后，从 Blueprint 或 C++ 调用 `UEditorManagerUtilityLibrary::GetSelectedAssetsForAction`。请参阅 [QUICKSTART.md](QUICKSTART.md)。

## 应如何打开撤销事务？

在调用方中持有 `FScopedTransaction`。`BeginTransactionAndGetSelectedAssets` 自 Unreal Engine 5.4 起已弃用。

## 为什么我的小部件 Blueprint 在运行时发出警告？

`BindWidget` 插槽（如按钮、文本块或图标）为空。请确保 Utility Widget Blueprint 绑定了 C++ 基类上声明的所有必需插槽。

## CheckoutAndSaveAssets 是否总是成功？

不是。它通过布尔输出参数报告签出和保存结果。源代码控制或保存失败会在此处以及 `SucceededWithCheckoutWarning` 等相关结果代码中显现。

## 是否有项目范围的 DeveloperSettings？

没有。可配置字段位于共享小部件和实用工具上。请参阅 [SettingsReference.md](SettingsReference.md)。

## 包中是否包含第三方软件？

没有。请参阅 [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md)。

## 支持哪些引擎版本？

打包的描述符针对 Win64、Linux 和 Mac 上的 Unreal Engine 5.4.0，用于编辑器模块的允许列表。

## 我如何获取支持？

请使用 `mailto:support@tiny-tool-development.com`（描述符中的 `SupportURL`）或 Fab 产品页面上的支持链接。

## 我是否可以仅使用运行时宏而不使用编辑器模块？

可以。`EditorExtensionRuntimeBase` 是一个独立的运行时模块，旨在为非编辑器消费者保持轻量级依赖。

## PrepareUndo 会立即修改资产吗？

它会为选定的事务性资产准备撤销选项，并跳过无效选择（附带警告）。当您有意写入时，持久化仍通过签出/保存辅助函数进行。

## 运行时宏是否可以拉取仅编辑器模块？

不可以。请保持 `EditorExtensionRuntimeBase` 依赖轻量。编辑器小部件和选择辅助函数仍保留在编辑器模块中。
