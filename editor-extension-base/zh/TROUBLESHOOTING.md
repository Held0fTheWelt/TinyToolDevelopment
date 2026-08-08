---
lang: zh
title: EditorExtensionBase Troubleshooting
audience: [end_user]
owner_ref: plugin:EditorExtensionBase
applies_to:
  component: EditorExtensionBase
symptom: Editor utility BindWidget slots are null or selection helpers warn in the log.
recovery:
  steps:
    - Confirm the plugin is enabled under Edit > Plugins and restart the editor
    - Re-read the matching troubleshooting entry and apply the documented fix
    - Re-run the quick start smoke check
version:
  since: "1.0"
---
# 故障排除

格式：症状 → 原因 → 解决方法。

## 0. 已启用但无任何反应

**症状：** 启用 **EditorExtensionBase** 并重启后，未出现新的 Tiny Tools 菜单，也无明显的 UI 变化。  
**原因：** 该插件是一个共享的基础层；它不会注册自己的产品菜单。  
**解决方法：** 在 **编辑 → 插件** 下验证插件已启用，然后从 **Editor Utility Widget** 或 C++ 编辑器工具中调用 `UEditorManagerUtilityLibrary::GetSelectedAssetsForAction`（参见 [QUICKSTART.md](QUICKSTART.md)）。未出现新菜单是预期行为。

## 1. 插件已启用，但辅助蓝图无法找到库

**症状：** 启用后，`Editor Manager Utility Library` 的蓝图节点缺失。  
**原因：** 编辑器模块未加载，或者在插件启用之前已编译了 Editor Utility 资产。  
**解决方法：** 确认 **EditorExtensionBase** 在 **编辑 → 插件** 下已启用，重启编辑器，然后刷新/重新编译 Editor Utility Blueprint。

## 2. `EditorUtilityButtonWidget: Button is null`

**症状：** 日志 `LogEditorExtensionBase` 警告按钮为空。  
**原因：** Utility Widget Blueprint 子类未绑定所需的 BindWidget 按钮槽位。  
**解决方法：** 打开 Widget Blueprint，绑定在 `UEditorUtilityButtonWidget` 上声明的按钮槽位，编译并重新打开工具。

## 3. `EditorUtilityButtonWidget: Text block is null`

**症状：** 警告文本块 BindWidget 为空。  
**原因：** 标签文本块在 Blueprint 中未绑定。  
**解决方法：** 绑定 C++ 基类上的文本块槽位，设置显示文本，然后编译。

## 4. `EditorUtilityTabButtonWidget: SelectedIcon is null` / `UnselectedIcon is null`

**症状：** 选项卡按钮警告缺少图标。  
**原因：** 选中或未选中图标槽位未绑定，或资产缺失。  
**解决方法：** 分配并绑定两个图标槽位；验证软引用/对象引用是否已解析。

## 5. `EditorUtilityTask_PrepareUndo: No assets selected`

**症状：** 撤销准备日志显示未选择任何资产。  
**原因：** 任务运行时，Content Browser 的选择为空。  
**解决方法：** 先选择事务性资产，然后运行 prepare-undo 实用工具。

## 6. 资产因非事务性而被跳过

**症状：** 警告资产非事务性 / 非 `UObject` / 无效。  
**原因：** prepare-undo 任务仅接受有效的、支持事务的 `UObject` 资产。  
**解决方法：** 将选择范围限制为支持编辑器事务的资产；跳过非资产或临时对象。

## 7. 仍在使用已弃用的 begin-transaction 辅助函数

**症状：** 出现引用 `BeginTransactionAndGetSelectedAssets` 的弃用警告。  
**原因：** 调用点仍在使用 UE 5.4 中已弃用的辅助函数。  
**解决方法：** 替换为 `GetSelectedAssetsForAction` 加上调用者拥有的 `FScopedTransaction`，并使用 `CheckoutAndSaveAssets` 进行持久化。

## 8. 签出成功但带有警告

**症状：** 结果代码为 `SucceededWithCheckoutWarning`，或签出输出参数为 false，但部分文件已保存。  
**原因：** 在签出期间，源代码控制返回了警告。  
**解决方法：** 检查资产的源代码控制状态，解决锁定/冲突，然后重试 `CheckoutAndSaveAssets`。

## 相关文档

- [QUICKSTART.md](QUICKSTART.md)
- [UserManual.md](UserManual.md)
- [SettingsReference.md](SettingsReference.md)
- [FAQ.md](FAQ.md)
