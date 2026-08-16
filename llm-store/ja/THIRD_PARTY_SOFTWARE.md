<!-- doc-provenance: AKDB:plugins/LLMStore/architecture.md; docs/architecture/plugins/LLMStore/product-facts.yml; reconciled 2026-06-20 -->
# サードパーティ製ソフトウェア

LLM Store には、**サードパーティ製ソースコード、ランタイムバイナリ、AI モデル、Node.js、Python、独立した実行可能ファイルは含まれていません**。これは、Unreal Engine 自体のモジュールと標準的な Unreal HTTP/JSON API を使用する C++ Unreal Engine プラグインです。

## オプションのプロバイダー統合（購入者が準備、非同梱）

LLM Store は、LLM プロバイダーの前の保管庫およびルーティング層です。接続するプロバイダー（存在する場合）は購入者が選択します。プラグインのインストールにプロバイダーは不要であり、組み込みの **Mock** プロバイダーはアカウントやダウンロードなしで完全にオフラインで動作します。

| プロバイダー | 概要 | 統合方法 |
| --- | --- | --- |
| Mock | 組み込みオフラインプロバイダー | アクション不要 — すぐに使用可能。 |
| Ollama | インストールして実行するローカル LLM サーバー | Ollama をインストールして実行し（デフォルト `http://localhost:11434`）、`ollama` プロバイダーを追加します。[QUICKSTART.md](QUICKSTART.md) §3 を参照してください。 |
| llama.cpp | 実行するローカル `llama-server` | `llama-server` を起動し、`llamacpp` プロバイダーを追加します。[QUICKSTART.md](QUICKSTART.md) §3 を参照してください。 |
| OpenAI | クラウド API（購入者のアカウント） | `openai` プロバイダーを作成し、API キーを貼り付けます（シークレットバックエンドに保存され、構成には含まれません）。[QUICKSTART.md](QUICKSTART.md) §4 および [SECRET_BACKENDS.md](SECRET_BACKENDS.md) を参照してください。 |
| Anthropic | クラウド API（購入者のアカウント） | `anthropic` プロバイダーを作成し、API キーを貼り付けます。[QUICKSTART.md](QUICKSTART.md) §4 を参照してください。 |

これらのプロバイダーは、それぞれのベンダーが所有する外部のソフトウェア/サービスを表し、それらから直接取得されます。LLM Store はこれらを再配布しません。API キーおよびエージェント資格情報は購入者に帰属します。[SECRET_BACKENDS.md](SECRET_BACKENDS.md) および [AGENT_AUTHENTICATION.md](AGENT_AUTHENTICATION.md) を参照してください。

**Fab 向けサードパーティ製ソフトウェアに関する申告:** サードパーティ製ソフトウェアは含まれていません。
