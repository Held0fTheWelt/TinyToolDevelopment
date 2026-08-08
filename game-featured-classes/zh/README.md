# GameFeaturedClasses 文档

GameFeaturedClasses 是一个轻量级的运行时插件外壳，用于项目特定的特色游戏类。版本 `1.0.1` 提供了描述符、打包元数据、图标、更新日志以及运行时模块边界（`StartupModule` / `ShutdownModule`）。

受众：当前项目中需要 GFC 包边界，且特色类和高级 GameFeature Workbench 仍为目标架构（本包中尚未提供）的团队。

## 当前包

- 运行时模块 `GameFeaturedClasses` 在启用并重启后加载。
- 尚未提供游戏特色类资产、Game Feature 操作、注册表或编辑器工作台。
- 该外壳无需其他 Tiny Tool 插件。

## 入门指南

1. 启用插件——参见 [QUICKSTART.md](QUICKSTART.md) 中的工作示例（模块冒烟测试）。
2. 阅读 [UserManual.md](UserManual.md) 了解当前与目标边界的区别。
3. 当预期存在但缺失工作台菜单时，请使用 [TROUBLESHOOTING.md](TROUBLESHOOTING.md)。

## 相关文件

- [../README.md](../README.md) — 产品概述。
- [../CHANGELOG.md](../CHANGELOG.md) — 发布历史。
- [SettingsReference.md](SettingsReference.md) · [FAQ.md](FAQ.md) · [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md)
