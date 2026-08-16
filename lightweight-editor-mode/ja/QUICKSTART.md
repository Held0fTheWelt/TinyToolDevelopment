<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/LightweightEditorMode/architecture.md -->
# クイックスタート

このガイドでは、インストールから**目に見える結果**（ワンクリックで完全復元可能な、より高速で応答性の高いエディタビューポート）を得るまでの手順を解説します。Lightweight Editor Mode は単体で動作し、他のプラグインは不要です。

## このガイド完了後に得られる結果

復元可能な「軽量」編集プロファイルが有効化され（ビューポートが高速化）、必要に応じてプロファイルを切り替えたり元のエディタ状態に戻したりできるようになります。

## 必要条件

- Unreal Engine 5 エディタ（本プラグインはエディタビューポートにのみ影響し、パッケージ化されたゲームのランタイムには影響しません）。
- サードパーティ製ソフトウェア、アカウント、追加ランタイムは不要です。[THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md) を参照してください。

## 1. インストールと有効化

1. Fab ライブラリから **Lightweight Editor Mode** をプロジェクトに追加（またはエンジンにインストール）します。
2. **Edit → Plugins** を開き、**Lightweight Editor Mode** を有効にして、促されたら再起動します。

## 2. ツールを開く（最初の結果）

1. **Tools → Performance → Lightweight Editor Mode** を開きます。プロファイルドロップダウン、切り替えボタン、*Enable on Editor startup* チェックボックスを備えたドッキング可能なタブが開きます。
2. **Balanced** プロファイル（推奨のデフォルト）を選択します。
3. **Enable Lightweight Mode** をクリックします。

**期待される出力:** ビューポートが即座に更新されます。Balanced プロファイルはスクリーンパーセンテージと拡張性を下げ、高負荷なライティングを無効化し、Unlit（ライティングなし）/ 非リアルタイムを強制します。これにより、エディタの応答性がすぐに向上します。

## 3. 実際の作業例: プロファイルの切り替えと復元

1. モードが有効な状態で、プロファイルのドロップダウンを **Aggressive** に変更します。ビューポートはよりアグレッシブな設定（より低いスクリーンパーセンテージ、低拡張性、高負荷なシャドウ/フォグの無効化）で更新されます。有効化前の元の状態は維持されています。
2. **Disable Lightweight Mode** をクリックします。

**期待される出力:** エディタはバックアップされた拡張性レベル、コンソール変数のオーバーライド、ビューポートの表示モード、リアルタイム状態を復元し、完全に開始時の状態に戻ります。

> プロファイルは応答性を優先してチューニングされており、画質を優先していません。有効化中は低解像度でライティングのない（Unlit）、シャドウの少ないビューポートになります。**ライティングの確認やスクリーンショット撮影の前にはモードを無効化してください。**

## 4. プロファイルのカスタマイズ

**Project Settings → Plugins → Lightweight Editor Mode** を開き、Mild / Balanced / Aggressive / Extreme の各プロファイル値を編集します。選択されたプロファイルは、モードが適用される前にアクティブ値にコピーされます。[PerformanceTuningReference.md](PerformanceTuningReference.md) を参照してください。

## 5. オプション: 起動時の自動有効化

**Enable on Editor startup** にチェックを入れると、次回の起動時にエディタビューポートが生成され次第、自動的にモードがオンになります。

## 6. 次のステップ

- プロファイルごとの詳細な挙動と推奨ワークフロー: [UserManual.md](UserManual.md)
- すべての設定一覧: [SettingsReference.md](SettingsReference.md)
- トラブルシューティング（例: 再起動後の状態の不整合 → *Restore Lightweight State*）:
  [TROUBLESHOOTING.md](TROUBLESHOOTING.md) および [FAQ.md](FAQ.md)
