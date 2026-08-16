<!-- doc-provenance: SAD architecture.md sections 1,2,7,8; facts product-facts.yml; reconciled 2026-07-16 -->
# Internal Index Service

Internal Index Service (IIS) は、**ローカル**でのインデックス作成、検索（retrieval）、コンテキストパック、およびエージェント向け検索を提供する Unreal Engine プラグインです。本プラグインは検索専用（retrieval-only）であり、プロジェクトコンテンツの変更やパッチの生成は行いません。

## モジュール

| モジュール | 目的 |
| --- | --- |
| `InternalIndexServiceInterface` | チャンク、検索、インポート、エンベディング、およびエージェントアクセス用の公開コントラクト。 |
| `InternalIndexService` | ランタイムエンジンサブシステム、チャンクカタログ、ベクトルバックエンド、エンベディングジョブ、増分インデックス作成。 |
| `InternalIndexServiceEditor` | エディタコントロールパネル、Python ブリッジ、および Tiny Tools メニューエントリー。 |

## コントロールパネルを開く

```text
Tiny Tools -> AI -> Internal Index Service -> Open Internal Index Service
```

または、レイアウトにすでに表示されている場合はノマドタブ **Internal Index Service** を使用します。

パネルは以下のように構成されています：

| タブ | 目的 |
| --- | --- |
| **Dashboard** | Index および Integrations のヘルスカード；クイックアクション（カタログの再構築）。 |
| **Overview** | サービスバージョン、インデックスルート、カタログ/ベクトルの存在確認。 |
| **Imports** | UII ハンドオフおよびインポートレポートの概要。 |
| **Catalog** | カタログの構築および `Saved/InternalIndexService/reports` 下でのランタイムカタログ構築サマリーの表示。 |
| **Embeddings** | 検出された `IIISEmbeddingRouteExecutor` を介した永続化エンベディングジョブの構築と実行。 |
| **Search** | ローカルインデックスに対するインラインのレキシカル/ベクトル/ハイブリッド検索。 |
| **Agent/MCP** | エージェントコントラクト、UCM ルート ID、および Unified MCP Server を介した MCP アクセスガイド。 |
| **Reports** | レポートおよびログフォルダへのショートカット。 |

ヘッダーには、プロジェクト名、検索専用マーカー、**Settings** ボタン、および **Refresh** ボタンが表示されます。Refresh を実行すると、すべてのタブサマリーが更新され、Dashboard カードの更新が強制され、Governance パネルが更新されます。

Dashboard カードは、開いたとき、明示的な **Refresh** 実行時、および **Rebuild** などのダッシュボードアクションの後に更新されます。パネルは定期タイマーでカードを再構築しないため、編集や検査中も UI が安定して保たれます。

## プロジェクト設定

IIS の設定は以下で行います：

```text
Edit -> Project Settings -> Plugins -> Internal Index Service
```

| 設定 | デフォルト | 意味 |
| --- | --- | --- |
| **Vector Backend** | `jsonl_bruteforce` | ローカルベクトルインデックスの実装（`jsonl_bruteforce` または `hnsw`）。レコード数に応じた自動ブルートフォース/HNSW ルーティング。 |
| **Index Root (optional)** | *(空)* | ディスク上のインデックスルートの上書き。空の場合は `Saved/InternalIndexService` を使用。 |
| **Brute Force Max Records** | `10000` | HNSW が使用される前の正確な検索のしきい値。 |
| **Embedding Executor Id** | *(空)* | 優先されるエンベディングエグゼキュータ。空の場合は通常の IIS 検出を使用。オプションの IIS LLM Store Bridge は、ロード時にこれを `llmstore` に設定します。 |
| **Vector Storage Format** | `Int8 Per-Vector Scale` | HNSW ストレージポリシー。通常の使用にはコンパクトなベクトルごとの int8 デフォルトを維持し、高精度/デバッグ実行には `Float32` を使用します。`Experimental Global Scale` は実験的ゲート内でのみ使用してください。 |
| **Allow Experimental Vector Formats** | `false` | 再現率（recall）を低下させる可能性がある計測専用のベクトルレイアウトを有効にします。 |
| **Rebuild On Vector Format Mismatch** | `true` | 不互換な永続化 HNSW パーティションを誤ったバイトレイアウトでロードする代わりに再構築します。 |
| **Quantization Recall Gate** | `0.7` | 量子化自動テストで使用される最小再現率目標。代表的なプロジェクトで検証した後に引き上げます。 |
| **HNSW M / efConstruction / efSearch** | `16` / `200` / `64` | HNSW の再現率、構築時間、メモリ、およびクエリレイテンシのチューニング。 |

MCP アクセスは、プロジェクトの Capability Mesh ルートを介して Unified MCP Server によって提供されます。IIS は専用の IIS UMCP ブリッジを出荷せず、必要ともしません。

## 統合

エンベディングの実行は `FIISEmbeddingDiscovery`（`IModularFeatures` / `IIISEmbeddingRouteExecutor`）を介して委譲されます。ブリッジプラグインは `StartupModule` で登録し、`ShutdownModule` で登録解除します。`FIISEmbeddingRouteExecutorRegistry` はレガシー呼び出し元向けの非推奨アダプタです。

Dashboard の **Integrations** カードには、`FIISEmbeddingDiscovery::GetExecutorIds()` から取得したエグゼキュータ ID と、各統合がアクティブかどうかがリスト表示されます。

エディタのジョブ履歴は、UMCP コンパイル時プロバイダではなく、UCM ルート（`iis.editor.jobs.list.v1`、`iis.editor.jobs.status.v1`）を介して公開されます。リストルートは、パネル履歴と最近の SQLite エンベディングジョブ行をマージします。

## 関連ドキュメント

| ドキュメント | 対象者 |
| --- | --- |
| [QUICKSTART.md](QUICKSTART.md) | 初めてのセットアップ、インポート、インデックス構築、および検索。 |
| [UserManual.md](UserManual.md) | 完全なエディタワークフローと運用の挙動。 |
| [SettingsReference.md](SettingsReference.md) | 設定、生成されるファイル、およびストレージパス。 |
| [TechnicalOverview.md](TechnicalOverview.md) | メンテナレベルのアーキテクチャとデータフロー。 |
| [CodeDocumentation.md](CodeDocumentation.md) | C++ ソースマップ、コアクラス、および実行パス。 |
| [INTEGRATION.md](INTEGRATION.md) | UII、LLM Store、および UMCP を IIS にブリッジする方法。 |
| [FAQ.md](FAQ.md) | 購入者およびレビュー担当者のよくある質問。 |
| [TROUBLESHOOTING.md](TROUBLESHOOTING.md) | よくある障害と解決策。 |
| [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md) | Fab 提出用のサードパーティソース宣言の詳細。 |
| [../CHANGELOG.md](../CHANGELOG.md) | リリースノート。 |

## パッケージング

`Config/FilterPlugin.ini` には `/Documentation/...` が含まれているため、購入者は Fab ビルドでこのフォルダを受け取ります。
また、BuildPlugin によって生成された事前コンパイルメタデータもパッケージ化された出力に残ります。IIS を Unreal Engine インストールにインストールする場合は、そのエンジンバージョン用にビルドされたパッケージを使用し、生成されたバイナリとメタデータをそのまま保持してください。
