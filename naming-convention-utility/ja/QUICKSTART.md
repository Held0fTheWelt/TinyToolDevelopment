<!-- doc-provenance: product-facts.yml reconciled 2026-07-04; source AKDB:plugins/NamingConventionUtility/architecture.md -->
# クイックスタートガイド

このガイドでは、インストールから実際のリネーム結果を得るまでの手順を説明します。Naming Convention Utility は独立して動作します。

## 完了時に得られる成果

ルールに基づき Naming Workbench でフォルダがスキャンされ、選択したアセット（例: `OldWall` -> `SM_OldWall`）が Unreal のアセットシステムを介してリネームされます。

## 前提条件

- リネーム対象のアセットを含むプロジェクトが用意された Unreal Engine 5 エディタ。
- サードパーティ製ソフトウェア、アカウント、追加の実行環境は不要です。[THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md) を参照してください。

## 1. インストールと有効化

1. Fab ライブラリから **Naming Convention Utility** をプロジェクトに追加するか、エンジンにインストールします。
2. **Edit > Plugins** を開き、**Naming Convention Utility** を有効化してエディタを再起動します。

## 2. ルールの確認

1. **Edit > Project Settings > Plugins > Naming Convention Utility** を開きます。
2. 主要な設定は **NamingConventionDataAssetPath** です。デフォルトでは同梱の `/NamingConventionUtility/Editor/Data/DA_NamingConvention` を指しています。
3. この DataAsset を開いてカスタムルールを確認します。各ルールには `FileTypeIdentifier`、`NamingsToRemove`、`PreFix`、`PostFix` が設定されています。

例:

```text
FileTypeIdentifier = FTC_STATICMESH
NamingsToRemove    = ["StaticMesh_", "Mesh_"]
PreFix             = "SM_"
PostFix            = ""
```

推奨: デフォルトの DataAsset をプロジェクトの Content フォルダに複製し、`NamingConventionDataAssetPath` をそのコピーに変更してください。

## 3. Naming Workbench でのスキャン

1. プラグインメニューまたはコンテンツブラウザのフォルダ右クリックメニューから **Naming Workbench** を開きます。
2. プロファイルを選択します:
   - **Epic Recommended**: Epic 準拠の標準設定。
   - **Tiny Legacy**: 1.0.x スタイルのデフォルト設定。
   - **Project Custom**: 設定済みの DataAsset ルール。
3. **Scan** をクリックします。Workbench に承認されたリネーム、既に規約に適合しているアセット、無視されたアセット、および適合率が表示されます。

## 4. リネームの実行

1. 承認された行の中から `OldWall` という名前のスタティックメッシュを見つけます。
2. ターゲットパスが `SM_OldWall.SM_OldWall` で終わっていることを確認します。
3. 対象の行のチェックボックスをオンのままにします。
4. 任意: **Export** をクリックしてプレビューレポートを出力します。
5. **Apply** をクリックし、確認ダイアログで実行します。

期待される結果: `OldWall` が `SM_OldWall` にリネームされます。変更されたパッケージを保存してください。

## 5. 主な除外理由

アセットタイプが未サポートである、対応するルールが存在しない、既に規約を満たしている、生成された名前が無効である、またはターゲット名が既に存在する場合は自動的にスキップされます。

## 6. 次のステップ

- 詳細なワークフローと DataTable 変換: [UserManual.md](UserManual.md)。
- 設定の詳細: [SettingsReference.md](SettingsReference.md)。
- トラブルシューティング: [TROUBLESHOOTING.md](TROUBLESHOOTING.md) および [FAQ.md](FAQ.md)。
