# 受控自动化

Asset Loader Studio 以独立部署为首要设计目标。它在编译时不依赖于 Unreal Capability Mesh 或 Unified MCP 服务器。可选的 UCM 清单文件位于 `Config/UnrealCapabilityMesh` 目录下。

路由：

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

权限配置文件：

- `read_only` 允许读取、检查、验证、预览和导出。
- `guided_safe` 允许在限制和确认机制下进行分阶段编辑。
- `expert` 允许批量操作和具有破坏性的功能标志，并对破坏性操作要求严格的审批。

所有自动化响应均使用稳定的信封格式，包含 `success`、`operation`、`summary`、`diagnostics`、`mutation_flags` 以及路由特定的负载数据。

自动化功能是可选的。如果未安装 UCM 或 MCP，请直接使用编辑器工作区、Blueprint 库或运行时子系统。路由调用者应在应用前进行预览，并将预览 ID 或审批令牌与其审查记录一同存储。
