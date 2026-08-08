# よくある質問

## EditorExtensionBase は何のためにありますか？

これは、Tiny Tool Development のエディター UI プラグインのための共有基盤です。再利用可能なエディター ユーティリティ ウィジェット、選択/チェックアウト/保存のヘルパー、アンドロップ準備ユーティリティ、および軽量なランタイム マクロ モジュールが含まれます。

## これはエンドユーザー向けツールですか？

いいえ。独自の Tiny Tools 製品メニューを登録しません。機能プラグインはこれを依存関係として消費します。

## どの Unreal モジュールを読み込みますか？

`EditorExtensionBase.uplugin` で宣言されている通り、`EditorExtensionBase` (エディター) と `EditorExtensionRuntimeBase` (ランタイム) です。

## 他の Tiny Tool プラグインが必要ですか？

いいえ。Unreal の **Editor Scripting Utilities** プラグイン（記述子で有効化済み）が必要です。シーン、AI、またはその他の Tiny Tool プラグインはオプションの消費者であり、セットアップの要件ではありません。

## 現在の Content Browser の選択内容を読み取るにはどうすればよいですか？

プラグインを有効にした後、Blueprint または C++ から `UEditorManagerUtilityLibrary::GetSelectedAssetsForAction` を呼び出します。[QUICKSTART.md](QUICKSTART.md) を参照してください。

## アンドロップ トランザクションを開くにはどうすればよいですか？

呼び出し元で `FScopedTransaction` を所有してください。`BeginTransactionAndGetSelectedAssets` は Unreal Engine 5.4 で非推奨となりました。

## ウィジェット Blueprint がランタイムで警告を出すのはなぜですか？

ボタン、テキスト ブロック、アイコンなどの BindWidget スロットが null です。Utility Widget Blueprint が C++ ベース クラスに宣言されているすべての必要なスロットをバインドしていることを確認してください。

## CheckoutAndSaveAssets は常に成功しますか？

いいえ。チェックアウトと保存の結果はブール値の出力パラメータを通じて報告されます。ソース コントロールまたは保存の失敗は、`SucceededWithCheckoutWarning` などの関連する結果コードとともにここで表示されます。

## プロジェクト全体の DeveloperSettings はありますか？

いいえ。設定可能なフィールドは共有ウィジェットとユーティリティに存在します。[SettingsReference.md](SettingsReference.md) を参照してください。

## パッケージにはサードパーティ ソフトウェアが含まれていますか？

いいえ。[THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md) を参照してください。

## 対応しているエンジン バージョンは何ですか？

パッケージ化された記述子は、エディター モジュールの許可リストに対して Win64、Linux、Mac 上の Unreal Engine 5.4.0 を対象としています。

## サポートはどこで受けられますか？

記述子の `SupportURL` に基づく `mailto:support@tiny-tool-development.com` または Fab 製品ページ上のサポートリンクを使用してください。

## エディター モジュールなしでランタイム マクロのみを使用できますか？

はい。`EditorExtensionRuntimeBase` は、エディター以外の消費者向けに依存関係を軽く保つために設計された別のランタイム モジュールです。

## PrepareUndo はアセットをすぐに変更しますか？

選択されたトランザクション対象のアセットに対してアンドロップ オプションを準備し、無効な選択は警告付きでスキップします。意図的に書き込む場合、永続化はチェックアウト/保存ヘルパーを通じて行われます。

## ランタイム マクロはエディター専用モジュールを参照できますか？

いいえ。`EditorExtensionRuntimeBase` の依存関係を軽く保ってください。エディター ウィジェットと選択ヘルパーはエディター モジュール内に残ります。
