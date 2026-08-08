# GameFeaturedClasses ドキュメント

GameFeaturedClasses は、プロジェクト固有の GameFeaturedClasses 用プレイクラスのための軽量なランタイムプラグインシェルです。バージョン `1.0.1` には、記述子、パッケージングメタデータ、アイコン、変更履歴、およびランタイムモジュールの境界（`StartupModule` / `ShutdownModule`）が含まれています。

対象読者：現在、GameFeature やプレミアムな GameFeature Workbench がターゲットアーキテクチャ（このパッケージではまだ利用不可）である一方で、プロジェクト内で GFC パッケージの境界が必要となるチーム。

## 現在のパッケージ

- ランタイムモジュール `GameFeaturedClasses` は、有効化と再起動後に読み込まれます。
- ゲームプレイの GameFeaturedClasses アセット、Game Feature アクション、レジストリ、またはエディタワークベンチは、まだ含まれていません。
- シェルに他の Tiny Tool プラグインは必要ありません。

## 始め方

1. プラグインを有効にする — [QUICKSTART.md](QUICKSTART.md) の作業例（モジュールの簡易チェック）を参照してください。
2. 現在の境界とターゲットの境界について [UserManual.md](UserManual.md) をお読みください。
3. ワークベンチメニューが期待されるが欠けている場合は、[TROUBLESHOOTING.md](TROUBLESHOOTING.md) を使用してください。

## 関連ファイル

- [../README.md](../README.md) — プロダクト概要。
- [../CHANGELOG.md](../CHANGELOG.md) — リリース履歴。
- [SettingsReference.md](SettingsReference.md) · [FAQ.md](FAQ.md) · [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md)
