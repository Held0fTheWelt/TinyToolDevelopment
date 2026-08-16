<!-- doc-provenance: AKDB:plugins/LLMStore/architecture.md; docs/architecture/plugins/LLMStore/product-facts.yml; reconciled 2026-06-20 -->
# 設定リファレンス

このリファレンスでは、LLM Store で使用される主要な構成データについて説明します。

プロジェクト構成のパス:

```text
Config/LLMStore.json
```

シークレットはこのファイルには保存されません。

## 構成 JSON ファイル

ガバナンス UI は、選択した任意のフォルダーから構成 JSON ファイルをエクスポート、検証、およびインポートできます。

エクスポートされるラッパー付きフォーマットの内容:

| フィールド | 意味 |
| --- | --- |
| `Format` | `LLMStoreSetup`。 |
| `FormatVersion` | 構成 JSON フォーマットのバージョン。 |
| `SetupName` | ユーザーが読める構成名。 |
| `ExportedUtc` | エクスポートの UTC タイムスタンプ。 |
| `Config` | ネストされた `FLLMStoreConfig` オブジェクト。 |

インポーターは、互換性のためにラッパーなしの生の `FLLMStoreConfig` JSON オブジェクトも受け入れます。

## FLLMStoreConfig

| フィールド | 型 | 意味 |
| --- | --- | --- |
| `Providers` | `TArray<FLLMProviderConfig>` | 認識されているプロバイダー。 |
| `Models` | `TArray<FLLMModelConfig>` | プロバイダーが提供するモデル。 |
| `Routes` | `TArray<FLLMTaskRoute>` | チャット/ツール/リランクタスク用のルート。 |
| `EmbeddingRoutes` | `TArray<FLLMStoreEmbeddingRoute>` | 埋め込み専用のルート。 |
| `RoutePolicies` | `TArray<FLLMRoutePolicy>` | グローバルまたはタスク固有のポリシー。 |
| `PromptTemplates` | `TArray<FLLMPromptTemplate>` | 再利用可能なプロンプトテンプレート。 |
| `CostRules` | `TArray<FLLMCostRule>` | コスト追跡用の価格設定ルール。 |
| `BuildRules` | `TArray<FLLMBuildConfigRule>` | ビルド構成用のガバナンス。 |
| `SecretBackend` | `FLLMSecretBackendConfig` | アクティブなシークレットバックエンド。 |
| `Modes` | `FLLMRuntimeModes` | ランタイムプロファイルのラベル。 |

## FLLMProviderConfig

| フィールド | 意味 |
| --- | --- |
| `Id` | プロジェクトローカルの安定したプロバイダーキー。 |
| `DisplayName` | UI やレポートで読みやすい表示名。 |
| `Type` | `openai`、`ollama`、`llamacpp` などのプロバイダータイプ。 |
| `BaseUrl` | サーバーまたは API のエンドポイント。 |
| `bEnabled` | 削除せずにプロバイダーを無効化します。 |
| `Meta` | Azure デプロイメント名など、プロバイダー固有のメタデータ。 |
| `RetryCount` | 一時的なエラーに対する再試行回数。 |
| `TimeoutSeconds` | プロバイダー固有のタイムアウト。`0` はデフォルト値を使用します。 |
| `CircuitBreakerFailureThreshold` | サーキットブレーカーが開くまでの障害発生回数。 |
| `CircuitBreakerCooldownSeconds` | 開いた後に再試行するまでのクールダウン時間（秒）。 |

## FLLMModelConfig

| フィールド | 意味 |
| --- | --- |
| `Id` | プロジェクトローカルの安定したモデルキー。 |
| `Name` | プロバイダー側のモデル名。 |
| `DisplayName` | UI で読みやすい表示名。 |
| `ProviderId` | `FLLMProviderConfig.Id` への参照。 |
| `Role` | `fast`、`reasoning`、`local`、`embedding` などのオプションの役割。 |
| `bStructured` | モデルが構造化 JSON 出力を適切に処理することが期待されるフラグ。 |
| `TimeoutSeconds` | モデル固有のタイムアウト。 |
| `bEnabled` | 削除せずにモデルを無効化します。 |

## FLLMTaskRoute

| フィールド | 意味 |
| --- | --- |
| `TaskKind` | 安定したタスク名（例: `docs.summarize`）。 |
| `PreferredModelId` | このルートが最初に試行するモデル。 |
| `FallbackModelId` | 従来の単一フォールバック。 |
| `FallbackModelIds` | 順序付けられたフォールバックチェーン。 |
| `MockModelId` | モックモードに使用されるモデル。 |
| `bUseMock` | モックの使用を強制します。 |
| `WorkflowScope` | `Editor`、`CI`、`Runtime` などのオプションのスコープ。 |
| `PromptTemplateId` | このルートのデフォルトテンプレート。 |
| `Policy` | ルート固有のポリシー。 |
| `bEnabled` | ルートを無効化します。 |

## FLLMRoutePolicy

| フィールド | 意味 |
| --- | --- |
| `TaskKind` | 空の場合はツールによってグローバルとして使用可能。それ以外はタスク固有。 |
| `bAllowCloud` | クラウドプロバイダータイプを使用可能。 |
| `bLocalOnly` | ローカルまたはモックプロバイダーのみ許可。 |
| `MaxContextTokens` | 最大コンテキスト予算。`0` は制限なし。 |
| `MaxEstimatedCost` | リクエストごとの最大推定コスト。`0` は制限なし。 |
| `AllowedProviderTypes` | プロバイダータイプの許可リスト。 |
| `DeniedProviderTypes` | プロバイダータイプの拒否リスト。 |

## FLLMStoreEmbeddingRoute

| フィールド | 意味 |
| --- | --- |
| `RouteId` | 安定した埋め込みルート ID。 |
| `TaskKind` | タスク（例: `docs.embed`）。 |
| `ProviderId` | 埋め込みプロバイダー。 |
| `ModelId` | 埋め込みモデル。 |
| `Dimensions` | 期待されるベクトル次元。`0` はプロバイダーのデフォルト。 |
| `bEnabled` | ルートはアクティブ。 |
| `bLocalOnly` | ローカル実行を優先または要求。 |
| `bAllowFallback` | フォールバックルートを使用可能。 |
| `FallbackRouteIds` | 埋め込み用フォールバックルート。 |
| `AllowedRuntimeModes` | オプションのランタイムプロファイル許可リスト。 |

## FLLMCostRule

| フィールド | 意味 |
| --- | --- |
| `ProviderType` | ルールがカバーするプロバイダータイプ。 |
| `ModelId` | オプションのモデル ID。空の場合は幅広く適用。 |
| `InputCostPer1KTokens` | 1000 プロンプトトークンあたりの価格。 |
| `OutputCostPer1KTokens` | 1000 完了トークンあたりの価格。 |
| `Currency` | 通貨ラベル（デフォルトは `USD`）。 |

## FLLMSecretBackendConfig

| フィールド | 意味 |
| --- | --- |
| `Backend` | `EncryptedFile`、`WindowsCredentialManager`、`MacOSKeychain`、`OnePassword`、または `AzureKeyVault`。 |
| `Vault` | ボールト、キーチェーン、またはバックエンド固有の名前空間名。 |
| `KeyPrefix` | 生成されるシークレット名の接頭辞。 |
| `Meta` | バックエンド固有のプロバイダーオーバーライド。 |

## FLLMBuildConfigRule

| フィールド | 意味 |
| --- | --- |
| `BuildConfiguration` | `Development`、`Test`、`Shipping` などの Unreal 構成。 |
| `bAllowCloud` | この構成でクラウドプロバイダーが許可されているか。 |
| `bRequireLocalOrMock` | すべてのルートにローカルまたはモックパスが必要か。 |
| `AllowedProviderTypes` | この構成で許可されているプロバイダータイプ。 |

## FLLMRuntimeModes

| フィールド | 意味 |
| --- | --- |
| `GenerationMode` | `Local`、`Hybrid`、`Cloud` などの自由形式ラベル。 |
| `RetrievalMode` | 検索/RAG 動作の自由形式ラベル。 |
| `ValidationMode` | 検証/レビュー動作の自由形式ラベル。 |
| `RuntimeProfile` | `LocalOnly`、`OpenAICloud`、`Hybrid` などの全体プロファイル。 |

## FLLMPromptTemplate

| フィールド | 意味 |
| --- | --- |
| `Id` | テンプレートキー。 |
| `Description` | UI およびチームメンバー向けの文脈説明。 |
| `Template` | 変数を含むプロンプトテキスト。 |
| `Variables` | 期待される変数名。 |

## チームへの推奨事項

- `Config/LLMStore.json` をリポジトリにコミットします。
- API キーはコミットしないでください。
- チームの期待を可視化するために `SecretBackend` を使用します。
- パッケージ化エラーを早期に検出するために `BuildRules` を使用します。
- 実際のクラウド使用前に `CostRules` を追加します。
- 各本番ルートに所有者、目的、およびデータ分類を記録します。

## エディター開発者設定

エディターの好みの設定は **Editor Settings -> Plugins -> LLM Store** にあり、`Config/LLMStore.json` とは別に保存されます。

| フィールド | デフォルト | 意味 |
| --- | --- | --- |
| `MaxJobHistoryCount` | `50` | エディター履歴および UCM ジョブエンドポイント用に保持されるパネル/ジョブレコードの最大数。 |
| `DefaultPanelPage` | `Setup` | LLM Store を開いたときに表示されるパネルページ。 |
| `bAutoOpenPanelOnStartup` | `false` | エディターモジュールの起動時にパネルを自動的に開きます。 |
| `bRunValidationOnReload` | `false` | 構成の再ロード後に検証健全性チェックを実行します。 |
