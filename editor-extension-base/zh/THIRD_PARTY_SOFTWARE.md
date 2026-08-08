---
lang: zh
title: EditorExtensionBase Third-Party Software
audience: [end_user]
owner_ref: plugin:EditorExtensionBase
applies_to:
  component: EditorExtensionBase
contract_ref: plugin:EditorExtensionBase/third-party-software
version:
  since: "1.0"
---
# 第三方软件

Editor Extension Base **不捆绑任何第三方源代码、运行时二进制文件、AI 模型、Node.js、Python 或独立可执行文件**。它是一个基于 Unreal Editor 模块和 Editor Scripting Utilities 构建的 C++ Unreal Engine 插件。

## 测量方法

在 `GovernanceDevelopmentPlugins/EditorExtensionBase` 中搜索了 `ThirdParty`、`LICENSE-` 以及版权标记。头文件标识了 Tiny Tool Development / Fab EULA。不存在任何内置的第三方代码库。

## 引擎依赖项（未捆绑）

| 依赖项 | 是否捆绑 | 备注 |
| --- | --- | --- |
| Unreal Engine Editor 模块 | 否 | 由引擎安装提供。 |
| Editor Scripting Utilities | 否 | 通过 `.uplugin` 的 `Plugins` 条目启用；属于 Epic 拥有的插件。 |

## 可选集成

功能插件可能依赖于 Editor Extension Base 来获取共享的小部件。这些消费者是独立的软件包，此处不进行重新分发。

**Fab 第三方软件声明：** 无。

## 相关文档

- [README.md](README.md)
- [QUICKSTART.md](QUICKSTART.md)
- [FAQ.md](FAQ.md)

## 版权头文件

编辑器和运行时源代码使用 Tiny Tool Development / Fab Standard EULA 头文件。未在 `ThirdParty` 目录下发现其他许可证文件。

## 买家声明检查清单

1. 声明 Fab **无** 捆绑的第三方软件。
2. Editor Scripting Utilities 仍然是 Epic 引擎插件依赖项，而非捆绑的第三方代码库。
3. 在任何未来的内置更改之后，在更新此文件之前重新运行搜索。
