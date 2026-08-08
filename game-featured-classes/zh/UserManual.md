# 用户手册

`GameFeaturedClasses` 目前为项目特定的特色玩法类提供了一个轻量级的运行时插件外壳。

## 当前包行为

| 区域 | 1.0.1 状态 |
| --- | --- |
| 运行时模块 (`GameFeaturedClasses`) | 已发布 — 仅包含启动/关闭逻辑。 |
| 描述符 / 打包 / 图标 / 更新日志 | 已发布。 |
| 特色玩法类 | 尚不可用 |
| Game Feature 操作 / 功能集资产 | 尚不可用 |
| 运行时注册表 / 接口边界 | 尚不可用 |
| 编辑器工作台 / 修复 / 证明报告 | 尚不可用 |
| 微型工具自动化路由 | 尚不可用 |

<!-- image slot: gfc-module-shell -->

## 源代码映射

- `Source/GameFeaturedClasses/GameFeaturedClasses.Build.cs` — 模块依赖项。
- `Source/GameFeaturedClasses/Public/GameFeaturedClasses.h` — `FGameFeaturedClassesModule` 接口。
- `Source/GameFeaturedClasses/Private/GameFeaturedClasses.cpp` — 启动和关闭逻辑。

## 今日如何使用外壳

1. 启用插件（请参阅 [QUICKSTART.md](QUICKSTART.md)）。
2. 在此包发布特色类之前，请将项目特定的特色类保留在您自己的模块中。
3. 不要记录或依赖本构建中不存在的工作台菜单。

## 目标架构（仅供参考，未发布）

内部产品架构描述了一个未来的高级 GameFeature 工作台，其中作者声明特色类和功能集，世界范围的操作注册它们，消费者通过注册表/接口边界解析它们，维护者扫描功能图、预览受控修复并导出证明报告。该行为**仅为目标规格**，不得在 1.0.1 中视为买家可用的功能。

## 自给自足

该模块外壳独立加载。未来与 `LightweightDummyActorSystem`、Unreal Capability Mesh 或 Project Intelligence Orchestrator 的可选集成并非此包的设置要求。

## 相关文档

- [QUICKSTART.md](QUICKSTART.md)
- [SettingsReference.md](SettingsReference.md)
- [FAQ.md](FAQ.md)
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md)
- [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md)
