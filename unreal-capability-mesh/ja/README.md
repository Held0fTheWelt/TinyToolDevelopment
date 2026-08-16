<!-- doc-provenance: AKDB:plugins/UnrealCapabilityMesh/architecture.md; docs/architecture/plugins/UnrealCapabilityMesh/product-facts.yml; reconciled 2026-07-19 -->
# Unreal Capability Mesh ドキュメント

このフォルダは、Unreal Engine 5.4+ 向けの Unreal Capability Mesh プラグイン、プロジェクトのセットアップ、統合、およびソースコードの解読について説明しています。

Fab 製品ページ: https://www.fab.com/listings/fd186d26-cdcf-4c4f-93d4-50e437b7673e

## ここから始める

| ドキュメント | 目的 |
| --- | --- |
| [BUYER_GUIDE.md](BUYER_GUIDE.md) | 製品のスコープ、含まれるモジュール、UCM の機能と非対象機能。 |
| [QUICKSTART.md](QUICKSTART.md) | マニフェストから生成レポートまでの最小セットアップフロー。 |
| [UserManual.md](UserManual.md) | コントロールパネルのワークフローと通常の操作手順。 |
| [TechnicalOverview.md](TechnicalOverview.md) | アーキテクチャ、データフロー、ストレージ場所、および診断。 |
| [CodeDocumentation.md](CodeDocumentation.md) | モジュールおよびクラスごとの C++ ソース読み込みガイド。 |
| [SettingsReference.md](SettingsReference.md) | マニフェストのフォルダレイアウト、プロジェクトプロファイルフィールド、ポリシーフィールド、出力パス。 |
| [INTEGRATION.md](INTEGRATION.md) | マニフェストまたはアダプターを通じて別のプラグインを接続する方法。 |
| [TROUBLESHOOTING.md](TROUBLESHOOTING.md) | 一般的な検証、検出、ルート、および呼び出しの問題。 |
| [FAQ.md](FAQ.md) | 購入者およびレビューアー向けの簡潔な回答。 |
| [ReleaseChecklist.md](ReleaseChecklist.md) | Fab 準拠およびパッケージングのチェックリスト。 |
| [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md) | サードパーティソフトウェア宣言に関する注記。 |

## コア概念

UCM は中立的なハブです。C++ コード内で特定のパートナープラグインを知りません。UCM 自体、有効化されたプロバイダープラグイン、およびプロジェクトは、それぞれ機能（capabilities）、エンドポイント、スキーマ、ルール、ルート、変換、およびアダプターを JSON で記述できます。ローダーはそれらのセットアップルートを優先順位に従って統合し、レジストリを構築し、安全ルールを評価し、レポートを出力します。

現在のプロジェクトセットアップでは、UCM を Tiny Tool Development 製品間の主要な統合層として使用します。製品固有の動作は、JSON 呼び出し可能なエンドポイントまたはファイルコントラクトとして所有プラグイン内に保持されます。UCM はそれらを接続するセットアップのみをロードします。Freebie Bridges は UCM を持たないチーム向けのオプションのフォールバック/参照プラグインであり、デフォルトの接続モデルではありません。

## 重要なパス

```text
<EnabledPlugin>/Config/UnrealCapabilityMesh/  ← プロバイダーが所有する読み取り専用マニフェスト
Config/UnrealCapabilityMesh/                   ← オプションのプロジェクト所有のオーバーライドおよび複合ルート
Saved/UnrealCapabilityMesh/                    ← 生成されたレポートおよびルート出力
```

プロバイダーのルートを公開するためだけに、そのマニフェストをプロジェクトにコピーしないでください。プロバイダープラグインを有効にしてセットアップをリロードします。プロジェクトが意図的にプロファイルフィールドを変更する場合、または複合ルートを所有する場合にのみ、プロジェクトオーバーライドを作成してください。
