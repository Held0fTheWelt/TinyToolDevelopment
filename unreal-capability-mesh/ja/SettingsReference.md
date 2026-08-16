<!-- doc-provenance: AKDB:plugins/UnrealCapabilityMesh/architecture.md; docs/architecture/plugins/UnrealCapabilityMesh/product-facts.yml; reconciled 2026-07-19 -->
# マニフェストおよび設定リファレンス

UCM は `UDeveloperSettings` ページを公開しません。設定は、3つのセットアップルートクラスからロードされる JSON です:

1. UCM にバンドルされたデフォルトセットアップ。
2. 有効化されたプロバイダープラグインによって提供される `Config/UnrealCapabilityMesh` フォルダ。
3. オプションのプロジェクト `Config/UnrealCapabilityMesh` オーバーライド。

プロファイルはこの順序でマージされ、プロジェクトのオーバーライドが優先されます。最初の使用時や有効化されたプロバイダープラグインのルートにおいては、プロジェクトローカルのプロファイルは必須ではありません。プロジェクトが意図的にセットアップをオーバーライドする場合、または複合ルートを所有する場合にのみ作成してください。

## `project_profile.json`

| フィールド | 目的 |
| --- | --- |
| `schema_version` | `capability_mesh.project_profile` で始まる必要があります。 |
| `profile_id` | アクティブプロファイルの安定した ID。 |
| `display_name` | 人間が読めるプロファイル名。 |
| `enable_knowledge_store` | true の場合、呼び出し履歴を書き込みます。 |
| `experimental_self_approval_all_routes` | **実験的機能。自己責任で使用してください。** true の場合、設定されたルートは後述の広範なポリシーバイパスを使用します。通常の運用では false を保持してください。 |
| `experimental_self_approved_route_ids` | **実験的機能。自己責任で使用してください。** `experimental_self_approval_all_routes` が false の場合に広範なポリシーバイパスを使用するルート ID。 |
| `active_ruleset_id` | アクティブとして扱うルールセットの名前。 |
| `enabled_capability_manifests` | 機能マニフェストのパス。 |
| `enabled_endpoint_manifests` | エンドポイントマニフェストのパス。 |
| `enabled_schema_manifests` | スキーマ表マニフェストのパス。 |
| `enabled_rule_manifests` | ルールマニフェストのパス。 |
| `enabled_route_manifests` | ルートマニフェストのパス。 |
| `enabled_transform_manifests` | 変換マニフェストのパス。 |
| `enabled_adapter_manifests` | アダプターマニフェストのパス。 |
| `enabled_config_target_ids` | Config Admin ターゲットのオプションの許可リスト。存在しない場合はすべてのターゲットマニフェストがスキャンされます。 |
| `tiny_tool_development_plugins_enabled` | Tiny Tool Development カタログ用の UI 管理オプトインスイッチ。 |
| `reflection_metadata_keys` | リフレクションに公開された機能をスキャンするときに使用されるメタデータキー。 |
| `optional_scan_paths` | JSON マニフェストをスキャンする追加のフォルダまたはファイル。 |
| `setup_editor_playground_enabled` | Setup Editor プレイグラウンドカタログ項目用の UI 管理オプトインスイッチ。 |
| `setup_editor_show_cpp_source_hints` | Setup Editor 参照ツリーで C++ ソースヒントを表示するためのオプションのプロファイルフラグ。 |

相対マニフェストエントリは、プロファイルを所有するセットアップルートから解決され、必要に応じてプロジェクトおよびプロジェクトルートへのフォールバックが行われます。カスタマイズする場合は、プロジェクトがオーバーライドするプロファイルまたはマニフェストのみをコピーしてください。プロバイダー所有の定義をプラグインローカルに残すことで、ルートの所有権が明確になり、重複定義の警告を防ぐことができます。

## Setup Editor アセット

| パス | 目的 |
| --- | --- |
| `editor/manifest_field_schema.json` | JSON フィールドパスをエディターウィジェット型（`bool`、`enum`、`string_array` など）にマッピングします。 |
| `editor/plugin_source_hints.json` | 読み取り専用参照ブラウジング用に、カタログの `item_id` 値を C++ プラグインソースフォルダにマッピングします。 |
| `playground/` | 実際のプラグインバインディングのない編集可能なサンドボックスマニフェスト。 |
| `tool_catalogs/setup_editor_playground.json` | プレイグラウンドマニフェストを `project_profile.json` に追加するカタログ項目。 |

## 機能マニフェスト (Capability Manifest)

機能は、プロバイダーが実行できることを宣言します。各機能には、ID、タイトル、カテゴリ、副作用、入力ポート、出力ポート、およびエンドポイント ID が含まれます。

## エンドポイントマニフェスト (Endpoint Manifest)

エンドポイントは、機能がどのように呼び出されるかを宣言します。重要なフィールド:

- `endpoint_id`
- `invocation_mode`
- `target`
- `parameters`
- `availability`

サポートされている呼び出しモードには、リフレクション関数、ファイルコントラクト、モジュール式機能プロバイダー、Python ブリッジ、コマンドレット、および外部プロセス宣言が含まれます。リフレクション、ファイルコントラクト、および UCM エンドポイントプロバイダーモジュール機能は直接実行されます。Python ブリッジ、コマンドレット、および外部プロセス宣言は、汎用呼び出し元が実装されるまで検出のみとなります。

## スキーマ表マニフェスト (Schema Manifest)

スキーマは、入力ポートおよび出力ポートの期待される形状を記述します。UCM はスキーマ ID を使用して互換性をチェックします。

## ルールマニフェスト (Rule Manifest)

ルールは、ルートが許可されているかどうかを判定します。一般的な副作用:

- `read_only`
- `saved_folder_write`
- `project_config_write`
- `asset_mutation`
- `project_mutation`
- `network`
- `ai_completion`

## ルートマニフェスト (Route Manifest)

ルートは順序付けられたステップを定義します。各ステップは機能 ID を参照し、入出力バインディングを宣言します。

変更を伴うルートは、操作が意図的である場合にのみ `allow_asset_mutation` または `allow_project_mutation` を設定する必要があります。実行側は通常、実行時に承認を要求します。後述の **実験的** セルフ自動承認オーバーライドが意図的にアクティブでない限り、ルート入力で `approval_granted: true`、`approvalGranted: true`、または `approval: "granted"` を指定してください。

### 実験的セルフ自動承認

`experimental_self_approval_all_routes` および `experimental_self_approved_route_ids` は、テストおよびローカルの自己責任ワークフローのための明示的な実験的エスケープハッチです。有効にすると、UCM はルート計画および実行を通じて `bExperimentalPolicyBypass=true` を渡します。`allow=false` の一致するルールはルートをブロックしなくなり、ルールレベルの承認要件とドライラン要件は無視され、ルートレベルのアセット/プロジェクト変更チェックはスキップされ、最終計画では承認要件とドライラン要件の両方が解除されます。

通常の運用および本番ワークフローでは、両方の設定をオフにしておいてください。エディターの Route Catalog はこれらのスイッチを **実験的** とラベル付けし、バイパス範囲全体を明記します。MCP ホストは `mesh_configure_experimental_self_approval` を介して同じ設定を読み取りまたは変更できます。MCP 経由での有効化には `acknowledge_experimental_risk: true` が必要です。

## 変換マニフェスト (Transform Manifest)

変換は、ソース JSON をターゲット JSON にマッピングします。これらは、ある機能からの出力を別の機能の入力に適合させるために使用されます。

## アダプターマニフェスト (Adapter Manifest)

アダプターは、ハブに直接的な C++ 依存関係を追加することなく、サードパーティ製プラグイン機能を UCM にマッピングします。

## アセット管理セットアップ

UCM 自身の `Config/UnrealCapabilityMesh` 配下にバンドルされたセットアップは、DataAsset/DataTable 管理機能を宣言します:

- `capability_mesh.asset_admin.export`
- `capability_mesh.asset_admin.import`
- `capability_mesh.asset_admin.sync`

3つすべてが `reflection_subsystem_function` エンドポイントを介して `UCapabilityMeshAssetAdminSubsystem` を呼び出します。MCP ホストは、プロジェクト固有のブリッジコードを呼び出すのではなく、これらの宣言を経由してルーティングする必要があります。

## 設定ターゲットマニフェスト

設定管理ターゲットは、以下においてルートマニフェストとは別に許可リストに登録されます:

```text
Config/UnrealCapabilityMesh/config_targets/*.json
```

ターゲットマニフェストの使用例:

```json
{
  "schema_version": "capability_mesh.config_target_manifest.v1",
  "targets": [
    {
      "target_id": "example_plugin.settings",
      "display_name": "Example Plugin Settings",
      "description": "Explains what the target controls and when it should be edited.",
      "kind": "uobject_config",
      "class_path": "/Script/ExamplePlugin.ExamplePluginSettings",
      "required_plugin_names": ["ExamplePlugin"]
    }
  ]
}
```

サポートされている `kind` の値:

- `uobject_config`: クラスデフォルトオブジェクト（CDO）の設定プロパティを読み書きし、コンフィグを保存します。
- `uobject_instance`: 許可リストに登録されたオブジェクトクラスの編集可能フィールドを読み書きします。リクエストには `object_path` を含める必要があります。
- `json_file`: 許可されたベースディレクトリ配下の宣言された1つの JSON ファイルを読み書きします。

各ターゲットには、空でない `description` を含める必要があります。ユーザーはターゲットを読み書きする前にコンテキストを必要とするため、Config Admin は欠落している説明をマニフェストの警告として表面化させます。

標準ルートは `capability_mesh.config_admin.list_targets.v1`、`capability_mesh.config_admin.read_target.v1`、および `capability_mesh.config_admin.write_target.v1` です。書き込みルートは `project_config_write` および `asset_mutation` を宣言するため、コンフィグファイル、コンフィグオブジェクト、DataAsset、および編集可能なオブジェクトインスタンスはすべて同じ承認およびドライランパスを通過します。

## ツールカタログマニフェスト

ツールカタログの場所:

```text
Config/UnrealCapabilityMesh/tool_catalogs/*.json
```

これらは、セットアップエントリを UI で切り替え可能なパッケージにグループ化します。パッケージは、機能、エンドポイント、スキーマ、ルール、ルート、変換、アダプターマニフェストのパス、および設定ターゲット ID を宣言できます。UI はそれらのエントリを `project_profile.json` から削除することでパッケージを非アクティブ化します。マニフェストファイル自体は削除しません。

カタログパッケージは、所有権の境界が許す限り小規模に保つ必要があります。プラグインパッケージは、そのプラグイン自身の機能、エンドポイント、スキーマ、および設定ターゲットのみを追加する必要があります。プラグイン間のワークフローは、すでに有効化されている構成要素を参照する個別のルートパッケージにする必要があります。これにより、すべての Tiny Tool Development プラグインを必要とすることなく、IIS のみ、LLM Store のみ、UII+IIS、および IIS+LLM Store のセットアップを有効に維持できます。
