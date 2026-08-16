<!-- doc-provenance: AKDB:plugins/VisualFidelityDirector/architecture.md; docs/architecture/plugins/VisualFidelityDirector/product-facts.yml; reconciled 2026-07-12 -->
# 設定リファレンス

VFD は **Edit > Editor Configurations > Visual Fidelity Director Editor Settings** 配下にエディタプラグイン設定を追加します。プロジェクトのレンダリング設定は、ガバナンス管理された永続適用または Expert Tools のセッションプレビューを通じてのみ変更されます。

## コックピットコントロール

| コントロール | 値 | 効果 |
| --- | --- | --- |
| プロファイルセレクター | `Saved/VisualFidelityDirector/profiles/` からの既知のプロファイル | コンパイル、エビデンス、比較用のアクティブなフィデリティプロファイルをセット。 |
| 軸バリアントコンボ | 軸ごとのパイプラインバリアント | 作用するバリアントを選択。利用不可のオプションも互換性エビデンス付きで表示。 |
| 軸インテントスライダー | `0.00`～`1.00` | 選択したバリアント内での軸のインテントレベルを調整。 |
| Compare against | 2 つ目のプロファイル | 比較カードで軸ごとの並列差分を駆動。 |
| 送信先承認チェックボックス | Scalability / renderer ini / Device Profiles | ガバナンス管理された永続書き込みを制御。未チェックの送信先には書き込みません。 |

## ガバナンス適用送信先（永続設定）

| 送信先 | ファイル | 永続書き込みか？ |
| --- | --- | --- |
| Scalability 品質レベル | `DefaultGameUserSettings.ini` `[ScalabilityGroups]` | はい（承認時）。 |
| レンダラー設定 | `DefaultEngine.ini` renderer セクション | はい（承認时）。 |
| デバイスプロファイル | `DefaultDeviceProfiles.ini` | はい（承認時）。 |
| コンソール変数（セッション） | エディタセッションのみ | Expert Tools プレビューパス。非永続。 |
| アセット、マテリアル、MRQ、アクセシビリティ | ブロック | VFD が書き込むことはありません。 |

適用フロー: 送信先構築 → 承認 → バックアップ → 書き込み → 検証 → ロールバックマニフェスト。

## Blueprint ライブラリ関数

`UVFDCockpitBlueprintLibrary` のカテゴリ:

| 関数 | カテゴリ | 出力 |
| --- | --- | --- |
| LoadFidelityProfiles | Visual Fidelity\|Profiles | プロファイル配列 + 警告 |
| ResolveFidelityProfile | Visual Fidelity\|Profiles | 解決済みプロファイルまたはエラー |
| ValidateFidelityProfile | Visual Fidelity\|Profiles | 検証結果 |
| CompileFidelityProfile | Visual Fidelity\|Profiles | コンパイル済み設定ターゲット + 検出事項 |
| CompareFidelityProfiles | Visual Fidelity\|Profiles | 軸ごとの比較結果 |
| DetectPipelineCapabilities | Visual Fidelity\|Capability | 機能レポート |
| BuildEvidenceState | Visual Fidelity\|Evidence | エビデンスステータス |
| PreviewPersistentDestinations | Visual Fidelity\|Apply | 読み取り専用送信先サマリー |
| ApplyPersistentConfiguration | Visual Fidelity\|Apply | 適用レポート（承認が必要） |
| RollbackPersistentConfiguration | Visual Fidelity\|Apply | ロールバックレポート |

ショーケースアセット: `Content/Blueprints/BPF_VFD_API`。

## インテントスライダー値（Expert Tools）

すべてのインテントスライダーは `0.00` から `1.00` の浮動小数点数を使用します。

| コントロール | デフォルトソース | 効果 |
| --- | --- | --- |
| Image Stability | 選択されたレシピ | 高い値は落ち着いた時間的安定性を優先。 |
| Motion Clarity | 選択されたレシピ | 高い値はブレ/ゴーストの減少を優先。 |
| Fine Detail Preservation | 選択されたレシピ | 高い値はエイリアシングリスクを伴うより鮮明な詳細を優先。 |
| Specular Calmness | 選択されたレシピ | 高い値はハイライトフリッカーの減少を優先。 |
| UI Crispness | 選択されたレシピ | 高い値は HUD/UMG の明瞭さを優先。 |
| Cinematic Accumulation | 選択されたレシピ | 高い値は最終レンダリング蓄積を優先。 |
| Performance Headroom | 選択されたレシピ | 高い値はより低コストな推奨事項を優先。 |

## 組み込みレシピ ID

エクスポートされたレシピ JSON およびレポートでこれらの ID を使用します:

```text
stable_gameplay
sharp_gameplay
cinematic_calm
vegetation_heavy_scene
specular_heavy_scene
ui_safe_temporal
vr_clarity
low_end_stable
marketing_screenshot
debug_no_temporal
lumen_static_material_performance
lumen_dynamic_material_safe
lumen_low_end_atlas_budget
lumen_surface_cache_debug
lumen_archviz_many_instances
```

## 取得される CVar

スナップショット取得では、利用可能な場合にこの厳選された CVar レジストリを読み取ります:

```text
r.AntiAliasingMethod
r.ScreenPercentage
r.TemporalAA.Upsampling
r.PostProcessAAQuality
r.TSR.History.ScreenPercentage
r.TSR.ShadingRejection.Flickering
r.DefaultFeature.MotionBlur
r.MotionBlurQuality
r.LumenScene.SurfaceCache.CardCapturesPerFrame
r.LumenScene.SurfaceCache.CardCaptureRefreshFraction
r.LumenScene.SurfaceCache.CardMaxResolution
r.LumenScene.SurfaceCache.AtlasSize
r.LumenScene.SurfaceCache.AllowCardSharing
r.LumenScene.SurfaceCache.DetectCardSharingCompatibility
r.LumenScene.SurfaceCache.MeshCardsMinSize
r.LumenScene.SurfaceCache.MeshCardsMergeComponents
r.LumenScene.SurfaceCache.MeshCardsMergeInstances
r.LumenScene.DirectLighting.UpdateFactor
r.LumenScene.Radiosity.UpdateFactor
```

利用できない CVar は、レポート全体を失敗させるのではなく利用不可として記録されます。

## Lumen Surface Cache レビュー

Lumen Surface Cache Review レーンは、メッシュおよびマテリアルコンテンツのレポート専用です。厳選された Lumen CVar の取得、Lumen レシピの評価、`visual_quality_report.md` への Lumen 検出事項のグループ化、およびエディタ専用 Asset Registry メタデータヒント用の **Lumen Deep Scan** の実行が可能です。Static Mesh カード設定、マテリアルグラフ、カード共有フラグ、プロジェクト設定、MRQ プリセットの変更は行いません。

## プレビュー適用サポート（Expert Tools）

| サポート対象ターゲット | サポート対象モード | 永続書き込みか？ |
| --- | --- | --- |
| コンソール変数 | Preview Only, Editor Session Only | プロジェクト設定の書き込みなし。 |
| プロジェクト設定 | Cockpit ページのガバナンス適用ドロワー | はい（明示的承認時）。 |
| Post Process Volume | 推奨/エクスポートのみ | いいえ。 |
| MRQ プリセット | 推奨/エクスポートのみ | いいえ。 |
| アセット | 推奨/エクスポートのみ | いいえ。 |
| Lumen メッシュ/マテリアル設定 | 推奨/エクスポート/手動レビューのみ | いいえ。 |

## レポートファイル

| ワークフロー | ファイル |
| --- | --- |
| Snapshot | `quality_snapshot.json`, `quality_snapshot.md` |
| Recipe dry run | `recipe_evaluation.json`, `settings_diff.md` |
| Scanner | `visual_quality_report.json`, `visual_quality_report.md` |
| Lumen deep scan | `visual_quality_report.json`, `visual_quality_report.md` |
| Apply (session) | `visual_fidelity_apply_report.json`, `visual_fidelity_apply_report.md` |
| Persistent apply | VFD 設定バックアップ/レポートルート配下のガバナンス適用レポート |
| A/B comparison | `comparison_report.json`, `comparison_report.md` |
| Cinematic | `cinematic_quality_report.json`, `cinematic_quality_report.md`, `mrq_recommendation.md` |
| Schema validation | `schema_validation_report.json`, `schema_validation_report.md` |
| Diagnostics | `experimental_diagnostics_report.json`, `experimental_diagnostics_report.md` |
| Productization | `productization_readiness_report.json`, `productization_readiness_report.md` |

最新のコピーは、`Saved/VisualFidelityDirector/reports/` 配下で `latest_` が付加された同じ名前を使用します。

プロファイル JSON はプラグインの `Schemas/` フォルダ配下のスキーマを使用し、`Saved/VisualFidelityDirector/profiles/` に保存されます。
