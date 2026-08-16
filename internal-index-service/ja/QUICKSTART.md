<!-- doc-provenance: SAD architecture.md sections 1,3,6,7,8; facts product-facts.yml; reconciled 2026-07-16 -->
# クイックスタート

## 1. プラグインを有効化する

プラグインブラウザで `Internal Index Service` を有効にします。Unreal から求められた場合はエディタを再起動します。

## 2. コントロールパネルを開く

以下を使用します：

```text
Tiny Tools -> AI -> Internal Index Service -> Open Internal Index Service
```

コントロールパネルが Dashboard で開きます。

## 3. 設定を構成する

以下を開きます：

```text
Edit -> Project Settings -> Plugins -> Internal Index Service
```

推奨される最初のセットアップ：

| 設定 | 値 |
| --- | --- |
| Vector Backend | `jsonl_bruteforce` |
| Vector Storage Format | `Int8 Per-Vector Scale` |
| Allow Experimental Vector Formats | `false` |
| Index Root | 空 |

`Index Root` が空の場合、IIS は以下を使用します：

```text
Saved/InternalIndexService
```

デフォルトのストレージポリシーは、HNSW パーティションにベクトルごとの int8 スケーリングを使用します。これが通常のコンパクトモードです。`Float32` は高精度/デバッグ実行で使用可能です。`Experimental Global Scale` は、トレードオフを意図的に測定している場合を除き、無効のままにしてください。

## 4. 準備されたチャンクをインポートする

コントロールパネルの Imports タブを使用するか、準備されたチャンク JSONL ファイルを指定してサービス API を呼び出します。準備されたチャンクは通常、Unreal Integration Intelligence などの付属抽出パイプラインから提供されます。

インポートにより、IIS の saved フォルダの下にレポートが書き込まれ、チャンクストアが更新されます。

## 5. カタログを構築する

Dashboard の **Rebuild** アクションまたは Catalog タブを使用します。IIS はインポートされたチャンクを読み取り、ライフサイクル状態を正規化して、カタログ構築レポートを書き込みます。

## 6. 検索する

Search タブを使用します：

- レキシカル検索はローカルカタログから動作します
- ベクトル検索にはエンベディングが必要です
- ハイブリッド検索は、ベクトルが存在する場合に両方を組み合わせます

## 7. エンベディングを構築する（任意 – ベクトル検索を追加、LLM Store が必要）

レキシカル検索（ステップ 1〜6）は、他のプラグインなしで単体で動作します。ベクトル検索およびハイブリッド検索はオプションの拡張機能です。最初に **LLM Store** プラグインを構成すると、IIS はエンベディングエグゼキュータリジストリにルートを要求し、ジョブを作成して、エンベディングレポートを書き込みます。Embeddings タブからジョブを実行します。LLM Store がなくても、IIS はインポート、構築、およびレキシカル検索を継続して処理します。

## 8. エージェントツールを公開する（任意 – Unified MCP Server + Capability Mesh が必要）

このステップはオプションであり、AI エージェントに IIS を呼び出させたい場合にのみ必要です。以下をインストールして有効にします：

- Unified MCP Server
- Unreal Capability Mesh

プロジェクトの Capability Mesh プロファイルに IIS エージェントルート（例：`iis.agent.search.v1`）が含まれていることを確認します。次に Unified MCP Server を起動します。各 IIS エージェント機能は自律的な UCM ルートとして公開され、以下のように `mesh_route_*` MCP ツールに平坦化されます：

```text
mesh_route_iis_agent_search_v1_<hash>
mesh_route_iis_agent_get_context_pack_v1_<hash>
mesh_route_iis_agent_get_chunk_v1_<hash>
mesh_route_iis_agent_get_source_references_v1_<hash>
mesh_route_iis_agent_find_usages_v1_<hash>
mesh_route_iis_agent_explain_blueprint_v1_<hash>
```

または、`route_id` をルート ID（例：`iis.agent.search.v1`）に設定して `mesh_execute_route` を呼び出します。

## 9. ランタイムチューニング（任意 - 追加プラグイン不要）

提供されるランタイムコントロールサーフェスは**自立的**（autark）であり、UCM や UMCP は不要です。

エディタの出力ログコンソールを開き、以下を実行します：

```text
iis.control.state
```

応答の抜粋例（デフォルトの `efSearch` は 64）：

```json
{"ok":true,"errorCode":"","errorMessage":"","efSearch":64,...}
```

クエリ時の `efSearch` をライブで引き上げます：

```text
iis.control.tune {"efSearch":128}
```

変更を確認します：

```text
iis.control.state
```

チューニング後の例：

```json
{"ok":true,"errorCode":"","errorMessage":"","efSearch":128,...}
```

上書きは `iis.control.persist` を実行するまで**一時的**（transient）です。設定からリロードするには `iis.control.reset` を使用します。コンソールコマンドの完全なリストと Blueprint API については `UserManual.md` を参照してください。
