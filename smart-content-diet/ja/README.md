<!-- doc-provenance: AKDB:plugins/SmartContentDiet/architecture.md; docs/architecture/plugins/SmartContentDiet/product-facts.yml; reconciled 2026-07-16 -->
# SmartContentDiet ドキュメント

SmartContentDiet は、Unreal Engine プロジェクトのアセットをスキャンし、最適化の検出事項を文脈に沿って説明し、ガバナンスビューを提供し、レビュー済みの QuickFix / 削減ワークフローを提案します。デフォルトの製品ループは **スキャン → レビュー → 安全な修正の適用 → 再スキャン → 改善の計測** であり、AI や外部ツールを必要としません。

## 安全に関する注意

QuickFix、メッシュ削減、テクスチャ/マテリアル変更、アセットレビューによる移動/削除、ベースライン更新、またはガバナンスの書き込みを適用すると、SmartContentDiet はプロジェクトのアセットを変更する可能性があります。バックアップが取られ、ソース管理された、使い捨て可能なブランチまたはワークスペースでのみ使用してください。保護されていないソースに対して実行しないでください。自己責任で使用してください。

機能は記載された範囲内で慎重に実装されていますが、バックアップ、ソース管理、コード/コンテンツレビュー、またはプロジェクト固有の検証に代わるものではありません。

## ドキュメントマップ

| ドキュメント | 対象読者 | 内容 |
|----------|----------|------|
| [UI_AND_BEHAVIOR.md](../Resources/UI_AND_BEHAVIOR.md) | アーティスト、テクニカルアーティスト、プロデューサー | エディタシェル、タブ、スキャンワークフロー、検出事項、QuickFix、ガバナンス |
| [OPTIMIZATION_QUEUE.md](../Resources/OPTIMIZATION_QUEUE.md) | すべてのエディタユーザー | 安全な最適化キュー、バケット、適用/プレビュー、前後の差分 |
| [SMART_ANALYSIS_ARCHITECTURE.md](../Resources/SMART_ANALYSIS_ARCHITECTURE.md) | エンジニア、インテグレーター | アナライザー、プリセット、影響、削減、トレンド、ガバナンスアーキテクチャ |
| [DIMENSION_INTEGRATION_STATUS.md](../Resources/DIMENSION_INTEGRATION_STATUS.md) | エンジニア | FindingType、ディメンションマッピング、コンバーター、UI統合ステータス |
| [SmartAnalysisResult_Usage.md](../Resources/SmartAnalysisResult_Usage.md) | エンジニア | 結果モデルの使用方法、自動修正メタデータ |
| [CHANGELOG.md](../CHANGELOG.md) | リリースオペレーター | バージョン履歴 |

**初めてですか？** インストールと安全なスキャン→修正ループについては、[QUICKSTART.md](QUICKSTART.md) から始めてください。

## インストール済み Engine 用パッケージ

インストールされている Engine バージョン用に作成された Smart Content Diet BuildPlugin パッケージを使用してください。このパッケージには、インストール済みビルドに必要な生成済みバイナリおよび事前コンパイルメタデータが含まれています。プラグインのコピーまたはアーカイブ時にこれらのファイルを削除しないでください。

> **メンテナー向け:** SCD リリースゲートおよびリリース/ランブックドキュメントは開発リポジトリにあり、Fab パッケージには含まれていません。SCD のインストールや使用にこれらは不要です。

## エディタのエントリポイント

**Tools → Content Tools → Smart Content Diet** を開きます。

### 役割に応じたシェル

メインウィンドウは対象読者の設定（初心者 / エンジニア / プロデューサー）を使用して、説明の深さと表示されるタブを制御します。

| タブ | 初心者 | 拡張（エンジニア / プロデューサー + 拡張モード） |
|-----|----------|--------------------------------------------------|
| Overview | ✓ | ✓ |
| Optimize | ✓ | ✓ |
| Findings | ✓ | ✓ |
| Preset | — | ✓ |
| Governance | — | ✓ （トレンド、負債、予算、所有権、Deep Scan をサブタブとして提供） |
| Redundancy | — | ✓ 外部類似性プロバイダーが登録されている場合のみ |
| Settings | ✓ | ✓ |

役割と説明レベルは **Settings** またはヘッダーの対象読者セレクターで変更できます。

### スキャン深度（ヘッダー）

| 深度 | アセットをロードするか？ | 主な用途 |
|-------|---------------|-------------|
| **Quick Safe** （デフォルト） | いいえ — レジストリ/メタデータパス | 初回実行、迅速な「安全に改善できる点」の確認 |
| **Full** | はい — 完全なアナライザーパイプライン | 実行可能なメッシュ/テクスチャ/マテリアルの検出事項 |
| **Deep** | はい — 詳細なマテリアル/スタティックメッシュメトリクスを含む | 最も低速。シェーダー統計および詳細メッシュ作業 |

ヘッダーのコンボボックスは、メインスキャンボタンのラベル（`Quick Safe Scan` / `Full Scan` / `Deep Scan`）を更新し、コントロールの下に深度のヒントを表示します。

選択された深度は**すべての**アナライザー実行で尊重されます。エディタの分析実行（Findings / Governance → Run analysis）はそれを `FSmartAnalysisOrchestrator` に渡し、ガバナンスステータスラインに使用された深度が表示されます。**Commandlet および CI** は従来通り `-QuickSafe`、`-FullScan`、`-DeepScan` を尊重します。詳細なマテリアル/メッシュメトリクスは、Commandlet と同様に Governance Deep Scan ワークフロー（`Governance → Deep Scan`）も使用します。

## クイックワークフロー

### UCM エコシステムルート

Unreal Capability Mesh (UCM) が有効になっている場合、SmartContentDiet は直接のプロバイダーブリッジではなく、設定で宣言されたルートを介して使用できます。SCD はピアプラグインをコードでリンクせず、`required_plugin_names` や `Build.cs` に記載することもありません。プラグイン間の価値はコード依存関係ではなく JSON ルートから得られます。アクティブなプロジェクトプロファイルは **12 の SCD 機能** を公開します:

| 機能 | 種類 | ポリシー |
| --- | --- | --- |
| `scd.migration.advice_from_handoff` | アドバイザリ | 読み取り専用 |
| `scd.scan.run` | プロバイダー | 読み取り専用 |
| `scd.findings.get` | プロバイダー | 読み取り専用 |
| `scd.findings.explain` | プロバイダー | 読み取り専用 |
| `scd.health.snapshot` | プロバイダー | 読み取り専用 |
| `scd.health.evidence` | プロバイダー | 読み取り専用 |
| `scd.governance.snapshot` | プロバイダー | 読み取り専用 |
| `scd.similarity.groups` | 類似性 | 読み取り専用 |
| `scd.similarity.ingest_groups` | 類似性 | 読み取り専用 |
| `scd.optimize.preview_safe` | 最適化 | 読み取り専用 |
| `scd.optimize.apply_safe` | 最適化 | **変更を伴う — 承認が必要** |
| `scd.optimize.apply_fix` | 最適化 | **変更を伴う — 承認が必要** |

**性能低下時の動作.** すべての機能は共有の `smart_content_diet.capability_mesh_endpoint.v1` エンベロープ（`ok`/`degraded`/`error` の `status`）を返します。前提条件が欠けている場合、失敗するのではなく機能を制限します。optimize/findings ルートは最初に `scd.scan.run` の実行を求める `error` エンベロープを返し、`scd.optimize.apply_fix` は `allow_destructive: true` なしで破壊的な修正が要求された場合、`degraded` エンベロープ（変更なし）を返します。SCD をピアに接続することは決して前提とされません。別のプラグインを参照するルート（例: `scd_ingest_from_iis.v1`、`iis.search.hybrid → scd.similarity.ingest_groups`）は、そのピアが存在しない場合、UCM 検出によって *利用可能だがプラグイン未ロード* と報告されますが、SCD 専用機能はすべて *利用可能* のままです。

**承認ゲート（およびオプション 3）.** 変更を伴う 2 つのルートには `requires_user_approval: true` が付与されているため、人が実行を承認するまで UCM は `ApprovalRequired` でブロックします。それまでアセットは一切変更されません。無人で安全適用を実行したいオペレーターは、ルートポリシーを変更して承認要件を削除できます（オプション 3）。デフォルトは承認ゲート付きで出荷されます。

PRS 配置ワークフローは PRS 所有の UCM ルートのままです。フリーブリッジは UCM のないチームおよび直接アダプターの参照実装としてのみ利用可能であり、メインプロジェクトでは必須ではありません。

### スタンドアロンの安全な最適化ループ（AI 不要）

### スキャンの正確性とパフォーマンス

現在のアナライザーパスは AssetRegistry 優先です。広範な候補セットを一度作成し、アセットをロードする前にタグメタデータを読み取り、読み取り専用の比較作業を並列化し、最終候補のみを詳細ロードします。タイムスタンプ/バージョンによる無効化を備えたアセットごとのメタデータキャッシュにより、変更のない作業の繰り返しを回避します。

重複およびアルファ分析は削減エンジンとヘルパーを共有します。削減の早期終了は削減に合わせた重複キー（`DuplicateTextureReduction`、`DuplicateStaticMeshReduction`）を使用するため、安全な統合チェックは実際の削減機能で使用されるフィンガープリントロジックと一致します。テクスチャアルファのヒューリスティックは `SCDMaterialAlpha` に集約され、アナライザーと削減の動作が一致するように保たれます。

エディタのジョブ履歴は、SCD に UMCP 依存関係を追加することなく、UMCP 集約のために UCM ルート（`scd.editor.jobs.list.v1`、`scd.editor.jobs.status.v1`）を介して利用できます。

1. Smart Content Diet を開きます。
2. スキャン深度を **Quick Safe** のままにするか、**Full** / **Deep** を選択します。
3. ヘッダーからスキャンを実行します。
4. **Overview** を確認し、**Optimize** → Safe Optimization Queue を開きます。
5. **Preview Safe** → **Apply Safe** （事前にバックアップ / ソース管理を実行）。
6. 適用が成功した場合、または **Findings** の詳細から単一アセットの修正を行った後、シェルは自動的に再スキャンします。
7. Optimize パネルでキューの数と差分のサマリーを比較します。JSON 適用レポートは `Saved/SmartContentDiet/OptimizationQueue/<timestamp>/` に保存されます。

バケット定義、安全ルール、およびレポートスキーマについては [OPTIMIZATION_QUEUE.md](../Resources/OPTIMIZATION_QUEUE.md) を参照してください。

### 一般的な分析ワークフロー

1. スキャンを実行します（選択、フォルダ、またはプロジェクトスコープ）。
2. 深刻度、影響、ディメンション、説明可能性チェーンごとに検出事項を確認します。
3. **Preset** （詳細）を使用して、評価ウェイトがスコアにどのように影響するかを理解します。
4. **Governance** （詳細）を使用して、トレンド、負債、予算、所有権、オプションの Deep Scan を確認します。
5. バックアップ/ソース管理を確認した後にのみ QuickFix を適用します。
6. 再スキャンし、ターゲットプロジェクトの文脈で検証します。

## Commandlet （CI / ヘッドレス）

```powershell
UnrealEditor-Cmd.exe "<Project>.uproject" -run=SmartContentDiet `
  -QuickSafe -OptimizationQueueReport -Path=/Game -Limit=50 `
  -NoFail -unattended -nop4 -nosplash
```

安全なキュー行を適用（バックアップ済みプロジェクトのみ）:

```powershell
UnrealEditor-Cmd.exe "<Project>.uproject" -run=SmartContentDiet `
  -QuickSafe -ApplySafeQueue -OptimizationQueueReport -Path=/Game `
  -NoFail -unattended -nop4 -nosplash
```

| フラグ | 効果 |
|--------|------|
| `-QuickSafe` | レジストリ/依存関係スキャン。アセットをロードしません |
| `-FullScan` | アセットをロードしてアナライザーを実行（`-QuickSafe` がない場合のデフォルト） |
| `-DeepScan` | 最も低速。詳細なマテリアル/メッシュメトリクス |
| `-OptimizationQueueReport` | キューの JSON/Markdown を書き出し（`-QuickSafe` で自動有効化） |
| `-ApplySafeQueue` | **Safe Now** 行のみを適用。破壊的な行は拒否されます |
| `-Path=/Game/...` | スキャン範囲 |
| `-NoFail` | ポリシー警告が存在しても 0 で終了（CI では注意して使用してください） |

Commandlet は使用時および実行開始時に安全警告を出力します。ベースラインの更新およびレポートの書き出しはワークスペースを変更する操作です。

## 成果物の保存場所（gitignored）

| 成果物 | パス |
|----------|------|
| 最適化キュー適用レポート | `Saved/SmartContentDiet/OptimizationQueue/<timestamp>/apply_report.json` |
| Commandlet キューレポート | `-ReportDir` / デフォルトは `Saved/SmartContentDiet/` 配下 |
| リリース検証出力 | メンテナー検証実行時は `Saved/SCDValidation/` |

## 実装済み QuickFix の範囲（概要）

SmartContentDiet は、テクスチャ、スタティック/スケレタルメッシュ、マテリアル、アニメーション、オーディオ/VFX のクリーンアップ、アセットレビュー/統合にわたってレビュー済みの QuickFix を提供します。破壊的またはクロスアセットのアクションには明示的な確認が必要であり、デフォルトではバッチ処理に対応していません。

完全なカタログ: [UI_AND_BEHAVIOR.md § Optimization Packs](../Resources/UI_AND_BEHAVIOR.md#71-optimization-packs)。

## リリース検証

リリース検証はメンテナー用のワークフローです。購入者の使用において、ローカルのゲートスクリプト、ホストプロジェクトのテストモジュール、リポジトリ固有のパスは不要です。
