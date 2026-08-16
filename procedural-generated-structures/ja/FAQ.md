<!-- doc-provenance: AKDB:plugins/ProceduralGeneratedStructures/architecture.md; docs/architecture/plugins/ProceduralGeneratedStructures/product-facts.yml; reconciled 2026-06-21 -->
# よくある質問 (FAQ)

**このプラグインは他のプラグインを必要としますか？**
いいえ。完全に単体で動作します。

**メッシュは含まれていますか？**
いいえ。ご自身の `UStaticMesh` アセットをご用意ください。プラグインはそれらをインスタンス化します。

**サポートされている Engine のバージョンは何ですか？**
Unreal Engine 5.4+ (Win64, Linux, Mac)。モジュールは Runtime であるため、Actor はエディタ内およびパッケージ化されたゲーム内で動作します。

**サードパーティ製ソフトウェア、Python、または AI モデルは同梱されていますか？**
いいえ。[THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md) を参照してください。

**明示的なインスタンスと行生成の違いは何ですか？**
明示的なインスタンスは正確なトランスフォーム（既存のコンポーネントからキャプチャされたものが多い）であり、そのまま再生されます。行生成は、データアセットで定義された行数と次元ごとの移動トランスフォームからインスタンスをプロシージャルに作成します。

**エディタ内だけでなく、ランタイム時にもビルドできますか？**
はい。Actor はランタイム対応であり、同期またはティックにわたってビルドできます (`bUseAsyncBuild`)。

**大きな構造体でのフレーム落ちを防ぐにはどうすればよいですか？**
`bUseAsyncBuild` を有効にし、`InstancesPerFrame` を調整してください。

**コンポーネントを変更する前にリビルド結果をプレビューできますか？**
はい。`GetBuildPlan` またはリビルドプレビュールートを使用してください。プランはターゲットコンポーネント、ブロッキングの問題、変更の意図、プルーニング後の正確なインスタンス数を報告します。

**ツールで非同期ビルドの進行状況を表示できますか？**
はい。`GetEstimatedBuildInstanceCount`、`GetAddedBuildInstanceCount`、`GetBuildProgress` がエディタツール、Blueprint、自動化ルート向けに進行状況を公開しています。

**問題の報告やサポートの受けるにはどこに問い合わせればよいですか？**
Fab 製品ページのサポートリンクをご利用ください。
