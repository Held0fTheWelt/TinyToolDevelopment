<!-- doc-provenance: AKDB:plugins/UnrealCapabilityMesh/architecture.md; docs/architecture/plugins/UnrealCapabilityMesh/product-facts.yml; reconciled 2026-07-19 -->
# 清单与设置参考

UCM 没有在 `UDeveloperSettings` 中暴露设置页面。配置是通过从三个设置根类加载的 JSON 完成的：

1. UCM 随附的默认设置。
2. 已启用的提供者插件随附的 `Config/UnrealCapabilityMesh` 文件夹。
3. 可选的项目 `Config/UnrealCapabilityMesh` 重写。

配置文件按此顺序合并，项目重写具有最高优先级。在首次使用或使用已启用的提供者插件路由时，不需要项目本地配置文件。仅当项目明确重写设置或拥有复合路由时才需要创建一个。

## `project_profile.json`

| 字段 | 目的 |
| --- | --- |
| `schema_version` | 必须以 `capability_mesh.project_profile` 开头。 |
| `profile_id` | 当前活跃配置文件的稳定 ID。 |
| `display_name` | 可读的配置文件名称。 |
| `enable_knowledge_store` | 为 true 时写入调用历史。 |
| `experimental_self_approval_all_routes` | **实验性，自担风险。** 为 true 时，配置的路由将使用下文所述的大范围策略旁路。常规使用请保持为 false。 |
| `experimental_self_approved_route_ids` | **实验性，自担风险。** 当 `experimental_self_approval_all_routes` 为 false 时使用大范围策略旁路的路由 ID。 |
| `active_ruleset_id` | 视为活跃的规则集名称。 |
| `enabled_capability_manifests` | 功能清单路径。 |
| `enabled_endpoint_manifests` | 端点清单路径。 |
| `enabled_schema_manifests` | 架构清单路径。 |
| `enabled_rule_manifests` | 规则清单路径。 |
| `enabled_route_manifests` | 路由清单路径。 |
| `enabled_transform_manifests` | 转换清单路径。 |
| `enabled_adapter_manifests` | 适配器清单路径。 |
| `enabled_config_target_ids` | Config Admin 目标的可选白名单。如果不存在，将扫描所有目标清单。 |
| `tiny_tool_development_plugins_enabled` | UI 管理的 Tiny Tool Development 目录选择开关。 |
| `reflection_metadata_keys` | 扫描通过反射暴露的功能时使用的元数据键。 |
| `optional_scan_paths` | 扫描 JSON 清单的额外文件夹或文件。 |
| `setup_editor_playground_enabled` | UI 管理的 Setup Editor 沙盒目录项选择开关。 |
| `setup_editor_show_cpp_source_hints` | 可选的配置文件标志，用于在 Setup Editor 参考树中显示 C++ 源码提示。 |

相对清单条目将从拥有该配置文件的设置根进行解析，并在适当时备用至项目和项目根。如需自定义，请仅复制项目打算重写的配置文件或清单。将提供者拥有的定义保留在插件本地，可以保持路由所有权清晰并避免重复定义警告。

## Setup Editor 资产

| 路径 | 目的 |
| --- | --- |
| `editor/manifest_field_schema.json` | 将 JSON 字段路径映射到编辑器控件类型（`bool`、`enum`、`string_array` 等）。 |
| `editor/plugin_source_hints.json` | 将目录 `item_id` 值映射到 C++ 插件源码文件夹，以进行只读参考浏览。 |
| `playground/` | 无真实插件绑定的可编辑沙盒清单。 |
| `tool_catalogs/setup_editor_playground.json` | 将沙盒清单添加到 `project_profile.json` 的目录项。 |

## 功能清单 (Capability Manifest)

功能声明提供者能做什么。每个功能都有 ID、标题、类别、副作用、输入端口、输出端口和端点 ID。

## 端点清单 (Endpoint Manifest)

端点声明如何调用功能。重要字段：

- `endpoint_id`
- `invocation_mode`
- `target`
- `parameters`
- `availability`

支持的调用模式包括反射函数、文件契约、模块化功能提供者、Python bridge、commandlet 和外部进程声明。反射、文件契约和 UCM 端点提供者模块化功能可直接执行；Python bridge、commandlet 和外部进程声明在实现其通用调用器前仅限探测。

## 架构清单 (Schema Manifest)

架构描述输入和输出端口的预期形状。UCM 使用架构 ID 检查兼容性。

## 规则清单 (Rule Manifest)

规则决定路由是否允许。常见副作用：

- `read_only`
- `saved_folder_write`
- `project_config_write`
- `asset_mutation`
- `project_mutation`
- `network`
- `ai_completion`

## 路由清单 (Route Manifest)

路由定义有序步骤。每个步骤引用一个功能 ID 并声明输入/输出绑定。

修改路由应仅在操作明确时设置 `allow_asset_mutation` 或 `allow_project_mutation`。执行器通常需要在运行时获得批准；除非下文所述的 **实验性** 自自动批准重写明确处于活跃状态，否则请在路由输入中提供 `approval_granted: true`、`approvalGranted: true` 或 `approval: "granted"`。

### 实验性自自动批准

`experimental_self_approval_all_routes` 和 `experimental_self_approved_route_ids` 是明确用于测试和本地自担风险工作流的实验性逃生出口。启用时，UCM 会在路由规划和执行过程中传递 `bExperimentalPolicyBypass=true`。匹配的 `allow=false` 规则将不再阻止路由，规则级别的批准与试运行要求将被忽略，路由级别的资产/项目修改检查将被跳过，且最终计划会清除批准与试运行要求。

对于日常和生产工作流，请保持这两项设置关闭。编辑器的 Route Catalog 将这些开关标注为 **实验性** 并说明了完整的旁路范围。MCP 主机可以通过 `mesh_configure_experimental_self_approval` 读取或更改相同设置；通过 MCP 启用需要 `acknowledge_experimental_risk: true`。

## 转换清单 (Transform Manifest)

转换将源 JSON 映射到目标 JSON。它们用于将一个功能的输出转换为另一个功能的输入。

## 适配器清单 (Adapter Manifest)

适配器将第三方插件函数映射到 UCM 中，而无需为枢纽添加直接 C++ 依赖。

## 资产管理设置

UCM 自身 `Config/UnrealCapabilityMesh` 下内建的设置声明了 DataAsset/DataTable 管理功能：

- `capability_mesh.asset_admin.export`
- `capability_mesh.asset_admin.import`
- `capability_mesh.asset_admin.sync`

三者均通过 `reflection_subsystem_function` 端点调用 `UCapabilityMeshAssetAdminSubsystem`。MCP 主机应通过这些声明进行路由，而不是调用特定于项目的 bridge 代码。

## 配置目标清单

配置管理目标在以下位置独立于路由清单列入白名单：

```text
Config/UnrealCapabilityMesh/config_targets/*.json
```

目标清单使用：

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

支持的 `kind` 值：

- `uobject_config`：读取并写入类默认对象（CDO）上的配置属性，然后保存配置。
- `uobject_instance`：读取并写入白名单对象类上的可编辑字段。请求必须包含 `object_path`。
- `json_file`：读取并写入允许的基础目录下的一个已声明 JSON 文件。

每个目标都应包含非空的 `description`；Config Admin 会将缺失描述标为清单警告，因为用户在读取或写入目标前需要了解上下文。

标准路由为 `capability_mesh.config_admin.list_targets.v1`、`capability_mesh.config_admin.read_target.v1` 和 `capability_mesh.config_admin.write_target.v1`。写入路由声明了 `project_config_write` 和 `asset_mutation`，因此配置文件、配置对象、DataAsset 和可编辑对象实例都会经过相同的批准和试运行路径。

## 工具目录清单

工具目录位于：

```text
Config/UnrealCapabilityMesh/tool_catalogs/*.json
```

它们将设置条目分组为可在 UI 中切换的包。一个包可以声明功能、端点、架构、规则、路由、转换、适配器清单路径以及配置目标 ID。UI 通过从 `project_profile.json` 中移除这些条目来停用包；它不会删除清单文件。

目录包应保持在所有权边界允许的最小范围内。插件包应仅添加该插件自身的功能、端点、架构和配置目标。跨插件工作流应为引用已启用组件的独立路由包。这可以在不需要每个 Tiny Tool Development 插件的情况下，保持仅 IIS、仅 LLM Store、UII+IIS 和 IIS+LLM Store 设置有效。
