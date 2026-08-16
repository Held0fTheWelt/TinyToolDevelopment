<!-- doc-provenance: AKDB:plugins/ProceduralGeneratedStructures/architecture.md; docs/architecture/plugins/ProceduralGeneratedStructures/product-facts.yml; reconciled 2026-06-21 -->
# ユーザーマニュアル

このマニュアルでは、Unreal Editor での Procedural Generated Structures の使用方法について説明します。

## 目的

Procedural Generated Structures は、データアセットから再利用可能なインスタンス化されたスタティックメッシュ構造体を構築します。
ランタイム Actor は、既存の `UInstancedStaticMeshComponent` インスタンスを `UProceduralStructureDataAsset` に読み込み、それらの明示的なインスタンスをリビルドしたり、追加の行ベースの構造体を生成したりできます。

## コアオブジェクト

- **`AAsyncProceduralGeneratedActor`** — ビルドワークフローを所有し、同期的に、またはエディタ/ゲームのティックにわたってコンポーネントをリビルドできます。
- **`UProceduralStructureDataAsset`** — 明示的なトランスフォームとオプションの行生成ルールを持つ名前付きメッシュエントリ (`FInstancedMeshInformation`) を保存します。
- **`FInstancedComponentConfiguration`** — Actor 上の名前付きインスタンス化メッシュコンポーネントを保存されたデータアセットエントリにマッピングします (`Name` + `StructureType`)。
- **`FProceduralStructureBuildPlan`** — ターゲットコンポーネント、ブロッキングの問題、変更の意図、非同期カウント、プルーニング後の正確なインスタンス合計など、リビルドによって何が行われるかを報告します。
- **`FProceduralStructureElementStats`** — エントリごとの明示的、生成、潜在的生成、および合計インスタンス数を報告します。
- **`EStructureType`** — `None`、`Structure`、`Railing`、`Tribune`、`Stairs`。

## ワークフロー

1. レベルまたは Blueprint に `AAsyncProceduralGeneratedActor` を追加します。
2. **安定したコンポーネント名**を持つ 1 つ以上の `UInstancedStaticMeshComponent` 子コンポーネントを追加します。
3. `UProceduralStructureDataAsset` を **ProceduralStructure** に割り当てます。
4. **ReadInComponentConfiguration** を構成して、既存のコンポーネントインスタンスをアセットにキャプチャします（**bReadInMeshComponentData** でトリガー）。
5. **ComponentConfiguration** を構成して、それらのエントリをコンポーネント上にリビルドします。
6. 自動化を使用する場合は、**GetBuildPlan** (Blueprint/C++) またはプレビュールートを検査します。リビルドを適用する前に報告された問題を解決してください。
7. **bClearProceduralStructureInformation**（クリア）、**bReadInMeshComponentData**（読み込み）、およびビルド（コンストラクション / 非同期）を使用して構造体を反復処理します。

## ビルドメモ

- シーンコンポーネントから読み取られた明示的なトランスフォームは**正確に再生**され、リビルド中に再中心化されることはありません。
- 生成された行のトランスフォームは、**bCenterGeneratedTransforms** を使用してローカル XY 原点の周りに中心化できます。
- **InstancesPerFrame** は、非同期ビルドが有効な場合に 1 ティックあたりに追加されるインスタンス数を制限します。
- 行数は、生成前に非負の値にクランプされます。
- ビルドプランと DataAsset 統計は、プルーニング前の未カットの行容量とプルーニング後の正確な生成数の両方を報告するため、変更前に大規模なリビルドを推定できます。
- **bAutoBuildOnConstruction** は、`OnConstruction` 中にビルドをトリガーします（スプライン Actor と同様）。
- **bUseAsyncBuild** は、ビルドを複数のフレームに分散します。それ以外の場合、ビルドは 1 つのパスで実行されます。
- **GetBuildProgress**、**GetEstimatedBuildInstanceCount**、および **GetAddedBuildInstanceCount** は、エディタツールおよび Blueprint 向けに非同期ビルドの進行状況を報告します。

## ビルドプランと検証

`AAsyncProceduralGeneratedActor::GetBuildPlan` は非変更のプレビューです。大規模または共有構造体をリビルドする前に使用してください。

ビルドプランの報告内容:

- データアセット、コンポーネント構成、および Actor が所有するインスタンス化されたメッシュコンポーネントが存在するかどうか。
- コンポーネントパス、メッシュパス、DataAsset エレメント統計、変更の意図、ブロッキング問題コードを含む、構成されたコンポーネントごとの 1 つのエントリ。
- 明示的なインスタンス、プルーニング前の潜在的な生成インスタンス、プルーニング後の生成インスタンス、および組み合わされたインスタンス数の合計。

一般的なブロッキング問題コードには以下が含まれます:

- `missing_procedural_structure_data_asset`
- `missing_component_configuration`
- `actor_has_no_instanced_static_mesh_components`
- `component_not_found:<Name>`
- `data_asset_element_not_found:<Name>`
- `data_asset_element_missing_mesh:<Name>`
- `data_asset_element_type_none:<Name>`

## データアセットエントリ

各 `FInstancedMeshInformation` エントリの内容:

- `Name`、`Type` (`EStructureType`)、`Mesh` (`UStaticMesh`)。
- `Instances` — 明示的なトランスフォーム（シーンからキャプチャされたものなど）。そのまま再生されます。
- `InstancedMeshRows` — オプションのプロシージャル行ルール（次元ごとの行数、次元ごとの移動トランスフォーム、プルーニング/定義済み配置オプション）。すべてのフィールドについては [SettingsReference.md](SettingsReference.md) を参照してください。

## プラグインが行わないこと

- スタティックメッシュの自動作成は行いません — ご自身で用意してください。
- 明示的にキャプチャされたインスタンスを再中心化することはありません。
- 完全なプロシージャルモデリングシステムではありません。データからインスタンス化されたメッシュを配置および再生成します。
