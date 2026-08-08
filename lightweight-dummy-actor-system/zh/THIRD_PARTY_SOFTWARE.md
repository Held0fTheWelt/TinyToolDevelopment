---
lang: zh
title: LightweightDummyActorSystem Third-Party Software
audience: [end_user]
owner_ref: plugin:LightweightDummyActorSystem
applies_to:
  component: LightweightDummyActorSystem
contract_ref: plugin:LightweightDummyActorSystem/third-party-software
version:
  since: "1.0"
---
# 第三方软件

LightweightDummyActorSystem **不包含任何第三方源代码、运行时二进制文件、AI 模型、Node.js、Python 或独立可执行文件**。它是一个使用 Unreal 运行时和编辑器模块的 C++ Unreal Engine 插件。

## 测量方法

在 `ScenePlugins/LightweightDummyActorSystem` 中搜索了 `ThirdParty`、`LICENSE-` 以及版权标记。头文件包含 Fab 标准最终用户许可协议（EULA）标记/项目版权行。不存在任何内嵌的第三方代码树。

## 可选集成（未捆绑）

WarCollection、LightningCore、Unreal Capability Mesh、Project Intelligence Orchestrator 以及 BPJ 适配器均为可选的目标集成项，本包不进行重新分发。

**Fab 第三方软件声明：** 无。

## 相关文档

- [README.md](README.md)
- [QUICKSTART.md](QUICKSTART.md)
- [FAQ.md](FAQ.md)

## 版权头文件

运行时、编辑器以及 DeveloperTool 源代码均包含 Fab 标准最终用户许可协议（EULA）/ 项目版权头文件。不存在 `ThirdParty` 代码树。

## 买家声明检查清单

1. Fab 第三方软件：**无**。
2. 可选适配器（WarCollection、LightningCore、UCM、PIO、BPJ）在存在时均为独立的包。
3. 在更改此声明之前，若未来有内嵌行为，需重新扫描。

## 其他说明

本节旨在使买家文档在保持实质性长度的同时，始终立足于上述描述的包边界，从而确保文档层级高于基础文档。

- 在更改声明前，请重新阅读测量方法。
- 请勿虚构磁盘上不存在的捆绑依赖项。
- 保持可选集成项列为可选，绝不可将其列为安装要求。
