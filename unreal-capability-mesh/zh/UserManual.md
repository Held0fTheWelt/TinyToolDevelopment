<!-- doc-provenance: AKDB:plugins/UnrealCapabilityMesh/architecture.md; docs/architecture/plugins/UnrealCapabilityMesh/product-facts.yml; reconciled 2026-07-19 -->
# 用户手册

## 控制面板

从以下位置打开面板：

```text
Tools -> Unreal Capability Mesh
```

面板是面向基于清单互操作性的技术操作视图。它现在使用状态横幅和专项页面，而不是将所有工具堆叠在一个长视图中。

页面：

- `Overview`：活跃配置文件、清单计数、可用性计数、设置流程和 MCP 契约。
- `Capabilities`：已加载的功能 ID、端点、副作用、可用性、警告和源清单。
- `Routes`：路由目录以及试运行和执行输入/输出。
- `Governance`：活跃的副作用词汇表和规则判定。
- `Tiny Tools`：面向 Tiny Tool Development 内容的设置包开关。
- `Setup Editor`：感知类型的 JSON 编辑器，用于项目设置清单、只读参考示例和非约束性沙盒（playground）。
- `Config Admin`：白名单配置目标和路由预设，用于列表/读取/写入操作。
- `Diagnostics`：设置验证、探测和重新加载消息。
- `Adapter`：启动清单编写器，用于在无需 bridge 依赖的情况下添加设置声明的功能。

## Tiny Tools

`Tiny Tools` 页面由以下位置的目录清单驱动：

```text
Config/UnrealCapabilityMesh/tool_catalogs/
```

第一个开关决定项目是否应使用 Tiny Tool Development 设置内容。当关闭时，所有属于目录的设置条目都会从活跃配置文件中移除。然后，单独的工具开关会添加或禁用目录声明的包条目：

- 功能清单
- 端点清单
- 架构清单
- 规则清单
- 路由清单
- 转换清单
- 适配器清单
- 配置目标 ID

这是一种停用模型，而非删除文件。清单文件仍保留在项目中，日后可以重新启用。

Tiny Tool 包按照所有权进行了故意拆分。IIS、LLM Store 和 UII 可以独立启用。跨插件工作流是单独的路由开关，因此项目可以在不拥有整个堆栈的情况下单独使用 IIS、单独使用 LLM Store、使用 UII+IIS 或 IIS+LLM Store。

配置文件字段 `enabled_config_target_ids` 限制了 Config Admin 可见的配置目标。如果该字段不存在，Config Admin 将保留旧行为并扫描每个目标清单。

## Setup Editor

`Setup Editor` 页面编辑 `Config/UnrealCapabilityMesh` 下的项目本地清单，并提供类型感知字段：

- 用于策略和配置文件开关的布尔值
- 用于 `enabled_*_manifests` 的字符串数组
- 枚举字段（如 `invocation_mode` 和 `side_effects`）
- 来自路由、功能和端点清单的嵌套对象和对象数组

左侧树包含三个根：

1. `Project Setup` — 可编辑的项目清单，包括 `project_profile.json`。
2. `Playground Sandbox` — `playground/` 下可编辑的沙盒清单，无真实插件绑定。使用 `Add playground to profile` 测试激活失败，或从 `Tiny Tools` 启用 `Setup Editor Playground` 目录项。
3. `Reference Samples` — 按目录插件分组的只读内建 Tiny Tool 清单，以及 UCM 核心示例。使用 `Copy to project` 将参考清单复制到项目配置中。

工具栏操作：

- `Save` / `Revert` — 写入或丢弃当前活跃的清单文件。
- `Validate file` — 对选定文件运行 `FCapabilityMeshSetupLoader::ValidateManifestFile`。
- `Reload Setup` — 在配置文件或清单更改后重新加载活跃网格。
- `Open source folder` — 当选中参考插件节点时，打开来自 `editor/plugin_source_hints.json` 的映射 C++ 插件路径。

字段类型规则位于 `editor/manifest_field_schema.json` 中。

## Reload Setup

`Reload Setup` 调用 `FCapabilityMeshService::ReloadSetup`。

它按顺序执行以下操作：

1. 清除先前的注册表和报告。
2. 发现内建的 UCM 设置、来自已启用插件的插件本地设置根以及可选的项目重写。
3. 按优先级顺序合并它们的 `project_profile.json` 文件。
4. 加载功能、端点、架构、规则、路由、转换和适配器。
5. 注册已加载的定义。
6. 写入设置与注册表诊断。
7. 运行探测。
8. 写入探测与兼容性报告。

提供者拥有的清单应保留在提供者插件的 `Config/UnrealCapabilityMesh/` 文件夹下。项目本地清单具有更高优先级，用于明确的重写或项目自有的复合路由。将提供者定义复制到项目中可能会产生重写警告并模糊所有权。

当启用可选的 Tiny Tool Execution Integration Bridge 时，其 Editor 模块会在注册和探测投影的 UCM 工具之前调用 `ReloadSetup`。UCM 仍拥有生成的路由定义和每个策略决定。

## Discovered Capabilities

已发现视图列出了功能 ID、提供者 ID、互操作模式和可用性。可用性可以是可用、不可用、不安全、缺少架构、需要批准或插件未加载。

## Diagnostics

诊断视图显示设置验证错误与警告，以及重新加载/探测返回的消息。当路由或端点未出现时，请首先查看此视图。

## Routes

输入路由 ID 并运行试运行（dry run）。UCM 会解析路由步骤、检查功能可用性、汇总副作用、评估规则并写入路由报告。

在试运行无误后，输入路由 JSON 输入并执行路由。UCM 会首先规划路由，阻止策略违规和需要试运行的路由，然后按步骤顺序调用每个端点。需要批准的路由必须在执行前在路由输入中包含 `approval_granted: true` 或 `approval: "granted"`，除非该路由显式标记为 **实验性** 的自自动批准重写处于活跃状态。步骤输出和路由输出将写入 `Saved/UnrealCapabilityMesh/route_execution_reports/`。

### Route Catalog

Routes 页面上的 **Route Catalog** 在按插件分组的表格中列出了来自设置清单的每个已加载路由：

| 列 | 内容 |
| --- | --- |
| Plugin / Route | 可展开的插件组和路由行，包含策略、步骤、端点、副作用和源清单详细信息 |
| Approve all at own risk | **实验性** 自自动批准控件 |

列标题：

- **Approve all at own risk** — 当前活跃配置文件中每个需要批准路由的总开关。启用时，每个路由的复选框将被禁用，因为所有需要批准的路由都会继承该重写。

插件行：

- 展开/折叠箭头、插件显示名称、路由数量，以及在该插件拥有需要批准的路由时的单插件批准复选框。

路由行：

- 展开/折叠箭头、路由 ID，以及来自试运行计划的路由详细信息文本。
- 需要批准的路由：单路由复选框（除非 **Approve all** 处于活跃状态）。
- 无需批准的路由：显示 `n/a`，并带有悬停提示解释不适用批准门控。

目录上方的橙色警告指出，自自动批准激活了大范围的策略旁路。匹配的 Deny 规则、路由资产/项目修改检查、批准要求和试运行要求将被跳过；因此启用的路由可以在没有这些保护措施的情况下更改编辑器状态。

相同的设置持久化在 `project_profile.json` 中（`experimental_self_approval_all_routes`、`experimental_self_approved_route_ids`），并可以通过 MCP 使用 `mesh_configure_experimental_self_approval` 读取或更改；通过 MCP 启用需要 `acknowledge_experimental_risk: true`。对于常规生产用途，请保持自自动批准关闭。

`Config Admin` 页面可以在路由运行器中准备标准的 config-admin 路由 ID 和 JSON 包。这使 MCP、编辑器用户和自动化保持在相同的路由契约上。

## DataAsset 和 DataTable 管理

`UCapabilityMeshAssetAdminSubsystem` 公开了可 JSON 调用的操作，用于 DataAsset/DataTable 管理：

- `ExportAdminSurfaceJson`：将 DataAsset 或 DataTable 导出为便携式管理包，并可将其写入 `Saved/UnrealCapabilityMesh/asset_admin` 下。
- `ImportAdminSurfaceJson`：将先前导出的包导入到现有 DataAsset 或 DataTable 中。
- `SyncAdminSurfaceJson`：将可编辑字段从 DataAsset 复制到 DataTable 行，或从 DataTable 行复制回 DataAsset。

复合 DataTable（Composite DataTable）是安全的导出源。直接写入复合 DataTable 将被阻止；请针对应该拥有该行的具体子 DataTable。

修改同步路由的路由输入示例：

```json
{
  "approval_granted": true,
  "request_json": "{\"source_object_path\":\"/Game/Config/DA_Settings.DA_Settings\",\"target_object_path\":\"/Game/Config/DT_Settings.DT_Settings\",\"mode\":\"data_asset_to_data_table\",\"row_name\":\"Default\"}"
}
```

## 配置管理

`UCapabilityMeshConfigAdminSubsystem` 公开了白名单配置目标。这是插件设置和项目配置文件标准的 MCP 路由。

目标声明于：

```text
Config/UnrealCapabilityMesh/config_targets/
```

常用路由：

- `capability_mesh.config_admin.list_targets.v1`
- `capability_mesh.config_admin.read_target.v1`
- `capability_mesh.config_admin.write_target.v1`

读取示例：

```json
{
  "request_json": "{\"target_id\":\"example_plugin.settings\"}"
}
```

写入示例：

```json
{
  "approval_granted": true,
  "request_json": "{\"target_id\":\"example_plugin.settings\",\"fields\":{\"bEnabled\":true}}"
}
```

对象实例目标（例如由资产支持的配置对象）还需要在请求 JSON 中提供 `object_path`。JSON 文件目标接受 `payload` 或 `payload_json`。

## MCP 访问

`UCapabilityMeshMcpGatewaySubsystem` 将设置重新加载、功能列表、路由试运行、路由执行和端点调用公开为可 JSON 调用的函数。当两个插件都已加载时，Unified MCP Server 会通过通用 `mesh` 提供者连接到该网关。

常用的 UMCP 工具名称：

- `mesh_reload_setup`
- `mesh_list_capabilities`
- `mesh_list_routes`
- `mesh_configure_experimental_self_approval`
- `mesh_dry_run_route`
- `mesh_execute_route`
- `mesh_invoke_endpoint`

Unified MCP Server 还会将声明的路由扁平化为名为 `mesh_route_<sanitized_route_id>_<hash>` 的直接 MCP 工具。这些工具接受用于分析的 `mode: "dry_run"` 或用于执行的 `mode: "execute"`。如果未提供 `input` 或 `input_json` 字段，则其余参数将成为路由输入对象。UCM 通过 `mesh_list_routes` 导出路由派生的 `input_schema`、`output_schema` 和 `tool_annotations`；UMCP 将这些发布为每个 `mesh_route_*` 工具的 MCP `inputSchema`、`outputSchema` 和注解。对于绑定到 `request_json` 的常用路由，UMCP 还会将扁平化参数镜像到该序列化请求字段中，以便 AI 可以使用易懂的命名参数调用工具。

对 DataAsset/DataTable 导入、同步和配置写入使用 `mesh_execute_route`，以便路由策略和批准检查保持活跃。仅对 **实验性** 测试或自担风险的工作流使用 `mesh_configure_experimental_self_approval`；它可以在全局或针对选定的路由 ID 启用大范围策略旁路。使用 `mesh_list_routes` 验证当前 MCP 可见状态；它报告全局实验性标志、选定的路由重写以及有效的单路由旁路计划。

## 主要 UCM 集成

活跃的项目配置文件通过设置声明的路由连接 Tiny Tool Development 产品。将此 UCM 路径作为常规集成模型。Freebie Bridges 仅适用于没有 UCM 的团队或需要直接适配器示例的开发者。

- `uii_to_iis_context_pack.v1`：UII 证据 -> IIS 导入/搜索/上下文包流程，并在配置时执行 LLM Store 嵌入路由。
- `prs.build_asset_move_plan.v1`, `prs.preview_plan.v1`, `prs.apply_plan.v1`, `prs.rollback.v1`：通过 UCM 路由策略和批准执行 PRS 放置工作流。
- `scd.migration_advice_from_handoff.v1`：UII 移交契约/包 -> 通过 UCM 的 SmartContentDiet 咨询迁移结论。
- `capability_mesh.asset_admin.export.v1`, `capability_mesh.asset_admin.import.v1`, `capability_mesh.asset_admin.sync.v1`：通过网格进行的 DataAsset/DataTable 管理。
- `capability_mesh.config_admin.list_targets.v1`, `capability_mesh.config_admin.read_target.v1`, `capability_mesh.config_admin.write_target.v1`：通过网格进行白名单设置与配置文件管理。

项目或资产修改路由仍需要显式的路由批准，除非该路由显式标记为 **实验性** 的自自动批准重写处于活跃状态。

## 规则

规则决定路由是允许、需要批准、需要试运行还是被阻止。规则按优先级排序，并以 JSON 声明。

## 适配器编辑器

适配器编辑器在 `Config/UnrealCapabilityMesh/adapters` 下写入简易适配器清单。它的目的是作为将另一个插件映射到 UCM 的起点，而无需为枢纽添加直接 C++ 依赖。
