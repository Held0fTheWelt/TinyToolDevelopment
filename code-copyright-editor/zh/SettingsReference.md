<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/CodeCopyrightEditor/architecture.md -->
# 设置参考

Code Copyright Editor 设置可在以下位置获取：

```text
Project Settings > Plugins > Code Copyright Editor
```

编辑器窗口也公开了最重要的模板和工作流操作。

## 身份

| 设置项 | 默认值 | 使用者 |
| --- | --- | --- |
| `OwnerName` | `Your Company or Name` | `{OwnerName}`, `{CopyrightText}`, 报告 |
| `ContactEmail` | 空 | `{ContactEmail}` |
| `ProductNameFallback` | `PluginProject` | 当未找到插件友好名称时的 `{ProductName}` |
| `CopyrightStartYear` | `2025` | `{Year}`, `{CopyrightText}` |

`{Year}` 当等于当前年份时渲染为起始年份。如果当前年份不同，则渲染为范围（如 `2025-2026`）。

## 许可证

| 设置项 | 默认值 | 使用者 |
| --- | --- | --- |
| `LicenseName` | `Fab Standard End User License Agreement` | `{LicenseName}` |
| `LicenseUrl` | `https://www.fab.com/eula` | `{LicenseUrl}` |
| `LicenseIdentifier` | `LicenseRef-Fab-Standard-EULA` | `{LicenseIdentifier}`, 报告 |

标准许可证请使用标准 SPDX 标识符（例如 `MIT` 或 `Apache-2.0`）。对于自定义或特定市场的许可证（如产品 EULA），请使用 `LicenseRef-*`。

## 模板

| 设置项 | 目的 |
| --- | --- |
| `SourceNoticeTemplate` | 渲染到源码文件中的标头。 |
| `ProjectSettingsNoticeTemplate` | 渲染到 Unreal 项目级版权字段中的声明。 |

## 范围 (Scope)

| 设置项 | 默认值 | 目的 |
| --- | --- | --- |
| `ScanRootPaths` | `Source`, `Plugins` | 由 `Scan Files` 扫描的文件夹。 |
| `SourceFileExtensions` | `.h`, `.hpp`, `.hh`, `.inl`, `.c`, `.cc`, `.cpp`, `.cxx`, `.cs`, `.usf`, `.ush` | 被视为源码文件的扩展名。 |
| `ExcludedPathFragments` | `.git`, `.vs`, `Binaries`, `Content`, `DerivedDataCache`, `External`, `Intermediate`, `Resources`, `Saved`, `ThirdParty` | 扫描时跳过的文件夹/路径片段。 |
| `ExcludedFilePaths` | 默认为空 | 扫描时跳过的精确项目相对文件。 |
| `ExcludedFilePatterns` | `*.generated.h` | 扫描时跳过的通配符模式。 |

## 保护

| 设置项 | 默认值 | 目的 |
| --- | --- | --- |
| `ProtectForeignNotices` | 启用 | 防止未知的声明文本被自动重写。 |
| `TreatUnrealDefaultNoticesAsReplaceable` | 启用 | 允许替换 Unreal 占位符/默认声明。 |
| `OwnNoticeMarkers` | 所有者名称、许可证标识符、Fab EULA 文本、Unreal 占位符文本 | 标识属于本项目的声明。 |
| `ProtectedNoticeMarkers` | 第三方和 Epic 版权标记 | 标识不应自动重写的声明。 |

## 推荐基线配置

对于大多数 Fab 插件产品：

- 保持 `ProtectForeignNotices` 启用。
- 保持 `TreatUnrealDefaultNoticesAsReplaceable` 启用。
- 保持 `ThirdParty`、`External`、`Binaries`、`Intermediate` 和 `Saved` 被排除。
- Fab EULA 产品请使用 `LicenseRef-Fab-Standard-EULA`。
- 将 SPDX 行放在源码模板顶部附近。
- 使用 `{FileMetadataBlock}` 提供可选的单文件上下文。
