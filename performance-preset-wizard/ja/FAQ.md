<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/PerformancePresetWizard/architecture.md -->
# よくある質問（FAQ）

## Performance Preset Wizard は自動最適化ツールですか？

いいえ。プリセットの作成と適用を行うツールであり、ハードウェアの自動ベンチマーク測定などは行いません。

## 実行時（Runtime）でも動作しますか？

はい。パッケージ化されたゲームでも `UPerformancePresetRuntimeSubsystem`、Blueprint、C++、同梱の UMG ウィジェットを介して手動適用が可能です。

## プリセットの適用によりプロジェクト設定が保存されますか？

いいえ。スケーラビリティ API および CVar API を介して、現在のエンジン / 実行時状態を変更するのみです。

## 適用を取り消す（Undo）ことはできますか？

エディタウィザードでは **Restore Previous** を使用できます。実行時には `RestoreLatestBackup` または `RestoreBackupById` を使用できます。

## CVar が存在しない場合はどうなりますか？

プラグインは見つからない項目としてログを出力・カウントし、プリセットの残りの設定の適用を継続します。

## なぜ CVar の値は文字列で保存されるのですか？

CVar には整数、浮動小数点数、ブール値、テキストなどがあります。文字列型にすることで全タイプを統一して保持できます。

## 「Editor Only」とはどういう意味ですか？

エディタ専用のオーバーライドはエディタ環境でのみ適用され、パッケージ化されたゲームではスキップされます。

## プラグインは Device Profiles の代わりになりますか？

いいえ。プラットフォームポリシーの定義には依然として Device Profiles が適しています。
