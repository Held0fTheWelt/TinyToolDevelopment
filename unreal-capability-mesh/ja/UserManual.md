<!-- doc-provenance: AKDB:plugins/UnrealCapabilityMesh/architecture.md; docs/architecture/plugins/UnrealCapabilityMesh/product-facts.yml; reconciled 2026-07-19 -->
# ユーザーマニュアル

## コントロールパネル

以下からパネルを開きます:

```text
Tools -> Unreal Capability Mesh
```

パネルは、マニフェスト駆動の相互運用性のための技術操作ビューです。すべてのツールを1つの長いビューに積み重ねる代わりに、ステータスバナーとテーマ別のページを使用します。

ページ構成:

- `Overview`: アクティブプロファイル、インベントリ数、可用性カウント、セットアップフロー、および MCP コントラクト。
- `Capabilities`: ロードされた機能 ID、エンドポイント、副作用、利用可能性、警告、およびソースマニフェスト。
- `Routes`: ルートカタログ、ドライラン、および実行入出力。
- `Governance`: アクティブな副作用ボキャブラリとルール判定。
- `Tiny Tools`: Tiny Tool Development コンテンツ用のセットアップパッケージスイッチ。
- `Setup Editor`: プロジェクトセットアップマニフェスト、読み取り専用参照サンプル、および拘束力のないプレイグラウンドサンドボックス用型認識 JSON エディター。
- `Config Admin`: 一覧表示/読み取り/書き込み操作のための許可リストに登録された設定ターゲットおよびルートプリセット。
- `Diagnostics`: セットアップ検証、検出、およびリロードメッセージ。
- `Adapter`: ブリッジ依存関係なしでセットアップ宣言された機能を追加するためのスターターマニフェストライター。

## Tiny Tools

`Tiny Tools` ページは、以下のカタログマニフェストによって駆動されます:

```text
Config/UnrealCapabilityMesh/tool_catalogs/
```

最初のスイッチは、プロジェクトが Tiny Tool Development のセットアップコンテンツを使用するかどうかを指定します。オフにすると、カタログ所有のすべてのセットアップエントリがアクティブプロファイルから削除されます。個別のツールスイッチにより、カタログで宣言された以下のパッケージエントリが追加または無効化されます:

- 機能マニフェスト
- エンドポイントマニフェスト
- スキーマ表マニフェスト
- ルールマニフェスト
- ルートマニフェスト
- 変換マニフェスト
- アダプターマニフェスト
- 設定ターゲット ID

これは無効化モデルであり、ファイルの削除ではありません。マニフェストファイルはプロジェクト内に残り、後で再有効化できます。

Tiny Tool パッケージは、所有権ごとに意図的に分割されています。IIS、LLM Store、および UII は独立して有効化できます。プラグイン間のワークフローは別々のルートスイッチとなっているため、プロジェクトはスタック全体を所有することなく、IIS のみ、LLM Store のみ、UII+IIS、または IIS+LLM Store を使用できます。

プロファイルフィールド `enabled_config_target_ids` は、Config Admin に表示される設定ターゲットを制限します。このフィールドが存在しない場合、Config Admin は以前の動作を維持し、すべてのターゲットマニフェストをスキャンします。

## Setup Editor

`Setup Editor` ページは、`Config/UnrealCapabilityMesh` 配下のプロジェクトローカルマニフェストを型認識フィールドで編集します:

- ポリシーおよびプロファイルスイッチ用のブール値
- `enabled_*_manifests` 用の文字列配列
- `invocation_mode` や `side_effects` などの列挙型フィールド
- ルート、機能、およびエンドポイントマニフェストからのネストされたオブジェクトおよびオブジェクト配列

左側のツリーには3つのルートがあります:

1. `Project Setup` — `project_profile.json` を含む編集可能なプロジェクトマニフェスト。
2. `Playground Sandbox` — 実際のプラグインバインディングのない `playground/` 配下の編集可能なサンドボックスマニフェスト。`Add playground to profile` を使用して活性化失敗をテストするか、`Tiny Tools` から `Setup Editor Playground` カタログ項目を有効にします。
3. `Reference Samples` — カタログプラグインごとにグループ化された読み取り専用のバンドル済み Tiny Tool マニフェスト、および UCM コアサンプル。`Copy to project` を使用して、参照マニフェストをプロジェクト設定に複製します。

ツールバーのアクション:

- `Save` / `Revert` — アクティブなマニフェストファイルを書き込みまたは破棄します。
- `Validate file` — 選択したファイルに対して `FCapabilityMeshSetupLoader::ValidateManifestFile` を実行します。
- `Reload Setup` — プロファイルまたはマニフェストの変更後にアクティブなメッシュをリロードします。
- `Open source folder` — 参照プラグインノードが選択されている場合、`editor/plugin_source_hints.json` からマッピングされた C++ プラグインパスを開きます。

フィールドタイピングルールは `editor/manifest_field_schema.json` にあります。

## Reload Setup

`Reload Setup` は `FCapabilityMeshService::ReloadSetup` を呼び出します。

以下のシーケンスを実行します:

1. 以前のレジストリとレポートをクリアします。
2. バンドルされた UCM セットアップ、有効化されたプラグインからのプラグインローカルセットアップルート、およびオプションのプロジェクトオーバーライドを検出します。
3. それらの `project_profile.json` ファイルを優先順位に従って統合します。
4. 機能、エンドポイント、スキーマ、ルール、ルート、変換、およびアダプターをロードします。
5. ロードされた定義を登録します。
6. セットアップおよびレジストリの診断を書き込みます。
7. 検出を実行します。
8. 検出および互換性レポートを書き込みます。

プロバイダー所有のマニフェストは、プロバイダープラグインの `Config/UnrealCapabilityMesh/` フォルダ内に残す必要があります。プロジェクトローカルのマニフェストは優先度が高く、意図的なオーバーライドやプロジェクト所有の複合ルート用です。プロバイダー定義をプロジェクトに複製すると、オーバーライドの警告が発生し、所有権が曖昧になる可能性があります。

オプションの Tiny Tool Execution Integration Bridge が有効になっている場合、その Editor モジュールは、投影された UCM ツールを登録および検出する前に `ReloadSetup` を呼び出します。UCM は、生成されるルート定義とすべてのポリシー判定の所有権を維持します。

## Discovered Capabilities

検出されたビューには、機能 ID、プロバイダー ID、相互運用モード、および利用可能性が一覧表示されます。利用可能性は、利用可能、利用不可、不安全、スキーマ不足、承認が必要、またはプラグインがロードされていない、のいずれかになります。

## Diagnostics

診断ビューには、セットアップ検証のエラーと警告、およびリロード/検出から返されたメッセージが表示されます。ルートやエンドポイントが表示されない場合は、まずここを確認してください。

## Routes

ルート ID を入力し、ドライランを実行します。UCM はルートステップを解決し、機能の利用可能性を確認し、副作用を集計し、ルールを評価し、ルートレポートを書き込みます。

ルート JSON 入力を入力し、ドライランにエラーがない場合はルートを実行します。UCM はまずルートを計画し、ポリシー違反やドライランが必要なルートをブロックしてから、ステップ順に各エンドポイントを呼び出します。承認が必要なルートは、そのルートに対して明示的に **実験的** とマークされたセルフ自動承認オーバーライドがアクティブでない限り、実行前にルート入力に `approval_granted: true` または `approval: "granted"` を含める必要があります。ステップの出力とルートの出力は `Saved/UnrealCapabilityMesh/route_execution_reports/` に書き込まれます。

### Route Catalog

Routes ページの **Route Catalog** には、セットアップマニフェストからロードされたすべてのルートがプラグインごとにグループ化された表形式で一覧表示されます:

| 列 | 内容 |
| --- | --- |
| Plugin / Route | 展開可能なプラグイングループと、ポリシー、ステップ、エンドポイント、副作用、およびソースマニフェストの詳細を含むルート行 |
| Approve all at own risk | **実験的** セルフ自動承認コントロール |

列ヘッダー:

- **Approve all at own risk** — アクティブプロファイル内の承認ゲート付きルート全体に対するグローバルスイッチ。有効にすると、すべての承認ゲート付きルートがオーバーライドを継承するため、ルートごとのチェックボックスは無効になります。

プラグイン行:

- 展開/折りたたみ矢印、プラグイン表示名、ルート数、およびそのプラグインが承認ゲート付きルートを所有している場合のプラグインごとの承認チェックボックス。

ルート行:

- 展開/折りたたみ矢印、ルート ID、およびドライラン計画からのルート詳細テキスト。
- 承認ゲート付きルート: ルートごとのチェックボックス（**Approve all** がアクティブな場合を除く）。
- 承認が不要なルート: 承認ゲートが適用されないことを説明するツールチップ付きの `n/a`。

カタログの上のオレンジ色の警告は、セルフ自動承認により広範なポリシーバイパスが有効化されることを示しています。一致する Deny ルール、ルートのアセット/プロジェクト変更チェック、承認要件、およびドライラン要件がスキップされます。そのため、有効化されたルートはこれらのセーフガードなしでエディターの状態を変更できます。

同じ設定は `project_profile.json` （`experimental_self_approval_all_routes`、`experimental_self_approved_route_ids`）に保持され、MCP 経由で `mesh_configure_experimental_self_approval` を使用して読み取りまたは変更が可能です。MCP 経由の有効化には `acknowledge_experimental_risk: true` が必要です。通常の運用ではセルフ自動承認を無効にしておいてください。

`Config Admin` ページでは、ルートランナーで標準的な config-admin ルート ID と JSON エンベロープを準備できます。これにより、MCP、エディターユーザー、および自動化が同じルートコントラクト上に維持されます。

## DataAsset および DataTable の管理

`UCapabilityMeshAssetAdminSubsystem` は、DataAsset/DataTable 管理のための JSON 呼び出し可能な操作を公開します:

- `ExportAdminSurfaceJson`: DataAsset または DataTable をポータブルな管理エンベロープにエクスポートし、`Saved/UnrealCapabilityMesh/asset_admin` 配下に書き込むことができます。
- `ImportAdminSurfaceJson`: 以前にエクスポートされたエンベロープを既存の DataAsset または DataTable にインポートします。
- `SyncAdminSurfaceJson`: DataAsset から DataTable の1行へ、または DataTable の1行から DataAsset へ編集可能フィールドをコピーします。

複合 DataTable（Composite DataTable）は安全なエクスポートソースです。複合 DataTable への直接書き込みはブロックされます。行を所有すべき具体的な子 DataTable をターゲットにしてください。

変更を伴う同期ルートのルート入力例:

```json
{
  "approval_granted": true,
  "request_json": "{\"source_object_path\":\"/Game/Config/DA_Settings.DA_Settings\",\"target_object_path\":\"/Game/Config/DT_Settings.DT_Settings\",\"mode\":\"data_asset_to_data_table\",\"row_name\":\"Default\"}"
}
```

## 設定の管理

`UCapabilityMeshConfigAdminSubsystem` は、許可リストに登録された設定ターゲットを公開します。これはプラグイン設定およびプロジェクトコンフィグファイル向けの標準的な MCP ルートです。

ターゲットは以下で宣言されます:

```text
Config/UnrealCapabilityMesh/config_targets/
```

一般的なルート:

- `capability_mesh.config_admin.list_targets.v1`
- `capability_mesh.config_admin.read_target.v1`
- `capability_mesh.config_admin.write_target.v1`

読み取り例:

```json
{
  "request_json": "{\"target_id\":\"example_plugin.settings\"}"
}
```

書き込み例:

```json
{
  "approval_granted": true,
  "request_json": "{\"target_id\":\"example_plugin.settings\",\"fields\":{\"bEnabled\":true}}"
}
```

アセットをバックに持つ設定オブジェクトなどのオブジェクトインスタンス ターゲットは、リクエスト JSON に `object_path` も必要とします。JSON ファイル ターゲットは `payload` または `payload_json` を受け入れます。

## MCP アクセス

`UCapabilityMeshMcpGatewaySubsystem` は、セットアップのリロード、機能の一覧表示、ルートのドライラン、ルートの実行、およびエンドポイントの呼び出しを JSON 呼び出し可能な関数として公開します。両方のプラグインがロードされている場合、Unified MCP Server は汎用 `mesh` プロバイダー経由でそのゲートウェイに接続します。

一般的な UMCP ツール名:

- `mesh_reload_setup`
- `mesh_list_capabilities`
- `mesh_list_routes`
- `mesh_configure_experimental_self_approval`
- `mesh_dry_run_route`
- `mesh_execute_route`
- `mesh_invoke_endpoint`

Unified MCP Server はまた、宣言されたルートを `mesh_route_<sanitized_route_id>_<hash>` という直接的な MCP ツールに平坦化します。これらのツールは分析用の `mode: "dry_run"` または実行用の `mode: "execute"` を受け入れます。`input` または `input_json` フィールドが指定されていない場合、残りの引数がルート入力オブジェクトになります。UCM はルート由来の `input_schema`、`output_schema`、および `tool_annotations` を `mesh_list_routes` を介してエクスポートします。UMCP はそれらを各 `mesh_route_*` ツールの MCP `inputSchema`、`outputSchema`、および注釈として公開します。`request_json` にバインドする一般的なルートの場合、UMCP は平坦化された引数をそのシリアル化されたリクエストフィールドにもミラーリングし、AI が理解しやすい名前付きパラメータでツールを呼び出せるようにします。

DataAsset/DataTable のインポート、同期、および設定書き込みには `mesh_execute_route` を使用し、ルートポリシーと承認チェックがアクティブのままになるようにしてください。**実験的** なテストまたは自己責任のワークフローにのみ `mesh_configure_experimental_self_approval` を使用してください。これにより、広範なポリシーバイパスをグローバルまたは選択したルート ID に対して有効化できます。現在 MCP に表示されている状態を確認するには `mesh_list_routes` を使用してください。グローバル実験フラグ、選択されたルートオーバーライド、および有効なルートごとのバイパス計画が報告されます。

## 主要な UCM 統合

アクティブなプロジェクトプロファイルは、Tiny Tool Development 製品をセットアップ宣言されたルートと接続します。この UCM パスを通常の統合モデルとして使用してください。Freebie Bridges は、UCM を持たないチームや、直接アダプターの例を求める開発者のみを対象としています。

- `uii_to_iis_context_pack.v1`: UII エビデンス -> IIS インポート/検索/コンテキストパックフロー（設定されている場合は LLM Store 埋め込みルート実行を含む）。
- `prs.build_asset_move_plan.v1`, `prs.preview_plan.v1`, `prs.apply_plan.v1`, `prs.rollback.v1`: UCM ルートポリシーと承認を通じた PRS 配置ワークフロー。
- `scd.migration_advice_from_handoff.v1`: UII ハンドオフコントラクト/エンベロープ -> UCM を通じた SmartContentDiet 助言的移行結果。
- `capability_mesh.asset_admin.export.v1`, `capability_mesh.asset_admin.import.v1`, `capability_mesh.asset_admin.sync.v1`: メッシュを通じた DataAsset/DataTable 管理。
- `capability_mesh.config_admin.list_targets.v1`, `capability_mesh.config_admin.read_target.v1`, `capability_mesh.config_admin.write_target.v1`: メッシュを通じた許可リスト登録済み設定およびコンフィグファイル管理。

プロジェクトまたはアセットの変更ルートは、そのルートに対して明示的に **実験的** とマークされたセルフ自動承認オーバーライドがアクティブでない限り、引き続いて明示的なルート承認が必要です。

## ルール

ルールは、ルートが許可されているか、承認が必要か、ドライランが必要か、あるいはブロックされているかを判定します。ルールは優先順位に従って順序付けられ、JSON で宣言されます。

## Adapter Editor

アダプターエディターは、`Config/UnrealCapabilityMesh/adapters` 配下にシンプルなアダプターマニフェストを書き込みます。これは、ハブに直接 C++ 依存関係を追加することなく、別のプラグインを UCM にマッピングするための出発点として意図されています。
