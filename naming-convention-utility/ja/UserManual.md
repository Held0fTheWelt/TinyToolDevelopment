<!-- doc-provenance: product-facts.yml reconciled 2026-07-04; source AKDB:plugins/NamingConventionUtility/architecture.md -->
# ユーザーマニュアル

このマニュアルでは、Unreal Editor における Naming Convention Utility の設定と使用方法について説明します。

## インストール

1. プラグインをプロジェクトの `Plugins` フォルダに追加するか、Fab 経由でインストールします。
2. **Edit > Plugins** で **Naming Convention Utility** を有効化します。
3. 再起動を求められた場合はエディタを再起動します。

## DataAsset の設定

**Edit > Project Settings > Plugins > Naming Convention Utility** を開きます。

重要な設定項目:

```text
NamingConventionDataAssetPath
```

デフォルト値:

```text
/NamingConventionUtility/Editor/Data/DA_NamingConvention.DA_NamingConvention
```

可能な操作:

- デフォルトのアセットをそのまま使用。
- プロジェクト内に複製してカスタマイズ。
- プレフィックスおよびサフィックスの変更。
- Workbench から組み込みプロファイルをコピー。
- 互換性のある DataTable から DataAsset への変換。

## ルール項目

各ルールには以下のフィールドが含まれます:

- `FileTypeIdentifier`: 対象とする Unreal アセットカテゴリ。
- `NamingsToRemove`: プレフィックス/サフィックス追加前に削除する文字列。
- `PreFix`: 付加するプレフィックス。
- `PostFix`: 付加するサフィックス。

例:

```text
FileTypeIdentifier = FTC_STATICMESH
NamingsToRemove = ["StaticMesh_", "Mesh_"]
PreFix = "SM_"
PostFix = ""
```

`OldWall` は `SM_OldWall` に変更されます。

## Naming Workbench

Naming Workbench はルールの確認、編集、実行を行うメインインターフェースです。

機能:

- フォルダの選択。
- `epic_recommended`、`tiny_legacy`、`project_custom` の選択。
- 再帰的なアセットスキャン。
- 承認、適合、スキップされた行の確認。
- ターゲットパスの確認。
- JSON/Markdown レポートのエクスポート。
- 計画ハッシュによる安全なリネーム実行。

## コンテンツブラウザからのクイック実行

フォルダの右クリックメニューからも実行可能です:

1. フォルダを右クリックします。
2. **Apply Naming Conventions** を選択します。
3. プレビューダイアログを確認します。
4. 実行を確定します。
5. 変更されたパッケージを保存します。

## プレビューと除外理由

プレビューダイアログの表示内容:

- スキャンされたアセット数。
- 計画されたリネーム数。
- スキップされたアセット数。
- 変更前の名前と変更後の名前のペア。
- 除外理由。

## 監査レポート

エクスポートおよび実行時、以下の場所にレポートが生成されます:

```text
Saved/NamingConventionUtility/Reports/
```

## DataTable の変換

互換性のある DataTable を設定済みの DataAsset に変換できます。

想定される行構造:

```text
FNamingConventionTableInformation
```

フィールド:

- `FileType`
- `ToolType`
- `Value`

## テクスチャサブタイプの判定

`TC_Normalmap` 圧縮設定および一般的な名前トークン（`normal`、`albedo`、`roughness`、`metallic` など）を使用して判定します。

## 元に戻す操作とソースコントロール

アセットのリネームはパッケージと参照に影響を与えます。最初は小さなフォルダでテストし、生成されたリダイレクタを確認してパッケージを保存してください。

## プラグインの削除

プラグインを削除する前の手順:

1. 進行中のリネーム操作を完了または取り消します。
2. パッケージを保存します。
3. プラグインを無効化してエディタを再起動します。
