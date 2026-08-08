---
lang: zh
title: EditorExtensionBase Settings Reference
audience: [end_user]
owner_ref: plugin:EditorExtensionBase
applies_to:
  component: EditorExtensionBase
contract_ref: plugin:EditorExtensionBase/widget-properties
version:
  since: "1.0"
---
# 设置参考

EditorExtensionBase **不**提供 `UDeveloperSettings` 类或项目 `.ini` 设置对象。可配置的值作为 `UPROPERTY` 字段存在于共享的 Editor Utility Widget 子类及工具对象中。

## UEditorToolHeaderWidget

| 名称 | 类型 | 默认值 | 效果 |
| --- | --- | --- | --- |
| `TitleText` | `FText` | 小部件默认值 | 标题栏中显示的标题。 |
| `SubtitleText` | `FText` | 小部件默认值 | 标题下方的副标题行。 |
| (BindWidget) 标题/副标题块 | 小部件引用 | 必须绑定 | 必需的 Slate/UMG 插槽；缺失绑定会在运行时发出警告。 |

## UEditorUtilityButtonWidget

| 名称 | 类型 | 默认值 | 效果 |
| --- | --- | --- | --- |
| 按钮样式属性 | 小部件上的样式字段 | 设计师设置 | 共享按钮的视觉样式。 |
| (BindWidget) `Button` / 文本块 | 小部件引用 | 必须绑定 | 点击目标和标签；按钮或文本为空时会记录警告。 |

## UEditorUtilityTabButtonWidget

| 名称 | 类型 | 默认值 | 效果 |
| --- | --- | --- | --- |
| 选中/未选中呈现 | 图标 + 状态字段 | 设计师设置 | 控制选项卡选中状态的外观。 |
| (BindWidget) 按钮/图标插槽 | 小部件引用 | 必须绑定 | 缺失选中/未选中图标时会记录警告。 |

## UUndoableAssetActionUtility

| 名称 | 类型 | 默认值 | 效果 |
| --- | --- | --- | --- |
| 操作描述/资产字段 | editanywhere 工具字段 | 调用者设置 | 描述工具执行的可撤销资产操作。 |
| 结果代码 | 枚举 | 运行时 | 当成功伴随签出警告时，包含 `SucceededWithCheckoutWarning`。 |

## UEditorUtilityTask_PrepareUndo

| 名称 | 类型 | 默认值 | 效果 |
| --- | --- | --- | --- |
| 选中的资产输入 | editanywhere 工具字段 | 调用者设置 | 用于准备撤销的资产；空/无效/非事务性资产将被跳过并记录警告。 |

## 不存在的内容

| 预期内容 | 状态 |
| --- | --- |
| `UEditorExtensionBaseSettings` DeveloperSettings | 源代码中尚不可用 |
| `Config/DefaultEditorExtensionBase.ini` | 未随软件包提供 |
| 项目偏好设置面板 | 尚不可用 |

## 相关文档

- [UserManual.md](UserManual.md) — 行为目录。
- [QUICKSTART.md](QUICKSTART.md) — 首次选择辅助调用。
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md) — BindWidget 和选择警告。
