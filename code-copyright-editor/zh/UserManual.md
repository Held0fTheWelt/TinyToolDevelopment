<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/CodeCopyrightEditor/architecture.md -->
# 用户手册

本手册介绍了 Code Copyright Editor 的完整编辑器工作流。

## 目的

Code Copyright Editor 在两个地方管理版权声明文本：

- Unreal Engine 项目级别的版权声明。
- 配置的项目和插件文件夹中的源码文件标头。

该插件专为受控的源码重写而构建。它先进行扫描、展示预览、允许用户选择文件，并且仅在确认后才重写被选中的可更改文件。

## 打开工具

启用插件后，打开：

```text
Tools > Code Tools > Code Copyright Editor
```

插件还在以下路径公开了配置：

```text
Project Settings > Plugins > Code Copyright Editor
```

## 核心工作流

1. 配置身份、许可证、模板、范围和保护设置。
2. 保存设置。
3. 必要时更新项目设置声明（Project Settings Notice）。
4. 扫描代码库。
5. 审查状态徽章和预览。
6. 添加可选的单文件元数据。
7. 仅选择应重写的文件。
8. 应用到选定文件。
9. 运行另一次扫描以进行验证。
10. 导出报告或在 CI 中运行 Commandlet。

扫描绝不会写入源码文件。应用操作仅重写被分类为可更改且被勾选的文件。

## 编辑器选项卡

主编辑器窗口划分为聚焦特定功能的选项卡：

| 选项卡 | 目的 |
| --- | --- |
| `Configure` | 编辑模板、所有者/许可证设置、扫描范围、保护规则和项目声明设置。 |
| `Scan & Review` | 运行扫描、检查文件状态、选择可更改文件、排除文件以及对比现有/提议声明。 |
| `File Metadata` | 添加或清除由元数据标记渲染的选定文件信息和描述。 |
| `Apply & Reports` | 确认选定的重写并导出最新的编辑器 JSON 扫描报告。 |
| `Help` | 阅读内置工作流指南和状态图例。 |

## 状态值

| 状态 | 含义 | 应用时的行为 |
| --- | --- | --- |
| `OK` | 文件已与渲染后的模板匹配。 | 不需要。 |
| `MISSING` | 未找到兼容的声明。 | 在启用时可以插入。 |
| `REPLACE` | 可以替换自有的声明或 Unreal 占位符。 | 可以重写。 |
| `PROTECTED` | 找到了外部、Epic 或第三方声明。 | 不会自动重写。 |
| `CONFLICT` | 自有标记和受保护标记同时出现。 | 需要人工审查。 |
| `EXCLUDED` | 文件匹配排除规则。 | 不予处理。 |
| `READ_ERROR` | 文件无法读取。 | 不予处理。 |
| `WRITE_ERROR` | 文件无法保存。 | 不予处理。 |
| `UPDATED` | 文件在上次应用流程中已写入。 | 运行另一次扫描以验证。 |

## 单文件元数据

单文件元数据为单个文件添加上下文，而无需更改全局模板。

可用元数据：

- `File Information`
- `Description`

推荐工作流：

1. 扫描文件。
2. 选择一个文件。
3. 输入文件信息或描述。
4. 点击 `Save File Metadata`。
5. 确保模板包含 `{FileMetadataBlock}`。
6. 检查预览。
7. 如果渲染后的声明正确，则应用该文件。

`Clear File Metadata` 会删除选定文件已存储的元数据。

## 应用选定项 (Apply Selected)

在应用之前，编辑器会提示确认。受保护文件和冲突文件保持原样。

在应用之后，工具会运行另一次扫描并显示：

- 应用结果。
- 当前扫描结果。
- 更新后的状态行。

在进行批量重写之前，请务必使用版本控制。为了在首次应用时获得额外的安全保障，建议启用 `Create Backup Before Write`。

## 插件不会做的事情

Code Copyright Editor 不会执行以下操作：

- 决定法律所有权。
- 授予许可证权利。
- 验证第三方许可证。
- 替代法律咨询。
- 自动重写受保护的声明。
- 在打包后的游戏中运行。

它为声明、报告和 CI 检查提供了一致的技术工作流。
