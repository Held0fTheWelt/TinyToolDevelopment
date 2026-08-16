<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/LogLevelEditor/architecture.md -->
# 設定リファレンス

LogLevelEditor は設定を `ULogLevelEditor_Settings` に保存します。

## 設定オブジェクト

ソースファイル:

```text
Source/LogLevelEditor/Public/LogLevelEditor_Settings.h
```

設定スコープ:

```text
EditorPerProjectUserSettings
```

これは、多くの設定がゲームプレイのランタイム設定ではなく、ユーザー / エディタスコープであることを意味します。

## LogLevelDataAsset

型:

```text
TSoftObjectPtr<ULogLevelDataAsset>
```

デフォルト:

```text
/LogLevelEditor/DA_LogLevelVerbosity.DA_LogLevelVerbosity
```

目的:

- カテゴリごとの永続的な詳細度オーバーライドを保存します。
- 起動時にモジュールによってロードされます。
- コマンド実行が成功した後、ウィジェットによって更新されます。

推奨事項:

- 小規模なプロジェクトでは提供されているデフォルトアセットを使用してください。
- 厳格なソースコントロール管理を行いたい場合は、プロジェクト専用のコピーを作成してください。

## bAutoSaveLogLevelDataAsset

デフォルト:

```text
true
```

目的:

- 永続オーバーライドの変更後に DataAsset を自動保存します。
- ログ方針変更後にユーザーがアセットの保存を忘れるリスクを軽減します。

## bShowToolbarButton

デフォルト:

```text
true
```

目的:

- レベルエディタのツールバーに Log Level Editor ショートカットを表示します。
- ショートカットが非表示の場合でも、**Tools → Log Tools → Log Level Editor** メニュー項目は利用可能です。

## bAlsoListEnginePluginChannels

デフォルト:

```text
false
```

目的:

- スキャナーにエンジンプラグインのソースディレクトリを含めます。

トレードオフ:

- より完全な結果が得られます。
- スキャン時間が長くなり、UI 上のカテゴリ数が増加します。

## bAlsoListEngineSourceChannels

デフォルト:

```text
false
```

目的:

- スキャナーにエンジンソースディレクトリを含めます。

トレードオフ:

- 非常によく広範囲の視認性が得られます。
- スキャン規模が非常に大きくなる可能性があります。

## bTemporaryHideLogLevels

デフォルト:

```text
false
```

目的:

- セッション限定の非表示リストを有効にします。

保存場所:

- セッション限定（Transient）。
- 設定ファイルには保存されません。

## LogChannelsToHideTemporary

目的:

- 現在のエディタセッション中のみ非表示にするカテゴリ名。

例:

```text
LogTemp
LogSlate
LogDerivedDataCache
```

## LogChannelsToHide

目的:

- セッションを超えて非表示にするカテゴリ名。

推奨事項:

- 控えめに使用してください。永久に非表示にすると、後から関連するログを発見しにくくなる可能性があります。

## 実践的なベースライン

ほとんどのプロジェクト向け:

```text
bAutoSaveLogLevelDataAsset = true
bAlsoListEnginePluginChannels = false
bAlsoListEngineSourceChannels = false
bTemporaryHideLogLevels = false
```
