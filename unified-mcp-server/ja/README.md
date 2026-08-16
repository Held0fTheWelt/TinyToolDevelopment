<!-- doc-provenance: AKDB:plugins/UnifiedMcpServer/architecture.md; docs/architecture/plugins/UnifiedMcpServer/product-facts.yml; reconciled 2026-07-04 -->
# Unified MCP Server

Unified MCP Server は、プロジェクト全体に対して単一のローカル Model Context Protocol (MCP) エンドポイントを提供する Unreal Engine エディタープラグインです。他のプラグインは小さなモジュール型機能インターフェースを介してツールを接続するため、サーバーはそれらのプラグインに直接依存することなく新しい機能を公開できます。

このプラグインは意図的にインフラストラクチャ専用として設計されています。外部実行可能ファイル、Node パッケージ、Python ランタイムは同梱されていません。エディター内にループバック JSON-RPC 2.0 MCP エンドポイントをホストし、プロバイダーがランタイム時にツールを登録できるようにします。

## モジュール構成

| モジュール | 目的 |
| --- | --- |
| `UnifiedMcpServerInterface` | 公開 `IUmcpToolProvider` 契約、およびツール記述子/結果型。 |
| `UnifiedMcpServerEditor` | サーバー、設定、トークン処理、プロバイダーレジストリ、ステータスコントロールパネル、および Tiny Tools メニューエントリーのエディターホスト。 |

## 主なワークフロー

1. プロジェクトでプラグインを有効化します。
2. `Edit -> Editor Settings -> Plugins -> Unified MCP Server` を開きます。
3. ローカルサーバーを有効にし、ポートを選択するか、デフォルトの `8732` を維持します。
4. ステータス、ライフサイクルボタン、プラグインごとにグループ化された接続機能ツリーを表示するには、`Tiny Tools -> AI -> Universal MCP -> Open Control Panel` を使用します。
5. コントロールパネルまたは `Tiny Tools -> AI -> Universal MCP -> Start Unified MCP Server` からサーバーを起動します。
6. `Saved/UnifiedMcpServer/agent/mcp_endpoint.json` から接続データを読み取ります。
7. `Authorization: Bearer <token>` を指定して `http://127.0.0.1:8732/mcp` を呼び出すように MCP クライアントを構成します。

## ツールプロバイダー (Tool Providers)

プロバイダープラグインは `IUmcpToolProvider` を実装し、Unreal モジュール型機能として登録します。公開されるツール名は次の構造を使用します:

```text
<providerId>_<toolName>
```

Unreal Capability Mesh がロードされている場合、組み込みのメッシュプロバイダーは `mesh_list_capabilities`、`mesh_list_routes`、`mesh_configure_experimental_self_approval`、`mesh_dry_run_route`、`mesh_execute_route` などの汎用ツールを公開します。また、セットアップで宣言された UCM ルートを直接的な `mesh_route_*` MCP ツールに平坦化します。これらのルートツールは、ルート由来の MCP `inputSchema`、`outputSchema`、およびツール注釈を公開するため、クライアントは呼び出し前にパラメーターとリスクのヒントを検査できます。`mesh_configure_experimental_self_approval` は**実験的（EXPERIMENTAL）**であり、**自己責任で使用**する必要があります。有効化には明示的なリスク確認が必要です。レガシーの直接プロバイダーブリッジも製品固有のツール名を登録できますが、UCM ルートがプロジェクトにおいて推奨されるセットアップパスです。

`tools/call` はプロバイダーの JSON をテキストコンテンツとして返し、結果が JSON オブジェクトの場合は MCP `structuredContent` としても返します。`initialize` は `tools.listChanged` を通知し、`tools/list` には `_meta.toolsRevision` 値が含まれるため、クライアントは UCM セットアップ変更後にキャッシュされたツール記述子を更新できます。

UMCP 1.0.3 では、単一エンドポイントの上にアクセス制御が追加されました。プロバイダー ID を無効化でき、公開ツール名は完全一致名またはワイルドカードパターンで許可またはブロックできます。UMCP 1.0.4 ではプロファイル（`Default`、`Read Only`、`Automation`、`Experimental`）および注釈由来のツールグループが追加されました。UMCP 1.0.5 ではスコープ付きセッショントークンが追加され、異なるクライアントが同じ `/mcp` エンドポイントを介して `default`、`read_only`、`automation`、または `experimental_admin` アクセスを使用できるようになりました。UMCP 1.0.6 では、ランタイム Access Guard ブロックと、直近の `tools/call` 診断用シークレットセーフ Access Journal が追加されました。同じポリシーが `tools/list` と `tools/call` の両方に適用されます。コントロールパネルには、接続された機能が公開、ブロック、非表示、または利用不可のいずれであるかが表示されます。

## セキュリティ

- サーバーは `127.0.0.1` にのみバインドします。
- サーバーはデフォルトで無効になっています。
- リクエストにはハンドシェイクファイルからの Bearer トークンが 1 つ必要です。
- プロバイダー/ツールアクセス制御により、`tools/list` からツールを非表示にし、直接の `tools/call` 実行をブロックできます。
- ランタイム Access Guard ブロックはメモリ内のみに存在し、サーバー停止時にクリアされます。
- トークンは **Tiny Tools -> AI -> Universal MCP** からローテーションできます。
- ハンドシェイクファイルはサーバー停止時に削除されます。
- リクエストメタデータは `Saved/UnifiedMcpServer/logs/mcp_requests.jsonl` に記録されます。
- アクセス診断は、シークレットと思われる引数キーを除外して `Saved/UnifiedMcpServer/logs/access_audit.jsonl` に記録されます。

## ドキュメント

| ドキュメント | 目的 |
| --- | --- |
| [BUYER_GUIDE.md](BUYER_GUIDE.md) | 製品概要、ユースケース、および制限事項。 |
| [QUICKSTART.md](QUICKSTART.md) | 初回セットアップとクライアント接続。 |
| [UserManual.md](UserManual.md) | 日常のエディターワークフロー。 |
| [TechnicalOverview.md](TechnicalOverview.md) | アーキテクチャとプロトコルの動作。 |
| [INTEGRATION.md](INTEGRATION.md) | プロバイダープラグインがツールを接続する方法。 |
| [SettingsReference.md](SettingsReference.md) | 設定と保存ファイル。 |
| [CodeDocumentation.md](CodeDocumentation.md) | ソースレイアウトと契約。 |
| [FAQ.md](FAQ.md) | 購入者からのよくある質問。 |
| [TROUBLESHOOTING.md](TROUBLESHOOTING.md) | 一般的な障害と修正方法。 |
| [ReleaseChecklist.md](ReleaseChecklist.md) | リリースおよび Fab パッケージ化のチェックリスト。 |

## パッケージ化

Fab パッケージにこのドキュメントセットが含まれるよう、`Config/FilterPlugin.ini` に `/Documentation/...` および `/CHANGELOG.md` が含まれています。
