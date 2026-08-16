<!-- doc-provenance: AKDB:plugins/VisualFidelityDirector/architecture.md; docs/architecture/plugins/VisualFidelityDirector/product-facts.yml; reconciled 2026-07-12 -->
# ユーザーマニュアル

Visual Fidelity Director は、ローカルの Unreal Editor ツールです。バージョン `2.0.0` ではプロファイル中心のコックピットに焦点を当てていますが、スナップショットおよびレシピワークフロー用の統合された 1.x Expert Tools パネルも保持しています。

## ツールを開く

**Tiny Tools > Visual Fidelity Director** を使用します。

ドックタブには **Cockpit**、**Evidence**、**Expert Tools** ページが用意されています。

オプション: **Edit > Editor Configurations > Visual Fidelity Director Editor Settings** でプラグインエディタの設定を開きます（メニューのショートカットは設定で無効化可能）。

## Cockpit ページ

### ステータスバナー

アクティブなプロファイルのコンパイルおよび検証ステータスから準備状態のヘッドラインと詳細テキストを表示します。

### アクションカード

| アクション | 期待される出力 |
| --- | --- |
| **Refresh** | プロファイルを再ロードし、アクティブプロファイルのプレビューを再コンパイルし、マルチフレームメトリクスサンプリングを再起動し、軸ストリップを更新します。 |
| **Compile Preview** | 設定を書き込むことなく、アクティブプロファイルの目標設定ターゲットを再コンパイルします。 |
| **Open Reports** | OS のファイルブラウザでローカルの VFD レポートフォルダを開きます。 |

### プロファイルバー

アクティブなフィデリティプロファイルを選択します。バーには検証ステータスと `Saved/VisualFidelityDirector/profiles/` からロードされた既知のプロファイルが表示されます。

### メトリクスバー

マルチフレームのライブエディタメトリクス（フレーム、ゲームスレッド、レンダースレッド、GPU、ボトルネック、および利用可能な場合は軸ごとのコストシェア）を表示します。`-1` や明示的な利用不可文字列は、現在のエディタコンテキストで計測が利用できないことを意味します — VFD が数値を捏造することはありません。

### 軸ストリップ

各コンポジション軸ストリップには以下が含まれます:

- 軸ラベルと準備色。
- **Variant** コンボ（利用できないオプションも表示されますが、互換性エビデンスとともに無効化されます）。
- **Intent** スライダー（`0.00`～`1.00`）。
- アクティブな軸詳細ドロワーの選択ハイライト。

### 軸詳細ドロワー

選択した軸について:

- **継承パス** — ルート祖先からアクティブプロファイルまでの順序付けられたチェーン。
- **プロベナンス** — コンパイルされた設定のフィールドレベルの行（送信先、値、ソース）。
- **検出事項** — コントロールローカルのコンパイルおよび互換性の検出事項。

### プロファイル比較カード

2 つ目のプロファイルを選択し、コンパイルされた目的の状態の軸ごとの差分を検査します。Blueprint ライブラリと同じ比較ランタイムを使用します。

### ガバナンス適用ドロワー

| アクション | 期待される出力 |
| --- | --- |
| **Build Destinations** | Scalability、renderer ini、Device Profile 送信先の読み取り専用サマリー。 |
| **Apply Approved** | バックアップ → 書き込み → 検証 → ロールバックマニフェストを通じて、チェックを入れてユーザーが承認した送信先のみを書き込みます。 |
| **Rollback** | ロールバックマニフェストから最後にバックアップされたファイルを復元します。 |

ブロックされた送信先（アセット、マテリアル、MRQ、アクセシビリティ、レビュー専用軸）が書き込み可能なターゲットとして表示されることはありません。

## Evidence ページ

宣言された軸マッピング、信頼度、および手動レビュー制限を備えた 11 の固定レーンエビデンスブロック（Lumen およびその他のレビューレーン）を表示します。このページは読み取り専用です。

## Expert Tools ページ

レガシーワークフロー用の統合された 1.x コントロールパネル:

### Intent Mixer

各スライダーは `0.00` から `1.00` を受け入れ、エクスポートまたは適用するまでレシピの試行評価にのみ影響します。

| スライダー | 意味 |
| --- | --- |
| Image Stability | より落ち着いたサブピクセル詳細とチラつきの減少を優先します。 |
| Motion Clarity | 動きのあるコンテンツでのブレ/ゴーストの減少を優先します。 |
| Fine Detail Preservation | より鮮明な見かけの詳細を優先します。 |
| Specular Calmness | ハイライト/光沢エリアでのフリッカーの減少を優先します。 |
| UI Crispness | HUD/UMG の明瞭さを優先します。 |
| Cinematic Accumulation | 最終レンダリングのサンプル蓄積を優先します。 |
| Performance Headroom | より低コストな推奨事項を優先します。 |

### 組み込みレシピ

バージョン `1.0.0` と同じ 15 の組み込みレシピ ID（[SettingsReference.md](SettingsReference.md) を参照）。

### Expert Tools アクション

| アクション | 期待される出力 |
| --- | --- |
| Export Snapshot (Expert Tools) | `quality_snapshot.json/.md` および最新コピー。 |
| Export Recipe Dry Run (Expert Tools) | `recipe_evaluation.json` および `settings_diff.md`（変更なし）。 |
| Duplicate Recipe | `Saved/VisualFidelityDirector/recipes/` 配下のプロジェクト所有 JSON。 |
| Import Recipe | インポートされた JSON からアクティブなレシピとスライダーを更新。 |
| Export Scanner Report | `visual_quality_report.json/.md`。 |
| Lumen Deep Scan (Expert Tools) | Lumen Surface Cache メタデータの検出事項（メッシュ/マテリアルの変更なし）。 |
| Preview Apply + Rollback (Expert Tools) | ロールバック付きセッション CVar プレビュー（`visual_fidelity_apply_report.*`）。 |
| Export A/B Report | `comparison_report.json/.md`。 |
| Export Cinematic Report | `cinematic_quality_report.*` および `mrq_recommendation.md`。 |
| Validate Schemas | `schema_validation_report.*`。 |
| Export Diagnostics | `experimental_diagnostics_report.*`。 |
| Productization Report | `productization_readiness_report.*`。 |
| Open Output Folder | レポートルートを開きます。 |

## Blueprint ライブラリ

`UVFDCockpitBlueprintLibrary` はコックピットと同じヘッドレスサービスを公開します:

- フィデリティプロファイルのロード、解決、検証、コンパイル。
- プロファイルの比較。
- パイプライン機能の検出。
- エビデンスステータスの構築。
- ガバナンス管理された永続設定のプレビュー、適用、ロールバック。

パッケージ化されたショーケース: `Content/Blueprints/BPF_VFD_API`。

## 安全性モデル

- コックピットの確認、エビデンス、比較、送信先プレビューは読み取り専用です。
- ガバナンス管理された永続適用はコックピットの唯一の変更パスであり、送信先ごとの明示的な承認が必要です。
- Expert Tools プレビュー適用は、ロールバック付きのセッション CVar のみに限定されます。
- アセット、マテリアル、Post Process Volume、MRQ プリセット、アクセシビリティ設定は VFD によって変更されません。

## レポートとプロファイル

```text
Saved/VisualFidelityDirector/profiles/
Saved/VisualFidelityDirector/reports/
Saved/VisualFidelityDirector/recipes/
```

出力にはプロジェクト名、CVar 値、品質方針が含まれる可能性があるため、ローカル/プライベートとして扱ってください。
