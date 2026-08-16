<!-- doc-provenance: product-facts.yml reconciled 2026-07-01; source AKDB:plugins/AssetLoaderStudio/architecture.md -->
# 設定リファレンス

Asset Loader Studio の設定は、ガバナンスプロファイル、許可されたルート/クラス、監査ポリシー、およびルートオーバーライドを中心に展開されます。

## ガバナンス設定

| 設定項目 | 型 | デフォルト値 | 効果 |
| --- | --- | --- | --- |
| `DefaultProfileId` | string | `guided_safe` | ルートまたはリクエストのプロファイルが指定されていない場合にデフォルトの権限プロファイルを選択します。 |
| `ProfileDirectories` | array | `Config/AssetLoaderStudio/Governance/Profiles` | 権限プロファイル JSON がスキャンされるフォルダを一覧表示します。 |
| `AllowedRoots` | array | `/Game`, `/Engine` | 変更対象を承認された Unreal ルートに制限します。 |
| `AllowedClasses` | array | パッケージのデフォルト | 設定されている場合、変更対象を承認されたクラスパスに制限します。 |
| `AuditRetentionDays` | integer | `30` | 削除前に監査ログを保持する期間を制御します。 |
| `AuditLogDirectory` | string | `Saved/AssetLoaderStudio/Audit` | プレビューおよび適用操作用の永続化された監査エントリを保存します。 |
| `bAuditPreviewOperations` | boolean | `true` | 操作プレビューの監査エントリを書き込みます。 |
| `bAuditApplyOperations` | boolean | `true` | 適用操作の監査エントリを書き込みます。 |

## 権限プロファイルフィールド

権限プロファイルは、`profile_id`、許可されたアクション、影響を受ける最大アセット/行数、許可されたルート/クラス、読み取り専用モード、ドライランモード、適用確認、破壊的操作の承認、および監査保持期間を定義します。検査には `read_only`、通常のレビュー付き編集には `guided_safe`、信頼できる一括作業のみに `expert` を使用します。

## ルートオーバーライド

オプションのルートオーバーライドは、UCM ルートをより厳格なプロファイルまたはより緩やかなプロファイルにマッピングできます。ルートオーバーライドはローカルのプレビュー/適用チェックを置き換えるものではなく、それらのチェックで使用されるプロファイルを選択するだけです。

## 実用的なデフォルト値

- レビューを行うエディター作業には `guided_safe` から始めてください。
- アセットを変更すべきではない検出、検証、テーブルエクスポート、自動チェックには `read_only` を維持してください。
- `expert` は信頼できる一括作業にのみ使用し、破壊的操作の承認は明示的に維持してください。
- 通常のリリースレビュー期間をカバーできるように、監査保持期間を十分に長く保持してください。
