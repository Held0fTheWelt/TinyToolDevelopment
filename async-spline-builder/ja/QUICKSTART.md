<!-- doc-provenance: product-facts.yml reconciled 2026-07-15; source AKDB:plugins/AsyncSplineBuilder/architecture.md -->
# クイックスタートガイド

このガイドでは、インストールから**視覚的な結果**（制御するスプラインに沿って生成された道路/トラックメッシュ）までをご案内します。Async Spline Builder は単体で動作します — 他のプラグインは不要です。

## このガイドの終了時に得られるもの

レベル内に配置された `Spline Generating Actor` と、スプラインポイントを移動して変形させ、必要に応じてリビルドできるスプラインメッシュセクションから構築された道路。

## 要件

- Unreal Engine 5 エディタと開いているレベル。
- ローカル X 軸に沿ってタイル配置される少なくとも 1 つの**道路メッシュ**（ユーザーマニュアルのステップ 3 / メッシュ作成を参照）。開始するにはプロジェクト内の任意のタイルメッシュを使用できます。
- サードパーティ製ソフトウェア、アカウント、ランタイムは不要です。[THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md) を参照してください。

## 1. インストールと有効化

1. Fab ライブラリから **AsyncSplineBuilder** をプロジェクトに追加します（または Engine にインストールします）。
2. **Edit → Plugins** を開き、**AsyncSplineBuilder** を有効にして、プロンプトが表示されたら再起動します。

## 2. パネルを開く (最初の結果)

1. レベルを開くか作成します。
2. **Tools → Track Tools → Async Spline Builder** を開きます。パネルには **Build**、**Segments**、**Terrain** タブがあります。

## 3. 実践例: トラックを構築する

1. **Build** タブで **Create Actor** をクリックするか（`ASplineGeneratingActor` がスポーンします）、既存のものを選択して **Use Selection** をクリックします。
2. **Setup** で、タイリングメッシュを **MainMesh** に割り当てます（必須）。オプションで **StartMesh** と **EndMesh** を割り当てます。
3. ビューポートで Actor のスプラインポイントを移動してパスを形成します。
4. **Validate** をクリックします（`MainMesh` が設定され、スプラインが構築可能であることを確認します）。
5. **Build Now** をクリックします。

**期待される出力:** Actor はスプラインに沿って `USplineMeshComponent` 道路セクションを生成します。スプラインポイントを移動し、**Rebuild** をクリックして道路の更新を確認します。

> 長いトラックの場合は、**Use Async Build** を有効にし、**SegmentsPerTick** を設定して、生成がティック間でバッチ処理され、エディタの応答性が維持されるようにします。進行中の非同期ビルドを停止するには **Cancel** を使用します。

## 4. さらに進む (オプション)

- **Segments** タブ: セグメントごとのメッシュ、ジャンプギャップ (`JumpGapsByPoints`)、スタントドロップ。
- **Terrain** タブ: ランドスケープへのスナップ、高さ変形、およびプロシージャルな**グランドウォール** (`bGenerateGroundWalls`)。[LandscapeAndWalls.md](LandscapeAndWalls.md) を参照してください。
- **データアセット:** `WriteSplineToDataAsset` / `ReadSplineFromDataAsset` でレイアウトを保存/読み込みします。

## 5. 次のステップ

- 完全なワークフロー、セグメントデータ、ギャップ、ドロップ、ウォール、ランドスケープ変形: [UserManual.md](UserManual.md)。
- 設定: [SettingsReference.md](SettingsReference.md)。
- トラブルシューティング: [TROUBLESHOOTING.md](TROUBLESHOOTING.md) および [FAQ.md](FAQ.md)。
