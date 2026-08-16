<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/CodeCopyrightEditor/architecture.md -->
# Code Copyright Editor ドキュメント

Code Copyright Editor は、プロジェクト全体で Unreal Engine のソースヘッダーの一貫性を維持します。プロジェクト設定（Project Settings）の著作権表示の更新、ソースツリーのスキャン、選択したファイルの書き換え、およびヘッドレス CI チェックとしての実行が可能です。

このフォルダには、プラグインに付属する完全なドキュメントが含まれています。

## ここから始める

- [QUICKSTART.md](QUICKSTART.md): インストール、最初のスキャン、および期待される結果を伴う実際の適用手順。
- [UserManual.md](UserManual.md): 完全なエディターワークフローと UI の使用方法。
- [SettingsReference.md](SettingsReference.md): すべての設定項目、デフォルト値、および推奨される基準構成。
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md): 一般的な問題と解決策。
- [FAQ.md](FAQ.md): 購入者および Fab 向けの Q&A。
- [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md): サードパーティソフトウェアに関する宣言（同梱なし）。

## クイックエディターワークフロー

1. **Tools > Code Tools > Code Copyright Editor** を開きます。
2. ソース用およびプロジェクト用の通知テンプレートを編集します。
3. ファイルを書き込むことなくコードベースを分類するために **Scan Files** を使用します。
4. ステータスバッジを確認し、書き換えるべきファイルのみを選択します。
5. 選択したファイルに対して、オプションのファイルごとの情報や説明を追加します。
6. プレビューを確認した後、**Apply Selected** を使用します。

## クイックテンプレートトークン

一般的なトークン：

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

REUSE/SPDX に準拠したヘッダーにするには、テンプレートの上部付近に次の2つのタグを配置します：

```text
/* {CopyrightText}
 * SPDX-FileCopyrightText: {CopyrightText}
 * SPDX-License-Identifier: {LicenseIdentifier}
```

## コマンドレット

CI またはローカルターミナルから同じスキャナーを実行します：

```powershell
UnrealEditor-Cmd.exe "D:\PluginProjectGit\PluginProject.uproject" -run=CodeCopyrightCheck -unattended -nop4 -nosplash -NoShaderCompile -ReportDir="Saved\CodeCopyrightEditor\Reports"
```

便利なスイッチ：

- `-Fix`: 最終レポートを作成する前に変更可能なファイルを書き換えます。
- `-ReportDir=<Path>`: プロジェクト相対または絶対ディレクトリにレポートを書き込みます。
- `-FailOnProtected`: 保護された外部通知を CI の失敗として扱います。
- `-NoJson`, `-NoSpdx`, `-NoReuse`: 個別のレポート形式をスキップします。
- `-NoFail`: レポートを書き込みますが、常に終了コード `0` を返します。

デフォルトでは、ファイルが変更される場合、コンフリクトが存在する場合、またはファイルの読み込み/書き込みができなかった場合に CI は失敗します。保護されたサードパーティの通知はレポートされますが、`-FailOnProtected` が設定されていない限りビルドは失敗しません。

## クイックレポート

コマンドレットの書き込み先：

- `CodeCopyrightReport.json`: 機械読み取り可能なスキャン要約。
- `CodeCopyrightReport.spdx`: SPDX 2.3 Tag/Value 形式のレポート。
- `REUSE-Report.md`: 人間が読める REUSE/SPDX レビューレポート。

## 法的事項

Code Copyright Editor は、通知テキストの一貫した適用とレビューを支援します。法的所有権の決定、サードパーティライセンスの検証、権利の付与、または法的助言の代わりとなるものではありません。

## 参照

- REUSE 仕様 3.3: https://reuse.software/spec-3.3/
- SPDX 仕様 2.3: https://spdx.github.io/spdx-spec/v2.3/
- Unreal Engine UCommandlet API: https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/Engine/Commandlets/UCommandlet
