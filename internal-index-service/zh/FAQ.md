<!-- doc-provenance: SAD architecture.md sections 1,2,7,8; facts product-facts.yml; reconciled 2026-07-16 -->
# 常见问题 (FAQ)

## IIS 会修改我的项目吗？

不会。IIS 纯粹用于检索（retrieval-only）。它会写入生成的索引/报告文件，但不会将源码、Blueprint、资产或配置变更作为代理操作应用。

## IIS 包含 MCP 服务器吗？

在当前版本中不包含。MCP 传输由 Unified MCP Server 提供。IIS 代理操作通过项目的 Capability Mesh 路由公开，而不是通过 IIS 自有的 MCP 服务器或桥接插件。

## 数据去向何处？

默认情况下：

```text
Saved/InternalIndexService
```

您可以在项目设置中覆盖根目录。

## IIS 会将项目数据发送到云端吗？

只有当 LLM Store 中的嵌入执行器路由使用云提供程序时才会。搜索、目录、导入和报告文件均位于本地。

## 为什么没有向量结果？

向量搜索需要嵌入。在通过 LLM Store 配置嵌入路由后，构建并执行嵌入任务。

## hnswlib 是用来做什么的？

hnswlib 为可选的 `hnsw` 近似最近邻向量后端提供支持。它作为源码附带在 `Source/ThirdParty/hnswlib` 下。

## 为什么我的 MCP 工具列表中缺失 IIS 工具？

检查是否启用了以下插件：

- Internal Index Service
- Unified MCP Server
- Unreal Capability Mesh

确保项目的 Capability Mesh 配置文件列出了 IIS 代理路由（`iis.agent.*.v1`），然后写入/刷新 IIS 代理契约并调用 `mesh_reload_setup` 或刷新 MCP 客户端。

## 我可以从 C++ 调用 IIS 吗？

可以。使用 `FInternalIndexServiceModule::Get().GetService()` 和 `IInternalIndexService` 接口。

## 我可以从 Blueprint 调用 IIS 吗？

IIS 主要公开编辑器 UI 和 C++ 服务。面向代理和集成的路径均基于 C++/JSON。
