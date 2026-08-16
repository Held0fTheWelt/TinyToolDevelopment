<!-- doc-provenance: AKDB:plugins/ProceduralGeneratedStructures/architecture.md; docs/architecture/plugins/ProceduralGeneratedStructures/product-facts.yml; reconciled 2026-06-21 -->
# トラブルシューティング

## プラグインを有効にしましたが何も起こりません

プラグインは `AAsyncProceduralGeneratedActor` クラスと `UProceduralStructureDataAsset` を追加します。
Actor をレベル内に配置してください (Place Actors → *Async Procedural Generated Actor*)。メニューはありません —
ワークフローは Actor の Details パネルに存在します。

## ビルドでインスタンスが生成されない

- Actor に**安定した名前**を持つ少なくとも 1 つの `UInstancedStaticMeshComponent` 子コンポーネントがあるか確認します。
- **ComponentConfiguration** に、そのコンポーネントと **Name** が一致するエントリがあるか確認します。
- データアセットエントリに有効な **Mesh** が割り当てられているか確認します。
- 読み込みを使用している場合は、一致する **ReadInComponentConfiguration** エントリを使用して最初にキャプチャ (**bReadInMeshComponentData**) したことを確認します。
- **GetBuildPlan** を検査します。`component_not_found:<Name>`、`data_asset_element_not_found:<Name>`、`data_asset_element_missing_mesh:<Name>` などの正確な問題コードが報告されます。

## プレビューで非常に高いインスタンス数が報告される

ビルドプランは、プルーニング前の潜在的な生成インスタンス数と、プルーニング後の正確な生成数の両方を報告します。両方が高すぎる場合は、行数を減らすか、プルーニングを追加するか、または **bUseAsyncBuild** を有効にして **InstancesPerFrame** を下げてください。

## キャプチャされたインスタンスが予期せず移動/再中心化された

キャプチャされた明示的なインスタンスは正確に再生され、再中心化されることはありません。**bCenterGeneratedTransforms** の影響を受けるのは、**生成された行**のトランスフォームのみです。

## 大規模な構造体でビルド時にエディタ/ゲームが引っかかる

**bUseAsyncBuild** を有効にし、**InstancesPerFrame** を下げることで、1 つのブロッキングパスではなく複数のティックにわたってインスタンスが追加されるようにします。

## 読み込みで誤ったコンポーネントがキャプチャされた

`ReadInComponentConfiguration` はコンポーネントの **Name** で一致判定を行います。コンポーネント名が安定かつ一意であり、構成エントリの `Name` が正確に一致していることを確認してください。

## 生成されたグリッドにギャップがある

行情報の `Pruned*` 配列を確認してください — プルーニングされたインデックス/インスタンスは意図的にスキップされます。完全なグリッドを生成するにはこれらをクリアしてください。
