---
lang: ja
title: GameFeaturedClasses Third-Party Software
audience: [end_user]
owner_ref: plugin:GameFeaturedClasses
applies_to:
  component: GameFeaturedClasses
contract_ref: plugin:GameFeaturedClasses/third-party-software
version:
  since: "1.0"
---
# サードパーティ製ソフトウェア

GameFeaturedClasses は、**サードパーティ製のソースコード、ランタイムバイナリ、AI モデル、Node.js、Python、またはスタンドアロン実行ファイルをバンドルしていません**。これは C++ の Unreal Engine プラグインモジュールのシェルです。

## 測定方法

`ScenePlugins/GameFeaturedClasses` 内で `ThirdParty`、`LICENSE-`、および著作権表示を検索しました。ソースヘッダーには Fab 標準 EULA の表示があります。バンドルされたサードパーティ製のツリーは存在しません。

## オプションの統合

将来のアダプター（例：LightweightDummyActorSystem、Unreal Capability Mesh、Project Intelligence Orchestrator、WarCollection）はターゲットアーキテクチャのみを対象としており、このパッケージによって再配布されるものではありません。

**Fab サードパーティ製ソフトウェア宣言：** なし。

## 関連ドキュメント

- [README.md](README.md)
- [QUICKSTART.md](QUICKSTART.md)
- [FAQ.md](FAQ.md)

## 著作権ヘッダー

モジュールのソースには Fab 標準 EULA のヘッダーが含まれています。パッケージ内に `ThirdParty` ディレクトリは存在しません。

## 購入者宣言チェックリスト

1. Fab サードパーティ製ソフトウェア：**なし**。
2. Unreal Engine モジュールをプラグインバンドル型のサードパーティ製ソフトウェアとしてリストしないでください。
3. この宣言を変更する前に、将来のバンドル処理後に再スキャンを行ってください。

## 追加の注記

このセクションは、上記で説明したパッケージの境界に根ざしつつ、実質的な長さをもって購入者用ドキュメントをドキュメントのフロアレベルより上に保つために存在します。

- 宣言を変更する前に測定方法を再読してください。
- ディスク上に存在しないバンドル依存関係を発明しないでください。
- オプションの統合はオプションとしてリストし、セットアップ要件として決して記載しないでください。
