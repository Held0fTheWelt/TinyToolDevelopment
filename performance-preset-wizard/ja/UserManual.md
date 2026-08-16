<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/PerformancePresetWizard/architecture.md -->
# ユーザーマニュアル

このマニュアルでは、Performance Preset Wizard の標準的なエディタワークフローについて説明します。

## ウィザードを開く

1. **Edit > Plugins** で **Performance Preset Wizard** を有効化します。
2. 再起動を求められた場合は Unreal Editor を再起動します。
3. **Tools > Performance > Performance Preset Wizard** を開きます。

ウィザードはアセットレジストリをスキャンして `UPerformancePresetAsset` を検索し、検出されたプリセットを一覧表示します。

## メインペイン

ウィザードには 2 つの主要エリアがあります:

- プリセットリスト: 検出されたすべてのパフォーマンスプリセットアセット。
- 詳細ペイン: 選択したプリセットの名前、説明、スケーラビリティレベル、CVar オーバーライド、ステータステキスト、アクションボタン。

新規作成、名前変更、移動、インポートを行った場合は **Refresh** を使用します。

## プリセットの選択

リスト内のプリセットをクリックして概要を読み込みます。

## プリセットの適用

1. プリセットを選択します。
2. 概要を確認します。
3. **Apply Preset** をクリックします。

処理手順:

1. 復元ポイント（Restore Point）のキャプチャ。
2. スケーラビリティ値を Unreal のサポート範囲 `0..4` にクランプ。
3. `Scalability::SetQualityLevels` によるスケーラビリティ適用。
4. CVar オーバーライドのループ処理。
5. 不正なエントリーのスキップ。
6. エディタ外での `editor-only` エントリーのスキップ。
7. ステータス領域および通知領域への結果表示。

## 以前の設定の復元

**Restore Previous** をクリックすると、最後に正常にプリセットが適用された直前にキャプチャされた設定に戻ります。

復元対象:

- 適用前の完全なスケーラビリティ構造。
- プリセットによって上書きされた特定の CVar の以前の値。

別のプリセットを適用すると、前回の復元ポイントは上書きされます。

## エディタ起動時プリセット

**Edit > Project Settings > Plugins > Performance Preset Wizard** を開きます。

利用可能な設定項目:

- **Apply Preset On Editor Startup**: 起動時自動適用の有効 / 無効。
- **Startup Preset**: エディタ初期化完了後に適用するプリセットアセットへのソフト参照。

## 実行時プリセット

実行時プリセットは同じ `UPerformancePresetAsset` アセットを使用します。パッケージ化されたゲームでは `UPerformancePresetRuntimeSubsystem` を介して手動適用します。

一般的な Blueprint フロー:

1. 現在の `GameInstance` を取得。
2. `Performance Preset Runtime Subsystem` を取得。
3. プリセットアセットを `ApplyRuntimePreset` に渡す。
4. キャンセル時は `RestoreLatestBackup` を呼び出す。

## 実行時セレクターウィジェット

`UPerformancePresetRuntimeSelectorWidget` が UMG の出発点として同梱されています。設定済みプリセットの列挙、選択プリセットの適用、最新バックアップの復元が可能です。

デフォルトウィジェットで表示されるプリセットは、**Project Settings > Plugins > Performance Preset Wizard Runtime** で設定できます。

## 一括 CVar エディタ

CVar テキストエディタを使用して、メモやコンソールセッションからオーバーライドをコピー＆ペーストできます。

サポートされている構文:

```text
# コメント行を使用できます
r.ScreenPercentage=85
r.Nanite=1
r.Shadow.Virtual.Enable=1,editor
```

**Export** で配列をテキストに出力し、**Apply** でテキストをアセットに再解析します。

## 推奨される命名規則

明確な名前を使用してください:

- `Laptop Dev`
- `Desktop Mid Range 60 FPS`
- `Console Like Review`
- `VR Mobile Stable`
- `Cinematic Capture 4k`

## プリセットの移動または削除

起動時プリセットが適用されなくなった場合は、Project Settings でアセットを再選択して設定を保存してください。
