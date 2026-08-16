<!-- doc-provenance: AKDB:plugins/LLMStore/architecture.md; docs/architecture/plugins/LLMStore/product-facts.yml; reconciled 2026-06-20 -->
# クイックスタート

このガイドでは、LLM Store で最初の動作するルートを設定する方法について説明します。

## 1. エディタータブを開く

開く:

```text
Tiny Tools -> LLM Store
```

上部領域には、ロードされているプロバイダー、モデル、ルート、埋め込みルート、準備状況、および推定コスト情報が要約表示されます。

## 2. Quick-Start カードを使用する（初回使用時の推奨）

**Setup** タブのプロバイダーおよびモデルセクションの上に **Quick Start** カードが表示されます。オプションを選択します:

| ボタン | 作成される内容 | API キー |
| --- | --- | --- |
| **Just try it (Mock)** | オフラインモックプロバイダー、モデル、および `default` ルート | なし |
| **Local (Ollama)** | `http://localhost:11434` の Ollama、デフォルトモデル `llama3`、`default` ルート | なし（Ollama が実行中である必要があります） |
| **Create OpenAI** | OpenAI プロバイダー、モデル `gpt-4o-mini`、`default` ルート | フィールドにキーを貼り付け（シークレットストアのみに保存） |
| **Create Anthropic** | Anthropic プロバイダー、モデル `claude-3-5-haiku-latest`、`default` ルート | フィールドにキーを貼り付け（シークレットストアのみに保存） |

ボタンをクリックすると、LLM Store は以下を実行します:

1. 初期セットをべき等に適用します（安定した `quickstart_*` ID。既存のプロバイダーや構成済みの `default` ルートを上書きすることはありません）。
2. 提供された場合は `SetProviderKey` 経由でクラウド API キーを保存します（`Config/LLMStore.json` には書き込まれません）。
3. **Test Connection** を実行し、準備状況バナーを更新します。

準備状況がすでに緑色の場合、カードは短縮タイトル「ready — expand to run Quick-Start again」で折りたたまれます。

カスタム URL、追加モデル、またはタスク固有のルートについては、以下の手動手順に進んでください。

## 3. ローカルプロバイダーを作成する（手動）

ローカルプロバイダーは API キーを必要としないため、最も簡単な初期テストとなります。

### オプション A: Ollama

1. ローカルで Ollama を起動します。
2. モデルをプルします:

```text
ollama pull llama3.1
```

3. `Setup` でプロバイダーを作成します:

```text
Id: ollama-local
DisplayName: Ollama Local
Type: ollama
BaseUrl: http://127.0.0.1:11434
Enabled: true
```

4. モデルを作成します:

```text
Id: local-chat
Name: llama3.1
DisplayName: Local Chat
ProviderId: ollama-local
Role: fast
Enabled: true
```

### オプション B: llama.cpp

ローカルの llama.cpp サーバーを起動します:

```text
llama-server -m C:\Models\model.gguf --host 127.0.0.1 --port 8080
```

次に以下を作成します:

```text
Provider:
  Id: llamacpp-local
  Type: llamacpp
  BaseUrl: http://127.0.0.1:8080

Model:
  Id: local-llamacpp
  Name: local-model
  ProviderId: llamacpp-local
```

## 4. クラウドプロバイダーを作成する（手動）

クラウドプロバイダーには通常 API キーが必要です。キーは `Config/LLMStore.json` ではなく、シークレットバックエンドに保存されます。

例:

```text
Provider:
  Id: openai-main
  Type: openai
  BaseUrl: https://api.openai.com/v1

Model:
  Id: openai-fast
  Name: gpt-4o-mini
  ProviderId: openai-main
```

次に、プロバイダーセクションでキーを設定するか、環境変数経由で設定します:

```text
LLMSTORE_OPENAI_MAIN_KEY
```

## 5. ルートを作成する

`Routes` タブでルートを作成します:

```text
TaskKind: docs.summarize
PreferredModelId: local-chat
FallbackModelIds:
  - openai-fast
MockModelId: mock-docs
bUseMock: false
```

llama.cpp から開始した場合は、優先モデルとして `local-llamacpp` を使用します。

## 6. ポリシー（Policy）を追加する

ローカル優先の安全なルートの場合:

```text
bAllowCloud: false
bLocalOnly: true
MaxContextTokens: 0
MaxEstimatedCost: 0
AllowedProviderTypes:
  - ollama
  - llamacpp
  - mock
```

ハイブリッド開発ルートの場合、クラウドを許可しコスト制限を追加します:

```text
bAllowCloud: true
bLocalOnly: false
MaxEstimatedCost: 0.05
```

## 7. プロバイダー、モデル、ルートをテストする

エディターのテストボタンを使用します。

ルートが解決しない場合は、以下を確認してください:

- プロバイダーは有効になっていますか？
- モデルは有効になっていますか？
- モデルは正しいプロバイダーを参照していますか？
- ルートは正しいモデル ID を使用していますか？
- クラウドプロバイダーの API キーは設定されていますか？
- ローカルサーバーは実行されていますか？
- ポリシーは選択されたプロバイダータイプを許可していますか？

## 8. コストルールを追加する

価格設定ルールが定義されると、`Costs` タブが役立ちます。

例:

```text
ProviderType: openai
ModelId: openai-fast
InputCostPer1KTokens: 0.00015
OutputCostPer1KTokens: 0.00060
Currency: USD
```

ローカルプロバイダーは `0` に維持するか、内部コストモデルを使用できます。

## 9. リクエストを実行する

リクエストを作成すると、`Costs` タブに以下が表示されます:

- イベント数
- 成功数
- キャッシュヒット数
- プロンプトトークン
- 完了トークン
- 推定コスト
- プロバイダー/モデル/タスク別の内訳
- 最近のイベント

`Export CSV` を使用して、レポートを以下に保存します:

```text
Saved/LLMStore/CostReports
```

## 10. ステータスを確認する

`Status` タブを開きます。欠落しているキー、壊れたルート、無効化されたプロバイダー、ポリシーの問題が表示されるため、`Attention` セクションが最も重要です。

## 11. オプションのエージェントセットアップ

Codex、Claude、Cursor、またはカスタムエージェントを接続するには:

1. `Agents` タブを開きます。
2. エージェントを選択します。
3. `Authenticate...` をクリックします。
4. `Copy Command` を使用し、ターミナルで手動でコマンドを実行します。
5. ステータスを更新します。

例:

```text
codex login
claude auth login
```

LLM Store はエージェント資格情報を保存しません。
