# ユーザーマニュアル

Editor Extension Base パッケージは、共有の Unreal エディター UI プリミティブとヘルパーライブラリを提供し、機能プラグインが一貫した選択、チェックアウト、保存、および元に戻す動作を維持できるようにします。

## 対象読者

- Editor Utility Widget やエディターツールを構築するプラグイン作者。
- ウィジェットボイラープレートのコピーなしで Tiny Tool Development エディター UX を標準化するチーム。

このプラグインは、独自の Tiny Tools メニューエントリを持つエンドユーザー向けツールではありません。

## モジュール

| モジュール | ローディング | 内容 |
| --- | --- | --- |
| `EditorExtensionBase` | エディター / デフォルト | ウィジェット、`UEditorManagerUtilityLibrary`、元に戻す / アセットアクションユーティリティ。 |
| `EditorExtensionRuntimeBase` | ランタイム / デフォルト | 共有マクロ (`UsefulMacros.h`) およびモジュールエントリ。 |

## 共有ウィジェット

<!-- image slot: eeb-widget-overview -->

| クラス | 目的 |
| --- | --- |
| `UEditorToolHeaderWidget` | タイトル / サブタイトルの BindWidget スロットと編集可能な表示テキストを含むヘッダー行。 |
| `UEditorUtilityButtonWidget` | テキストブロックの BindWidgets とクリックデリゲートを持つスタイル付きボタン。 |
| `UEditorUtilityTabButtonWidget` | 選択済み / 未選択のアイコンスロットを持つタブスタイルボタン。 |
| `UTwoPaneUserWidget` | エディターユーティリティ画面用の 2 パンレイアウトコンテナ。 |

ウィジェット Blueprint サブクラスは、宣言された BindWidget スロットをバインドする必要があります。バインドが欠落している場合、`LogEditorExtensionBase` 下に警告がログ出力されます。

## エディターマネージャーユーティリティライブラリ

`UEditorManagerUtilityLibrary` は、選択と永続化のヘルパーで `UEditorUtilityLibrary` を拡張します。

| 関数 | 動作 |
| --- | --- |
| `GetSelectedAssetsForAction` | 現在の選択を返します。オプションでプライマリオブジェクトによってアンカーされます。 |
| `CheckoutAndSaveAssets` | ソースコントロールのチェックアウトと保存を試み、アウトパラメータを介して成功を報告します。 |
| `GetEditorWorld` | 利用可能な場合、現在のエディターワールドを返します。 |
| `BeginTransactionAndGetSelectedAssets` | **5.4 で非推奨** — 呼び出し元は `FScopedTransaction` を自身で所有する必要があります。 |

## 元に戻す操作とアセットアクション

| クラス | 動作 |
| --- | --- |
| `UEditorUtilityTask_PrepareUndo` | 選択されたトランザクショナルアセットの元に戻すオプションを準備するエディターユーティリティタスク。null、無効、またはトランザクショナルでないオブジェクトは警告付きでスキップされます。 |
| `UUndoableAssetActionUtility` | チェックアウト警告が成功に付随する場合に `SucceededWithCheckoutWarning` を含む、元に戻せるアセットアクションの結果をエンコードします。 |

## デザインルール

1. 機能固有のビジネスロジックは、消費するプラグインに保持してください。
2. このプラグインを、無関係なシーンや AI プラグインのセットアップ要件として扱わないでください。
3. 非推奨の begin-transaction ヘルパーよりも、呼び出し元が所有するトランザクションを優先してください。

## オプションの統合

消費する Tiny Tool エディタープラグインは、UI の一貫性のために Editor Extension Base に依存する場合があります。これらの統合は消費側が所有します。このパッケージは、有効化されていない場合にのみ「ヘルパーが利用不可」に低下します。他のプラグインの動作を代替するものではありません。

## 関連ドキュメント

- [QUICKSTART.md](QUICKSTART.md)
- [SettingsReference.md](SettingsReference.md)
- [FAQ.md](FAQ.md)
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md)
