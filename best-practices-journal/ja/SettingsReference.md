<!-- doc-provenance: product-facts.yml reconciled 2026-07-19; source AKDB:plugins/BestPracticesJournal/architecture.md; release 1.1.2 -->
# 設定リファレンス

BPJ の設定では、プロジェクトローカルのプラクティスアーティファクトがどこに配置されるか、およびオプションのストレージ投影がどのように動作するかを選択します。

| 設定項目 | 型 | デフォルト値 | 効果 |
| --- | --- | --- | --- |
| `StorageBackend` | enum | `JsonArtifacts` | JSON アーティファクト、SQLite ローカルモード、または Postgres ベースのスタジオプロファイルを選択します。 |
| `StorageScope` | enum | `ProjectSaved` | プロジェクト、ユーザー、ワークスペース、またはカスタムストレージスコープを選択します。 |
| `StorageRootOverride` | path | 空 | カスタムの場所が必要な場合、ローカルアーティファクトルートをオーバーライドします。 |
| `WorkspaceStorageRoot` | path | 空 | 共有ワークスペースアーティファクトルートを BPJ に指定します。 |
| `SQLiteDatabasePathOverride` | path | 空 | ローカルプロフェッショナルモード用の SQLite データベースファイルパスをオーバーライドします。 |
| `SQLiteDatabaseFileName` | string | `bpj.sqlite` | デフォルトのローカル SQLite データベースファイルに名前を付けます。 |
| `PostgresConnectionProfileName` | string | プロファイル定義 | スタジオ Postgres セットアップで使用される外部ブリッジプロファイルに名前を付けます。 |
| `PostgresDsnEnvironmentVariable` | string | `BPJ_POSTGRES_DSN` | 外部ブリッジツールで使用される環境変数に名前を付けます。 |
| `bEnableJsonCompatibilityExport` | boolean | true | 別のストレージモードが選択されている場合でも、ポータブルな JSON エクスポートを利用可能な状態に維持します。 |
| `bEnableMarkdownProjection` | boolean | true | レビューおよびハンドオフ用に人間が読める Markdown 投影を書き込みます。 |
| `bEnableIisDerivedIndex` | boolean | true | オプションのインデックス作成ワークフローが存在する場合、派生した IIS 検索エクスポートを許可します。 |
| `JournalSourceFolders` | path array | 空 | BPJ が認識しその場で表示する、プロジェクトまたは単一ファイルジャーナルを含むローカルディレクトリを選択します。 |

配布可能なプラグインファイルの外に機密情報を保持してください。BPJ はデータベースサーバーを同梱せず、プロバイダーの資格情報を永続化しません。

## ストレージの安全性

デフォルトの `JsonArtifacts` バックエンドは、選択されたストレージルート配下にポータブルなファイルを書き込むことで、BPJ の扱いやすさとレビューしやすさを保持します。SQLite および Postgres プロファイルは、ローカルのプロフェッショナル向けまたはスタジオ向けワークフロー用オプションのストレージ選択肢です。これらがデータベースサーバーをプラグインパッケージの一部にすることはありません。

下流のツール、レビューアー、または CI が安定した JSON アーティファクトを必要とする場合は、`bEnableJsonCompatibilityExport` を有効に維持してください。人間が読めるレビューおよびハンドオフファイルを必要とする場合は、`bEnableMarkdownProjection` を有効に維持してください。

## 推奨されるデフォルト値

- 初回利用および Fab セーフなパッケージ検証には `JsonArtifacts` と `ProjectSaved` を使用してください。
- プロジェクトにレビュー済みのローカルアーティファクトポリシーがある場合にのみ `StorageRootOverride` を設定してください。
- ブリーフおよび成果のレビュー用に Markdown 投影を有効に維持してください。
- SQLite または Postgres が選択されている場合は、JSON 互換エクスポートを有効に維持してください。
- IIS 派生インデックスは標準の BPJ ストアではなく、オプションの派生出力として扱ってください。

## データ処理

選択されたストレージルートには、プロジェクトのパス、レビューメモ、エビデンスの説明、実装成果の詳細、検証レポートのパス、および出所のメタデータが含まれる場合があります。プロジェクト外部に送信する前に、エクスポート内容をレビューしてください。
