---
lang: zh
title: EditorExtensionBase Quick Start
audience: [end_user]
owner_ref: plugin:EditorExtensionBase
applies_to:
  component: EditorExtensionBase
preconditions:
  - Unreal Engine project open with the plugin package available
  - Edit > Plugins can enable EditorExtensionBase
expected_result:
  text: GetSelectedAssetsForAction returns the current Content Browser selection after the plugin is enabled.
version:
  since: "1.0"
---
# 快速入门

本指南将引导您完成从安装到**首次实际使用**的全过程：启用 EditorExtensionBase 并从 Blueprint Utility 或 C++ 编辑器工具中调用共享的编辑器辅助函数。EditorExtensionBase 是用于支持其他编辑器插件的基础层，它并非一个独立的 Tiny Tools 菜单产品。

## 完成本指南后您将拥有

已启用的插件，以及成功调用 `UEditorManagerUtilityLibrary::GetSelectedAssetsForAction`（或其 Blueprint 可调用等效函数），该调用将返回当前 Content Browser 中的选中项。

## 前置要求

- Unreal Engine 5.4 或更高版本（描述符 `EngineVersion` 为 5.4.0）。
- 已启用 Editor Scripting Utilities（在 `EditorExtensionBase.uplugin` 中声明为依赖项）。
- 无需第三方软件、账户或外部运行时。请参阅 [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md)。

## 1. 安装与启用

1. 从您的 Fab 库中将 **EditorExtensionBase** 添加到项目中（或安装至引擎的 Plugins 目录下）。
2. 打开 **Edit → Plugins**，启用 **EditorExtensionBase**，并在提示时重启。
3. 确认 **Editor Scripting Utilities** 仍处于启用状态。

## 2. 验证模块已加载

重启后，该插件将暴露两个模块：

| 模块 | 类型 | 作用 |
| --- | --- | --- |
| `EditorExtensionBase` | Editor | 小部件、选中项辅助函数、撤销工具。 |
| `EditorExtensionRuntimeBase` | Runtime | 轻量级宏，对非编辑器使用者安全。 |

## 3. 示例：读取当前选中项

1. 在 Content Browser 中选择一个或多个资产。
2. 从依赖此插件的 Editor Utility Widget 或编辑器 C++ 工具中调用：

```cpp
TArray<UObject*> Selected = UEditorManagerUtilityLibrary::GetSelectedAssetsForAction(nullptr);
```

3. 当您有意进行写入时，使用 `CheckoutAndSaveAssets` 持久化或对返回的对象执行操作：

```cpp
bool bCheckoutOk = false;
bool bSaveOk = false;
const bool bOk = UEditorManagerUtilityLibrary::CheckoutAndSaveAssets(
	Selected, bCheckoutOk, bSaveOk);
```

## 预期结果

- `Selected` 包含 Content Browser 中的选中项（若未选中任何内容，则为空）。
- 当您调用 `CheckoutAndSaveAssets` 时，布尔输出参数将报告签出和保存的结果，而不会为您创建事务——调用方负责 `FScopedTransaction` 的作用域。

## 后续步骤

- 阅读 [UserManual.md](UserManual.md) 以获取小部件和工具目录。
- 阅读 [SettingsReference.md](SettingsReference.md) 以了解共享小部件上的可编辑属性。
- 当 BindWidget 插槽或选中项辅助函数在日志中发出警告时，使用 [TROUBLESHOOTING.md](TROUBLESHOOTING.md) 进行排查。
