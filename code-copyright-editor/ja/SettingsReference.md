<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/CodeCopyrightEditor/architecture.md -->
# 設定リファレンス

Code Copyright Editor の設定は以下から利用可能です：

```text
Project Settings > Plugins > Code Copyright Editor
```

エディターウィンドウにも、主要なテンプレートおよびワークフローアクションが表示されます。

## アイデンティティ

| 設定項目 | デフォルト値 | 使用先 |
| --- | --- | --- |
| `OwnerName` | `Your Company or Name` | `{OwnerName}`, `{CopyrightText}`, レポート |
| `ContactEmail` | 空 | `{ContactEmail}` |
| `ProductNameFallback` | `PluginProject` | プラグインのフレンドリー名が見つからない場合の `{ProductName}` |
| `CopyrightStartYear` | `2025` | `{Year}`, `{CopyrightText}` |

`{Year}` は、現在の年と等しい場合は開始年としてレンダリングされます。現在の年と異なる場合は、`2025-2026` のような範囲としてレンダリングされます。

## ライセンス

| 設定項目 | デフォルト値 | 使用先 |
| --- | --- | --- |
| `LicenseName` | `Fab Standard End User License Agreement` | `{LicenseName}` |
| `LicenseUrl` | `https://www.fab.com/eula` | `{LicenseUrl}` |
| `LicenseIdentifier` | `LicenseRef-Fab-Standard-EULA` | `{LicenseIdentifier}`, レポート |

標準ライセンスには、`MIT` や `Apache-2.0` などの標準 SPDX 識別子を使用します。製品 EULA などのカスタムまたはマーケットプレイス固有のライセンスには `LicenseRef-*` を使用します。

## テンプレート

| 設定項目 | 目的 |
| --- | --- |
| `SourceNoticeTemplate` | ソースファイルに表示されるヘッダー。 |
| `ProjectSettingsNoticeTemplate` | Unreal のプロジェクトレベルの著作権フィールドに表示される通知。 |

## スキャン範囲 (Scope)

| 設定項目 | デフォルト値 | 目的 |
| --- | --- | --- |
| `ScanRootPaths` | `Source`, `Plugins` | `Scan Files` によってスキャンされるフォルダ。 |
| `SourceFileExtensions` | `.h`, `.hpp`, `.hh`, `.inl`, `.c`, `.cc`, `.cpp`, `.cxx`, `.cs`, `.usf`, `.ush` | ソースファイルとして扱われる拡張子。 |
| `ExcludedPathFragments` | `.git`, `.vs`, `Binaries`, `Content`, `DerivedDataCache`, `External`, `Intermediate`, `Resources`, `Saved`, `ThirdParty` | スキャン時にスキップされるフォルダ/パス断片。 |
| `ExcludedFilePaths` | デフォルトは空 | スキャン時にスキップされる正確なプロジェクト相対ファイル。 |
| `ExcludedFilePatterns` | `*.generated.h` | スキャン時にスキップされるワイルドカードパターン。 |

## 保護

| 設定項目 | デフォルト値 | 目的 |
| --- | --- | --- |
| `ProtectForeignNotices` | 有効 | 不明な通知テキストが自動的に書き換えられるのを防ぎます。 |
| `TreatUnrealDefaultNoticesAsReplaceable` | 有効 | Unreal のプレースホルダー/デフォルト通知の置き換えを許可します。 |
| `OwnNoticeMarkers` | 所有者名、ライセンス識別子、Fab EULA テキスト、Unreal プレースホルダーテキスト | このプロジェクトに属する通知を識別します。 |
| `ProtectedNoticeMarkers` | サードパーティおよび Epic の著作権マーカー | 自動書き換えすべきでない通知を識別します。 |

## 推奨される基準構成

多くの Fab プラグイン製品向け：

- `ProtectForeignNotices` を有効に維持します。
- `TreatUnrealDefaultNoticesAsReplaceable` を有効に維持します。
- `ThirdParty`, `External`, `Binaries`, `Intermediate`, および `Saved` を除外に維持します。
- Fab EULA 製品には `LicenseRef-Fab-Standard-EULA` を使用します。
- ソーステンプレートの上部付近に SPDX 行を配置します。
- オプションのファイルレベルのコンテキストには `{FileMetadataBlock}` を使用します。
