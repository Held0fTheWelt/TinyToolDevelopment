---
lang: ja
title: GameFeaturedClasses Settings Reference
audience: [end_user]
owner_ref: plugin:GameFeaturedClasses
applies_to:
  component: GameFeaturedClasses
contract_ref: plugin:GameFeaturedClasses/module-shell-settings
version:
  since: "1.0"
---
# 設定リファレンス

GameFeaturedClasses 1.0.1 には、DeveloperSettings、構成 `.ini` オブジェクト、または編集可能なフィーチャードクラス記述子は同梱されていません。ランタイム モジュールは、空のモジュールインターフェース以外に `UPROPERTY` 設定表面を公開していません。

## 同梱されている表面

| 名前 | 型 | デフォルト | 効果 |
| --- | --- | --- | --- |
| プラグインの有効化 | エディタ プラグイン UI | バイヤーが有効化するまで無効 | `GameFeaturedClasses` ランタイム モジュールを読み込みます。 |
| `FGameFeaturedClassesModule::StartupModule` | モジュールフック | エンジンによって呼び出される | モジュールの起動; バイヤー設定なし。 |
| `FGameFeaturedClassesModule::ShutdownModule` | モジュールフック | エンジンによって呼び出される | モジュールのシャットダウン; バイヤー設定なし。 |

## まだ利用不可

| 期待される設定表面 | ステータス |
| --- | --- |
| フィーチャードクラス記述子アセット | まだ利用不可 |
| フィーチャセットアセット | まだ利用不可 |
| レジストリ / 解決設定 | まだ利用不可 |
| エディタワークベンチ環境設定 | まだ利用不可 |
| `UGameFeaturedClassesSettings` DeveloperSettings | まだ利用不可 |
| `Config/DefaultGameFeaturedClasses.ini` | 同梱されていない |

ここで設定行を捏造することはありません。後続のパッケージバージョンで実際の `UPROPERTY` / DeveloperSettings フィールドが追加された場合、このリファレンスは同じ変更でソースから更新されなければなりません。

## 関連ドキュメント

- [UserManual.md](UserManual.md) — 現在のターゲット境界。
- [QUICKSTART.md](QUICKSTART.md) — 有効化スモークチェック。
- [FAQ.md](FAQ.md)

## パッケージングメタデータ（ランタイム設定ではない）

`.uplugin` 記述子には、パッケージング用の `Version` / `VersionName` が含まれています。これらのフィールドはプラグインメタデータであり、ランタイム DeveloperSettings ではなく、バイヤーのドキュメントワークフローから安易に編集してはなりません。

## 更新ルール

このファイル内の将来の設定行は、同じドキュメント変更において、ソースからのヘッダーパスとプロパティ名を引用しなければなりません。
