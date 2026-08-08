---
lang: ja
title: EditorExtensionBase Third-Party Software
audience: [end_user]
owner_ref: plugin:EditorExtensionBase
applies_to:
  component: EditorExtensionBase
contract_ref: plugin:EditorExtensionBase/third-party-software
version:
  since: "1.0"
---
# サードパーティ製ソフトウェア

Editor Extension Base は、**サードパーティ製のソースコード、ランタイムバイナリ、AI モデル、Node.js、Python、またはスタンドアロン実行ファイルをバンドルしていません**。これは、Unreal Editor モジュールと Editor Scripting Utilities を基盤とした C++ 製の Unreal Engine プラグインです。

## 測定方法

`GovernanceDevelopmentPlugins/EditorExtensionBase` 内で `ThirdParty`、`LICENSE-`、および著作権表示を検索しました。ヘッダーには Tiny Tool Development / Fab EULA が記載されています。バンドルされたサードパーティ製のツリーは存在しません。

## エンジン依存関係（バンドルされていないもの）

| 依存関係 | バンドル済み？ | 備考 |
| --- | --- | --- |
| Unreal Engine Editor モジュール | いいえ | エンジンのインストールによって提供されます。 |
| Editor Scripting Utilities | いいえ | `.uplugin` の `Plugins` エントリを介して有効化されます。Epic 所有のプラグインです。 |

## オプションの統合

機能プラグインは、共有ウィジェットのために Editor Extension Base に依存する場合があります。それらの消費側は別のパッケージであり、ここでは再配布されていません。

**Fab サードパーティ製ソフトウェア宣言：** なし。

## 関連文書

- [README.md](README.md)
- [QUICKSTART.md](QUICKSTART.md)
- [FAQ.md](FAQ.md)

## 著作権ヘッダー

エディターおよびランタイムのソースには、Tiny Tool Development / Fab Standard EULA のヘッダーが使用されています。`ThirdParty` ディレクトリ内に追加のライセンスファイルは見つかりませんでした。

## 購入者宣言チェックリスト

1. Fab に対して、バンドルされたサードパーティ製ソフトウェアは**ない**ことを宣言します。
2. Editor Scripting Utilities は Epic エンジンのプラグイン依存関係であり、バンドルされたサードパーティ製のツリーではありません。
3. このファイルを更新する前に、将来のバンドル変更の後に検索を再実行してください。
