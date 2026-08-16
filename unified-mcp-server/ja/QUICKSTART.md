<!-- doc-provenance: AKDB:plugins/UnifiedMcpServer/architecture.md; docs/architecture/plugins/UnifiedMcpServer/product-facts.yml; reconciled 2026-07-04 -->
# クイックスタート

## 1. プラグインを有効化する

プラグインブラウザーで `Unified MCP Server` を有効にし、Unreal から求められた場合はエディターを再起動します。

## 2. サーバーを有効化する

開く:

```text
Edit -> Editor Settings -> Plugins -> Unified MCP Server
```

**Enable MCP Server** をオンにします。他のローカルサービスがすでに使用していない限り、デフォルトポート `8732` を維持します。

## 3. サーバーを起動する

使用手順:

```text
Tiny Tools -> AI -> Universal MCP -> Start Unified MCP Server
```

ステータス、ライフサイクルボタン、およびプラグインごとにグループ化された接続機能ツリーを表示するには、以下を使用します:

```text
Tiny Tools -> AI -> Universal MCP -> Open Control Panel
```

接続機能エリアはツールをプラグインごとにグループ化し、スキーマの遅延展開をサポートし、訪問間で変更されていないメタデータをキャッシュします。UCM セットアップ変更後に完全な再ロードを強制するには、**Refresh** を使用します。

UMCP 1.0.3 以降では、コントロールパネルにアクセス状態も表示されます。単一プロバイダーグループを無効にすると、そのツールが `tools/list` から非表示になり、直接の `tools/call` 実行がブロックされます。

エディター起動前に設定が有効になっている場合、エディターモジュールのロード時にサーバーの自動起動も試行されます。

## 4. ハンドシェイクファイルを読み取る

起動後、エディターは以下を書き出します:

```text
Saved/UnifiedMcpServer/agent/mcp_endpoint.json
```

構造例:

```json
{
  "host": "127.0.0.1",
  "port": 8732,
  "token": "<default-token>",
  "tokens": {
    "default": {"token": "<default-token>", "scope": "default", "profile": "Project Settings"},
    "read_only": {"token": "<read-only-token>", "scope": "read_only", "profile": "Read Only"},
    "automation": {"token": "<automation-token>", "scope": "automation", "profile": "Automation"},
    "experimental_admin": {"token": "<experimental-token>", "scope": "experimental_admin", "profile": "Experimental"}
  }
}
```

互換性用の `token` フィールドを使用するか、`tokens` からトークンを 1 つ選択します:

```text
Authorization: Bearer <選択したトークン>
```

## 5. クライアントを接続する

HTTP 対応の MCP クライアントは以下を呼び出すことができます:

```text
http://127.0.0.1:8732/mcp
```

サーバーが実行されている状態でコントロールパネルを開き、**Copy MCP Client Config** をクリックします。
これにより、ライブエンドポイント URL と現在のデフォルト Bearer トークンが含まれた、そのまま貼り付け可能な `mcp.json` スニペットがコピーされます。MCP クライアントの構成ファイルに貼り付けてください。
**Rotate Tokens** を実行した後は、Bearer トークンが変更されるため、スニペットを再度コピーしてください。

`initialize` 時に UMCP は `protocolVersion` をネゴシエートします。クライアントがサポートされているバージョン（`2025-06-18`、`2025-03-26`、または `2024-11-05`）を要求した場合、サーバーはそのバージョンを応答します。それ以外の場合は `2024-11-05` で応答します。UMCP は Streamable-HTTP JSON 応答サブセットを使用し、サーバーからクライアントへの SSE ストリームをホストしないため、`GET /mcp` によるクライアントのプローブは HTTP 405 を返します。

Stdio 専用クライアントには、`mcp-remote` などのユーザーがインストールしたブリッジが必要です。そのブリッジはこのプラグインには同梱されていません。

## 6. ツールを追加する（オプション）

サーバーは単体で動作します。このステップではクライアントが呼び出すツールを追加します。独立した 2 つのオプションがあり、プロジェクトに適合するものだけが必要となります:

- **独自（または任意の）プラグイン:** `IUmcpToolProvider` モジュール型機能を登録すると、そのツールが `<providerId>_<toolName>` として自動的に表示されます。カタログプラグインは不要です。[INTEGRATION.md](INTEGRATION.md) を参照してください。
- **オプション — Unreal Capability Mesh (UCM):** Unreal Capability Mesh も所有している場合、それを有効にするとセットアップ宣言された `mesh_*` ツールが追加され、呼び出し元は構成された UCM ルート（例: IIS コンテキストパック、PRS 配置、SCD 移行アドバイス、DataAsset/DataTable 管理）を `mesh_execute_route` または生成された直接の `mesh_route_*` ツール経由で実行できるようになります。また、`mesh_configure_experimental_self_approval` も公開されます。このツールは**実験的（EXPERIMENTAL）**であり、有効化には明示的なリスク確認が必要で、自己責任によるテストワークフロー専用です。

両方ともオプションです — サーバー、ハンドシェイク、およびクライアント接続（ステップ 1〜5）は、プロバイダーがインストールされていなくても動作します。

## 7. 停止またはローテーション

Tiny Tools メニューを使用します:

```text
Tiny Tools -> AI -> Universal MCP -> Stop Unified MCP Server
Tiny Tools -> AI -> Universal MCP -> Rotate MCP Token
```

停止するとハンドシェイクファイルが削除されます。ローテーションすると新しいスコープ付きトークンで上書きされます。両方のアクションはコントロールパネルからも利用できます。
