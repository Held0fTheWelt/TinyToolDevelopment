<!-- doc-provenance: AKDB:plugins/SmartContentDiet/architecture.md; docs/architecture/plugins/SmartContentDiet/product-facts.yml; reconciled 2026-07-16 -->
# 設定リファレンス

## 役割 / 対象読者

**Settings** またはヘッダーの対象読者セレクターで設定します。説明の深さとタブの表示を制御します:

- **Beginner** — Overview、Optimize、Findings、Settings。
- **Engineer / Producer (advanced)** — Preset と Governance（Trend、Debt、Budget、Ownership、Deep Scan）を追加。Redundancy は外部類似性プロバイダーが登録されている場合のみ表示。

## スキャン深度（ヘッダー）

| 深度 | アセットをロードするか？ | 備考 |
| --- | --- | --- |
| `Quick Safe` （デフォルト） | いいえ | レジストリ/メタデータパス。高速な初回パス。 |
| `Full` | はい | 完全なアナライザーパイプライン。実行可能なメッシュ/テクスチャ/マテリアルの検出事項。 |
| `Deep` | はい | 詳細なマテリアル/スタティックメッシュメトリクス。Governance → Deep Scan を使用。最も低速。 |

選択された深度はすべてのアナライザー実行（エディタおよび Commandlet）で尊重されます。

Quick Safe は AssetRegistry 優先パスです。広範囲のスキャンでは、安価なメタデータチェックを通過しない限りアセットの重いロードを回避します。Full および Deep は、実用的なアナライザーの詳細を得るためにアセットをロードする場合があります。

## 出力場所

```text
Saved/SmartContentDiet/OptimizationQueue/<timestamp>/   ← 安全なキューの適用レポート
```

## 承認 / 安全性

変更を伴う機能（`scd.optimize.apply_safe`、`scd.optimize.apply_fix`）は**デフォルトで承認ゲートが付与されています**。破壊的な修正には明示的な `allow_destructive: true` が必要です。変更処理は必ずバックアップが取られ、ソース管理された使い捨て可能なワークスペースでのみ実行してください。

## Commandlet （CI / ヘッドレス）

スイッチ: `-QuickSafe`、`-FullScan`、`-DeepScan`、`-OptimizationQueueReport`、`-ApplySafeQueue`、`-Path=`、`-Limit=`、`-NoFail`、および標準の `-unattended -nop4 -nosplash`。適用スイッチはバックアップされたプロジェクトのみを対象とする必要があります。

## オプションのエコシステムルート

**Unreal Capability Mesh (UCM)** が有効になっている場合、SCD は JSON 宣言された UCM ルートを通じて読み取り専用のプロバイダー機能および 2 つの承認ゲート付き変更最適化ルートを公開します。SCD はコード内でピアプラグインをリンクしません。この統合は完全にオプションです。[ドキュメントインデックス](README.md) および [../Resources/SMART_ANALYSIS_ARCHITECTURE.md](../Resources/SMART_ANALYSIS_ARCHITECTURE.md) を参照してください。

SCD は、UCM を通じた UMCP 集約用に読み取り専用のエディタジョブルート（`scd.editor.jobs.list.v1`、`scd.editor.jobs.status.v1`）も公開します。

アナライザー/プリセット/ガバナンスのより詳細な設定については、[../Resources/SMART_ANALYSIS_ARCHITECTURE.md](../Resources/SMART_ANALYSIS_ARCHITECTURE.md) を参照してください。
