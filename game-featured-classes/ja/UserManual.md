# ユーザーマニュアル

`GameFeaturedClasses` は現在、プロジェクト固有のフィーチャーゲームプレイクラス用の軽量なランタイムプラグインシェルを提供しています。

## 現在のパッケージの動作

| 領域 | 1.0.1 でのステータス |
| --- | --- |
| ランタイムモジュール (`GameFeaturedClasses`) | 同梱 — 起動/シャットダウンのみ。 |
| デスクリプタ / パッケージング / アイコン / 変更履歴 | 同梱。 |
| フィーチャーゲームプレイクラス | まだ利用不可 |
| Game Feature アクション / フィーチャーセットアセット | まだ利用不可 |
| ランタイムレジストリ / インターフェース境界 | まだ利用不可 |
| エディターワークベンチ / 修復 / 証明レポート | まだ利用不可 |
| Tiny Tools 自動化ルート | まだ利用不可 |

<!-- image slot: gfc-module-shell -->

## ソースマップ

- `Source/GameFeaturedClasses/GameFeaturedClasses.Build.cs` — モジュール依存関係。
- `Source/GameFeaturedClasses/Public/GameFeaturedClasses.h` — `FGameFeaturedClassesModule` インターフェース。
- `Source/GameFeaturedClasses/Private/GameFeaturedClasses.cpp` — 起動とシャットダウン。

## 現在のシェル使用方法

1. プラグインを有効にします（[QUICKSTART.md](QUICKSTART.md) を参照）。
2. このパッケージがそれらを同梱するまで、プロジェクト固有のフィーチャークラスを独自のモジュールに保持してください。
3. このビルドに存在しないワークベンチメニューについて文書化したり、依存したりしないでください。

## 目標アーキテクチャ（参考情報、同梱されません）

内部製品アーキテクチャは、著者がフィーチャークラスとフィーチャーセットを宣言し、ワールドスコープのアクションがそれらを登録し、消費者がレジストリ/インターフェース境界を通じてそれらを解決し、メンテナがフィーチャーグラフをスキャンし、管理された修復をプレビューし、証明レポートをエクスポートする将来のプレミアム GameFeature Workbench を記述しています。その動作は**目標指定のみ**であり、1.0.1 において購入者利用可能な機能として扱ってはなりません。

## 自律性

このモジュールシェルは単独でロードされます。`LightweightDummyActorSystem`、Unreal Capability Mesh、または Project Intelligence Orchestrator との将来のオプション統合は、このパッケージのセットアップ要件ではありません。

## 関連ドキュメント

- [QUICKSTART.md](QUICKSTART.md)
- [SettingsReference.md](SettingsReference.md)
- [FAQ.md](FAQ.md)
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md)
- [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md)
