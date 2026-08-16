<!-- doc-provenance: AKDB:plugins/ProceduralGeneratedStructures/architecture.md; docs/architecture/plugins/ProceduralGeneratedStructures/product-facts.yml; reconciled 2026-06-21 -->
# クイックスタートガイド

このガイドでは、インストールから**視覚的な結果**（データアセットからインスタンス化されたメッシュ構造体をリビルドする `AAsyncProceduralGeneratedActor`）までをご案内します。プラグインは単体で動作します — 他のプラグインは不要です。

## このガイドの終了時に得られるもの

インスタンス化されたスタティックメッシュのインスタンスがデータアセットにキャプチャされ、そこからリビルドされることで、構造体が再利用および再生成可能になったレベル内の Actor。

## 要件

- Unreal Engine 5 エディタと開いているレベル。
- インスタンス化するプロジェクト内の `UStaticMesh`（壁や柱のメッシュなど）。
- サードパーティ製ソフトウェア、アカウント、ランタイムは不要です。[THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md) を参照してください。

## 1. インストールと有効化

1. Fab ライブラリから **ProceduralGeneratedStructures** をプロジェクトに追加します（または Engine にインストールします）。
2. **Edit → Plugins** を開き、**ProceduralGeneratedStructures** を有効にして、プロンプトが表示されたら再起動します。

## 2. Actor を配置する (最初の結果)

1. **Place Actors** パネルで **Async Procedural Generated Actor** を検索し、レベル内にドラッグします（またはクラス一覧から `AAsyncProceduralGeneratedActor` を追加します）。
2. 1 つ以上の **Instanced Static Mesh Component** 子コンポーネントを Actor に追加し、それぞれに**安定したコンポーネント名**（`Walls` など）を指定します。スタティックメッシュを割り当て、いくつかのインスタンスを配置します。

## 3. 実践例: キャプチャとリビルド

1. Content Browser で **Procedural Structure Data Asset** (`UProceduralStructureDataAsset`) を作成し、Actor の **ProceduralStructure** プロパティに割り当てます。
2. **ReadInComponentConfiguration** で、**Name** がコンポーネント (`Walls`) と一致するエントリを追加し、**StructureType** (`Structure` など) を選択します。
3. **bReadInMeshComponentData** を設定して、コンポーネントの現在のインスタンスをデータアセットにキャプチャします。
4. **ComponentConfiguration** で、同じ **Name** (`Walls`) をデータアセットエントリにマッピングし直すエントリを追加します。
5. Blueprint/C++ の **GetBuildPlan** または自動化プレビュールートでプレビューします。クリーンなプランにはブロッキングの問題がなく、リビルドされる正確なインスタンス総数が報告されます。
6. リビルド — **bAutoBuildOnConstruction** を有効にするか（コンストラクション時にリビルド）、Actor を移動/編集してビルドをトリガーします。

**期待される出力:** インスタンス化されたメッシュがデータアセットからリビルドされます。キャプチャされた明示的なトランスフォームは正確に再生されます（再中心化されることはありません）。反復処理を行うには、**bClearProceduralStructureInformation** を設定して保存されたデータをクリアし、再度キャプチャします。

## 4. パフォーマンス / 非同期

- **bUseAsyncBuild**: 1 回のブロッキングパスではなく、複数のフレームにわたってビルドを分散します。
- **InstancesPerFrame**: 非同期ビルドが有効な場合に 1 ティックあたりに追加されるインスタンス数。
- **GetBuildProgress** / **GetAddedBuildInstanceCount**: ツール向けに非同期ビルドの進行状況を追跡します。
- **bCenterGeneratedTransforms**: *生成された行*のトランスフォームをローカル XY 原点の周りに中心化します（キャプチャされた明示的なインスタンスは再中心化されません）。

## 5. 行ベースの構造体を生成する (オプション)

キャプチャされたインスタンスを再生するだけでなく、データアセットエントリで **InstancedMeshRows** を定義してグリッド/行をプロシージャルに生成できます（次元ごとの行数と次元ごとの移動トランスフォーム）。すべてのフィールドについては [SettingsReference.md](SettingsReference.md) を参照してください。

## 6. 次のステップ

- 完全なワークフローとビルドメモ: [UserManual.md](UserManual.md)。
- すべての Actor プロパティとデータアセットフィールド: [SettingsReference.md](SettingsReference.md)。
- トラブルシューティング: [TROUBLESHOOTING.md](TROUBLESHOOTING.md) および [FAQ.md](FAQ.md)。
