<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/PerformancePresetWizard/architecture.md -->
# 設定リファレンス

プラグインの設定項目およびプリセットアセットのフィールド一覧です。

## プロジェクト設定

**Edit > Project Settings > Plugins > Performance Preset Wizard** を開きます。

| 設定項目 | 型 | デフォルト値 | 説明 |
| --- | --- | --- | --- |
| Apply Preset On Editor Startup | Boolean | `false` | 有効な場合、エディタ初期化完了時に選択された起動時プリセットが適用されます。 |
| Startup Preset | Soft Object Pointer | 空 | エディタ起動時に適用する `UPerformancePresetAsset`。 |

## 実行時プロジェクト設定

**Edit > Project Settings > Plugins > Performance Preset Wizard Runtime** を開きます。

| 設定項目 | 型 | デフォルト値 | 説明 |
| --- | --- | --- | --- |
| Max Backup History | Integer | `10` | 保持する実行時バックアップエントリーの最大数。`1..100` に制限。 |
| Runtime Preset Library | Array of Soft Object Pointers | 空 | デフォルトの実行時セレクターウィジェットで表示されるアセットリスト。 |
| Storage Provider Class | Class | `PerformancePresetGameUserSettingsStorage` | 実行時サブシステムが使用するストレージプロバイダー。 |

## プリセットアセットフィールド

プリセットアセットは `UPerformancePresetAsset` クラスを使用します。

| フィールド | 型 | デフォルト値 | 説明 |
| --- | --- | --- | --- |
| Display Name | `FText` | 空 | ウィザード上で表示される名前。 |
| Description | `FText` | 空 | ターゲットデバイスや用途の短い説明。 |
| Target Platform | Enum | Desktop Mid Range | グループ化およびソート用ヒント。 |
| View Distance Quality | Integer | `2` | 描画距離のスケーラビリティレベル。 |
| Anti-Aliasing Quality | Integer | `2` | アンチエイリアスのスケーラビリティレベル。 |
| Shadow Quality | Integer | `2` | シャドウのスケーラビリティレベル。 |
| Global Illumination Quality | Integer | `2` | グローバルイルミネーションのスケーラビリティレベル。 |
| Reflection Quality | Integer | `2` | リフレクションのスケーラビリティレベル。 |
| Post Process Quality | Integer | `2` | ポストプロセスのスケーラビリティレベル。 |
| Texture Quality | Integer | `2` | テクスチャのスケーラビリティレベル。 |
| Effects Quality | Integer | `2` | エフェクトのスケーラビリティレベル。 |
| Foliage Quality | Integer | `1` | フォリッジのスケーラビリティレベル。 |
| Shading Quality | Integer | `2` | シェーディングのスケーラビリティレベル。 |
| Landscape Quality | Integer | `2` | ランドスケープのスケーラビリティレベル。 |
| CVar Overrides | Array | 空 | 追加のコンソール変数オーバーライド。 |

すべての品質フィールドは `0..4` の範囲に制限されます:

- `0`: Low
- `1`: Medium
- `2`: High
- `3`: Epic
- `4`: Cinematic

## CVar オーバーライドフィールド

各 `FPerformanceCVarOverride` の内容:

| フィールド | 型 | 説明 |
| --- | --- | --- |
| Name | `FString` | コンソール変数名（例: `r.ScreenPercentage`）。 |
| Value | `FString` | CVar に渡される値。 |
| Editor Only | Boolean | `true` の場合、エディタ環境でのみ適用されます。 |
