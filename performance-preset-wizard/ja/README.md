<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/PerformancePresetWizard/architecture.md -->
# Performance Preset Wizard ドキュメント

Performance Preset Wizard は、Unreal Editor 内で作成・確認し、エディタウィザード、C++、Blueprint、または同梱の実行時セレクターウィジェットを介して手動で適用できる、実行時の目標パフォーマンスプリセットを作成します。プリセットはエンジンのスケーラビリティレベルとオプションのコンソール変数（CVar）オーバーライドを組み合わせることで、ハードウェア階層、VR 予算、キャプチャ設定、ノート PC 開発設定、プロジェクト固有の品質目標を迅速に切り替えることができます。

このフォルダには、プラグインに同梱されている完全なドキュメントが含まれています。

## はじめに

- [BUYER_GUIDE.md](BUYER_GUIDE.md): 購入者向けの概要、含まれる価値、一般的な制作ワークフロー。
- [UserManual.md](UserManual.md): ウィザードの起動、プリセットの適用、以前の設定の復元、起動時プリセットの設定に関する完全なエディタワークフロー。
- [RuntimeUsage.md](RuntimeUsage.md): 実行時サブシステム、Blueprint API、バックアップ履歴、ストレージプロバイダー、セレクターウィジェット。
- [FAQ.md](FAQ.md): Fab 購入者、デザイナー、テクニカルアーティスト向けのよくある質問と回答。

## リファレンス

- [PresetAuthoringGuide.md](PresetAuthoringGuide.md): 信頼性の高いプリセットの設計、スケーラビリティレベルの選択、CVar オーバーライドの記述方法。
- [RuntimeUsage.md](RuntimeUsage.md): パッケージ化されたゲームでプリセットアセットを手動適用および復元する方法。
- [SettingsReference.md](SettingsReference.md): プラグインの全設定項目およびアセットフィールドのデフォルト値と推奨用途。
- [SamplePresetsReference.md](SamplePresetsReference.md): 同梱の `DA_*` サンプルプリセットとそのカスタマイズ方法。
- [CodeDocumentation.md](CodeDocumentation.md): ソース構造、公開コントラクト、実装メモ、拡張ポイント。
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md): 一般的なセットアップ、アセット、CVar、ビルドの問題と解決策。

## 同梱リソース

- [Screenshots/](Screenshots): ウィザードのワークフロー、プリセット作成、復元 / 起動時の挙動を示す図解。
- `../Content/DA_*.uasset`: デスクトップ、VR、コンソール風、モバイルプロトタイプ、ノート PC 開発、シネマティック用途をカバーするサンプルプリセットデータアセット。
- `../PerformancePresetWizard_Changelog.txt`: プラグインに同梱されているリリースノート。

## クイックエディタワークフロー

1. プラグインを有効化し、再起動を求められた場合はエディタを再起動します。
2. **Tools > Performance > Performance Preset Wizard** を開きます。
3. リストからプリセットを選択します。新しいプリセットを作成またはインポートした直後の場合は **Refresh** を使用します。
4. 表示名、説明、ターゲットプラットフォーム、スケーラビリティの概要、CVar オーバーライドを確認します。
5. **Apply Preset** をクリックします。ウィザードはまずスケーラビリティ設定を適用し、次に有効な CVar オーバーライドを適用します。
6. 直前の適用前の状態に戻したい場合は **Restore Previous** をクリックします。
7. エディタ起動時に自動適用したい場合は、Project Settings で **Apply on Editor Startup** を有効にします。

## クイック実行時ワークフロー

1. エディタ内で `UPerformancePresetAsset` プリセットを作成・確認します。
2. **Project Settings > Plugins > Performance Preset Wizard Runtime** に実行時プリセットを追加するか、実行時サブシステムに直接渡します。
3. C++ または Blueprint で、現在の `GameInstance` から `UPerformancePresetRuntimeSubsystem` を取得します。
4. 明示的なユーザー操作またはプロジェクト処理のために `ApplyRuntimePreset` を呼び出します。
5. 元に戻す操作が必要な場合は、`GetBackupHistory`、`RestoreLatestBackup`、または `RestoreBackupById` を使用します。
6. テストメニューやオプション画面用に、`UPerformancePresetRuntimeSelectorWidget` を置き換え可能な軽量 UMG セレクターとして使用します。

## クイック CVar フォーマット

一括 CVar エディタは、1 行につき 1 つのオーバーライドを受け付けます:

```text
r.ScreenPercentage=85
r.Nanite=1
r.Lumen.Reflections.Allow=0
r.Shadow.Virtual.Enable=1,editor
```

ルール:

- 空行は無視されます。
- `#` または `//` で始まる行はコメントとして扱われます。
- `Name=Value` は通常オーバーライドを作成します。
- `Name=Value,editor` はエディタ専用（editor-only）としてマークします。
- 未知の CVar は報告されますが、プリセットの適用自体は停止しません。
- 空の名前や値はスキップされます。

## スケーラビリティレベル

Performance Preset Wizard は、Unreal Engine の標準品質スケールに従います:

- `0`: Low
- `1`: Medium
- `2`: High
- `3`: Epic
- `4`: Cinematic

本プラグインは、描画距離、アンチエイリアス、シャドウ、グローバルイルミネーション、リフレクション、ポストプロセス、テクスチャ、エフェクト、フォリッジ、シェーディング、ランドスケープなど、現在の UE5 スケーラビリティ領域に対応しています。

## 重要な制限事項

Performance Preset Wizard はベンチマークフレームワーク、ハードウェア検出器、自動最適化ツール、または Device Profiles の代替ではありません。プリセットはプロダクションのデフォルトとして使用する前に、ターゲットプロジェクトおよびプラットフォームで検証してください。
