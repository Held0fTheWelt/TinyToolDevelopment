<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/CodeCopyrightEditor/architecture.md -->
# Code Copyright Editor 文档

Code Copyright Editor 用于保持整个项目中 Unreal Engine 源码标头的一致性。它可以更新项目设置（Project Settings）中的版权声明、扫描源码树、重写选定的文件，并作为无头 CI 检查运行。

本文件夹包含随插件交付的完整文档。

## 从这里开始

- [QUICKSTART.md](QUICKSTART.md)：安装、首次扫描以及包含预期结果的真实应用流程。
- [UserManual.md](UserManual.md)：完整的编辑器工作流和 UI 使用说明。
- [SettingsReference.md](SettingsReference.md)：各项设置、默认值和推荐的基线配置。
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md)：常见问题与解决方案。
- [FAQ.md](FAQ.md)：针对买家和 Fab 的常见问题与解答。
- [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md)：第三方软件声明（未捆绑任何第三方软件）。

## 快速编辑器工作流

1. 打开 **Tools > Code Tools > Code Copyright Editor**。
2. 编辑源码和项目声明模板。
3. 使用 **Scan Files** 对代码库进行分类，无需写入文件。
4. 审查状态徽章，仅选择应重写的文件。
5. 为选定文件添加可选的单文件信息和描述。
6. 检查预览后使用 **Apply Selected**。

## 快速模板标记 (Tokens)

常用标记：

- `{CopyrightText}`
- `{OwnerName}`
- `{ContactEmail}`
- `{ProductName}`
- `{ModuleName}`
- `{FileName}`
- `{RelativeFilePath}`
- `{Year}`
- `{LicenseName}`
- `{LicenseUrl}`
- `{LicenseIdentifier}`
- `{FileInformation}`
- `{FileDescription}`
- `{FileMetadataBlock}`

对于符合 REUSE/SPDX 规范的标头，请在模板顶部附近保持以下两个标签：

```text
/* {CopyrightText}
 * SPDX-FileCopyrightText: {CopyrightText}
 * SPDX-License-Identifier: {LicenseIdentifier}
```

## Commandlet

在 CI 或本地终端中运行相同的扫描器：

```powershell
UnrealEditor-Cmd.exe "D:\PluginProjectGit\PluginProject.uproject" -run=CodeCopyrightCheck -unattended -nop4 -nosplash -NoShaderCompile -ReportDir="Saved\CodeCopyrightEditor\Reports"
```

实用开关：

- `-Fix`：在生成最终报告前重写可更改的文件。
- `-ReportDir=<Path>`：将报告写入项目相对或绝对目录。
- `-FailOnProtected`：将受保护的外部声明视为 CI 失败。
- `-NoJson`, `-NoSpdx`, `-NoReuse`：跳过单独的报告格式。
- `-NoFail`：写入报告但始终返回退出代码 `0`。

默认情况下，当文件将被修改、存在冲突或文件无法读取/写入时，CI 将会失败。受保护的第三方声明会被报告，但除非设置了 `-FailOnProtected`，否则不会导致构建失败。

## 快速报告

Commandlet 将写入：

- `CodeCopyrightReport.json`：机器可读的扫描摘要。
- `CodeCopyrightReport.spdx`：SPDX 2.3 Tag/Value 风格报告。
- `REUSE-Report.md`：人类可读的 REUSE/SPDX 审查报告。

## 法律说明

Code Copyright Editor 旨在帮助一致地应用和审查声明文本。它不会决定法律所有权、验证第三方许可证、授予权利或替代法律咨询。

## 参考资料

- REUSE 规范 3.3：https://reuse.software/spec-3.3/
- SPDX 规范 2.3：https://spdx.github.io/spdx-spec/v2.3/
- Unreal Engine UCommandlet API：https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/Engine/Commandlets/UCommandlet
