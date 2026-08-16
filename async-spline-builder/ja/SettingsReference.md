<!-- doc-provenance: product-facts.yml reconciled 2026-07-15; source AKDB:plugins/AsyncSplineBuilder/architecture.md -->
# 設定リファレンス

このリファレンスでは、`ASplineGeneratingActor` を構成する際にほとんどのユーザーが必要とする設定について説明します。

## ワークフローパネルのマッピング

タスク優先の UI については **Tools > Track Tools > Async Spline Builder** を開きます。パネルは **Build**、**Segments**、**Terrain** タブに分かれています。Actor 選択、メッシュセットアップ、検証、ビルド/リビルドコマンド、非同期バッチ処理、閉ループ状態、デバッグラベル、セグメント行ヘルパー、ジャンプギャップ、スタントドロップ、ランドスケープ割り当て、レイヤーペイント設定、高さ変形、スナップ切り替え、Actor レベルのグランドウォールをカバーしています。

設定が Details パネルにしか露出していない場合や、正確なフィールド挙動が必要な場合はこのリファレンスを参照してください。セグメントごとの追加メッシュ配列、詳細なグランドウォール設定、トレースオブジェクト配列、コリジョンフラグ、UV コントロール、データアセットフィールドは Details パネルの高度な設定のままです。

## メッシュセットアップ

### StartMesh

オープントラックで最初に生成される道路ピースに使用されるオプションのメッシュ。未設定の場合、選択されたセグメントの道路メッシュが使用されます。

### MainMesh

必須のフォールバック道路メッシュ。これが欠けている場合、検証により生成がブロックされます。

### EndMesh

オープントラックで最後に生成される道路ピースに使用されるオプションのメッシュ。未設定の場合、選択されたセグメントの道路メッシュが使用されます。

## TrackTools

### bEditSpline

有効にすると、生成されたコンポーネントがクリアされ、コンストラクション中はスプライン/デバッグ編集のみがアクティブなままになります。メッシュをリビルドせずにスプラインを整形する際に使用します。

### bShowSegmentNumbers / bShowPointNumbers

セグメントまたはポイントのインデックス用デバッグテキストコンポーネントを作成します。これらは他の生成されたコンポーネントとともにタグ付けされ、クリーンアップされます。

### bShowLayoutConnectorDebug

ブール値、デフォルトは `false`。パネルの **Layout Connectors** セクションにある **Show Connector Debug** チェックボックスは同じ設定を制御します。有効にすると、エディタは独立して解決可能なコネクタエンドポイントごとにテキストマーカーを表示します。各ラベルには、コネクタのインデックスと種類、`From` または `To` の役割、レイアウト ID、構成された距離が含まれ、そのサイズは `DebugTextWorldSize` に従います。

不足しているレイアウトや範囲外の距離は、誤った位置に表示されるのではなく無視されます。コネクタラベルの切り替えや更新は視覚専用です。トラックをリビルドしたり、コネクタ道路ジオメトリを作成したり、生成された道路数を変更したり、地形の挙動を拡張したりすることはありません。設定を無効にするとコネクタラベルのみが削除されます。

### bShowSplineVisualizationWidth / SplineVisualizationWidth

エディタスプラインの可視化幅を制御します。

### bSnapPointsToLandscape

スプラインポイントをトレースヒット位置に移動します。`ObjectsToHitForLandscapeLineTrace` が必要です。

### bTangentPointsUpdate

ポイントをランドスケープにスナップした後に接線を更新します。

### bMirrorExtraMesh

X スケールを反転して追加メッシュをミラーリングします。

### SplinePointType

スプライン更新時に適用されるスプラインポイントタイプ。`CurveCustomTangent` は道路に適したデフォルト値です。

### SplineZOffset

スプラインコンポーネントに垂直オフセットを適用します。

### TrackSplineData

セグメントごとのデータ。セグメントのエントリが存在しない場合は、インデックス `0` がフォールバックとして使用されます。

### AdditionalLayouts

ピットロード、代替ルート、サービスロード、装飾スプライン用のオプションのルートレコード。レガシー Actor スプラインは `Main` レイアウトのファサードのままです。

### LayoutConnectors

2 つのレイアウト距離間のパッシブな意味的リンク。各コネクタは以下を保存します:

- `FromLayoutId` / `FromDistance`
- `ToLayoutId` / `ToDistance`
- `ConnectorKind`

既知の種類は `PitEntry`、`PitExit`、`Link`、`ServiceAccess` です。`ConnectorKind` はオープンの `FName` のままであり、空でないカスタム種類も許可され警告として検証されます。空の種類、欠落したレイアウト、不良な距離、同じレイアウト上の非常に近いエンドポイントは、コネクタ検証によって報告されるコネクタスコープのエラーですが、コネクタエラーによってジオメトリのリビルドがブロックされることはありません。

コネクタ行はトランジションメッシュを生成せず、自動的にリビルドされず、地形変形の挙動を変更しません。

## TrackSplineData

### RoadMesh

セグメント用のオプションの道路メッシュ。`MainMesh` にフォールバックします。

### MeshInstances

セグメント内の正確な道路ピース数。ゼロより大きい場合、自動の長さベースのカウントをオーバーライドします。

### SegmentLength

`RoadMeshLength` が設定されていない場合の間隔フォールバック。`1` より大きい値が使用されます。

### RoadMeshLength

明示的な希望道路メッシュカバー長。メッシュの境界が視覚的なタイル長と一致しない場合に使用します。

### ExtraMeshStart / ExtraMesh / ExtraMeshEnd

最初、中間、最後のピース用のオプションの追加メッシュ配列。

### ExtraMeshOffset

追加メッシュスロットごとの横方向オフセット。

### GroundWallSettings

セグメントごとのウォール生成、トレース、幅、コリジョン、UV 設定。

## Options

### bClosedLoop

最後のスプラインポイントを最初のポイントに接続します。

### bEnableCollision

生成された道路およびプロシージャルウォールコンポーネントのコリジョンを有効にします。

### bCastShadow / bCastContactShadow

生成されたスプラインメッシュの影フラグを制御します。

### bMirrorMesh

道路メッシュのスケールをミラーリングします。

### bSnapMeshesToLandscape

生成された道路および追加メッシュのエンドポイントをトレースヒットにスナップします。トレースオブジェクトタイプが必要です。

## Landscape

### Landscape

エディタ専用の変形によって使用されるランドスケーププロキシ。

### ActorsToIgnoreForGenerationTraces

スナップおよびウォールトレースによって無視される Actor。

### bSnapTraceLandscapeOnly

true の場合、スナップトレースはランドスケープのヒットのみを受け入れます。

### ObjectsToHitForLandscapeLineTrace

メッシュおよびポイントのスナップに使用されるオブジェクトタイプ。スナップが有効な場合に必須です。

### FallOff

道路幅の外側で高さ変形が既存の地形になだらかになじむ距離。

### NumberOfSubdivisionsForDeform

ランドスケープ変形のスプラインサンプリング解像度。値が高いほどフィット感が向上しますがコストが増加します。

### bRaiseHeights / bLowerHeights

変形がランドスケープサンプルを上げるおよび/または下げることができるかを制御します。

### PaintHalfWidth

レイヤーペイント用の全重量の半幅 (cm)。`0` は各変形サンプルでの道路の半幅を使用します。

### PaintFallOff

レイヤーペイントの Smoothstep フォールオフ距離 (cm)。高さの `FallOff` とは独立しています。`0` は `PaintHalfWidth` の外側にソフトバンドのないハードエッジを与えます。

### PaintLayer

`PaintLandscapeLayerNow` / パネルの **Paint Layer** によって道路に沿ってペイントされる `ULandscapeLayerInfoObject`。ターゲットランドスケープに登録されている必要があります。レイヤー情報が `bNoWeightBlend` を使用している場合、ターゲットレイヤーはペイントを受け取ることができますが、道路の下で他のマテリアルレイヤーが減少することは保証されません。

### LandscapeEditLayerName

ランドスケープ設定でサポートされている場合に、ランドスケープ高さ編集に使用される編集レイヤー名。

### LineTraceLength

ランドスケープスナップ用のトレース深度。

## Async Build

### bUseAsyncBuild

バッチリビルドを有効にします。

### SegmentsPerTick

ティックごとに処理される非同期作業ユニットの数。1 作業ユニットは生成された 1 つの道路または追加メッシュピースであるため、多くのピースを持つ長いスプラインセグメントは一度に生成されず複数のティックに分散されます。応答性のために低めから開始し、テスト後に増やしてください。

### bAutoRebuildOnConstruction

コンストラクションの変更後にリビルドをスケジュールします。

## Ground Walls

### bGenerateGroundWalls

プロシージャルグランドウォール生成を有効にします。

### GroundWallSubdivisions

スプラインに沿ったウォールサンプル数。高い値ほど滑らかなウォールと多くのジオメトリを生成します。

### GroundWallOutset

派生した道路の半幅を超える追加の水平オフセット。

### GroundWallFallbackDepth

ウォールトレースがヒットしなかった場合に使用される深度。

### bGroundWallsDoubleSided

両面からウォールがレンダリングされるように逆三角形を追加します。

### GroundWallObjectsToHitForLineTrace

セグメントごとのトレース設定が空の場合の、グランドウォール用のデフォルトのトレースオブジェクトタイプ。

## GroundWallSettings

### bGenerateGroundWalls

セグメントごとのウォール有効化。

### bGenerateBothSides

false の場合、そのセグメントでは左側が抑制されます。

### TrackHalfWidth

手動の半幅オーバーライド。選択した道路メッシュの境界から幅を派生させるには `0` のままにします。

### MinWallHeight / MaxWallHeight

極小のウォールをスキップし、極大なウォールをクランプします。

### bCreateCollision

プロシージャルウォールのコリジョンを制御します（Actor の `bEnableCollision` でも制御されます）。

### TraceSettings

セグメントごとのトレースオブジェクトタイプ、トレース長、トレースの複雑さ。

### UVSettings

セグメントごとのウォール UV タイリングと反転。

## Drop Walls

### DropWallMaterial

生成されたドロップウォールに適用されるマテリアル。

### DropWallUVWorldUnitsU / DropWallUVWorldUnitsV

ドロップウォール用のワールド単位 UV タイリング。

## 推奨ベースライン

- `bUseAsyncBuild = true`
- `SegmentsPerTick = 24`
- `bAutoRebuildOnConstruction = true`
- `MainMesh` 割当済み
- メッシュの境界が誤っていない限り `RoadMeshLength = 0`
- メッシュの境界が誤っていない限り `TrackHalfWidth = 0`
- ウォールを有効にする前に構成されたグランドウォールトレースオブジェクトタイプ
- 道路の形状が安定した後に手動で実行されるランドスケープ変形
