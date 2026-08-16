<!-- doc-provenance: AKDB:plugins/UnifiedMcpServer/architecture.md; docs/architecture/plugins/UnifiedMcpServer/product-facts.yml; reconciled 2026-07-04 -->
# サードパーティ製ソフトウェア

Unified MCP Server には、**サードパーティ製ソースコード、ランタイムバイナリ、AI モデル、Node.js、Python、`mcp-remote`、独立した実行可能ファイルは含まれていません**。これは、標準の Unreal ネットワーキングおよび JSON API を使用してローカル MCP-over-HTTP サーバーをホストする C++ Unreal Engine プラグインです。

## オプションのユーザーインストールブリッジ（非同梱）

| ソフトウェア | 必要な場合 | 統合方法 |
| --- | --- | --- |
| `mcp-remote` (Node.js) | MCP クライアントが **Stdio** のみをサポートし、HTTP を直接呼び出せない場合のみ | npm 経由で自分でインストールし（`npx mcp-remote …`）、ハンドシェイクファイルから抽出したサーバー URL に向けます。HTTP 対応のクライアントには不要です。[QUICKSTART.md](QUICKSTART.md) §5 を参照してください。 |

HTTP 対応の MCP クライアントは、ハンドシェイクファイルの Bearer トークンを使用して `http://127.0.0.1:<port>/mcp` に直接接続できます。サードパーティ製ソフトウェアは不要です。

**Fab 向けサードパーティ製ソフトウェアに関する申告:** サードパーティ製ソフトウェアは含まれていません。
