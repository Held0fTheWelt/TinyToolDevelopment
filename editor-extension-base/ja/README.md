# エディター拡張ベース ドキュメント

エディター拡張ベースは、Tiny Tool Development UI プラグイン向けの共有 Unreal エディター基盤です。再利用可能なエディター ユーティリティ ウィジェット、Content Browser の選択/チェックアウト/保存ヘルパー、アンドロップ準備ユーティリティ、および軽量なランタイム マクロ モジュールが含まれています。

対象読者: ウィジェットや選択処理の定型コードをコピーすることなく、一貫したエディター UX を必要とするプラグイン作者およびチーム。このパッケージはサポート層であり、独自の Tiny Tools 製品メニューを登録しません。

## 機能

- 共有エディター ユーティリティ ウィジェット（ヘッダー、ボタン、タブ ボタン、2 パネル レイアウト）。
- `UEditorManagerUtilityLibrary` による選択、チェックアウト/保存、エディター ワールド ヘルパー。
- アンドロップ準備およびアンドロップ可能なアセット アクション ユーティリティ。
- 非エディター コンシューマー向けの共有マクロを含むランタイム モジュール (`EditorExtensionRuntimeBase`)。

## 始め方

1. プラグイン（および Editor Scripting Utilities）を有効にします — [QUICKSTART.md](QUICKSTART.md) を参照してください。
2. エディター ユーティリティまたは C++ エディター ツールから `GetSelectedAssetsForAction` を呼び出します。
3. 完全なカタログについては、[UserManual.md](UserManual.md) および [SettingsReference.md](SettingsReference.md) をお読みください。

## 関連ファイル

- [../README.md](../README.md) — 製品概要。
- [../CHANGELOG.md](../CHANGELOG.md) — リリース履歴。
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md) · [FAQ.md](FAQ.md) · [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md)
