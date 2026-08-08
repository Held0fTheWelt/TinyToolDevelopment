---
lang: ja
title: GameFeaturedClasses Quick Start
audience: [end_user]
owner_ref: plugin:GameFeaturedClasses
applies_to:
  component: GameFeaturedClasses
preconditions:
  - Unreal Engine project open with the plugin package available
  - Edit > Plugins can enable GameFeaturedClasses
expected_result:
  text: GameFeaturedClasses runtime module is enabled and loads after editor restart.
version:
  since: "1.0"
---
# クイックスタート

このガイドでは、**GameFeaturedClasses** のインストールと有効化を行い、ランタイム モジュールが正常に読み込まれることを確認します。バージョン `1.0.1` は**モジュールのシェル**です。記述子、パッケージング メタデータ、アイコン、変更履歴が含まれていますが、ゲームプレイ クラス、Game Feature アクション、またはエディタ ワークベンチは含まれていません。

## このガイド完了後

プロジェクトでプラグインが有効化され、エディタの再起動後にモジュール リストに `GameFeaturedClasses` ランタイム モジュールが表示されます。

## 要件

- Unreal Engine 5.4–5.8（パッケージ化されたリリース マトリックス）。
- シェルには他の Tiny Tool プラグインは必要ありません。
- サードパーティ製ソフトウェア、アカウント、または外部ランタイムは不要です。[THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md) を参照してください。

## 1. インストールと有効化

1. Fab から **GameFeaturedClasses** を取得し、プロジェクトに追加します（またはエンジンの Plugins ディレクトリにインストールします）。
2. **編集 → プラグイン** を開き、**GameFeaturedClasses** を検索して有効化し、指示されたら再起動します。

## 2. モジュール境界の確認

再起動後、ランタイム モジュールが読み込まれていることを確認します（出力ログ / モジュール マネージャー）。公開モジュール インターフェースは `Source/GameFeaturedClasses/Public/GameFeaturedClasses.h` 内の `FGameFeaturedClassesModule` で、`StartupModule` / `ShutdownModule` のみが定義されています。

## 3. 実例：シェルのスモークテスト

1. Unreal Engine 5.4 以上のプロジェクトを作成するか、既存のプロジェクトを開きます。
2. 上記の手順でプラグインを有効化し、再起動します。
3. 出力ログで、ロード後の `GameFeaturedClasses` のモジュール起動時のノイズをフィルタリングします。

このパッケージ バージョンには、フィーチャード クラスのレジストリ UI や実行可能なサンプル Game Feature アクションはありません。存在しないワークベンチ メニューを呼び出すと失敗することは想定されており、これらの機能は**まだ利用できません**。

## 期待される結果

- プラグインが **編集 → プラグイン** で有効化されているとして表示されます。
- ランタイム モジュールが、他の Tiny Tool プラグインを必要とせずに起動およびシャットダウンします。
- このパッケージからはゲームプレイのフィーチャード クラス アセットが Content Browser に表示されません（パッケージに含まれていないため）。

## 次のステップ

- 現在の境界と目標とする境界については [UserManual.md](UserManual.md) をお読みください。
- スコープに関する質問については [FAQ.md](FAQ.md) をお読みください。
- 後続のパッケージでこれらのクラスとエディタ画面が提供されるまで、プレミアム GameFeature Workbench の動作を目標アーキテクチャとして扱ってください。

## 覚えておくべき境界

- 1.0.1 で GFC コンテンツとして提供されることを期待して、プロジェクトのゲームプレイ クラスをこのプラグイン フォルダに追加しないでください。
- まだパッケージ化されていないワークベンチを「アンロック」するためにのみ、関連プラグインを有効化しないでください。
- 後続のバージョンでフィーチャード クラスが提供された場合、このクイックスタートを更新し、実際のクラス名とそのリリースからの実例を含めてください。
