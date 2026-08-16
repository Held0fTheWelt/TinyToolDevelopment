<!-- doc-provenance: AKDB:plugins/UnrealCapabilityMesh/architecture.md; docs/architecture/plugins/UnrealCapabilityMesh/product-facts.yml; reconciled 2026-07-19 -->
# 常见问题

## UCM 是 AI 模型或 Agent 吗？

不是。UCM 是一个互操作性枢纽。它可以描述与 AI 相关的功能，但本身不包含模型、提示词、提供者或 Agent 运行时。

## UCM 会修改资产吗？

它本身不会。它仅加载清单、规划路由、调用已声明的端点并写入诊断。资产修改必须由提供者端点执行并由策略允许。

## 可以旁路批准吗？

仅能通过 Routes 页面上 Route Catalog 批准列中明确标注为 **实验性** 的自自动批准控件、`project_profile.json` 中的相应字段或 MCP 工具 `mesh_configure_experimental_self_approval` 进行旁路。这是一项大范围策略旁路：Deny 规则、路由资产/项目修改检查、批准和试运行要求都会被跳过。它仅适用于测试或自担风险的本地工作流；常规使用请保持 **Approve all at own risk** 和所有单路由开关处于关闭状态。

## 为什么使用清单而不是直接的 C++ 依赖？

清单允许项目连接工具，而无需在插件之间创建编译时依赖链。这保持了枢纽的中立性，且更易于打包。

## 报告写入在哪里？

报告写入在 `Saved/UnrealCapabilityMesh` 下。

## 项目清单存储在哪里？

项目清单存储在 `Config/UnrealCapabilityMesh` 下。

## UCM 可以集成商城中的第三方插件吗？

可以，只要这些插件公开了可通过清单或适配器描述的可调用函数、文件契约或模块化功能。

## UCM 是否捆绑了第三方代码？

插件中不包含捆绑的第三方源代码或运行时依赖。
