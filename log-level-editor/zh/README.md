<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/LogLevelEditor/architecture.md -->
# LogLevelEditor 文档

LogLevelEditor 是一款 Unreal Engine 编辑器插件，用于发现日志类别并从专注的编辑器仪表板更改其详细级别（Verbosity）。它帮助团队减少日常工作中的冗余日志，在调试时临时调高诊断通道，并在 DataAsset 中持久化保存有意的修改。

核心操作为 **Scan**（扫描）、**Set Verbosity**（设置详细级别）和 **Hide Category**（隐藏类别）。

本文件夹包含随插件提供的完整文档。

## 从这里开始

- [BUYER_GUIDE.md](BUYER_GUIDE.md)：买家友好型概述、适用场景和实用价值。
- [UserManual.md](UserManual.md)：从设置到应用重写的完整编辑器工作流。
- [FAQ.md](FAQ.md)：面向 Fab 的常见买家问答。

## 参考资料

- [SettingsReference.md](SettingsReference.md)：每个设置项、默认行为和推荐基线。
- [TechnicalOverview.md](TechnicalOverview.md)：面向维护者的架构和运行时行为。
- [CodeDocumentation.md](CodeDocumentation.md)：源码布局、代码契约和扩展点。
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md)：常见问题和修复方法。
- [ReleaseChecklist.md](ReleaseChecklist.md)：发布 Fab 更新前的验证步骤。

## 包含的资产

- `../Readme.pdf`：传统打包 Readme。
- `../LogLevelEditor_Changelog.txt`：发布说明。
- `../Content/DA_LogLevelVerbosity.uasset`：用于持久化详细级别重写的默认 DataAsset。
- `../Content/Map_Tutorial_LogLevelEditor.umap`：教程 / 演示内容。

## 快速工作流

1. 启用插件，并在收到提示时重启编辑器。
2. 通过 **Tools → Log Tools → Log Level Editor** 或可选的工具栏快捷方式打开 Log Level Editor 选项卡。
3. 让扫描器发现项目和插件的日志类别。
4. 使用搜索和隐藏设置来专注于重要的通道。
5. 通过该行对应的详细级别按钮更改日志类别的详细级别。
6. 当更改是有意为之时，将重写持久化保存在配置的 `ULogLevelDataAsset` 中。
7. 通过再次选择检测到的默认值，将类别重置为其检测到的默认值。

## 工具所做的修改

插件通过以下形式应用 Unreal 控制台命令：

```text
Log <CategoryName> <VerbosityName>
```

它不会修改日志类别的源码声明。持久性更改存储在配置的 DataAsset 中，并在引擎准备好接受控制台命令后由编辑器模块重新应用。

## 支持的详细级别名称

共享的详细级别助手支持 Unreal 的标准日志级别：

- `NoLogging`
- `Fatal`
- `Error`
- `Warning`
- `Display`
- `Log`
- `Verbose`
- `VeryVerbose`

编辑器特意使用了与 Unreal 日志配置相同的名称，以便用户可以将 UI 更改直接映射到控制台命令行为。

## 安全模型

LogLevelEditor 避免向用户显示虚假状态：

- 当可以查询类别时，`Current`（当前）标签直接从 Unreal 的运行时状态获取。
- 仅在控制台命令执行成功后才更新 UI 状态。
- 当选择的值与检测到的默认值匹配时，将自动移除持久重写。
- 临时隐藏设置保持挥发性（Transient），不会写入配置文件。
- 保存的重写在启动期间带有按类别的重试逻辑，因为编辑器在模块启动时并不总是准备好接受控制台命令。

## 典型用途

- 减少繁杂插件的日志轰炸，同时保持插件处于启用状态。
- 临时将 Gameplay、构建、资产或编辑器子系统提升至 `Verbose`。
- 排查问题后恢复干净的默认设置。
- 共享包含有意的项目级详细级别重写的团队 DataAsset。
- 通过设置分离引擎和项目类别，保持扫描快速且高效。

## 重要限制

- 日志类别必须存在于源码中，或者已被运行时/编辑器模块注册。
- 源码扫描只能从常见的 Unreal 宏中推断默认值。
- 在编辑器应用保存的重写之后，运行时代码仍可能更改详细级别。
- 打包发布的最终构建（Shipping build）不受此编辑器插件影响。

## 法律说明

LogLevelEditor 是一款编辑器生产力工具。它不会改变 Unreal Engine 的日志记录语义、引擎源码或项目许可条款。
