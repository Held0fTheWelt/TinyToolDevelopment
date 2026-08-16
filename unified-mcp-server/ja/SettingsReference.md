<!-- doc-provenance: AKDB:plugins/UnifiedMcpServer/architecture.md; docs/architecture/plugins/UnifiedMcpServer/product-facts.yml; reconciled 2026-07-04 -->
# 設定リファレンス

設定は `UUmcpSettings` に存在し、エディター構成に保存されます。

開く:

```text
Edit -> Editor Settings -> Plugins -> Unified MCP Server
```

## サーバー (Server)

| 設定 | 構成フィールド | デフォルト | メモ |
| --- | --- | --- | --- |
| Enable MCP Server | `bEnableServer` | `false` | デフォルトでオフ。true の場合、エディターモジュールは起動時にサーバーの開始を試みます。 |
| Server Port | `ServerPort` | `8732` | ループバックエンドポイント用のローカル TCP ポート。有効範囲: 1-65535。 |

## ツール (Tools)

| 設定 | 構成フィールド | デフォルト | メモ |
| --- | --- | --- | --- |
| Validate Tool Arguments | `bValidateToolArguments` | `false` | 有効にすると、UMCP はプロバイダー呼び出しの前に、着信する `tools/call` 引数を各ツールの `inputSchema` に対して検証します。検証は軽量でトップレベルです（必須フィールド、`additionalProperties:false` 時の不明なフィールド、基本型、Enum）。 |

## アクセス制御 (Access Control)

| 設定 | 構成フィールド | デフォルト | メモ |
| --- | --- | --- | --- |
| Access Profile | `AccessProfile` | `Default` | ハイレベルの公開モード。`Default` は従来の公開を維持し、`Read Only` は読み取り専用として注釈付けされたツールのみを公開し、`Automation` はリスクのある/破壊的な/オープンワールドの/未分類のツールを非表示にし、`Experimental` は手動でブロックされない限りリスクのあるツールを意図的に許可します。 |
| Disabled Provider IDs | `DisabledProviderIds` | 空 | `tools/list` から非表示になり、`tools/call` 時にブロックされるプロバイダー ID。コントロールパネルから単一プロバイダーグループをこのリストに切り替えることができます。 |
| Allowed Tool Names | `AllowedToolNames` | 空 | 公開する MCP ツール名またはワイルドカードパターン（例: `iis_search` や `mesh_route_*`）のオプション許可リスト。空の場合は、無効化またはブロックされていない限り、すべてのツールが許可されます。 |
| Blocked Tool Names | `BlockedToolNames` | 空 | `tools/list` から非表示になり、`tools/call` 時にブロックされる公開 MCP ツール名またはワイルドカードパターン。 |
| Allowed Tool Groups | `AllowedToolGroups` | 空 | `read_only`、`non_destructive`、`idempotent`、`risky`、`destructive`、`open_world`、`unclassified` などの注釈由来グループのオプション許可リスト。 |
| Blocked Tool Groups | `BlockedToolGroups` | 空 | `tools/list` から非表示になり、`tools/call` 時にブロックされる注釈由来グループ。 |

ポリシー順序は、プロバイダー無効化、明示的なツールブロック、アクセスプロファイル、ブロックされたグループ、オプションのツール/グループ許可リスト、公開の順です。許可リストにエントリーが含まれている場合、ツールはその名前または少なくとも 1 つのグループが一致したときに公開されます。同じポリシーが `tools/list` と `tools/call` に使用されます。

コントロールパネルまたは Blueprint ヘルパーから作成されたランタイム Access Guard ブロックはセッションローカルであり、永続ポリシーの後に適用されます。影響を受けるトークンの `tools/list` から一致するツールを非表示にし、直接の `tools/call` を拒否し、サーバー停止時にクリアされます。

ジョブ集計ツールは読み取り専用ですが、他のすべての MCP ツールと同じプロバイダー/ツール/プロファイルポリシーを通過します。`jobs_*` または `jobs` プロバイダーをブロックすると、`jobs_list` と `jobs_status` の両方が非表示になります。

## アクセスジャーナル (Access Journal)

| 設定 | 構成フィールド | デフォルト | メモ |
| --- | --- | --- | --- |
| Enable Access Journal | `bEnableAccessJournal` | `true` | 意味的な `tools/call` アクセス診断を書き出します。 |
| Access Journal Ring Capacity | `AccessJournalRingCapacity` | `500` | コントロールパネルおよび Blueprint 診断用に RAM 内に保持される直近のエントリー数。 |
| Access Journal Max File Bytes | `AccessJournalMaxFileBytes` | `5242880` | ファイルローテーション前の `access_audit.jsonl` の最大サイズ。 |
| Access Journal Redacted String Limit | `AccessJournalRedactedStringLimit` | `128` | 伏字化された JSONL 引数内の最大文字列長。 |
| Access Journal Max RAM Entry Bytes | `AccessJournalMaxRamEntryBytes` | `8192` | エントリーごとにメモリ内に保持されるサニタイズされた最大引数 JSON バイト数。シークレットと思われるキーは除外されます。 |

## 生成されるファイル

| ファイル | 目的 |
| --- | --- |
| `Saved/UnifiedMcpServer/agent/mcp_endpoint.json` | ホスト、ポート、互換性トークン、およびスコープ付きセッショントークンを含む接続ハンドシェイク。 |
| `Saved/UnifiedMcpServer/logs/mcp_requests.jsonl` | リクエストメタデータログ。 |
| `Saved/UnifiedMcpServer/logs/access_audit.jsonl` | `tools/call` 用のシークレットセーフな意味的アクセスジャーナル。 |

## セキュリティのデフォルト値

- サーバーはデフォルトで無効。
- ループバックホストのみ。
- Bearer トークンが必須。
- トークンは **Tiny Tools -> AI -> Universal MCP** からローテーション可能。
- ハンドシェイクファイルはサーバー停止時に削除。
- UMCP 1.0.5 は `default`、`read_only`、`automation`、および `experimental_admin` のセッショントークンを書き出します。レガシーの `token` フィールドは互換性のためにデフォルトトークンとして残されます。
- UMCP 1.0.6 は、token、secret、password、API キー、authorization、bearer などのシークレットと思われる引数キーをアクセス診断から除外します。

## ポートの選択

次の場合に異なるポートを使用してください:

- 別のエディターインスタンスがすでに `8732` を使用している
- ローカルサービスが同じポートにバインドされている
- 個別のプロジェクトで個別の MCP エンドポイントが必要

クライアント URL:

```text
http://127.0.0.1:<ServerPort>/mcp
```
