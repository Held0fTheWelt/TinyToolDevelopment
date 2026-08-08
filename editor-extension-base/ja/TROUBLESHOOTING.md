---
lang: ja
title: EditorExtensionBase Troubleshooting
audience: [end_user]
owner_ref: plugin:EditorExtensionBase
applies_to:
  component: EditorExtensionBase
symptom: Editor utility BindWidget slots are null or selection helpers warn in the log.
recovery:
  steps:
    - Confirm the plugin is enabled under Edit > Plugins and restart the editor
    - Re-read the matching troubleshooting entry and apply the documented fix
    - Re-run the quick start smoke check
version:
  since: "1.0"
---
# トラブルシューティング

形式: 症状 → 原因 → 解決策

## 0. 有効化したのに何も起こらない

**症状:** `EditorExtensionBase` を有効化してエディタを再起動した後、新しい Tiny Tools メニューが表示されず、目立った UI 変更もありません。  
**原因:** このプラグインは共有基盤レイヤーであり、独自の製品メニューを登録しません。  
**解決策:** **[編集] → [プラグイン]** でプラグインが有効になっていることを確認し、[Editor Utility Widget](Editor Utility Widget) または C++ エディタツールから `UEditorManagerUtilityLibrary::GetSelectedAssetsForAction` を呼び出します ([QUICKSTART.md](QUICKSTART.md) 参照)。新しいメニューが表示されないのは正常な動作です。

## 1. プラグインは有効化されるが、ヘルパー [Blueprint](Blueprint) がライブラリを見つけられない

**症状:** 有効化後、`Editor Manager Utility Library` の [Blueprint](Blueprint) ノードが欠落しています。  
**原因:** エディタモジュールが読み込まれていない、またはプラグインを有効化する前に [Editor Utility Widget](Editor Utility Widget) アセットがコンパイルされていた。  
**解決策:** **[編集] → [プラグイン]** で **EditorExtensionBase** が有効になっていることを確認し、エディタを再起動してから、[Editor Utility Widget](Editor Utility Widget) の [Blueprint](Blueprint) を更新/再コンパイルします。

## 2. `EditorUtilityButtonWidget: Button is null`

**症状:** ログ `LogEditorExtensionBase` に、ボタンが null であるという警告が表示されます。  
**原因:** ユーティリティウィジェットの [Blueprint](Blueprint) サブクラスで、必要な `BindWidget` ボタンスロットがバインドされていません。  
**解決策:** ウィジェットの [Blueprint](Blueprint) を開き、`UEditorUtilityButtonWidget` で宣言されたボタンスロットをバインドし、コンパイルしてからツールを再度開きます。

## 3. `EditorUtilityButtonWidget: Text block is null`

**症状:** テキストブロックの `BindWidget` が null であるという警告。  
**原因:** ラベルのテキストブロックが [Blueprint](Blueprint) でバインドされていません。  
**解決策:** C++ ベースのテキストブロックスロットをバインドし、表示テキストを設定してコンパイルします。

## 4. `EditorUtilityTabButtonWidget: SelectedIcon is null` / `UnselectedIcon is null`

**症状:** タブボタンで、アイコンが不足しているという警告。  
**原因:** 選択時または非選択時のアイコンスロットがバインドされていない、またはアセットが欠落しています。  
**解決策:** 両方のアイコンスロットを割り当ててバインドし、ソフト参照/オブジェクト参照が解決されることを確認します。

## 5. `EditorUtilityTask_PrepareUndo: No assets selected`

**症状:** アンドウ準備のログで、アセットが選択されていないと記録されます。  
**原因:** タスク実行時に [Content Browser](Content Browser) の選択が空です。  
**解決策:** トランザクション対象のアセットを最初に選択し、その後で prepare-undo ユーティリティを実行します。

## 6. トランザクション対象ではないためアセットがスキップされる

**症状:** アセットがトランザクション対象ではない / `UObject` ではない / 無効であるという警告。  
**原因:** prepare-undo タスクは、有効なトランザクション対応の `UObject` アセットのみを受け入れます。  
**解決策:** 選択範囲をエディタトランザクションをサポートするアセットに制限し、アセットではないオブジェクトや一時的なオブジェクトをスキップします。

## 7. 非推奨の begin-transaction ヘルパーがまだ使用されている

**症状:** `BeginTransactionAndGetSelectedAssets` を参照する非推奨警告。  
**原因:** コールサイトが UE 5.4 で非推奨となったヘルパーをまだ使用しています。  
**解決策:** `GetSelectedAssetsForAction` と呼び出し元所有の `FScopedTransaction` に置き換え、永続化には `CheckoutAndSaveAssets` を使用します。

## 8. チェックアウトは成功したが警告あり

**症状:** 結果コードが `SucceededWithCheckoutWarning`、またはチェックアウトの出力パラメータが false だが、一部のファイルが保存された。  
**原因:** チェックアウト中にソースコントロールから警告が返されました。  
**解決策:** アセットのソースコントロールステータスを確認し、ロックや競合を解決してから、`CheckoutAndSaveAssets` を再試行します。

## 関連ドキュメント

- [QUICKSTART.md](QUICKSTART.md)
- [UserManual.md](UserManual.md)
- [SettingsReference.md](SettingsReference.md)
- [FAQ.md](FAQ.md)
