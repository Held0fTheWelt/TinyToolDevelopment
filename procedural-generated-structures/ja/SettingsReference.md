<!-- doc-provenance: AKDB:plugins/ProceduralGeneratedStructures/architecture.md; docs/architecture/plugins/ProceduralGeneratedStructures/product-facts.yml; reconciled 2026-06-21 -->
# 設定リファレンス

すべてのユーザー向けプロパティとデータアセットフィールド、およびその目的。

## `AAsyncProceduralGeneratedActor`

| プロパティ | カテゴリ | タイプ | 目的 |
| --- | --- | --- | --- |
| `InstancesPerFrame` | Procedural\|Performance | int32 (min 1) | 非同期ビルドが有効な場合に、すべてのビルドタスクにわたって 1 ティックあたりに追加されるインスタンス数。 |
| `bAutoBuildOnConstruction` | Procedural\|Build | bool | `OnConstruction` 中にビルドをトリガーします。 |
| `bUseAsyncBuild` | Procedural\|Build | bool | ビルドを複数のフレームに分散します（非ブロッキング）。それ以外の場合は 1 パスでビルドします。 |
| `bCenterGeneratedTransforms` | Procedural\|Build | bool | **生成された行**のトランスフォームをローカル XY 原点の周りに中心化します。キャプチャされた明示的なインスタンスは再中心化されません。 |
| `ProceduralStructure` | Procedural | `UProceduralStructureDataAsset` | 構築されるものを定義するデータソース。 |
| `ReadInComponentConfiguration` | Procedural | `FInstancedComponentConfiguration` の配列 | シーンの `UInstancedStaticMeshComponent` → データアセットエントリをマッピングします（読み込み）。 |
| `ComponentConfiguration` | Procedural | `FInstancedComponentConfiguration` の配列 | データアセットエントリ → この Actor 上のコンポーネントをマッピングします（リビルド）。 |
| `bClearProceduralStructureInformation` | Procedural\|Debug | bool | `ProceduralStructure` データをクリアします（エディタトリガー）。 |
| `bReadInMeshComponentData` | Procedural\|Debug | bool | シーンコンポーネントのインスタンスをデータアセットに読み込みます（エディタトリガー）。 |
| `EstimatedBuildInstanceCount` | Procedural\|Debug | int64 | 現在または最新のリビルドの推定インスタンス数。 |
| `AddedBuildInstanceCount` | Procedural\|Debug | int64 | 現在または最新のリビルドによって追加されたインスタンス。 |

### Actor ヘルパー関数

| 関数 | 目的 |
| --- | --- |
| `GetBuildPlan` | ターゲットコンポーネント、ブロッキング問題、変更の意図、プルーニング後の正確なインスタンス数を含む非変更のプレビュー。 |
| `GetEstimatedBuildInstanceCount` | 現在または最新のビルドの推定インスタンス数を返します。 |
| `GetAddedBuildInstanceCount` | 現在または最新のビルドによって追加されたインスタンス数を返します。 |
| `GetBuildProgress` | 見積もりが利用可能な場合に `0.0` から `1.0` までのビルド進行状況を返します。 |

## `FInstancedComponentConfiguration`

| フィールド | タイプ | 目的 |
| --- | --- | --- |
| `Name` | FName | Actor 上のインスタンス化されたメッシュコンポーネントの名前。 |
| `StructureType` | `EStructureType` | マッピング用の構造体分類。 |

## `EStructureType`

`None`、`Structure`、`Railing`、`Tribune`、`Stairs`。

## `UProceduralStructureDataAsset` → `FInstancedMeshInformation`

| フィールド | タイプ | 目的 |
| --- | --- | --- |
| `Name` | FName | エントリ名（コンポーネント構成と一致）。 |
| `Type` | `EStructureType` | 構造体分類。 |
| `Mesh` | `UStaticMesh` | インスタンスに使用されるメッシュ。 |
| `Instances` | `FTransform` の配列 | 正確に再生される明示的なトランスフォーム。 |
| `InstancedMeshRows` | `FInstancedMeshRowInformation` の配列 | プロシージャル行生成ルール。 |

### DataAsset ヘルパー関数

| 関数 | 目的 |
| --- | --- |
| `GetElementStats` | 名前付きエントリの `FProceduralStructureElementStats` を返します。 |
| `GetAllElementStats` | すべてのエントリの統計を返します。 |
| `GetTotalExplicitInstanceCount` | すべてのエントリにわたってキャプチャされた明示的なインスタンスをカウントします。 |
| `GetTotalPotentialGeneratedInstanceCount` | プルーニング前の生成行容量をカウントします。 |
| `GetTotalGeneratedInstanceCount` | プルーニング後の生成行インスタンスをカウントします。 |
| `GetTotalInstanceCount` | 明示的インスタンスとプルーニング後の生成インスタンスの合計をカウントします。 |

## `FProceduralStructureBuildPlan`

| フィールド | タイプ | 目的 |
| --- | --- | --- |
| `bHasDataAsset` / `bHasComponentConfiguration` / `bHasInstancedComponents` | bool | ハイレベルな準備完了フラグ。 |
| `ConfiguredComponentCount` / `AvailableInstancedComponentCount` | int32 | マッピング数と検出された Actor 所有の ISM コンポーネント数。 |
| `MutatingComponentCount` | int32 | クリアされてリビルドされるコンポーネント。 |
| `InstanceAddingComponentCount` | int32 | 1 つ以上のインスタンスを受け取るコンポーネント。 |
| `TotalExplicitInstanceCount` | int64 | ビルド可能なエントリ内のキャプチャされた明示的なインスタンス。 |
| `TotalPotentialGeneratedInstanceCount` | int64 | プルーニング前の生成行容量。 |
| `TotalGeneratedInstanceCount` | int64 | プルーニング後の生成行インスタンス。 |
| `TotalInstanceCount` | int64 | 明示的インスタンスとプルーニング後の生成インスタンスの合計。 |
| `Entries` | `FProceduralStructureBuildPlanEntry` の配列 | 構成されたコンポーネントごとのプレビューエントリ。 |
| `Issues` | string の配列 | ブロッキング問題コード。 |

## `FProceduralStructureElementStats`

| フィールド | タイプ | 目的 |
| --- | --- | --- |
| `Name` / `Type` / `Mesh` / `bHasMesh` | 混合 | データアセットエントリの識別情報とメッシュ準備状態。 |
| `ExplicitInstanceCount` | int32 | キャプチャされた明示的トランスフォームの数。 |
| `RowRuleCount` | int32 | 行生成ルールの数。 |
| `PotentialGeneratedInstanceCount` | int64 | プルーニング前の行容量。 |
| `GeneratedInstanceCount` | int64 | プルーニング後の正確な生成数。 |
| `TotalInstanceCount` | int64 | 明示的数とプルーニング後の生成数の合計。 |

## `FInstancedMeshRowInformation` (行生成)

| フィールド | タイプ | 目的 |
| --- | --- | --- |
| `Transform` | FTransform | 行の基本トランスフォーム。 |
| `RowCount_FirstDimension` / `_SecondDimension` / `_ThirdDimension` | int32 (min 0) | 次元ごとのインスタンス数。 |
| `Movement_First_Dimension` / `_Second_Dimension` / `_Third_Dimension` | FTransform | 各次元に沿って適用されるステップごとのトランスフォーム。 |
| `MovementAdjustmentByRotation_First_Dimension` | FVector | 最初の次元に沿った回転によって適用される移動調整。 |
| `DefinedSecondDimension` | FVector の配列 | 2 番目の次元の明示的な配置。 |
| `PrunedInstances` / `PrunedFirstDimension` / `PrunedSecondDimension` / `PrunedThirdDimension` / `PrunedSecondDimensionInThirdDimension` | 配列 | 生成中にスキップするインデックス/インスタンス。 |
| `bApplyRowCountAdjust` | bool | 行数調整を適用します。 |
| `bUseDefinedPlacementMethod` | bool | ステップ移動の代わりに `DefinedSecondDimension` 配置を使用します。 |
