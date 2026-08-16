<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/CodeCopyrightEditor/architecture.md -->
# 快速入门

本指南将带您从安装走向**真实成果**：将一致的版权声明应用于选定的源码文件，并生成可打开查看的扫描报告。Code Copyright Editor 完全独立运行——不需要任何其他插件。

## 完成本指南后您将获得

已配置的所有者/许可证信息、具有单文件状态的代码库扫描结果，以及对您选择的文件施加的受控重写——加上位于 `Saved/CodeCopyrightEditor/` 下的 JSON 扫描报告。

## 要求

- Unreal Engine 5 编辑器（插件运行在编辑器中，而不是打包后的游戏中）。
- 包含要扫描的源码/插件文件夹的 C++ 或 Blueprint 项目。
- 无需第三方软件、账号或外部运行时。请参阅 [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md)。

## 1. 安装与启用

1. 从您的 Fab 库中将 **Code Copyright Editor** 添加到项目（或安装到引擎中）。
2. 在编辑器中，打开 **Edit → Plugins**，启用 **Code Copyright Editor**，并在提示时重启。

## 2. 打开工具 (首次成果)

1. 打开 **Tools → Code Tools → Code Copyright Editor**。
2. 在 **Configure** 选项卡上，设置您的身份和许可证（所有者、许可证标识符、模板、扫描范围）。点击 **Save**。
3. 切换到 **Scan & Review** 并点击 **Scan Files**。

您现在可以看到每个符合条件的文件的状态徽章（`OK`、`MISSING`、`REPLACE`、`PROTECTED`……）。扫描绝不会写入文件——这是一个安全的预览。

## 3. 真实示例：将声明应用于选定文件

1. 在 **Scan & Review** 上，点击 **Select Changeable**——这只会勾选可以安全重写的行（`MISSING`、`REPLACE`）。`PROTECTED` 和 `CONFLICT` 文件保持原样。
2. 先选择单行，并在预览中对比**现有**声明与**提议**声明。
3. （推荐）在 **Configure** 选项卡上，启用 **Create Backup Before Write**，并先将您的工作提交到版本控制。
4. 点击 **Apply Selected** 并确认。工具仅重写被勾选且可更改的文件，然后重新扫描。

**预期输出：** 应用的文件转为状态 `UPDATED`；显示应用结果和新的扫描结果。在 **Apply & Reports** 上，点击 **Export JSON**。

## 4. 结果存放位置

```text
Saved/CodeCopyrightEditor/LastCopyrightScan.json
```

您还可以通过 **Update Project Notice** 更新项目级声明（不重写源码），该操作会写入 *Project Settings → Project → Description → Legal → Copyright Notice*。

## 5. 后续步骤

- 完整工作流及每个选项卡/操作：[UserManual.md](UserManual.md)。
- 所有模板标记 (`{CopyrightText}`, `{LicenseIdentifier}`, `{FileMetadataBlock}`, …)：[SettingsReference.md](SettingsReference.md)。
- 设置项：[SettingsReference.md](SettingsReference.md)。
- 问题排查：[TROUBLESHOOTING.md](TROUBLESHOOTING.md) 和 [FAQ.md](FAQ.md)。
