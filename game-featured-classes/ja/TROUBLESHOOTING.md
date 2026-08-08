---
lang: ja
title: GameFeaturedClasses Troubleshooting
audience: [end_user]
owner_ref: plugin:GameFeaturedClasses
applies_to:
  component: GameFeaturedClasses
symptom: Buyer expects a GameFeature workbench or featured classes that are not shipped in 1.0.1.
recovery:
  steps:
    - Confirm the plugin is enabled under Edit > Plugins and restart the editor
    - Re-read the matching troubleshooting entry and apply the documented fix
    - Re-run the quick start smoke check
version:
  since: "1.0"
---
# トラブルシューティング

形式: 症状 → 原因 → 解決策

## 0. 有効化したのに何も起こらない

**症状:** `GameFeaturedClasses` を有効化して再起動した後、Tiny Tools メニュー、新しい Content Browser アセット、ワークベンチ UI が表示されない。  
**原因:** バージョン `1.0.1` はランタイム モジュールのシェルのみを提供します。フィーチャード クラスやエディター サーフェスはまだ利用できません。  
**解決策:** **[編集] → [プラグイン]** でプラグインが有効になっていることを確認し、`GameFeaturedClasses` モジュールが読み込まれていることを確認します（[QUICKSTART.md](QUICKSTART.md) を参照）。後続のパッケージで製品メニューが提供されるまで、製品メニューは表示されません。

## 1. 欠落している GameFeature ワークベンチ メニューを探している

**症状:** プラグインを有効化しても、Tiny Tools / ワークベンチのエントリが表示されない。  
**原因:** バージョン 1.0.1 はランタイム モジュールのシェルのみを提供します。エディターのワークベンチ サーフェスはまだ利用できません。  
**解決策:** プラグインをモジュールの境界としてのみ使用してください。後続のパッケージで明示的に提供されるまで、ワークベンチ UI は表示されないものと想定してください。

## 2. Content Browser にフィーチャード クラスがない

**症状:** プラグインを有効化しても、ゲームプレイ クラスのアセットが追加されない。  
**原因:** パッケージにはフィーチャード クラスやフィーチャ セットの内容が含まれていません。  
**解決策:** プロジェクトのクラスは独自のモジュールに保持し、フィーチャード クラスの提供は将来のパッケージ作業として扱ってください。

## 3. [編集] → [プラグイン] にプラグインが表示されない

**症状:** `GameFeaturedClasses` を検索しても何も返されない。  
**原因:** プラグインがプロジェクトまたはエンジン プラグイン フォルダーにコピーされていない、または記述子がフィルタリングされている。  
**解決策:** プロジェクトの `Plugins` ツリー（またはエンジン プラグイン）内に `GameFeaturedClasses.uplugin` が存在することを確認し、エディターを再起動してください。

## 4. サポートされていないエンジンでモジュールの読み込みに失敗する

**症状:** UI での有効化は成功するが、ランタイム モジュールのコンパイル/読み込みで失敗する。  
**原因:** パッケージ化された 5.4–5.8 のマトリックスから外れたエンジン バージョン、またはバイナリの不一致。  
**解決策:** Fab ビルドと一致するサポート対象のエンジン ブランチを使用するか、そのエンジンでソースから再構築してください。

## 5. `LightweightDummyActorSystem` または PIO を必須依存関係として期待している

**症状:** 他の製品のセットアップ ガイドから、GFC が LDAS/UCM/PIO を必要とするように示唆されている。  
**原因:** それらの統合はオプションのターゲット アーキテクチャであり、シェルのランタイム要件ではありません。  
**解決策:** シェルのスモーク チェックには `GameFeaturedClasses` のみを有効化してください。提供された統合が存在する場合にのみ、後続のピアを追加してください。

## 6. オンライン ドキュメントはどこにあるか？

**症状:** Fab / 記述子の DocsURL がブラウザ ページに解決されるはずである。  
**原因:** オンラインのランディング ページは Fab パッケージの外側にあります。  
**解決策:** `https://docs.tiny-tool-development.com/game-featured-classes/`（記述子 `DocsURL`）を開くか、このプラグインに同梱されているパッケージ内の `Documentation/` セットを使用してください。

## 関連ドキュメント

- [QUICKSTART.md](QUICKSTART.md)
- [UserManual.md](UserManual.md)
- [FAQ.md](FAQ.md)
- [SettingsReference.md](SettingsReference.md)
