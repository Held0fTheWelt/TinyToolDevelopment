<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/PerformancePresetWizard/architecture.md -->
# クイックスタートガイド

このガイドでは、インストールから**確実な結果**を得るまでの手順を説明します: エディタへのパフォーマンスプリセット適用（スケーラビリティ + コンソール変数）、および 1 クリックでの完全復元。Performance Preset Wizard は単体で動作します。

## 完了時に得られる成果

検出されたプリセットが表示されたウィザード、適用された 1 つのプリセット（スケーラビリティレベル + CVar オーバーライド）、および以前の設定を復元する機能。

## 前提条件

- Unreal Engine 5 エディタ。パッケージ化されたゲームでの実行時適用は任意です。
- サードパーティ製ソフトウェア、アカウント、追加の実行環境は不要です。[THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md) を参照してください。

## 1. インストールと有効化

1. Fab ライブラリから **Performance Preset Wizard** をプロジェクトに追加（またはエンジンにインストール）します。
2. **Edit → Plugins** を開き、**Performance Preset Wizard** を有効化してエディタを再起動します。

## 2. ウィザードを開く

1. **Tools → Performance → Performance Preset Wizard** を開きます。
2. ウィザードがアセットレジストリから `UPerformancePresetAsset` を検索し、表示名、ターゲットプラットフォーム、パスごとに一覧表示します。
3. プリセットをクリックして詳細ペインを読み込みます。

## 3. 実践例: 適用と復元

1. 同梱のサンプルプリセットを選択します。
2. **Apply Preset** をクリックします。

**期待される結果:** ウィザードが復元ポイントをキャプチャし、スケーラビリティを Unreal の `0..4` 範囲に収めて適用し、各 CVar オーバーライドを適用します。

3. **Restore Previous** をクリックします。

**期待される結果:** スケーラビリティ構造とプリセットによって変更された特定の CVar が、適用直前にキャプチャされた値に戻ります。

## 4. 独自のプリセットを作成する

コンテンツブラウザで任意の `PerformancePresetAsset` を開きます。Details ペインにはカテゴリごとの品質ドロップダウンと**一括 CVar エディタ**が用意されています:

```text
# コメント行を使用できます
r.ScreenPercentage=85
r.Nanite=1
r.Shadow.Virtual.Enable=1,editor
```

`,editor` はオーバーライドをエディタ専用としてマークします。**Export** でテキストエディタに出力し、**Apply** でアセットに解析して反映します。[PresetAuthoringGuide.md](PresetAuthoringGuide.md) を参照してください。

## 5. 任意: 起動時および実行時の使用

- **エディタ起動時:** *Project Settings → Plugins → Performance Preset Wizard* → **Apply Preset On Editor Startup** + **Startup Preset**。
- **パッケージ化ゲーム:** `UPerformancePresetRuntimeSubsystem.ApplyRuntimePreset` および `RestoreLatestBackup` を使用するか、同梱の `UPerformancePresetRuntimeSelectorWidget` を使用します。[RuntimeUsage.md](RuntimeUsage.md) を参照してください。

## 6. 次のステップ

- 完全なワークフローとバックアップ履歴: [UserManual.md](UserManual.md)。
- 同梱プリセット: [SamplePresetsReference.md](SamplePresetsReference.md)。
- 設定: [SettingsReference.md](SettingsReference.md)。トラブルシューティング: [TROUBLESHOOTING.md](TROUBLESHOOTING.md)、[FAQ.md](FAQ.md)。
