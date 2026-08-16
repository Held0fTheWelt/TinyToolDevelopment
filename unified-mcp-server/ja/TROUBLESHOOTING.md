<!-- doc-provenance: AKDB:plugins/UnifiedMcpServer/architecture.md; docs/architecture/plugins/UnifiedMcpServer/product-facts.yml; reconciled 2026-07-04 -->
# トラブルシューティング

## クライアントが 401 Unauthorized を受信する

クライアントが以下を送信しているか確認してください:

```text
Authorization: Bearer <token>
```

現在の互換性トークンまたはスコープ付きトークンを以下から読み取ります:

```text
Saved/UnifiedMcpServer/agent/mcp_endpoint.json
```

トークンがローテーションされた場合は、クライアント構成を更新してください。

## ステータス応答でトークンが公開される場合

ライフサイクルおよびステータス応答は、ハンドシェイクの有無、パス、ポート、およびトークン数のみをレポートします。生のハンドシェイク JSON や Bearer トークン値を返してはなりません。診断経由でシークレットをコピーするのではなく、承認されたクライアント構成にはローカルハンドシェイクファイルを使用してください。

## ハンドシェイクファイルが存在しない

考えられる原因:

- サーバーが実行されていない
- サーバーが構成されたポートへのバインドに失敗した
- プラグインが無効になっている
- エディターがまだモジュールを起動していない

以下からサーバーを起動します:

```text
Tiny Tools -> AI -> Universal MCP -> Start Unified MCP Server
```

## ポートがすでに使用されている

以下でポートを変更します:

```text
Edit -> Editor Settings -> Plugins -> Unified MCP Server
```

その後、サーバーを再起動します。

## `tools/list` がツールを返さない

Unified MCP Server はホストにすぎません。汎用の `mesh_*` ツールを取得するには Unreal Capability Mesh を有効にするか、別のプロバイダープラグインを有効にします。また、プロバイダーが準備完了状態を報告し、モジュール型機能を登録していることを確認してください。

Editor Settings およびコントロールパネルでアクセス制御を確認してください。無効化されたプロバイダー ID、制限の厳しいアクセスプロファイル、空でない許可リスト、ブロックされたツールパターン、またはブロックされたツールグループは、一致するツールを `tools/list` から意図的に非表示にします。

汎用の `mesh_*` ツールは表示されるが `mesh_route_*` ツールが表示されない場合は、`mesh_reload_setup` を実行するか Capability Mesh パネルで **Reload Setup** をクリックし、MCP クライアントを更新してください。ルートツールは `Config/UnrealCapabilityMesh` 内のアクティブなルートマニフェストから生成されます。

`mesh_configure_experimental_self_approval` が表示される場合、自己責任の**実験的（EXPERIMENTAL）**テストツールとして扱ってください。有効化には `acknowledge_experimental_risk: true` が必要で、選択されたルートまたは承認が必要なすべてのルートに対する Capability Mesh の承認動作を変更します。

UCM Routes UI で自動自己承認が変更されたにもかかわらず、MCP クライアントに古いルート説明が表示される場合は、再度 `tools/list` を呼び出すか、クライアントを再接続/更新してください。UMCP はルートツールを一覧表示する前に UCM セットアップを再ロードし、`mesh_list_routes` は現在の `experimental_self_approval_*` 状態を直接返します。

## コントロールパネルの接続機能が古いように見える

コントロールパネルは、訪問を高速化するためにツールのメタデータをキャッシュします。UCM セットアップの変更、プロバイダーの追加、またはルートの再ロード後は、コントロールパネルで **Refresh** をクリックして接続機能の完全な再ロードを強制してください。起動/停止および展開/折りたたみは、基礎となるスナップショットに変更がない場合、キャッシュを再利用します。

## Stdio クライアントが直接接続できない

プラグインは HTTP トランスポートを公開します。Stdio 専用クライアントには、`mcp-remote` などのユーザーがインストールしたブリッジが必要です。

## ツール呼び出しが未知のツールを返す

`tools/list` から公開されている名前を確認してください。接頭辞付きの名前を使用します:

```text
<providerId>_<toolName>
```

プロバイダーローカルの名前を直接呼び出さないでください。

## ツール呼び出しが `tool_access_denied` を返す

ツール名は存在しますが、UMCP アクセス制御によってブロックされました。`AccessProfile` を確認し、`DisabledProviderIds` からプロバイダー ID を削除するか、`AllowedToolNames` または `AllowedToolGroups` を調整するか、`BlockedToolNames` または `BlockedToolGroups` から一致するエントリーを削除してください。

## UE 5.6 で C++ 標準エラーが発生してビルドが失敗する

UMCP モジュールおよび依存するブリッジモジュールが C++20 でコンパイルされていることを確認してください。UE 5.6 のエンジンヘッダーはコアヘッダーで C++20 構文を使用しています。

## リクエストログの場所

リクエストメタデータは以下に書き出されます:

```text
Saved/UnifiedMcpServer/logs/mcp_requests.jsonl
```

メソッド名、ステータスコード、レイテンシ、およびエラーコードを検査するために使用してください。
