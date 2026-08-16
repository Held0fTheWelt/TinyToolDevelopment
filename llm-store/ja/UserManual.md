<!-- doc-provenance: AKDB:plugins/LLMStore/architecture.md; docs/architecture/plugins/LLMStore/product-facts.yml; reconciled 2026-06-20 -->
# ユーザーマニュアル

このマニュアルでは、購入者、テクニカルアーティスト、Blueprint 開発者、またはツールプログラマーの視点から LLM Store について説明します。エディターでのワークフローを説明し、必要に応じてより深い技術リファレンスを参照します。

## プラグインの目的

LLM Store は、Unreal Engine プロジェクト向けの一元化された AI 制御層です。他のプラグインやツールは、プロンプトが Ollama、llama.cpp、OpenAI、Claude、Gemini、Azure OpenAI、Mistral、OpenRouter、またはモックテストのどれに送信されるかを知る必要はありません。次のような安定したタスクルートを呼び出します:

```text
docs.summarize
asset.explain
naming.review
rag.embed
agent.patch
```

ルートによって、プロバイダー、モデル、フォールバック（fallback）、ポリシー、コストルール、シークレットバックエンドが決定されます。

## エディターを開く

開く:

```text
Tiny Tools -> LLM Store
```

タブは日常的に使用するように設計されています。単に基本設定を表示するだけでなく、セットアップ、ルート、ステータス、ヘルプ、エージェント、コスト、ガバナンスを案内します。

## 初回設定

### Quick-Start カード（最も早い方法）

1. `Tiny Tools -> LLM Store` を開きます。
2. `Setup` に移動します。上部に **Quick Start — get running in one click** セクションが表示されます。
3. オプションを選択します:
   - **Just try it (Mock)** — 完全オフライン。API キー不要。CI や最初の試用に最適。
   - **Local (Ollama)** — `localhost:11434` に `quickstart_ollama` を作成。テスト前に Ollama を起動してください。
   - **Create OpenAI** または **Create Anthropic** — パスワードフィールドに API キーを貼り付け、プロバイダーボタンをクリックします。キーはシークレットバックエンドのみに保存されます。
4. ボタンの下のステータスラインと、タブの上の準備状況バナーを確認します。
5. 準備状況が緑色の場合、別の初期スタックが必要な場合のみ Quick-Start セクションを再展開してください（既存の `quickstart_*` エントリは複製されず、独自の `default` ルートが上書きされることもありません）。

初期スタックは安定した ID（`quickstart_mock`、`quickstart_ollama`、`quickstart_openai`、`quickstart_anthropic`）を使用し、すでに定義されていない限り常に `default` タスクルートを接続します。

### 手動セットアップ（完全な制御）

1. `Tiny Tools -> LLM Store` を開きます。
2. `Setup` に移動します（Quick-Start カードの下）。
3. `ollama`、`llamacpp`、`openai`、`anthropic` などのプロバイダーを作成します。
4. デフォルトのベース URL が適切であることを確認します。
5. プロバイダーのモデルを作成します。
6. `Routes` に移動します。
7. `docs.summarize` などのルートを作成します。
8. 優先モデルを選択します。
9. `Test Route` をクリックします。
10. `Status` をチェックして警告やブロックを確認します。

## プロバイダーの構成

プロバイダーは、モデル自体ではなく技術的なサービスを記述します。

| フィールド | 意味 |
| --- | --- |
| `Id` | プロジェクトローカルの安定した ID（例: `local-ollama`）。 |
| `DisplayName` | UI やレポートで読みやすい表示名。 |
| `Type` | `ollama`、`llamacpp`、`openai` などのプロバイダータイプ。 |
| `BaseUrl` | HTTP エンドポイント。既知のプロバイダーには有用なデフォルト値が設定されます。 |
| `Enabled` | 構成を削除せずにプロバイダーを無効化します。 |
| `RetryCount` | 一時的なエラーに対する再試行回数。 |
| `TimeoutSeconds` | プロバイダー固有のタイムアウト制限。 |
| `CircuitBreaker...` | 繰り返し発生する障害やフリーズしたサーバーに対する保護。 |

ローカルプロバイダーは通常キーを必要としません。クラウドプロバイダーは通常シークレットストア内にキーを必要とします。

## 既知のプロバイダー

| プロバイダータイプ | デフォルトベース URL | 主な用途 |
| --- | --- | --- |
| `ollama` | `http://localhost:11434` | Ollama 経由のローカルモデル。 |
| `llamacpp` | `http://localhost:8080` | llama.cpp サーバーによるローカル推論。 |
| `lmstudio` | `http://localhost:1234/v1` | LM Studio のローカルモデル。 |
| `vllm` | `http://localhost:8000/v1` | 高パフォーマンスなローカルまたはサーバー推論。 |
| `tgi` | `http://localhost:8080` | Hugging Face Text Generation Inference。 |
| `openai` | `https://api.openai.com/v1` | OpenAI API。 |
| `anthropic` | `https://api.anthropic.com` | Claude API。 |
| `gemini` | `https://generativelanguage.googleapis.com/v1beta` | Google Gemini API。 |
| `azure-openai` | プロジェクト固有 | Azure エンドポイントおよびデプロイメントロジック。 |
| `mistral` | `https://api.mistral.ai/v1` | Mistral API。 |
| `openrouter` | `https://openrouter.ai/api/v1` | 複数のクラウドモデル用ルーター。 |
| `mock` | 空 | テスト、UI 開発、CI、オフライン作業。 |

## モデル

モデルは単一のプロバイダーに属します。

| フィールド | 意味 |
| --- | --- |
| `Id` | プロジェクトローカルの安定したモデル ID。 |
| `Name` | プロバイダー側のネットワーク名（例: `llama3.1:8b`、`gpt-4o-mini`）。 |
| `ProviderId` | モデルを提供するプロバイダー。 |
| `Role` | `fast`、`reasoning`、`embedding`、`local` などのオプションの役割。 |
| `Structured` | JSON / スキーマ出力を適切に処理することが期待されるモデルにフラグを立てます。 |
| `TimeoutSeconds` | モデル固有のタイムアウト制限。 |
| `Enabled` | ルートを削除せずにモデルを無効化します。 |

## ルート

ルートはストアにおける最も重要な概念です。機能はモデルではなくタスクを要求します。

例:

```text
TaskKind: docs.summarize
PreferredModelId: local-fast
FallbackModelIds:
  - cloud-reasoning
  - mock-docs
Policy: local-only for shipping
```

利点:

- モデルが変更されても機能コードは安定したまま
- タスクごとにポリシーを適用可能
- フォールバックチェーンによりローカル、クラウド、モックモデルを組み合わせ可能
- タスクごとにコストを分析可能
- CI は各ツールを知らなくてもルートポリシーを検証可能

## ルートのテスト

`Routes` タブで `Test Route` を使用します。テストでは以下を確認します:

- ルートは存在するか？
- ルートは有効か？
- モデルは存在するか？
- プロバイダーは存在するか？
- プロバイダーは有効か？
- 必要なキーは存在するか？
- プロバイダーは小さなプロンプトに応答するか？

エラーはステータス領域およびプロバイダーのヘルスパネルに表示されます。

## ポリシー（Policies）

ポリシーはルートを使用できるかどうかを決定します。

一般的なルール:

- 機密データに対するクラウドの使用を禁止
- 出荷用ビルドではローカルモデルのみを許可
- 最大コンテキスト予算を設定
- リクエストごとの最大コストを設定
- 特定のプロバイダータイプを許可または拒否

ポリシーは LLM Store で構成する必要があります。別のプラグインがコンテキストを提供したりルートを呼び出したりできますが、一元化されたガバナンスの決定はストア内に残ります。

## エージェント

`Agents` タブには、Codex、Claude、Cursor、カスタムスタジオツールなどのオプションのアダプターが表示されます。

| 状態 | 意味 |
| --- | --- |
| `NotInstalled` | ツールが見つかりません。 |
| `Installed` | ツールは存在しますが、認証が不明または不足しています。 |
| `AuthRequired` | 認証を完了する必要があります。 |
| `Available` | ツールを使用する準備ができています。 |
| `Disabled` | アダプターは無効化されています。 |
| `Error` | アダプターがエラーを報告しています。 |

`Authenticate...` ボタンを押すと、コマンド、手順、ヘルプリク、および手動のターミナル用コピーアクションを含むダイアログが開きます。LLM Store は外部ツールの資格情報を保存しません。

## コスト分析

`Costs` タブは、コスト元帳（cost ledger）を収集および分析します。

以下が表示されます:

- 総イベント数
- 成功イベント数
- キャッシュヒット数
- プロンプト（prompt）トークン
- 完了（completion）トークン
- 推定コスト
- プロバイダー、モデル、ルート別の内訳
- CSV エクスポート

コストは、プロバイダーの利用データおよび構成されたコストルールと同じくらい正確です。ローカルモデルは無料に設定することも、内部ハードウェアコストを割り当てることもできます。

## シークレットストア (Secret Store)

API キーを `Config/LLMStore.json` に含めてはいけません。

サポートされているバックエンド:

- 暗号化されたローカルファイル
- Windows Credential Manager
- macOS Keychain
- 1Password CLI
- Azure CLI 経由の Azure Key Vault

環境変数が優先されます:

```text
LLMSTORE_<PROVIDER_ID>_KEY
```

例:

```text
LLMSTORE_OPENAI_MAIN_KEY
```

## Status タブ

`Status` タブは、「現在ストアを使用できますか？」という質問に答えます。

以下が表示されます:

- グローバルな準備状況
- ブロック
- 警告
- プロバイダーインベントリ
- 欠落しているキー
- 無効化されたプロバイダーまたはモデル
- ルートの問題

チームと構成を共有する前、CI を実行する前、またはリリースをパッケージ化する前にこのタブを確認してください。

## 構成 JSON のエクスポート、検証、インポート

`Governance` タブには、LLM Store の完全な構成を共有または移行するための構成 JSON アクションが含まれています。

利用可能なアクション:

| アクション | 目的 |
| --- | --- |
| `Export Setup JSON` | 任意のフォルダーとファイル名を選択し、現在の構成を JSON として保存します。シークレットは含まれません。 |
| `Validate JSON` | JSON ファイルを選択し、適用せずにスキーマ、プロバイダー ID、モデル参照、ルート、および警告を検査します。 |
| `Import JSON` | JSON ファイルを選択し、検証が成功した場合のみ検証して適用します。 |

インポーターは、LLM Store のラッパー付き構成フォーマットと、ラッパーなしの `FLLMStoreConfig` JSON オブジェクトの両方を受け入れます。これにより、プリセット、バックアップ、チーム間の引き継ぎファイル、および手動でレビューされた構成スナップショットに適しています。

## Help タブ

`Help` タブは、エディター内で直接以下を説明します:

- プロバイダーとは何か
- モデルとは何か
- なぜ直接的なモデル名ではなくルートを使用するのか
- ローカルプロバイダーとクラウドプロバイダーがどのように連携するか
- ポリシーとビルドルールがどのように適用されるか
- コスト追跡で何が測定されるか
- エージェントがどのように接続されるか

ヘルプセクションがプラグインに含まれているため、購入者は基本概念を理解するためにウェブサイト、README、エディター UI の間を行き来する必要がありません。

## Blueprint での使用

消費者向けの主な統合ポイントは Blueprints で利用可能です。

| クラス | 目的 |
| --- | --- |
| `ULLMBlueprintProviderAddOn` | Blueprint からプロバイダーを接続。 |
| `ULLMBlueprintEmbeddingProviderAddOn` | Blueprint から埋め込みプロバイダーを接続。 |
| `ULLMBlueprintContractAddOn` | モデル契約を検証。 |
| `ULLMBlueprintPolicyAddOn` | ランタイムでルートを許可または拒否。 |
| `ULLMBlueprintTestAddOn` | セットアップテストまたはヘルスチェックを追加。 |
| `ULLMBlueprintContextProviderAddOn` | プロジェクトコンテキストをコンテキストバンドルとして提供。 |
| `ULLMBlueprintAgentAddOn` | 外部 CLI またはエディターアシスタントを接続。 |

## C++ での使用

C++ ユーザーはエンジンサブシステムからストアを取得します:

```cpp
ULLMStoreSubsystem* Store = GEngine->GetEngineSubsystem<ULLMStoreSubsystem>();
```

その後、ルートの解決、リクエストの実行、コンテキストバンドルの作成、エージェントの呼び出し、コストレポートの読み取りを行うことができます。

[INTEGRATION.md](INTEGRATION.md) および [CodeDocumentation.md](CodeDocumentation.md) を参照してください。

## 推奨ワークフロー

### ローカル開発

1. `ollama` または `llamacpp` プロバイダーを作成します。
2. ローカルモデルを追加します。
3. ルートをローカルモデルに向けます。
4. ポリシー経由でクラウドを無効化します。
5. テスト用に `mock` ルートを維持します。

### ハイブリッド開発

1. 高速なタスクにはローカルモデルを使用します。
2. より複雑なタスクにはクラウドフォールバックを追加します。
3. コスト上限を設定します。
4. 定期的にコスト追跡を確認します。
5. 出荷用ビルドルールをローカル/モック専用に維持します。

### チームセットアップ

1. `Config/LLMStore.json` をリポジトリにコミットします。
2. キーはコミットしないでください。
3. シークレットバックエンドをドキュメント化します。
4. プリセットをエクスポートします。
5. `Status` タブを確認します。
6. CI ポリシーチェックを有効化します。

## 制限事項

LLM Store は、完成したアセット説明ツール、Blueprint レビューツール、または RAG 製品ではありません。ルート、プロバイダー、ポリシー、コスト追跡、シークレット、およびインターフェースを提供します。具体的な機能を持つツールは、LLM Store がそれらに依存することなく接続できます。
