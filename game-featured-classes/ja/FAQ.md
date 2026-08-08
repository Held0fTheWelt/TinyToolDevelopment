# よくある質問

## GameFeaturedClasses はゲームプレイクラスを提供しますか？

いいえ。バージョン 1.0.1 は、記述子、モジュール境界、パッケージングメタデータ、アイコン、変更履歴を含む軽量なランタイムプラグインのシェルです。プレミアムな GameFeature Workbench の動作はターゲットで指定されますが、このパッケージにはまだ実装されていません。

## 他の Tiny Tool プラグインが必要ですか？

いいえ。現在のモジュールシェルは単独で読み込まれます。LightweightDummyActorSystem、Unreal Capability Mesh、または Project Intelligence Orchestrator との将来の統合は、オプションのターゲットアーキテクチャであり、このパッケージのランタイム要件ではありません。

## 対応しているエンジンバージョンは何ですか？

パッケージ化されたリリースマトリクスは Unreal Engine 5.4 から 5.8 を対象としています（このブランチの記述子 `EngineVersion` は 5.4.0 です）。

## サードパーティソフトウェアや外部サービスが含まれていますか？

いいえ。このパッケージにはサードパーティソフトウェアはバンドルされておらず、アカウント、AI プロバイダー、または外部ランタイムを必要としません。[THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md) を参照してください。

## サポートはどこで受けられますか？

`mailto:support@tiny-tool-development.com`（記述子 `SupportURL`）または Fab 製品ページのサポートリンクを使用してください。

## なぜ設定パネルがないのですか？

バージョン 1.0.1 は DeveloperSettings や featured-class 記述子を公開していません。[SettingsReference.md](SettingsReference.md) を参照してください。

## プロジェクトの featured classes をこのプラグインフォルダ内に配置できますか？

1.0.1 で GFC コンテンツとして出荷する場合、それはできません。後続のパッケージが明示的に featured-class アセットを出荷するまで、プロジェクトのゲームプレイクラスは独自のモジュールに保持してください。

## シェルが読み込まれたことをどうやって確認しますか？

プラグインを有効にし、エディタを再起動して、`GameFeaturedClasses` ランタイムモジュールが存在することを確認します。[QUICKSTART.md](QUICKSTART.md) の実演例を参照してください。

## オンラインドキュメントはどこにありますか？

https://docs.tiny-tool-development.com/game-featured-classes/
