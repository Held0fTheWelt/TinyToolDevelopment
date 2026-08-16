<!-- doc-provenance: AKDB:plugins/SmartContentDiet/architecture.md; docs/architecture/plugins/SmartContentDiet/product-facts.yml; reconciled 2026-07-16 -->
# クイックスタートガイド

このガイドでは、インストールから**実際の成果**（最適化の検出事項を含むプロジェクトアセットのスキャン、およびオプションで前後のレポートが付いたレビュー済みの安全な修正の適用）までをご案内します。Smart Content Diet のコアループは単体で動作します — **AI、ピアプラグイン、外部ツールは不要です**。

> **⚠ 安全第一.** 修正、削減、アセット移動/削除、ベースライン更新、またはガバナンス書き込みの適用は**プロジェクトのアセットを変更します**。必ず**バックアップが取られ、ソース管理された使い捨て可能な**ワークスペースでのみ実行してください。保護されていないソースに対して実行しないでください。スキャンおよびプレビューは読み取り専用で安全です。

## このガイドの終了時に得られるもの

選択した役割でツールが開き、Quick Safe スキャンが検出事項とともに完了し、安全な最適化をプレビューして適用し、前後の差分を読み取る方法が理解できます。

## 要件

- コンテンツアセットを持つプロジェクトが開いている Unreal Engine 5.4+ エディタ。
- サードパーティ製ソフトウェア、アカウント、AI モデル、外部ランタイムは不要です。[THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md) を参照してください。

## 1. インストールと有効化

1. Fab ライブラリから **SmartContentDiet** をプロジェクトに追加します（または Engine にインストールします）。
2. **Edit → Plugins** を開き、**SmartContentDiet** を有効にして、プロンプトが表示されたら再起動します。

## 2. ツールを開き役割を選択する（最初の成果）

1. **Tools → Content Tools → Smart Content Diet** を開きます。
2. ヘッダーの対象読者セレクター（または **Settings**）で役割を選択します:
   - **Beginner** — Overview、Optimize、Findings、Settings。より詳細な説明。
   - **Engineer / Producer (advanced)** — Preset と Governance（Trend、Debt、Budget、Ownership、Deep Scan）を追加し、外部類似性プロバイダーが登録されている場合は Redundancy も追加。
3. **スキャン深度** を **Quick Safe**（デフォルト — レジストリ/メタデータのみ、アセットのロードなし、高速）のままにします。
4. ヘッダーの **Quick Safe Scan** をクリックします。

**期待される出力:** スキャンが完了し、**Overview** タブに検出事項（安全に改善できる点）のサマリーが表示されます。これは読み取り専用です。

## 3. 実践例: 安全な修正のプレビューと適用

> 事前にプロジェクトのバックアップ / コミットを行ってください（上記の安全に関する注意を参照）。

1. **Optimize** タブ → **Safe Optimization Queue** を開きます。
2. **Preview Safe** をクリックして、キューに入れられた安全な最適化と予測される前後の差分を確認します（まだ読み取り専用です）。
3. **Apply Safe** をクリックして安全なキューを適用します。適用が成功した後（または **Findings** 詳細からの単一アセット修正後）、シェルは**自動的に再スキャン**します。
4. Optimize パネルでキューの数と差分のサマリーを比較します。

**期待される出力:** 安全な最適化が適用され、JSON 適用レポートが以下に書き出されます:

```text
Saved/SmartContentDiet/OptimizationQueue/<timestamp>/
```

## 4. スキャン深度

| 深度 | アセットをロードするか？ | 用途 |
| --- | --- | --- |
| **Quick Safe** （デフォルト） | いいえ | 迅速な「安全に改善できる点」の確認 |
| **Full** | はい | 実行可能なメッシュ/テクスチャ/マテリアルの検出事項 |
| **Deep** | はい | 最も低速。詳細なマテリアル/スタティックメッシュメトリクス（Governance → Deep Scan） |

ヘッダーのボタンラベルとヒントは選択した深度に応じて更新され、すべてのアナライザー実行で尊重されます。

## 5. 次のステップ

- エディタシェル、タブ、検出事項、ガバナンス: [../Resources/UI_AND_BEHAVIOR.md](../Resources/UI_AND_BEHAVIOR.md)。
- 安全な最適化キュー（バケット、安全ルール、レポートスキーマ）: [../Resources/OPTIMIZATION_QUEUE.md](../Resources/OPTIMIZATION_QUEUE.md)。
- 設定と役割: [SettingsReference.md](SettingsReference.md)。
- トラブルシューティング: [TROUBLESHOOTING.md](TROUBLESHOOTING.md) および [FAQ.md](FAQ.md)。

> **オプション / 高度な機能:** SCD は CI 用のヘッドレス Commandlet（`-QuickSafe`、`-FullScan`、`-DeepScan`、`-OptimizationQueueReport`、`-ApplySafeQueue`）および、**Unreal Capability Mesh (UCM)** を所有している場合のみ利用可能な設定宣言型エコシステムルートも提供します。上記のエディタワークフローにこれらは不要です。[ドキュメントインデックス](README.md)を参照してください。
