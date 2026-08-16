<!-- doc-provenance: SAD architecture.md sections 6,8,10,11; facts product-facts.yml; reconciled 2026-07-16 -->
# 故障排除

## UE 5.6 编译失败并出现引擎头文件错误

确保 IIS 模块使用 C++20 编译。UE 5.6 引擎头文件使用 C++20 语法。IIS 的 `.Build.cs` 文件应使用：

```csharp
CppStandard = CppStandardVersion.Cpp20;
```

## 搜索未返回任何结果

检查：

- 是否已导入准备好的 chunk
- 是否已重建目录
- 查询文本是否非空
- 生命状态是否为激活
- 索引根目录是否指向预期的项目文件夹

## 向量搜索未返回任何结果

检查：

- 是否构建了嵌入任务
- 嵌入任务是否执行成功
- LLM Store 路由/执行器是否已注册
- 向量后端设置是否与持久化产物匹配

## 导入失败

检查准备好的 chunk JSONL 是否存在且可读。查看 IIS 保存根目录下的导入报告，检查验证警告和拒绝的记录。

## HNSW 索引无法加载或产生后端警告

如果 HNSW 后端无法加载，或者在更改向量存储设置后出现后端警告，请临时切换到 `jsonl_bruteforce`，以将向量数据问题与特定于后端的索引问题区分开来。保持 **Rebuild On Vector Format Mismatch** 处于启用状态，以便从源向量重建不兼容的持久化 HNSW 分区，而不是以错误的字节布局加载它们。

确认包中存在 `Source/ThirdParty/hnswlib`，并在更改 **Vector Storage Format** 后重建向量产物。

## 运行时调优或索引动作动词返回 Disabled

检查项目设置中的 **Enable Runtime Control Mutations**。当其关闭时，像 `iis.control.state` 这样的读取动词仍然有效，但 tune、act、persist 和 reset 动词按设计会返回已禁用的响应。

重新启用该设置以使用变更控制动词，或者继续使用只读状态和诊断命令。

## MCP 客户端缺失代理工具

检查：

- Unified MCP Server 是否已启用并正在运行
- Unreal Capability Mesh 是否已启用
- 项目设置是否包含 IIS 代理路由清单（`iis.agent.*.v1`）
- 调用 `mesh_list_routes` 或 `mesh_reload_setup` 并刷新 MCP 客户端
- IIS 是否可以写入代理工具契约
- MCP 客户端是否已连接到 UMCP 端点，而不是旧版的单插件 MCP 服务器

在路由更改后刷新 Capability Mesh 设置并重新连接或刷新 MCP 客户端。

## 代理工具返回纯检索护栏提示

这是预期行为。IIS 响应故意表明不允许项目变更。

## 性能自检报告偏差

在 `iis.perf.last` 中查看最新的性能结果或重新运行 `iis.perf.run`。偏差通常意味着当前的向量工作负载、后端或调优超出了配置的预算。

首先降低查询宽度或向量工作负载。仅在目标机器/项目配置文件上进行代表性验证后才更新预算。

## 在何处查找报告

默认路径：

```text
Saved/InternalIndexService/reports
Saved/InternalIndexService/imports
Saved/InternalIndexService/agent_contracts
```
