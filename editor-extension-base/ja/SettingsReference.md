---
lang: ja
title: EditorExtensionBase Settings Reference
audience: [end_user]
owner_ref: plugin:EditorExtensionBase
applies_to:
  component: EditorExtensionBase
contract_ref: plugin:EditorExtensionBase/widget-properties
version:
  since: "1.0"
---
# 設定リファレンス

`EditorExtensionBase` は `UDeveloperSettings` クラスやプロジェクトの `.ini` 設定オブジェクトを同梱していません。設定可能な値は、共有される `Editor Utility Widget` のサブクラスおよびユーティリティオブジェクト上の `UPROPERTY` フィールドとして保持されます。

## UEditorToolHeaderWidget

| 名前 | 型 | デフォルト | 効果 |
| --- | --- | --- | --- |
| `TitleText` | `FText` | ウィジェットデフォルト | ヘッダーに表示されるタイトル。 |
| `SubtitleText` | `FText` | ウィジェットデフォルト | タイトルの下の2行目。 |
| (BindWidget) タイトル / サブタイトル ブロック | ウィジェット参照 | 結合必須 | 必須の Slate/UMG スロット；結合が欠けているとランタイム時に警告されます。 |

## UEditorUtilityButtonWidget

| 名前 | 型 | デフォルト | 効果 |
| --- | --- | --- | --- |
| ボタンのスタイルプロパティ | ウィジェット上のスタイルフィールド | デザイナー設定 | 共有ボタンの視覚的スタイル。 |
| (BindWidget) `Button` / テキストブロック | ウィジェット参照 | 結合必須 | クリック対象とラベル；ボタンまたはテキストが null の場合、警告がログ出力されます。 |

## UEditorUtilityTabButtonWidget

| 名前 | 型 | デフォルト | 効果 |
| --- | --- | --- | --- |
| 選択中 / 未選択の表示 | アイコン + ステートフィールド | デザイナー設定 | タブの選択状態の表示を制御します。 |
| (BindWidget) ボタン / アイコン スロット | ウィジェット参照 | 結合必須 | 選択中/未選択のアイコンが欠けている場合、警告がログ出力されます。 |

## UUndoableAssetActionUtility

| 名前 | 型 | デフォルト | 効果 |
| --- | --- | --- | --- |
| アクションの説明 / アセットフィールド | editanywhere ユーティリティフィールド | 呼び出し元設定 | ユーティリティが実行するアンドゥ可能なアセットアクションを記述します。 |
| 結果コード | 列挙型 | ランタイム | チェックアウトの警告を伴う成功の場合、`SucceededWithCheckoutWarning` を含みます。 |

## UEditorUtilityTask_PrepareUndo

| 名前 | 型 | デフォルト | 効果 |
| --- | --- | --- | --- |
| 選択されたアセット入力 | editanywhere ユーティリティフィールド | 呼び出し元設定 | アンドウ準備の対象となるアセット；null、無効、またはトランザクション対象外のアセットは警告を出してスキップされます。 |

## 含まれていないもの

| 期待される対象 | 状態 |
| --- | --- |
| `UEditorExtensionBaseSettings` DeveloperSettings | ソース上でまだ利用不可 |
| `Config/DefaultEditorExtensionBase.ini` | 同梱されていない |
| プロジェクト設定パネル | まだ利用不可 |

## 関連ドキュメント

- [UserManual.md](UserManual.md) — 動作カタログ。
- [QUICKSTART.md](QUICKSTART.md) — 最初の選択ヘルパー呼び出し。
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md) — BindWidget および選択に関する警告。
