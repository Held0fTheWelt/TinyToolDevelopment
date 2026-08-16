# 管理された自動化

Asset Loader Studio はスタンドアロンファーストです。コンパイル時に Unreal Capability Mesh や Unified MCP サーバーには依存しません。オプションの UCM マニフェストは `Config/UnrealCapabilityMesh` の下に同梱されます。

ルート:

- `asset_loader_studio.tools.describe.v1`
- `asset_loader_studio.state.read.v1`
- `asset_loader_studio.load.submit.v1`
- `asset_loader_studio.jobs.status.v1`
- `asset_loader_studio.table.snapshot.v1`
- `asset_loader_studio.table.validate.v1`
- `asset_loader_studio.graph.build.v1`
- `asset_loader_studio.governance.snapshot.v1`
- `asset_loader_studio.governance.profile.save.v1`
- `asset_loader_studio.operation.preview.v1`
- `asset_loader_studio.operation.apply.v1`
- `asset_loader_studio.table.export.v1`
- `asset_loader_studio.audit.read.v1`
- `asset_loader_studio.audit.prune.v1`

権限プロファイル:

- `read_only` は読み取り、検査、検証、プレビュー、エクスポートを許可します。
- `guided_safe` は制限付きの段階的な編集と確認を許可します。
- `expert` は一括および破壊的な機能フラグを許可し、破壊的な作業には強力な承認を必要とします。

すべての自動化レスポンスは、`success`、`operation`、`summary`、`diagnostics`、`mutation_flags`、およびルート固有のペイロードを含む安定したエンベロープを使用します。

自動化はオプションです。UCM または MCP がインストールされていない場合は、エディターワークスペース、Blueprint ライブラリ、またはランタイムサブシステムを直接使用してください。ルートを呼び出す側は適用前にプレビューを行い、プレビュー ID または承認トークンをレビュー記録とともに保存してください。
