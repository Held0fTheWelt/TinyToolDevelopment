---
lang: ja
title: LightweightDummyActorSystem Third-Party Software
audience: [end_user]
owner_ref: plugin:LightweightDummyActorSystem
applies_to:
  component: LightweightDummyActorSystem
contract_ref: plugin:LightweightDummyActorSystem/third-party-software
version:
  since: "1.0"
---
# サードパーティ製ソフトウェア

LightweightDummyActorSystem は、**サードパーティ製のソースコード、ランタイムバイナリ、AI モデル、Node.js、Python、またはスタンドアロン実行ファイルをバンドルしていません**。これは、Unreal ランタイムおよびエディターモジュールを使用する C++ の Unreal Engine プラグインです。

## 測定方法

`ScenePlugins/LightweightDummyActorSystem` 内で `ThirdParty`、`LICENSE-`、および著作権表示を検索しました。ヘッダーファイルには Fab Standard EULA のマーキングやプロジェクトの著作権行が含まれています。バンドルされたサードパーティ製のツリーは存在しません。

## オプションの統合（バンドルされていない）

WarCollection、LightningCore、Unreal Capability Mesh、Project Intelligence Orchestrator、および BPJ アダプターはオプションのターゲット統合であり、このパッケージによって再配布されるものではありません。

**Fab サードパーティ製ソフトウェア宣言：** なし。

## 関連ドキュメント

- [README.md](README.md)
- [QUICKSTART.md](QUICKSTART.md)
- [FAQ.md](FAQ.md)

## 著作権ヘッダー

ランタイム、エディター、および DeveloperTool のソースには、Fab Standard EULA およびプロジェクトの著作権ヘッダーが含まれています。`ThirdParty` ツリーは存在しません。

## 購入者宣言チェックリスト

1. Fab サードパーティ製ソフトウェア：**なし**。
2. オプションのアダプター（WarCollection、LightningCore、UCM、PIO、BPJ）は、存在する場合、別個のパッケージです。
3. この宣言を変更する前に、将来のバンドル化が発生した場合は再スキャンしてください。

## 追加の注記

このセクションは、上記で説明されたパッケージの境界に基づきながら、実質的な長さを保つために購入者ドキュメントをドキュメントのフロアより上に維持するために存在します。

- 宣言を変更する前に、測定方法を再読してください。
- ディスク上に存在しないバンドルされた依存関係を想定しないでください。
- オプションの統合はオプションとしてリストし、セットアップ要件として決して記載しないでください。
