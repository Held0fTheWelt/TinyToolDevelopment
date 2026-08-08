---
lang: zh
title: GameFeaturedClasses Settings Reference
audience: [end_user]
owner_ref: plugin:GameFeaturedClasses
applies_to:
  component: GameFeaturedClasses
contract_ref: plugin:GameFeaturedClasses/module-shell-settings
version:
  since: "1.0"
---
# 设置参考

GameFeaturedClasses 1.0.1 **不**包含 DeveloperSettings、配置 `.ini` 对象或可编辑的特色类描述符。运行时模块未暴露任何 `UPROPERTY` 设置接口，仅包含空的模块接口。

## 已提供的接口

| 名称 | 类型 | 默认值 | 效果 |
| --- | --- | --- | --- |
| 插件启用 | 编辑器插件 UI | 禁用，直到买家启用 | 加载 `GameFeaturedClasses` 运行时模块。 |
| `FGameFeaturedClassesModule::StartupModule` | 模块钩子 | 引擎调用 | 模块启动；无买家设置。 |
| `FGameFeaturedClassesModule::ShutdownModule` | 模块钩子 | 引擎调用 | 模块关闭；无买家设置。 |

## 尚不可用

| 预期设置接口 | 状态 |
| --- | --- |
| 特色类描述符资产 | 尚不可用 |
| 功能集资产 | 尚不可用 |
| 注册表 / 解析设置 | 尚不可用 |
| 编辑器工作台首选项 | 尚不可用 |
| `UGameFeaturedClassesSettings` DeveloperSettings | 尚不可用 |
| `Config/DefaultGameFeaturedClasses.ini` | 未提供 |

此处未虚构任何设置行。当后续软件包版本添加真实的 `UPROPERTY` / DeveloperSettings 字段时，必须在此更改中从源代码更新此参考文档。

## 相关文档

- [UserManual.md](UserManual.md) — 当前与目标边界。
- [QUICKSTART.md](QUICKSTART.md) — 启用冒烟测试。
- [FAQ.md](FAQ.md)

## 打包元数据（非运行时设置）

`.uplugin` 描述符包含用于打包的 `Version` / `VersionName`。这些字段是插件元数据，而非运行时 DeveloperSettings，不得从买家文档工作流程中随意编辑。

## 更新规则

本文件中任何未来的设置行必须在同一文档更改中引用源代码中的头路径和属性名称。
