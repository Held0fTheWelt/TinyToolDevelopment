<!-- doc-provenance: AKDB:plugins/VisualFidelityDirector/architecture.md; docs/architecture/plugins/VisualFidelityDirector/product-facts.yml; reconciled 2026-07-12 -->
# 快速入门指南

本指南带您从安装到获得实际成果：打开 Visual Fidelity Director 驾驶舱，刷新预设视图，并进行并排预设对比。

## 完成本指南后您将获得什么

在 Unreal Editor 中打开 VFD 驾驶舱，启动实时指标采样，审查一个带有变体和出处细节的合成轴，并与第二个预设进行对比。

## 要求

- Win64、Linux 或 Mac 上的 Unreal Engine 5.4 编辑器。
- 可以加载编辑器插件的项目。
- 无需第三方软件、帐户、AI 服务或其他 Tiny Tool 插件。

## 1. 安装与启用

1. 从 Fab 库将 **VisualFidelityDirector** 添加到项目，或将其安装到引擎。
2. 打开 **Edit > Plugins**。
3. 搜索 **Visual Fidelity Director**。
4. 启用插件，并在收到提示时重新启动 Unreal Editor。

如果您将纯源代码插件包安装到 C++ 项目中，请让 Unreal 在下次编辑器启动时编译项目模块。

## 2. 打开驾驶舱

1. 打开 **Tiny Tools > Visual Fidelity Director**。
2. 确认 **Cockpit** 页面处于活动状态（默认）。
3. 审查状态横幅、预设选择器和指标栏。

预期输出：

- 停靠标签页标题为 **Visual Fidelity Director**。
- 预设栏列出了来自 `Saved/VisualFidelityDirector/profiles/` 的已知预设以及内置/项目上下文。
- 指标栏在多个编辑器 Tick（多帧采样）中填满，或显示显式的不可用状态。

## 3. 实际操作示例：审查一个轴

1. 单击 Cockpit 操作卡上的 **Refresh**。
2. 选择任意合成轴条（例如 **Anti-Aliasing** 或 **Upscaling**）。
3. 在轴细节抽屉中审查：
   - 从根预设到活动预设的**继承路径**；
   - 编译设置的**出处**行；
   - 该轴的**控件本地发现**。
4. 当有多个管道变体可用时，更改 **Variant** 组合框。不可用的变体保持可见，但禁用并带有兼容性证据。

预期输出：

- 意图滑块更新反映所选变体。
- 所选轴的出处和发现已刷新。
- 在使用受治理的应用或 Expert Tools 预览应用之前，项目文件不会发生任何更改。

## 4. 实际操作示例：对比两个预设

1. 滚动到 Cockpit 页面上的 **Profile Comparison** 卡片。
2. 从下拉列表中选择 **Compare against** 预设。
3. 读取每个轴的差分摘要。

预期输出：

- 存在差异的轴将列出设置级别的细节。
- 匹配的轴不显示差分行。
- 对比使用与 `UVFDCockpitBlueprintLibrary::CompareFidelityProfiles` 相同的运行时比较器。

## 5. 可选：Expert Tools 快照

1. 切换到 **Expert Tools** 页面。
2. 单击 **Export Snapshot**。

预期输出：

- 存在 `Saved/VisualFidelityDirector/reports/<timestamp>/quality_snapshot.json`。
- 最新副本保存在 `Saved/VisualFidelityDirector/reports/` 下。

此路径为喜欢基于报告审查的用户保留了 1.x 快照和配方工作流。

## 6. 可选：受治理的持久应用

仅当您打算写入项目配置文件时才继续。

1. 在 Cockpit 页面上，单击应用抽屉中的 **Build Destinations**。
2. 审查每个目标摘要（Scalability、renderer ini、Device Profiles）。
3. 仅对您接受的目标勾选批准。
4. 单击 **Apply Approved**。

预期输出：

- 在 VFD 配置备份根目录下带有时间戳的备份和回滚清单。
- 带有验证结果的应用报告。
- 如果验证失败，**Rollback** 将恢复已备份的文件。

## 7. 成果保存位置

```text
Saved/VisualFidelityDirector/profiles/
Saved/VisualFidelityDirector/reports/<timestamp>/
Saved/VisualFidelityDirector/recipes/
```

## 8. 后续步骤

- 完整操作列表: [UserManual.md](UserManual.md)
- 控件和 Blueprint 函数: [SettingsReference.md](SettingsReference.md)
- 疑难解答与修复: [TROUBLESHOOTING.md](TROUBLESHOOTING.md)
- 兼容性和安全性解答: [FAQ.md](FAQ.md)
