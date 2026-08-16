<!-- doc-provenance: product-facts.yml reconciled 2026-07-04; source AKDB:plugins/NamingConventionUtility/architecture.md -->
# 設定リファレンス

Naming Convention Utility は `UNamingConventionUtility_Settings` 内にプロジェクトレベルの設定を保存します。

## 設定オブジェクト

ソースファイル:

```text
Source/NamingConventionUtility/Public/NamingConventionUtility_Settings.h
```

エディタ上の設定場所:

```text
Edit > Project Settings > Plugins > Naming Convention Utility
```

## NamingConventionDataAssetPath

型:

```text
FSoftObjectPath
```

デフォルト値:

```text
/NamingConventionUtility/Editor/Data/DA_NamingConvention.DA_NamingConvention
```

目的:

- 命名規則が定義された DataAsset を指定します。
- フォルダリネームのワークフローで使用されます。
- DataTable 変換時の保存先として使用されます。

## bConfirmBeforeApplyingConventions

デフォルト値:

```text
true
```

目的:

- 一括リネームの実行前にプレビューと確認ダイアログを表示します。

## bFixRedirectorsAfterRename

デフォルト値:

```text
true
```

目的:

- リネーム完了後、選択したフォルダ内のリダイレクタを自動的に修正します。

## DataAsset: NamingConventions

各ルールは `EFileTypeIdentifier` ごとに定義されます。

フィールド:

- `FileTypeIdentifier`: 対象アセットタイプ。
- `NamingsToRemove`: 削除する文字列。
- `PreFix`: 付加するプレフィックス。
- `PostFix`: 付加するサフィックス。

## Workbench プロファイル

Workbench では以下の 3 つから選択可能です:

- `epic_recommended`: Epic ガイドラインに準拠した読み取り専用ルール。
- `tiny_legacy`: 1.0.x 互換の読み取り専用ルール。
- `project_custom`: `NamingConventionDataAssetPath` で指定されたルール。

## レポート

以下の場所に生成されます:

```text
Saved/NamingConventionUtility/Reports/
```
