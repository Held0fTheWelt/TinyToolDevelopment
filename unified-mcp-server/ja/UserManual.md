<!-- doc-provenance: AKDB:plugins/UnifiedMcpServer/architecture.md; docs/architecture/plugins/UnifiedMcpServer/product-facts.yml; reconciled 2026-07-04 -->
# ユーザーマニュアル

## 設定を開く

Unified MCP Server は以下から構成します:

```text
Edit -> Editor Settings -> Plugins -> Unified MCP Server
```

設定項目:

| 設定 | デフォルト | 意味 |
| --- | --- | --- |
| Enable MCP Server | オフ | エディターモジュールがローカル MCP サーバーを実行できるようにします。 |
| Server Port | 8732 | `127.0.0.1` で使用される TCP ポート。 |
| Validate Tool Arguments | オフ | プロバイダー呼び出しの前に、`tools/call` の引数を各ツールの `inputSchema` に対してオプションで検証します。 |
| Access Profile | Default | ハイレベルの公開モード: Default、Read Only、Automation、または Experimental。 |
| Disabled Provider IDs | 空 | 一致するプロバイダー ID のすべてのツールを非表示にしてブロックします。 |
| Allowed Tool Names | 空 | 公開するツール名またはワイルドカードパターンのオプション許可リスト。空の場合はブロックされていないすべてのツールを許可します。 |
| Blocked Tool Names | 空 | 公開ツール名またはワイルドカードパターンを非表示にしてブロックします。 |
| Allowed Tool Groups | 空 | `read_only`、`non_destructive`、`idempotent` などの注釈由来グループのオプション許可リスト。 |
| Blocked Tool Groups | 空 | `risky`、`destructive`、`open_world` などの注釈由来グループを非表示にしてブロックします。 |
| Enable Access Journal | オン | `tools/call` 用のシークレットセーフなアクセス診断を書き出します。 |
| Access Journal Ring Capacity | 500 | コントロールパネルおよび Blueprint 診断用にメモリ内に保持される直近のエントリー数。 |
| Access Journal Max File Bytes | 5242880 | ファイルローテーション前の `access_audit.jsonl` の最大サイズ。 |

## Tiny Tools メニュー

エディターの **Tiny Tools -> AI -> Universal MCP** の下にライフサイクルとステータスのアクションが追加されます:

| アクション | 結果 |
| --- | --- |
| Open Control Panel | ライフサイクルボタンとプラグインごとにグループ化された接続機能ツリーを備えた UMCP コントロールパネルを開きます。 |
| Start Unified MCP Server | ループバック HTTP エンドポイントを起動します。 |
| Stop Unified MCP Server | エンドポイントを停止し、ハンドシェイクファイルを削除します。 |
| Rotate MCP Token | 新しいスコープ付き Bearer トークンを生成し、ハンドシェイクファイルを書き換えます。 |

**AI** セクションは、Unified MCP Server を Internal Index Service などの Tiny Tool Development の他の AI プラグインとともにグループ化します。

## コントロールパネル (Control Panel)

コントロールパネルには以下が表示されます:

| エリア | 詳細 |
| --- | --- |
| Status | 実行/停止状態、起動設定、エンドポイント URL、トークンの有無/数、リクエスト数、プロバイダー数、ツール数、およびハンドシェイクファイルのパス。 |
| Actions | 起動、停止、トークンローテーション、エージェントフォルダーを開く、および更新。 |
| Tabs | プロバイダー/ツール/スキーマ用の Connected Functions と、直近のツール呼び出しおよびランタイムブロックコントロール用の Access Activity。 |
| Connected Functions | プロバイダーの切り替え、ツール行、アクセス/準備状態、MCP ツール名、説明、および遅延ロードされる入力/出力スキーマテーブルを備えた展開可能なプラグイングループ。 |
| Access Activity | トークン/クライアント/結果の詳細を備えた直近のツール呼び出し、ランタイムブロック数、更新、トークン/ツールのブロック/ブロック解除、およびランタイムブロック解除アクション。 |

### Connected Functions のレイアウト

Connected Functions は Capability Mesh ルートカタログに似た階層ツリーを使用します:

1. **プラグイングループ** — インターフェース数と、グループが単一プロバイダーにマップされている場合はアクセス有効/無効ボタンを備えたプラグインごとの 1 行。矢印をクリックすると、そのプラグインのツールを表示または非表示にできます。
2. **ツール行** — 接続された MCP ツールまたはセットアップ宣言された UCM 機能ごとの 1 行。矢印をクリックすると、そのツールの入力/出力スキーマテーブルを表示または非表示にできます。

列レイアウトは**各プラグイングループ内**の展開状態に依存します:

| 状態 | 列 |
| --- | --- |
| すべてのツールが折りたたまれている | `Provider`、`Ready`、`Tool`、`Description`（広め） |
| いずれかのツールが展開されている | `Provider`、`Ready`、`Tool`、`Input`、`Output`、`Description` |

**プロバイダーのグループ化:** 直接的なプロバイダーツールはその `GetProviderDisplayName()` の下に表示されます。平坦化された UCM ルートツール（`mesh_route_*`）は、メッシュホストエントリーの下ではなく、Capability Mesh 機能メタデータ（例: Internal Index Service または SmartContentDiet）からの**所有プラグイン**の下に表示されます。`mesh_list_routes` や `mesh_reload_setup` などの汎用メッシュホストツールは **Unreal Capability Mesh** の下に残ります。

**パフォーマンス:** パネルはツールのメタデータを非同期でロードします。変更されていないデータは、再訪問、起動/停止、および展開/折りたたみ時にキャッシュから取得されます。UCM セットアップの変更後に完全な再ロードを強制するには **Refresh** を使用します。

`Needs approval` とマークされた行は承認が必要な UCM 機能です。ツールチップは UCM ルート内または `mesh_configure_experimental_self_approval` 内の**実験的（EXPERIMENTAL）**自動自己承認パスを指しています。これは自己責任のテストにのみ使用してください。

`Blocked` または `Hidden` とマークされた行は MCP クライアントに公開されません。UMCP はこれらを `tools/list` から削除し、クライアントが直接ツール名を呼び出した場合は `tool_access_denied` を返します。

**Access Activity** タブからのランタイムブロックは、エディターセッションの一時的なブロックです。エディター設定には書き込まれず、影響を受けるトークンの `tools/list` からツールを非表示にし、直接の呼び出しを `runtime_access_denied` で拒否し、サーバー停止時にクリアされます。

ツールの説明には、プロバイダーが公開している場合、読み取り専用、破壊的、冪等、またはオープンワールド動作などの MCP 注釈ヒントが含まれます。パネルには、プロファイルおよびグループアクセスポリシーで使用される派生グループも表示されます。

## 接続ファイル

ハンドシェイクファイル:

```text
Saved/UnifiedMcpServer/agent/mcp_endpoint.json
```

リクエストログ:

```text
Saved/UnifiedMcpServer/logs/mcp_requests.jsonl
```

アクセスジャーナル:

```text
Saved/UnifiedMcpServer/logs/access_audit.jsonl
```

ハンドシェイクファイルには、ローカルホスト、ポート、互換性用 `token`、およびスコープ付き `tokens` が含まれています。ローカル資格情報として扱ってください。

アクセスジャーナルでは、token、secret、password、API キー、authorization、bearer などのシークレットと思われる引数キーが除外されます。

## サポートされている MCP 呼び出し

サーバーは以下の JSON-RPC メソッドを処理します:

| メソッド | 動作 |
| --- | --- |
| `initialize` | プロトコルバージョン、ツール機能、およびサーバー情報を返します。 |
| `notifications/initialized` | クライアントの初期化を確認します。 |
| `ping` | 空の結果を返します。 |
| `tools/list` | `inputSchema`、オプションの `outputSchema`、オプションのツール `annotations`、および `_meta.toolsRevision` を含む、登録されているプロバイダーからのすべてのツールを返します。 |
| `tools/call` | 接頭辞付きのプロバイダーツール名をそのプロバイダーにルーティングし、可能であれば JSON 結果をテキストおよび `structuredContent` として返します。 |

不明なメソッドは JSON-RPC の method-not-found エラーを返します。

## エディタージョブツール

Unreal Capability Mesh が利用可能な場合、UMCP は読み取り専用のジョブ集計ツールを公開します:

| ツール | 目的 |
| --- | --- |
| `jobs_list` | IIS、SmartContentDiet、LLM Store、および UMCP 用の固定 UCM ルートからの直近のジョブを統合します。オプションの `provider_id` および `max_count` 引数で結果を絞り込むことができます。 |
| `jobs_status` | 同じルートテーブルから 1 つのジョブ ID を検索し、一致するソースプロバイダー ID を返します。 |

ソースプラグインは UCM ルートを介して自身のエディタージョブ一覧/ステータスを公開し、UMCP には依存しません。UCM または 1 つのルートが利用できない場合、集計はそのルートをスキップし、利用可能なプロバイダーからのジョブを返します。

## プロバイダーの操作

Unified MCP Server 自体にはプロジェクトツールが含まれていません。プロバイダーがそれらを追加します。プロバイダーは `IUmcpToolProvider` を介して記述子、入力スキーマ、および呼び出しロジックを提供します。

プロバイダーがインストールされると、ツールは次のように表示されます:

```text
provider_tool
```

例:

```text
mesh_route_iis_agent_search_v1_<hash>
```

Unreal Capability Mesh がロードされている場合、UMCP は汎用メッシュツールを公開します:

```text
mesh_reload_setup
mesh_list_capabilities
mesh_list_routes
mesh_configure_experimental_self_approval
mesh_dry_run_route
mesh_execute_route
mesh_invoke_endpoint
```

UMCP は、宣言された Capability Mesh ルートごとに平坦化された MCP ツールとしても公開します:

```text
mesh_route_<sanitized_route_id>_<hash>
```

平坦化されたルートツールは `mode: "execute"` または `mode: "dry_run"` を受け入れます。`input` または `input_json` が省略された場合、残りの引数はルート入力オブジェクトとして扱われます。シリアル化された `request_json` を内部でバインドするルートの場合、UMCP は平坦化された引数を自動的に `request_json` にミラーリングします。平坦化された各ルートツールは、`readOnlyHint`、`destructiveHint`、`openWorldHint` などのルート由来の MCP `inputSchema`、`outputSchema`、および注釈を公開します。変更を伴うルートは引き続き Capability Mesh のポリシーおよび承認チェックを通過します。

変更を伴う操作には `mesh_execute_route` を使用し、Capability Mesh のルートポリシーと承認チェックがアクティブのままになるようにしてください。

`mesh_configure_experimental_self_approval` は明示的に**実験的（EXPERIMENTAL）**であり、**自己責任で使用**する必要があります。承認が必要な UCM ルートがグローバルまたはルート ID ごとに自動自己承認するかどうかを読み取りまたは変更できます。有効化には `acknowledge_experimental_risk: true` が必要です。

## 運用上の注意

- エディターインスタンスごとに一意のポートを使用してください。
- ハンドシェイクファイルが表示される可能性があるログやスクリーンショットを共有した後は、トークンをローテーションしてください。
- 外部エージェントがアクセスを必要としなくなった場合は、サーバーを停止してください。
- プロバイダープラグインが有効になっていない場合、`tools/list` が正当に空のリストを返すことがあります。
