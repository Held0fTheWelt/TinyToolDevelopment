<!-- doc-provenance: SAD architecture.md sections 2,8,10; facts product-facts.yml; reconciled 2026-07-16 -->
# 設定リファレンス

IIS の設定は `UIISSettings` に保存されます。

開く：

```text
Edit -> Project Settings -> Plugins -> Internal Index Service
```

## フィールド

| 設定 | デフォルト | 意味 |
| --- | --- | --- |
| Vector Backend | `jsonl_bruteforce` | ローカルベクトル検索バックエンドを選択します。サポートされている値には `jsonl_bruteforce` および `hnsw` が含まれます。`jsonl_bruteforce` を使用すると、IIS は以下のブルートフォースレコード制限を超えた場合に自動的に HNSW に切り替わります。 |
| Index Root | 空 | 生成される IIS データのオプションの上書き。空の場合は `Saved/InternalIndexService` を使用。 |
| Brute Force Max Records | `10000` | このレコード数以下では正確なブルートフォース検索が使用され、これを超えると HNSW が使用されます。 |
| Embedding Executor Id | 空 | 優先される IIS エンベディングエグゼキュータ ID。空の場合は通常の検出を使用。オプションの IIS LLM Store Bridge は、ロード時にこれを `llmstore` に設定します。 |
| Vector Storage Format | `Int8 Per-Vector Scale` | HNSW ベクトルストレージポリシー。`Int8 Per-Vector Scale` はサポートされているコンパクトなデフォルトです。`Float32` は高精度/デバッグ実行に便利です。`Experimental Global Scale` は制限付きの計測専用です。 |
| Allow Experimental Vector Formats | `false` | 実験的な HNSW ストレージフォーマットを有効にします。無効な場合、実験的な選択肢は `Int8 Per-Vector Scale` にフォールバックします。 |
| Rebuild On Vector Format Mismatch | `true` | 不互換な永続化 HNSW パーティションを削除し、誤ったバイトレイアウトで読み込む代わりにソースベクトルから再構築できるようにします。 |
| Quantization Recall Gate | `0.7` | 量子化ベクトルストレージ自動化ゲートで使用される最小再現率目標。代表的なプロジェクトエンベディングで検証した後にのみ引き上げてください。 |
| HNSW M | `16` | HNSW グラフの接続性。高くするとメモリと構築時間を犠牲にして再現率が向上します。新規構築インデックスに適用されます。 |
| HNSW efConstruction | `200` | 構築時の候補リストサイズ。高くすると構築時間を犠牲にしてグラフ品質と再現率が向上します。新規構築インデックスに適用されます。 |
| HNSW efSearch | `64` | クエリ時の候補リストサイズ。高くするとクエリレイテンシを犠牲にして再現率が向上します。ロード時および再構築時に適用されます。 |
| Enable Runtime Control Mutations | `true` | ランタイムコントロールサーフェスのマスターゲート。オフの場合、tune/act/persist コンソールおよび API 動詞は拒否されますが、読み取りは引き続き機能します。 |
| Retain Recent Diagnostics | `false` | オンにすると、IIS は `diagnostics.recent` / コンソール検査用に直近のクエリごとの診断の制限付きインメモリリングバッファを保持します。 |
| Recent Diagnostics Max Count | `64` | Retain Recent Diagnostics がオンのときに保持される最大診断数。 |
| Estimate Recall By Default | `false` | オンにすると、クエリが明示的にオプトアウトしない限り、検索時に recall@K を推定します。正確な参照スキャン（SYN-1）が追加されます。 |

> HNSW インデックスはデフォルトで int8 スカラー量子化（ベクトルごとのスケーリング）を使用して保存されるため、インデックスメモリとディスクサイズを削減しながら高い再現率を維持します。Float32 は高精度/デバッグポリシーとして利用可能です。実験的なグローバルスケール int8 は、正規化された高次元エンベディングでほとんどの int8 レベルを無駄にする可能性があるため、意図的に制限されています。別のストレージポリシーで構築されたインデックスは検出され、デフォルトで自動的に再構築されます。

## 生成されるパス

デフォルトルート：

```text
Saved/InternalIndexService
```

重要な生成エリア：

| パス | 目的 |
| --- | --- |
| `chunks.jsonl` | インポートされたチャンクストア。 |
| `imports/` | インポートマニフェストおよびレポート。 |
| `reports/` | カタログ、エンベディング、および診断レポート。 |
| `agent_contracts/` | ブリッジによって消費されるエージェントツールコントラクトおよび MCP マニフェスト。 |
| `vectors/` またはバックエンド固有のファイル | 永続化されたエンベディング/ベクトルデータ。 |

正確なファイル名はワークフローやバックエンドによって異なる場合があります。

## MCP 設定

MCP サーバー設定は IIS 内にはありません。以下で構成してください：

```text
Edit -> Editor Settings -> Plugins -> Unified MCP Server
```

IIS エージェントアクセスは、`iis.agent.search.v1` などのプロジェクト Capability Mesh ルートを介して公開されます。

## 秘密情報の取り扱い

IIS はプロバイダの秘密情報を保存しません。エンベディングプロバイダの資格情報は LLM Store またはプロバイダ環境に属します。

## 推奨されるデフォルト

| シナリオ | Vector Backend | Vector Storage Format | 実験的フォーマット | Index Root |
| --- | --- | --- | --- | --- |
| 初めてのセットアップ | `jsonl_bruteforce` | `Int8 Per-Vector Scale` | 無効 | 空 |
| 大規模ローカルインデックス | `hnsw` | `Int8 Per-Vector Scale` | 無効 | 空またはプロジェクトローカルのカスタムパス |
| 高精度デバッグ | `hnsw` | `Float32` | 無効 | 一時ワークスペースパス |
| 再現率実験 | `hnsw` | `Experimental Global Scale` | 有効 | 一時ワークスペースパス |
| 共有 CI 検証 | `jsonl_bruteforce` | `Int8 Per-Vector Scale` | 無効 | 一時ワークスペースパス |
