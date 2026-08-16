<!-- doc-provenance: AKDB:plugins/VisualFidelityDirector/architecture.md; docs/architecture/plugins/VisualFidelityDirector/product-facts.yml; reconciled 2026-07-12 -->
# 常见问题解答 (FAQ)

## VFD 是否替代了 Unreal 的渲染器或抗锯齿？

没有。它是 Unreal 现有渲染系统之上的诊断、预设、证据、对比、配方、测试、扫描器和建议层。

## 2.0.0 版本有什么变化？

`2.0.0` 版本添加了以预设为中心的驾驶舱（变体选择器、继承路径、出处、发现、预设对比、受治理的持久应用、多帧实时指标）、`UVFDCockpitBlueprintLibrary` 和打包的 Blueprint 展示资产。集成的 Expert Tools 页面保留了 1.x 快照和配方工作流。

## 它需要 AI 或云服务吗？

不需要。VFD 没有外部 AI、云、Python、Node.js 或帐户要求。

## 它需要其他 Tiny Tool 插件吗？

不需要。核心工作流是独立的。

## 针对的是哪个 Unreal 版本？

Visual Fidelity Director 通过匹配的引擎分支描述符支持 Unreal Engine 5.4 到 5.8，并允许 Win64、Linux 和 Mac。

## 它会修改我的项目吗？

默认情况下不会。受治理的持久应用仅在您显式批准时才能写入三个配置目标：`DefaultGameUserSettings.ini` 中的 Scalability 组、`DefaultEngine.ini` 中的渲染器设置以及 `DefaultDeviceProfiles.ini` 中的 Device Profiles。Expert Tools **Preview Apply + Rollback** 可以临时设置支持的编辑器会话 CVar，然后对其进行恢复。资产、材质、Post Process Volumes 和 MRQ 预设不会被修改。

## Lumen Deep Scan 会更改网格或材质吗？

不会。Lumen 深入扫描会从快照和 Asset Registry 元数据写入审查发现。它不会更改静态网格卡片设置、材质图、材质卡片共享标志、项目配置或 MRQ 预设。

## 它会捕获截图吗？

除非未来的工作流提供截图路径，否则 Expert Tools A/B 工作流会写入仅限元数据的对比报告。使用报告链接决策，并在需要时手动捕获视觉证据。

## 为什么有些发现是“中等置信度”？

许多视觉缺陷取决于内容和运动。VFD 将事实与启发式方法分开，以便您可以路由人工审查，而无需将元数据视为证据。

## 预设和报告保存在哪里？

```text
Saved/VisualFidelityDirector/profiles/
Saved/VisualFidelityDirector/reports/
Saved/VisualFidelityDirector/recipes/
```

## 我可以从 Blueprint 使用 VFD 吗？

可以。`UVFDCockpitBlueprintLibrary` 公开了预设、证据、能力和受治理的应用函数。有关连接示例，请参阅 `Content/Blueprints/BPF_VFD_API`。

## 我应该联系谁寻求支持？

使用插件描述符中列出的支持电子邮箱：
`support@tiny-tool-development.com`。

Discord: `#support`（发布时请参阅产品列表）。
