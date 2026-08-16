<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/PerformancePresetWizard/architecture.md -->
# トラブルシューティング

## プラグインが Tools メニューに表示されない

**Edit > Plugins** でプラグインが有効になっていることを確認し、エディタを再起動してください。

## プリセットがリスト表示されない

ウィザードで **Refresh** を実行してください。アセットが `UPerformancePresetAsset` データアセットであることを確認してください。

## プリセットを適用できない

プリセットが選択されていることを確認してください。アセットが削除または移動された場合はリストを更新してください。

## 一部の CVar が「見つからない（Missing）」と報告される

CVar 名が Unreal のコンソールマネージャーで解決できませんでした（入力ミス、無効化されたプラグイン、異なるエンジンバージョンなど）。見つからない CVar があっても、他の設定の適用は継続されます。

## CVar が「無効（Invalid）」とカウントされる

無効なエントリーは、トリミング後の名前または値が空です。一括エディタで該当行を修正してください。

## 「Restore Previous」が利用できない

復元機能は、現在のエディタセッションでプリセットを適用した後にのみ利用可能になります。

## 起動時プリセットが適用されない

**Apply Preset On Editor Startup** が有効で、**Startup Preset** が有効なアセットを指しているか確認してください。
