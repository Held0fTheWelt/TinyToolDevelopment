<!-- doc-provenance: AKDB:plugins/LLMStore/architecture.md; docs/architecture/plugins/LLMStore/product-facts.yml; reconciled 2026-06-20 -->
# LLM Store

LLM Store は、AI プロバイダー、モデル、タスクルート（task routes）、ポリシー（policies）、コスト、シークレット（secrets）、およびオプションの外部エージェントを一元管理するための Unreal Engine プラグインです。インフラストラクチャプラグインとして設計されており、エディターツールやランタイムシステムは、リクエストが Ollama、llama.cpp、OpenAI、Claude、Gemini、Azure OpenAI、Mistral、OpenRouter、またはモック（mock）のいずれによって処理されているかを知る必要はありません。`asset.explain`、`docs.summarize`、`naming.review` などの安定したルート名を呼び出すだけです。

## 対象ユーザー

LLM Store は、プロジェクトに複数の AI 機能が含まれており、それらの機能にプロバイダー資格情報、モデル名、クラウドのルール、コストロジックをハードコードしたくない場合に役立ちます。

主なユースケース:

- 開発、テスト、CI、出荷関連のワークフローでローカルモデルを使用する
- 開発中にクラウドモデルを許可し、出荷（shipping）ビルドではブロックする
- 直接的なモデル名ではなく、安定したタスク名で AI タスクをルーティングする
- プロバイダー、モデル、ルートごとにコストを評価する
- API キーをプロジェクトリポジトリの構成ファイルに含めないようにする
- C++ と Blueprint の両方のチームに同一の統合インターフェースを提供する
- Codex、Claude、Cursor、またはスタジオ独自のツールなどのオプションのエージェントを接続する
- LLM Store に依存させずに、プロジェクト固有のプラグインからコンテキストを提供する
- Unified MCP Server に依存せずに、UCM ルート経由でエディターのタスク履歴を公開する

## モジュール構成

| モジュール | 目的 |
| --- | --- |
| `LLMStoreInterface` | 公開構造体、ファサードインターフェース、プロバイダー契約、アドオン契約、および Blueprint ベースクラス。 |
| `LLMStore` | エンジンサブシステム、ルーティング、実行、ガバナンス、シークレット、コスト元帳（cost ledger）、エージェントブリッジ。 |
| `LLMStoreEditor` | セットアップ、ルート、ステータス、ヘルプ、エージェント、コスト、ガバナンス用のエディタータブ。 |

## 主な概念

| 概念 | 意味 |
| --- | --- |
| プロバイダー (Provider) | `ollama`、`llamacpp`、`openai` などの技術的サービスまたはローカルサーバー。 |
| モデル (Model) | プロバイダーが提供する具体的なモデル。 |
| ルート (Route) | モデル、フォールバック（fallback）チェーン、およびポリシーに解決される安定したタスク名。 |
| ポリシー (Policy) | クラウドアクセス、ローカル専用動作、コンテキスト予算、プロバイダーの許可/拒否リスト、コスト上限のルール。 |
| コストルール (Cost Rule) | プロンプトおよび完了トークンからリクエストコストを推定するために使用される価格設定ルール。 |
| エージェント (Agent) | Codex、Claude、Cursor、またはスタジオアシスタントなどの外部ツール用オプションアダプター。 |
| コンテキストプロバイダー | プロジェクトソース、アセット、ドキュメント、またはその他のシステムから中立的なコンテキストバンドルを提供するアドオン。 |

## エディター UI

次からプラグインを開きます:

```text
Tiny Tools -> LLM Store
```

メインタブ:

- `Setup`: 初回使用時の 1 クリック **Quick-Start**（モック / Ollama / クラウド）、プロバイダーおよびモデルの作成、ベース URL の編集、キーの設定、接続テスト。
- `Routes`: タスクルート、フォールバックチェーン、モックモデル、プロンプトテンプレート、ポリシーの構成。
- `Agents`: Codex、Claude、Cursor、カスタムエージェントアダプターの検査、認証ダイアログの起動。
- `Costs`: リクエスト、トークン、推定コスト、キャッシュヒットの分析、CSV レポートのエクスポート。
- `Governance`: ステータス検査、監査イベント、プリセット、キャッシュ状態、ビルドルール。
- `Status`: 現在の構成状態、警告、ブロック、インベントリの読み取り。
- `Help`: 概念および想定ワークフローのエディター内解説。
- `Advanced`: アドオンによって提供されるオプションのエディター UI セクション。

## クイックスタート

1. `Tiny Tools -> LLM Store` を開きます。
2. **Setup** タブで、**Quick-Start** カード（モック、ローカル Ollama、または OpenAI/Anthropic クラウド）を使用し、動作する `default` ルートを 1 クリックで取得します。
3. または、手動でプロバイダーとモデルを作成し、`Routes` タブでルートを追加します。
4. プロバイダー、モデル、ルートをテストし、準備完了バナーが緑色に変わることを確認します。
5. クラウドまたは予算分析が重要な場合は、コストルールを追加します。
6. リクエストを実行し、`Costs` および `Status` タブを確認します。

手順の詳細は [QUICKSTART.md](QUICKSTART.md) を参照してください（Quick-Start カードおよび手動設定）。

## ローカルプロバイダー

サポートされているローカルまたはセルフホストプロバイダーのタイプ:

- `ollama`
- `llamacpp`
- `lmstudio`
- `vllm`
- `tgi`
- `mock`

これらのプロバイダーは、デフォルトで API キーを必要としません。

## クラウドプロバイダー

サポートされているクラウドプロバイダーのタイプ:

- `openai`
- `anthropic`
- `gemini`
- `azure-openai`
- `mistral`
- `openrouter`

クラウドプロバイダーには通常 API キーが必要です。キーは構成されたシークレットバックエンドに保存され、`Config/LLMStore.json` には保存されません。

## Blueprint と C++

消費者向け機能は、C++ と Blueprint の両方から利用可能です。

Blueprint ベースクラス:

- `ULLMBlueprintProviderAddOn`
- `ULLMBlueprintEmbeddingProviderAddOn`
- `ULLMBlueprintContractAddOn`
- `ULLMBlueprintPolicyAddOn`
- `ULLMBlueprintTestAddOn`
- `ULLMBlueprintContextProviderAddOn`
- `ULLMBlueprintAgentAddOn`

[INTEGRATION.md](INTEGRATION.md) および [CodeDocumentation.md](CodeDocumentation.md) を参照してください。

ストリーミングありおよびなしのルート実行は、並行制御されたキューを共有します。長時間実行されるローカルタスクには `EnqueueRoute` を使用します。`ExecuteRouteStreaming` は、コールバック API を介してストリーミングチャンクを返しながら、同じアクティブタスク保護に従います。

## エージェント認証

`Agents` タブには、各エージェントの `Authenticate...` ボタンが表示されます。ダイアログには、ログインコマンド、手順、ヘルプリク、実行またはコマンドコピーのアクションが表示されます。資格情報は外部ツール側に保持され、LLM Store は状態と手順のみを保持します。

[AGENT_AUTHENTICATION.md](AGENT_AUTHENTICATION.md) を参照してください。

## コスト追跡

LLM Store は以下からコストを推定します:

- プロバイダーから報告された、またはストアによって推定されたプロンプトトークン
- プロバイダーから報告された、またはストアによって推定された完了トークン
- 一致する `FLLMCostRule` エントリ

コスト元帳は以下に保存されます:

```text
Saved/LLMStore/CostLedger.json
```

CSV エクスポートはデフォルトで以下に保存されます:

```text
Saved/LLMStore/CostReports/LLMStoreCostReport.csv
```

[COST_TRACKING.md](COST_TRACKING.md) を参照してください。

## プライバシーとセキュリティ

- API キーを `Config/LLMStore.json` に含めてはいけません。
- 機密性の高いプロジェクトデータには、ローカルプロバイダーが推奨されるデフォルトです。
- ポリシーによってルートごとのクラウド使用を制限できます。
- ビルドルールによって、出荷用ビルドでのクラウドプロバイダーをブロックできます。
- エージェントの実行は明示的であり、リクエストフラグによって制御されます。

暗号化されたローカルファイル、Windows Credential Manager、macOS Keychain、1Password、Azure Key Vault については [SECRET_BACKENDS.md](SECRET_BACKENDS.md) を参照してください。

## ここから始める

- [BUYER_GUIDE.md](BUYER_GUIDE.md): 購入者向けの概要、価値提案、実用的なワークフロー。
- [QUICKSTART.md](QUICKSTART.md): 最初の実用的なプロバイダー/モデル/ルート設定。
- [UserManual.md](UserManual.md): 完全なエディターワークフローと UI の使用方法。
- [FAQ.md](FAQ.md): Fab 向けの購入者 Q&A。

## リファレンス

- [SettingsReference.md](SettingsReference.md): 構成フィールド、デフォルト値、構成 JSON、推奨ライン。
- [ProviderReference.md](ProviderReference.md): サポートされているローカル/クラウドプロバイダータイプ、ベース URL、メモ。
- [RoutePolicyReference.md](RoutePolicyReference.md): ルートポリシー、クラウド/ローカル制限、予算ルール、ビルドルール。
- [COST_TRACKING.md](COST_TRACKING.md): コスト元帳、コストルール、CSV エクスポート、分析ワークフロー。
- [SECRET_BACKENDS.md](SECRET_BACKENDS.md): 暗号化されたローカルストレージと外部シークレットバックエンドの動作。
- [AGENT_AUTHENTICATION.md](AGENT_AUTHENTICATION.md): Codex/Claude/Cursor スタイルのエージェントアダプターと認証ダイアログの動作。
- [INTEGRATION.md](INTEGRATION.md): 他のプラグイン向けの C++ および Blueprint 統合パターン。
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md): 一般的な問題と解決策。
- [TechnicalOverview.md](TechnicalOverview.md): メンテナレベルのアーキテクチャ概要。

## 同梱アセット

- [Screenshots/](Screenshots): ドキュメント用スクリーンショットおよびビジュアルワークフロー図。

## ビジュアル解説

- [Screenshots/01-workflow-overview.svg](Screenshots/01-workflow-overview.svg)
- [Screenshots/02-editor-tabs.svg](Screenshots/02-editor-tabs.svg)
- [Screenshots/03-agent-cost-governance.svg](Screenshots/03-agent-cost-governance.svg)

## 構成 JSON によるクイックワークフロー

1. `Tiny Tools -> LLM Store` を開きます。
2. プロバイダー、モデル、ルート、ポリシー、コストルールを構成します。
3. `Governance` を開きます。
4. `Export Setup JSON` を使用して、現在の構成を選択したファイルに保存します。
5. `Validate JSON` を使用して、適用せずに構成ファイルを検査します。
6. 検証が成功した後にのみ `Import JSON` を使用します。

シークレットは構成 JSON に書き込まれません。共有構成をインポートした後、シークレットバックエンドまたは環境変数を介してプロバイダーキーを再接続してください。

## UCM タスクの可視性

LLM Store は、Unreal Capability Mesh が有効になっている場合、`llmstore.editor.jobs.list.v1` および `llmstore.editor.jobs.status.v1` を介してエディターのタスク履歴を読み取り専用で公開します。Unified MCP Server は `jobs_list` / `jobs_status` 経由でそれらのルートを集約できます。LLM Store 自体は自立しており、UMCP へのコンパイル時依存関係を必要としません。

## コマンドレット

ローカルターミナルまたは自動化ランナーから CI ポリシーチェックを実行します:

```powershell
<UnrealEditorCommand> "D:\PluginProjectGit\PluginProject.uproject" -run=LLMStoreCIPolicy -unattended -nop4 -nosplash -NoShaderCompile
```

`<UnrealEditorCommand>` は、ローカルエンジンインストール環境用の Unreal Editor コマンドラインターゲットです。

コマンドレットは、構成されたプロバイダー、モデル、ルート、ポリシー、ビルドルールをチェックします。これはライブプロバイダーのベンチマークではなく、リリースガバナンスを目的としています。
