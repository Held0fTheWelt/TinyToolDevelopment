<!-- doc-provenance: SAD architecture.md sections 1,5,6,8; facts product-facts.yml; reconciled 2026-07-16 -->
# ユーザーマニュアル

## メインワークフロー

IIS は読み取り専用の検索ワークフローに従います：

1. 準備されたエビデンスをインポートします。
2. ローカルカタログを構築または更新します。
3. ベクトル検索が必要な場合にエンベディングを構築します。
4. 検索を実行するか、コンテキストパックを構築します。
5. UMCP を介してエージェントに同じ読み取り専用ツールを公開します。

IIS はプロジェクトに対する変更（mutation）を適用しません。

## プロダクト機能マップ

| ファクトシートの機能 | 購入者向けインターフェース |
| --- | --- |
| `ImportPreparedChunks` | コントロールパネルの Imports タブまたはサービス API から準備されたチャンク JSONL をインポートします。 |
| `Search` | Search タブおよびサービス API からレキシカル、ベクトル、またはハイブリッド検索を実行します。 |
| `BuildContextPack` | クエリまたは選択した結果からエビデンス重視のコンテキストパックを構築します。 |
| `RunPerfSelfCheck` | Blueprint/API およびコンソールから、出荷された合成パフォーマンスセルフチェックを実行します。 |
| `RuntimeControlDispatch` | ランタイムコントロールサーフェスを介して observe、tune、act、persist、および reset コマンドを配信します。 |
| `AgentRetrievalTools` | ローカルコントラクトおよびオプションの UCM/UMCP ルートを介して読み取り専用のエージェント検索操作を提供します。 |

## コントロールパネル

開く：

```text
Tiny Tools -> AI -> Internal Index Service -> Open Internal Index Service
```

タブ：

| タブ | 用途 |
| --- | --- |
| Dashboard | インデックスヘルス、統合ヘルス、再構築ショートカット、検索ショートカット。 |
| Index | インポート、カタログ構築、エンベディングジョブの作成/実行。 |
| Use | ローカルエビデンスに対する検索。 |
| Agents | エージェントコントラクトおよび UMCP ブリッジのステータス。 |
| Governance | 読み取り専用の姿勢、ローカルパス、ブリッジおよびツールの可視性。 |
| Diagnostics | レポート、概要、および生成されたアーティファクトの場所。 |
| Settings | パネル内での `UIISSettings` の表示。 |

## インポートの動作

インポート処理は準備されたチャンク JSONL を消費します。各チャンクには ID、コンテンツ、ソース参照、アセット/シンボル元データ、およびライフサイクル状態が含まれます。IIS は入力検証を行い、承認されたチャンクを追加して、インポートレポートを書き込みます。

重要なファイル：

```text
Saved/InternalIndexService/chunks.jsonl
Saved/InternalIndexService/imports/
Saved/InternalIndexService/reports/
```

## カタログ構築

カタログ構築は保存されたチャンクを読み取り、検索可能なローカル構造を生成します。非アクティブなチャンクライフサイクル状態をフィルタリングし、ユーザーが警告を確認できるようにレポートを書き込みます。

## 検索

検索クエリフィールドには、クエリテキスト、検索モード、最大結果数、フィルター、およびコンテキストパックオプションが含まれます。結果には、チャンク ID、スコア情報、スニペット、およびソース参照が含まれます。

検索モード：

| モード | 意味 |
| --- | --- |
| Lexical | チャンクカタログに対するローカルテキストマッチングを使用します。 |
| Vector | 永続化されたエンベディングと構成されたベクトルバックエンドを使用します。 |
| Hybrid | レキシカル候補とベクトル候補を組み合わせます。 |

## ランタイムコントロールサーフェス

IIS には、エディタを再ロードせずに observe → tune → act を行う**自立的**（autark）なランタイムコントロールサーフェスが含まれています。メモリ内のアクティブな `UIISSettings` オブジェクトを変更し（デフォルトでは一時的）、HNSW の `efSearch` やアクティブな int8 カーネルなどのキャッシュされたレバーを即座に再適用します。

**UCM や UMCP への依存はありません** — サーフェスは Blueprint、C++、およびエディタコンソールから単体で機能します。

### 型定義された Blueprint API (`UIISSubsystem`)

| メソッド | 目的 |
| --- | --- |
| `GetControlState` | 有効なレバーとミューテーションゲート状態のスナップショット。 |
| `SetTuning` | フィールドごとのオプションのチューニング差分（`FIISTuningRequest`）を適用します。 |
| `PersistTuning` | 現在の上書きを設定に書き込みます（`SaveConfig`）。 |
| `ResetTuning` | 設定を再ロードし、一時的な上書きを元に戻します。 |
| `RunPerfSelfCheck` | 構成された予算に対して SYN-2 パフォーマンスワークロードを実行します。 |

### コンソールコマンド

| コマンド | 目的 |
| --- | --- |
| `iis.control.state` | 有効なコントロール状態の JSON を出力します。 |
| `iis.control.tune {json}` | 一時的なチューニング（例：`{"efSearch":128}`）。 |
| `iis.control.persist` | 上書きを設定に保存します。 |
| `iis.control.reset` | 設定を再ロード / 上書きを元に戻します。 |
| `iis.control.diagnostics.recent` | 直近のクエリごとの診断（保持が有効な場合）。 |
| `iis.perf.run` / `iis.perf.last` | 最後のパフォーマンスセルフチェックを実行または読み取ります。 |
| `iis.index.sync` / `iis.index.rebuild` / `iis.index.import` | インデックスメンテナンスのアクション動詞。 |

変更を伴う動詞は、プロジェクト設定の **Enable Runtime Control Mutations**（デフォルトでオン）を尊重します。

## エンベディング

IIS はプロバイダ資格情報を保持しません。エンベディングルートの解決と実行は `FIISEmbeddingDiscovery`（`IModularFeatures` 経由の `IIISEmbeddingRouteExecutor`）を介して委譲されます。通常は `StartupModule` で登録し `ShutdownModule` で登録解除する LLM Store ブリッジによって提供されます。

エンベディングのフロー：

1. ベクトルが必要なチャンクのジョブを構築します。
2. エンベディングルートを解決します。
3. 登録されたエグゼキュータを介してジョブを実行します。
4. ベクトルレコードを永続化します。
5. レポートを更新します。

## エージェントツール

エージェントツールは読み取り専用で、構造化された JSON を返します。IIS は 6 つの自律的な検索操作を定義します。ローカルコントラクト名は、エンジン内および JSON ファイルの呼び出しで引き続き利用可能です：

| ローカルコントラクト | UCM ルート ID | 目的 |
| --- | --- | --- |
| `iis_search` | `iis.agent.search.v1` | インデックス付きチャンクを検索します（インライン JSON ペイロードとアーティファクトパス）。 |
| `iis_get_context_pack` | `iis.agent.get_context_pack.v1` | 検索結果からコンパクトなコンテキストパックを構築します（インライン JSON ペイロードとアーティファクトパス）。 |
| `iis_get_chunk` | `iis.agent.get_chunk.v1` | ID で 1 つのチャンクを取得します。 |
| `iis_get_source_references` | `iis.agent.get_source_references.v1` | チャンクのソース参照を返します。 |
| `iis_find_usages` | `iis.agent.find_usages.v1` | 使用状況レコードを検索します。 |
| `iis_explain_blueprint` | `iis.agent.explain_blueprint.v1` | インデックス付き Blueprint エビデンスを要約します（インライン JSON ペイロードとアーティファクトパス）。 |

`iis.index.status.v1` はさらに `catalog_exists`、`chunk_store_records`、および `vector_records` をレポートするため、エージェントはファイルを読み取らなくてもインデックスが作成されたか確認できます。

MCP トランスポートは Unified MCP Server が所有します。IIS 自体は MCP ツールを登録しません。プロジェクトの Capability Mesh 設定がエージェント操作ごとに 1 つのルートを宣言し、UMCP がそれらを汎用的な `mesh_route_*` ツールとして公開します。ブリッジプラグインは不要です。

## データとプライバシー

IIS は生成されたインデックスをデフォルトでプロジェクトの `Saved` フォルダに保存します。カスタムインデックスルートが設定されている場合は、チームが生成されたエビデンスを意図的に共有していない限り、ローカル/プライベートパスを使用してください。

クラウドへの露出は、LLM Store 内のエンベディングエグゼキュータルートがクラウドプロバイダを使用している場合にのみ発生します。
