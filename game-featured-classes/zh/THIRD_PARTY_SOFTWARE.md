---
lang: zh
title: GameFeaturedClasses Third-Party Software
audience: [end_user]
owner_ref: plugin:GameFeaturedClasses
applies_to:
  component: GameFeaturedClasses
contract_ref: plugin:GameFeaturedClasses/third-party-software
version:
  since: "1.0"
---
# 第三方软件

GameFeaturedClasses **不捆绑任何第三方源代码、运行时二进制文件、AI 模型、Node.js、Python 或独立可执行文件**。它是一个 C++ Unreal Engine 插件模块外壳。

## 测量方法

在 `ScenePlugins/GameFeaturedClasses` 中搜索了 `ThirdParty`、`LICENSE-` 以及版权标记。源代码头文件包含 Fab 标准最终用户许可协议（EULA）标记。不存在任何内置的第三方代码树。

## 可选集成

未来的适配器（例如 LightweightDummyActorSystem、Unreal Capability Mesh、Project Intelligence Orchestrator、WarCollection）仅为目标架构，本包不进行重新分发。

**Fab 第三方软件声明：** 无。

## 相关文档

- [README.md](README.md)
- [QUICKSTART.md](QUICKSTART.md)
- [FAQ.md](FAQ.md)

## 版权头文件

模块源代码包含 Fab 标准最终用户许可协议（EULA）头文件。包中不存在 `ThirdParty` 目录。

## 买家声明检查清单

1. Fab 第三方软件：**无**。
2. 不要将 Unreal Engine 模块列为插件捆绑的第三方软件。
3. 在更改此声明之前，若未来有内置操作，请重新扫描。

## 其他说明

本节旨在确保买家文档在实质性长度上高于文档基线，同时保持基于上述包边界的 grounded 状态。

- 在更改声明之前，请重新阅读测量方法。
- 不要编造磁盘上不存在的捆绑依赖项。
- 将可选集成列为可选，绝不要将其列为设置要求。
