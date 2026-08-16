<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/LogLevelEditor/architecture.md -->
# クイックスタート

このガイドでは、インストールから**実際の成果**（ログカテゴリの詳細度を変更し、エディタの再起動後も維持される永続的なオーバーライドとして保存する）までの手順を解説します。Log Level Editor は単体で動作し、他のプラグインは不要です。

## このガイド完了後に得られる結果

ツールが開き、プロジェクトのログカテゴリが一覧表示され、1 つのカテゴリの詳細度が変更され、そのオーバーライドがプラグインの DataAsset に永続化されます。

## 必要条件

- Unreal Engine 5 エディタ。
- サードパーティ製ソフトウェア、アカウント、追加ランタイムは不要です。[THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md) を参照してください。

## 1. インストールと有効化

1. Fab ライブラリから **LogLevelEditor** をプロジェクトに追加（またはエンジンにインストール）します。
2. **Edit → Plugins** を開き、**LogLevelEditor** を有効にして、促されたら再起動します。

## 2. ツールを開く（最初の結果）

1. **Tools → Log Tools → Log Level Editor** を開きます。ドッキング可能なタブが開き、プロジェクト（およびプロジェクトプラグイン）のソースコードからログカテゴリをスキャンします。
2. 各行には、**カテゴリ名**（例: `LogTemp`）、**検出されたデフォルト**、**現在のレベル**、および利用可能な場合は**ソースパス**が表示されます。

これで、発見されたすべてのログカテゴリとリアルタイムの詳細度を確認できます。

## 3. 実際の作業例: カテゴリの詳細度を変更する

1. 検索ボックスを使用して `LogTemp` を探します。
2. その行の **Warning** 詳細度ボタンをクリックします。

**期待される出力:** プラグインが対応する Unreal コンソールコマンドを実行し、行が `Warning` に更新され、変更がプラグインの DataAsset に永続オーバーライドとして書き込まれます（次回のエディタ起動時に再生されます）。

3. 元に戻す場合: その行の**検出されたデフォルト**詳細度を選択します。選択された値が検出されたデフォルトと一致すると、プラグインは永続オーバーライドを自動的に削除し、DataAsset に実際のオーバーライドのみが保持されるようにします。

## 4. オーバーライドの保存場所

永続オーバーライドは、設定された `ULogLevelDataAsset`（設定の **LogLevelDataAsset** で指定）に保存されます。保存されたオーバーライドは、エンジンがコンソールコマンドを受け入れられるようになった後のエディタ起動時に再生されます。

## 5. 設定

プラグイン設定（Project/Editor settings → Log Level Editor）を開き、以下を制御します。

- `LogLevelDataAsset`, `bAutoSaveLogLevelDataAsset`
- `bShowToolbarButton`
- `bAlsoListEnginePluginChannels`, `bAlsoListEngineSourceChannels`（エンジンのスキャンは高負荷です）
- `LogChannelsToHide`, `LogChannelsToHideTemporary`

[SettingsReference.md](SettingsReference.md) を参照してください。

## 6. 次のステップ

- 完全なワークフロー（一時的 vs 永続的な非表示、チームワークフロー、起動時適用）:
  [UserManual.md](UserManual.md)
- 問題発生時: [TROUBLESHOOTING.md](TROUBLESHOOTING.md) および [FAQ.md](FAQ.md)
