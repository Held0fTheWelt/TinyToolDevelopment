<!-- doc-provenance: AKDB:plugins/SmartContentDiet/architecture.md; docs/architecture/plugins/SmartContentDiet/product-facts.yml; reconciled 2026-07-16 -->
# ユーザーマニュアル

このマニュアルでは、Smart Content Diet のエディタワークフローをまとめ、詳細なガイドをご案内します。

## エントリポイント

**Tools → Content Tools → Smart Content Diet** を開きます。ウィンドウは役割を認識するシェルです。

## 役割とタブ

**Settings** またはヘッダーの対象読者セレクターで、役割（Beginner / Engineer / Producer）と説明レベルを設定します。タブの表示は役割に従います:

| タブ | Beginner | Advanced (Engineer / Producer) |
| --- | --- | --- |
| Overview, Optimize, Findings, Settings | ✓ | ✓ |
| Preset | — | ✓ |
| Governance (Trend, Debt, Budget, Ownership, Deep Scan) | — | ✓ |
| Redundancy | — | ✓ （外部類似性プロバイダーがある場合のみ） |

## スキャン深度

ヘッダーで選択します: **Quick Safe**（レジストリ/メタデータ、アセットロードなし）、**Full**（アセットをロード）、**Deep**（詳細なマテリアル/メッシュメトリクス。Governance → Deep Scan）。すべてのアナライザー実行は選択された深度を尊重します。Commandlet は `-QuickSafe` / `-FullScan` / `-DeepScan` を尊重します。

広範囲のスキャンは AssetRegistry 優先パイプラインを使用します。SCD は候補を一度収集し、可能であればタグから安価なテクスチャ/マテリアルメタデータを読み取り、タグ優先で比較し、オブジェクトデータを必要とする残りの候補セットのみを詳細ロードします。読み取り専用比較ステージは並列実行可能です。変更を伴う QuickFix には明示的なユーザーまたは Commandlet のアクションが必要です。

重複およびアルファパスは、スキャン検出事項と削減の間でヘルパーコードを共有します。テクスチャ/マテリアルアルファチェックは同じマテリアルインスタンス不透明度ロジックを使用し、削減の早期終了は削減に合わせた重複キーを使用するため、より厳格なスキャンインデックスでアセットがグループ化されなかったという理由だけで安全な統合がスキップされることはありません。

## コアワークフロー — 安全な最適化ループ（AI 不要）

1. ツールを開きます。
2. スキャン深度を選択します（Quick Safe / Full / Deep）。
3. ヘッダーからスキャンを実行します。
4. **Overview** を確認し、**Optimize → Safe Optimization Queue** を開きます。
5. **Preview Safe** → バックアップ / ソース管理 → **Apply Safe**。
6. 適用が成功した後、または単一アセットの修正後、シェルは自動的に再スキャンします。
7. キューの数と差分を比較します。JSON レポートは `Saved/SmartContentDiet/OptimizationQueue/<timestamp>/` に保存されます。

## 一般的な分析ワークフロー

1. スキャンを実行します（選択、フォルダ、またはプロジェクトスコープ）。
2. 深刻度、影響、ディメンション、説明可能性チェーンごとに検出事項を確認します。
3. **Preset** （詳細）を使用して、評価ウェイトがスコアにどのように影響するかを確認します。
4. **Governance** （詳細）を使用して、トレンド、負債、予算、所有権、オプションの Deep Scan を確認します。
5. バックアップ/ソース管理を確認した後にのみ QuickFix を適用します。
6. 再スキャンし、ターゲットプロジェクトの文脈で検証します。

## 安全性

変更を伴うアクションはプロジェクトのアセットを変更し、デフォルトで承認ゲートが付与されています。バックアップが取られ、ソース管理された使い捨て可能なワークスペースでのみ実行してください。[QUICKSTART.md](QUICKSTART.md) の安全に関する注意を参照してください。

## エディタジョブと UCM

最近のエディタ作業は、スキャン、検証、最適化アクションのジョブ履歴として記録されます。Unreal Capability Mesh が有効になっている場合、SCD は読み取り専用のジョブルートを公開します:

```text
scd.editor.jobs.list.v1
scd.editor.jobs.status.v1
```

Unified MCP Server は `jobs_list` / `jobs_status` を介してこれらのルートを集約できます。SCD 自体は UMCP に依存しません。

## 詳細ガイド

- エディタシェル、タブ、検出事項、QuickFix、ガバナンス: [../Resources/UI_AND_BEHAVIOR.md](../Resources/UI_AND_BEHAVIOR.md)。
- 安全な最適化キュー（バケット、安全ルール、レポートスキーマ）: [../Resources/OPTIMIZATION_QUEUE.md](../Resources/OPTIMIZATION_QUEUE.md)。
- アーキテクチャ: [../Resources/SMART_ANALYSIS_ARCHITECTURE.md](../Resources/SMART_ANALYSIS_ARCHITECTURE.md)。
