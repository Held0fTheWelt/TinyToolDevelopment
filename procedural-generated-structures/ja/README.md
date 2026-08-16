<!-- doc-provenance: AKDB:plugins/ProceduralGeneratedStructures/architecture.md; docs/architecture/plugins/ProceduralGeneratedStructures/product-facts.yml; reconciled 2026-06-21 -->
# ProceduralGeneratedStructures ドキュメント

ProceduralGeneratedStructures は、データアセットから再利用可能なインスタンス化されたスタティックメッシュ構造体を構築します。ランタイム Actor は、既存の `UInstancedStaticMeshComponent` インスタンスを `UProceduralStructureDataAsset` に読み込み、それらの明示的なインスタンスをリビルドしたり、追加の行ベースの構造体を生成したりできます。また、リビルドを適用する前に、ターゲットコンポーネント、ブロッキングの問題、変更の意図、非同期の進行状況、プルーニング（剪定）後の正確なインスタンス数を検査できるように、ビルドプランと統計データも公開します。

## ドキュメント

- [QUICKSTART.md](QUICKSTART.md): インストール → Actor 配置 → キャプチャとリビルド（期待される結果を含む）。
- [UserManual.md](UserManual.md): 完全なワークフロー、コアオブジェクト、ビルドメモ。
- [SettingsReference.md](SettingsReference.md): すべての Actor プロパティとデータアセットフィールド。
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md) · [FAQ.md](FAQ.md)
- [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md): サードパーティ製ソフトウェアの宣言（同梱なし）。

## コアアセット

- `AAsyncProceduralGeneratedActor` はビルドワークフローを所有し、同期的に、またはエディタ/ゲームのティックにわたってコンポーネントをリビルドできます。
- `UProceduralStructureDataAsset` は、明示的なトランスフォームとオプションの行生成ルールを持つ名前付きメッシュエントリを保存します。
- `FInstancedComponentConfiguration` は、Actor 上の名前付きインスタンス化メッシュコンポーネントを保存されたデータアセットエントリにマッピングします。
- `FProceduralStructureBuildPlan` と `FProceduralStructureElementStats` は、ツール、Blueprint、UCM ルート向けに正確なプレビューデータを公開します。

## ビルドメモ

- シーンコンポーネントから読み取られた明示的なトランスフォームは正確に再生され、リビルド中に再中心化されることはありません。
- 生成された行のトランスフォームは、`bCenterGeneratedTransforms` を使用してローカル XY 原点の周りに中心化できます。
- `InstancesPerFrame` は、非同期ビルドが有効な場合に 1 ティックあたりに追加されるインスタンス数を制限します。
- 行数は、生成前に非負の値にクランプされます。
- ビルドプランは、プルーニング前の生成行容量と、プルーニング後の正確な生成数を報告します。

## 推奨ワークフロー

1. レベルまたは Blueprint に `AAsyncProceduralGeneratedActor` を追加します。
2. 安定したコンポーネント名を持つ 1 つ以上の `UInstancedStaticMeshComponent` 子コンポーネントを追加します。
3. `UProceduralStructureDataAsset` を割り当てます。
4. 既存のコンポーネントインスタンスをキャプチャするように `ReadInComponentConfiguration` を構成します。
5. それらのエントリをリビルドするように `ComponentConfiguration` を構成します。
6. `GetBuildPlan` またはプレビュールートを検査し、エディタで呼び出し可能な読み取り、クリア、ビルドアクションを使用して構造体を反復処理します。
