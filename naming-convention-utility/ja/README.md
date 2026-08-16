<!-- doc-provenance: product-facts.yml reconciled 2026-07-04; source AKDB:plugins/NamingConventionUtility/architecture.md -->
# Naming Convention Utility ドキュメント

Naming Convention Utility は、Unreal Engine コンテンツブラウザ内の選択したフォルダ配下のアセットに対して、一貫した接頭辞および接尾辞を適用するためのエディタプラグインです。アセットタイプを検出し、リネーム計画を作成し、ターゲット名を検証し、ドッキング可能な Naming Workbench で変更をプレビューした上で、エディタのアセットツールを介して選択した Unreal アセットのリネームを実行します。

このフォルダには、プラグインに同梱されている完全なドキュメントが含まれています。

## はじめに

- [BUYER_GUIDE.md](BUYER_GUIDE.md): 購入者向けの概要、ユースケース、適合性。
- [QUICKSTART.md](QUICKSTART.md): インストールから結果確認までのクイックガイド。
- [UserManual.md](UserManual.md): 設定、スキャン、編集、レポート作成、規約適用までの完全なワークフロー。
- [FAQ.md](FAQ.md): Fab 向けのよくある質問と回答。

## リファレンス

- [SettingsReference.md](SettingsReference.md): 設定項目、DataAsset のフィールド、推奨設定。
- [TechnicalOverview.md](TechnicalOverview.md): メンテナ向けのアーキテクチャと安全モデル。
- [CodeDocumentation.md](CodeDocumentation.md): コード構造、コントラクト、拡張ポイント。
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md): 一般的な問題と解決策。
- [ReleaseChecklist.md](ReleaseChecklist.md): リリース前の検証チェックリスト。

## 同梱リソース

- `../Readme.pdf`: 従来の Readme ファイル。
- `../Content/Editor/Data/DA_NamingConvention.uasset`: デフォルトの命名規約 DataAsset。
- `../Content/Editor/Data/DT_NamingConvention.uasset`: サンプル / ソース DataTable。
- `../Resources/NamingConvention.csv`: CSV インポートリファレンス。
- `../Resources/NamingConvention.json`: JSON インポートリファレンス。
- `../Resources/NamingConvention_EpicRecommended.csv`: Epic 推奨プロファイルインポートリファレンス。
- `../Resources/NamingConvention_TinyLegacy.csv`: 1.0.x 互換プロファイルインポートリファレンス。
- `../Resources/FileTypeValues.txt`: ファイルタイプ列挙型リファレンス。
- `../Resources/ToolTypeValues.txt`: DataTable ツールタイプリファレンス。

## クイックワークフロー

1. プラグインを有効化し、必要に応じてエディタを再起動します。
2. Project Settings を開き、設定されている命名規約 DataAsset を確認します。
3. プラグインメニューまたはフォルダのコンテキストメニューから Naming Workbench を開きます。
4. **Epic Recommended**、**Tiny Legacy**、または **Project Custom** を選択します。
5. フォルダをスキャンし、適合率、除外理由、ターゲットパスを確認します。
6. 適用したい承認済み行を選択し、レポートをエクスポートするか、確認後に適用を実行します。
7. Unreal によるリネーム処理が完了したら、影響を受けたアセット / パッケージを保存します。

## 安全モデル

本プラグインはリネーム操作を影響の大きいアクションとして取り扱います。Unreal のリネームツールを呼び出す前に計画を構築し、リスクのあるエントリーを除外します。

計画チェック内容:

- 未サポートのアセットタイプ。
- 該当する規約ルールが存在しないアセット。
- 空または無効な生成名。
- 無効なターゲットオブジェクトパス。
- 既に存在するターゲットアセット。
- ディスク上に既に存在するターゲットパッケージ。
- 同一バッチ内でのターゲットの重複。
- 重複するフォルダ選択による同一ソースアセットの重複。

Workbench は計画適用前にプレビューを表示し、検証済み計画ハッシュによって適用を保護するとともに、`Saved/NamingConventionUtility/Reports/` 配下に JSON/Markdown レポートを出力します。

## ツールが変更するもの

プラグインは `IAssetTools::RenameAssets` を介して Unreal アセットの名前を変更します。

以下は行いません:

- アセットシステム外の生のファイルの変更。
- インポートされたソースファイルの変更。
- C++ クラス名の変更。
- 生成コード内の Blueprint クラス名の変更。
- スタジオ独自の命名ポリシーの強制決定。

## デフォルトの命名ファミリー

デフォルトの DataAsset には、次のような標準的な Unreal プレフィックスが含まれています:

- テクスチャ用: `T_`, `T_N_`, `T_D_`
- マテリアル用: `M_`, `MI_`, `MF_`
- メッシュおよびスケルトン用: `SM_`, `SK_`, `SKEL_`
- Blueprint およびウィジェット用: `BP_`, `BPI_`, `BPF_`, `WB_`
- エフェクト用: `NS_`, `NE_`, `PS_`
- データおよびカーブ用: `DT_`, `CT_`, `CF_`, `CV_`, `CLC_`

Workbench には以下も含まれます:

- `epic_recommended`: Epic ガイドラインに準拠したプレフィックス。
- `tiny_legacy`: 1.0.x 互換のデフォルトスタイル。
- `project_custom`: DataAsset に保存されているカスタムルール。

必要に応じて DataAsset を変更または置換できます。Workbench から組み込みプロファイルをプロジェクトの DataAsset にコピーすることも可能です。

## 重要な制限事項

- テクスチャサブタイプの自動判定は、圧縮設定と名前トークンの組み合わせに基づきます。
- プラグインが認識できないアセットタイプは無視されます。
- 参照、ソースコントロール、ファイルのロック状態により、Unreal がダイアログを表示したりリネームに失敗したりする場合があります。
- 大規模なフォルダのリネーム前には、必ず設定と内容を確認してください。

## 法的注意事項

Naming Convention Utility は生産性向上ツールです。命名標準の適用を支援しますが、特定のルールがすべてのスタジオやパイプラインに適していることを保証するものではありません。
