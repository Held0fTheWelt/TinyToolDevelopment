<!-- doc-provenance: AKDB:plugins/VisualFidelityDirector/architecture.md; docs/architecture/plugins/VisualFidelityDirector/product-facts.yml; reconciled 2026-07-12 -->
# Visual Fidelity Director 文档

本文件夹是 Visual Fidelity Director 交付的买家文档。核心工作流是独立的：启用插件，打开驾驶舱，审查保真度预设和合成轴，检查证据，选择性批准受治理的配置写入，并使用 Expert Tools 进行传统的快照/配方工作流，无需其他插件或外部服务。

当前软件包文档已针对版本 `2.0.0` 和发布状态 `In Publishment` 完成和解。

## 从这里开始

- [QUICKSTART.md](QUICKSTART.md)：安装、启用、首次驾驶舱刷新以及一个预设对比任务。
- [UserManual.md](UserManual.md)：每个驾驶舱、证据和 Expert Tools 操作。
- [SettingsReference.md](SettingsReference.md)：控件、预设路径、Blueprint 库函数、报告输出和应用行为。
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md)：常见问题和修复方法。
- [FAQ.md](FAQ.md)：关于兼容性、安全性、MRQ、截图和支持的解答。
- [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md)：外部依赖声明。

## 驾驶舱入口

从 **Tiny Tools > Visual Fidelity Director**（Performance 区域）打开 Visual Fidelity Director。

停靠标签页提供三个页面：

| 页面 | 目的 |
| --- | --- |
| **Cockpit** | 预设栏、多帧实时指标、九个合成轴、变体选择器、意图滑块、带继承路径的轴细节、出处、发现、预设对比和受治理的持久应用。 |
| **Evidence** | 映射到合成轴的 11 个固定车道证据块。 |
| **Expert Tools** | 集成的 1.x 控制面板，用于快照、配方、扫描器、预览应用和遗留报告。 |

## 预设与报告

保真度预设保存在：

```text
Saved/VisualFidelityDirector/profiles/
```

来自 Expert Tools 和验证工作流的报告保存在：

```text
Saved/VisualFidelityDirector/reports/
```

配方副本仍保存在：

```text
Saved/VisualFidelityDirector/recipes/
```

## Blueprint 接口

运行时 Blueprint 调用方使用 `UVFDCockpitBlueprintLibrary`（与驾驶舱 UI 相同的 C++ 服务）。打包的展示资产保存在 `Content/Blueprints/BPF_VFD_API`。

## 安全模型

- 除非您使用受治理的应用抽屉，否则驾驶舱审查、证据和对比操作都是只读的。
- **受治理的持久应用** 仅写入 `DefaultGameUserSettings.ini` Scalability 组、`DefaultEngine.ini` 渲染器设置和 `DefaultDeviceProfiles.ini`，并且仅在显式获得每个目标的批准后才进行，同时支持备份、验证和回滚。
- **Expert Tools > Preview Apply + Rollback** 仍为会话 CVar 预览路径。
- 资产、材质、Post Process Volumes、MRQ 预设、LevelSequences、Blueprints 和无障碍设置保持阻止状态。

## Schema

打包的运行时 Schema 文件保存在插件根目录下的 `Schemas/` 中。

## 相关文件

- [../README.md](../README.md)：产品概述。
- [../CHANGELOG.md](../CHANGELOG.md)：版本历史。
