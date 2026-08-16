<!-- doc-provenance: AKDB:plugins/UnrealCapabilityMesh/architecture.md; docs/architecture/plugins/UnrealCapabilityMesh/product-facts.yml; reconciled 2026-07-19 -->
# Unreal Capability Mesh 文档

本文件夹介绍了面向 Unreal Engine 5.4+ 的 Unreal Capability Mesh 插件、项目设置、集成以及源代码阅读指南。

Fab 产品页面：https://www.fab.com/listings/fd186d26-cdcf-4c4f-93d4-50e437b7673e

## 从这里开始

| 文档 | 目的 |
| --- | --- |
| [BUYER_GUIDE.md](BUYER_GUIDE.md) | 产品范围、包含模块、UCM 的功能与非功能。 |
| [QUICKSTART.md](QUICKSTART.md) | 从清单到生成报告的最小设置流程。 |
| [UserManual.md](UserManual.md) | 控制面板工作流和常规操作规程。 |
| [TechnicalOverview.md](TechnicalOverview.md) | 架构、数据流、存储位置和诊断。 |
| [CodeDocumentation.md](CodeDocumentation.md) | 按模块和类划分的 C++ 源码阅读指南。 |
| [SettingsReference.md](SettingsReference.md) | 清单文件夹布局、项目配置文件字段、策略字段、输出路径。 |
| [INTEGRATION.md](INTEGRATION.md) | 如何通过清单或适配器连接另一个插件。 |
| [TROUBLESHOOTING.md](TROUBLESHOOTING.md) | 常见验证、探测、路由和调用问题。 |
| [FAQ.md](FAQ.md) | 面向买家和审查者的简短解答。 |
| [ReleaseChecklist.md](ReleaseChecklist.md) | Fab 合规与打包检查清单。 |
| [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md) | 第三方软件声明说明。 |

## 核心概念

UCM 是一个中立枢纽。它在 C++ 代码中不了解特定的合作插件。UCM 本身、已启用的提供者插件以及项目均可以 JSON 形式描述功能（capabilities）、端点、架构、规则、路由、转换和适配器。加载器按优先级顺序合并这些设置根、构建注册表、评估安全规则并写入报告。

当前项目设置将 UCM 作为 Tiny Tool Development 产品之间的主要集成层。特定于产品行为保留在所属插件中作为可 JSON 调用的端点或文件契约；UCM 仅加载连接它们的设置。Freebie Bridges 是面向无 UCM 团队的可选备用/参考插件，而非默认连接模型。

## 重要路径

```text
<EnabledPlugin>/Config/UnrealCapabilityMesh/  ← 提供者拥有的只读清单
Config/UnrealCapabilityMesh/                   ← 可选的项目自有重写与复合路由
Saved/UnrealCapabilityMesh/                    ← 生成的报告和路由输出
```

请勿仅为了公开提供者的路由而将其清单复制到项目中。请启用提供者插件并重新加载设置。仅当项目有意更改配置文件字段或拥有复合路由时，才创建项目重写。
