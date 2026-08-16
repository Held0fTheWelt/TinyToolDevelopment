<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/LogLevelEditor/architecture.md -->
# 快速入门

本指南将带您从安装一步步实现**实际效果**：更改日志类别的详细级别（Verbosity），并将其保存为跨编辑器重启依然有效的持久重写。Log Level Editor 独立运行，无需安装其他插件。

## 完成本指南后您将获得

打开工具并列出项目的日志类别，更改其中一个类别的详细级别，并将该重写持久化保存到插件的 DataAsset 中。

## 要求

- Unreal Engine 5 编辑器。
- 无需第三方软件、账号或运行时，详见 [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md)。

## 1. 安装并启用

1. 从 Fab 库将 **LogLevelEditor** 添加到项目中（或安装到引擎中）。
2. 打开 **Edit → Plugins**，启用 **LogLevelEditor**，并在收到提示时重启编辑器。

## 2. 打开工具（初次效果）

1. 打开 **Tools → Log Tools → Log Level Editor**。此时将打开一个可停靠的选项卡，并扫描您的项目（以及项目插件）源码中的日志类别。
2. 每行显示 **类别名称**（例如 `LogTemp`）、其 **检测到的默认值**、**当前级别** 以及 **源码路径**（可用时）。

您现在可以看到发现的每个日志类别及其实时详细级别。

## 3. 实际操作示例：更改类别的详细级别

1. 使用搜索框找到 `LogTemp`。
2. 点击该行上的 **Warning** 详细级别按钮。

**预期输出：** 插件运行对应的 Unreal 控制台命令，该行更新为 `Warning`，且该更改作为持久重写写入插件 DataAsset 中（因此在下次编辑器启动时会被重新应用）。

3. 如需撤销：选择该行 **检测到的默认** 详细级别。当选择的值与检测到的默认值匹配时，插件会自动移除持久重写，使 DataAsset 仅关注真实的重写项。

## 4. 重写项保存位置

持久重写存储在配置的 `ULogLevelDataAsset` 中（通过设置中的 **LogLevelDataAsset** 指定）。保存的重写项会在编辑器启动且引擎可以接受控制台命令后重新应用。

## 5. 设置

打开插件设置（Project/Editor settings → Log Level Editor）以控制：

- `LogLevelDataAsset`、`bAutoSaveLogLevelDataAsset`
- `bShowToolbarButton`
- `bAlsoListEnginePluginChannels`、`bAlsoListEngineSourceChannels`（引擎扫描较为耗时）
- `LogChannelsToHide`、`LogChannelsToHideTemporary`

详见 [SettingsReference.md](SettingsReference.md)。

## 6. 后续步骤

- 完整工作流（临时与永久隐藏、团队工作流、启动应用）：
  [UserManual.md](UserManual.md)。
- 常见问题：[TROUBLESHOOTING.md](TROUBLESHOOTING.md) 与 [FAQ.md](FAQ.md)。
