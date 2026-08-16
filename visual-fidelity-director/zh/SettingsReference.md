<!-- doc-provenance: AKDB:plugins/VisualFidelityDirector/architecture.md; docs/architecture/plugins/VisualFidelityDirector/product-facts.yml; reconciled 2026-07-12 -->
# 设置参考

VFD 在 **Edit > Editor Configurations > Visual Fidelity Director Editor Settings** 下添加编辑器插件设置。项目渲染设置仅通过受治理的持久应用或 Expert Tools 会话预览进行更改。

## Cockpit 控件

| 控件 | 值 | 效果 |
| --- | --- | --- |
| 预设选择器 | 来自 `Saved/VisualFidelityDirector/profiles/` 的已知预设 | 设置用于编译、证据和对比的活动保真度预设。 |
| 轴变体组合框 | 每个轴的管道变体 | 选择作用变体；不可用选项保持可见并带有兼容性证据。 |
| 轴意图滑块 | `0.00`–`1.00` | 在所选变体中调整轴的意图级别。 |
| Compare against | 第二个预设 | 在对比卡中驱动并排的逐轴差分。 |
| 目标批准复选框 | Scalability / renderer ini / Device Profiles | 门控受治理的持久写入；取消勾选的目标绝不会被写入。 |

## 受治理的应用目标（持久配置）

| 目标 | 文件 | 是否持久写入？ |
| --- | --- | --- |
| Scalability 质量级别 | `DefaultGameUserSettings.ini` `[ScalabilityGroups]` | 是（经批准时）。 |
| 渲染器设置 | `DefaultEngine.ini` 渲染器部分 | 是（经批准时）。 |
| 设备配置文件 | `DefaultDeviceProfiles.ini` | 是（经批准时）。 |
| 控制台变量（会话） | 仅编辑器会话 | Expert Tools 预览路径；非持久。 |
| 资产、材质、MRQ、无障碍 | 阻止 | 绝不被 VFD 写入。 |

应用流程：构建目标 → 批准 → 备份 → 写入 → 验证 → 回滚清单。

## Blueprint 库函数

`UVFDCockpitBlueprintLibrary` 类别：

| 函数 | 类别 | 输出 |
| --- | --- | --- |
| LoadFidelityProfiles | Visual Fidelity\|Profiles | 预设数组 + 警告 |
| ResolveFidelityProfile | Visual Fidelity\|Profiles | 已解析预设或错误 |
| ValidateFidelityProfile | Visual Fidelity\|Profiles | 验证结果 |
| CompileFidelityProfile | Visual Fidelity\|Profiles | 已编译设置目标 + 发现 |
| CompareFidelityProfiles | Visual Fidelity\|Profiles | 逐轴对比结果 |
| DetectPipelineCapabilities | Visual Fidelity\|Capability | 能力报告 |
| BuildEvidenceState | Visual Fidelity\|Evidence | 证据状态 |
| PreviewPersistentDestinations | Visual Fidelity\|Apply | 只读目标摘要 |
| ApplyPersistentConfiguration | Visual Fidelity\|Apply | 应用报告（需要批准） |
| RollbackPersistentConfiguration | Visual Fidelity\|Apply | 回滚报告 |

展示资产: `Content/Blueprints/BPF_VFD_API`。

## 意图滑块值（Expert Tools）

所有意图滑块均使用 `0.00` 到 `1.00` 的浮点值。

| 控件 | 默认来源 | 效果 |
| --- | --- | --- |
| Image Stability | 所选配方 | 较高值有利于更平稳的时间稳定性。 |
| Motion Clarity | 所选配方 | 较高值有利于减少拖尾/重影。 |
| Fine Detail Preservation | 所选配方 | 较高值有利于更清晰的细节，但锯齿风险更高。 |
| Specular Calmness | 所选配方 | 较高值有利于减少高光闪烁。 |
| UI Crispness | 所选配方 | 较高值优先考虑 HUD/UMG 清晰度。 |
| Cinematic Accumulation | 所选配方 | 较高值有利于最终渲染积累。 |
| Performance Headroom | 所选配方 | 较高值有利于更低成本的建议。 |

## 内置配方 ID

在导出的配方 JSON 和报告中使用这些 ID：

```text
stable_gameplay
sharp_gameplay
cinematic_calm
vegetation_heavy_scene
specular_heavy_scene
ui_safe_temporal
vr_clarity
low_end_stable
marketing_screenshot
debug_no_temporal
lumen_static_material_performance
lumen_dynamic_material_safe
lumen_low_end_atlas_budget
lumen_surface_cache_debug
lumen_archviz_many_instances
```

## 捕获的 CVar

快照捕获在可用时读取此精选的 CVar 注册表：

```text
r.AntiAliasingMethod
r.ScreenPercentage
r.TemporalAA.Upsampling
r.PostProcessAAQuality
r.TSR.History.ScreenPercentage
r.TSR.ShadingRejection.Flickering
r.DefaultFeature.MotionBlur
r.MotionBlurQuality
r.LumenScene.SurfaceCache.CardCapturesPerFrame
r.LumenScene.SurfaceCache.CardCaptureRefreshFraction
r.LumenScene.SurfaceCache.CardMaxResolution
r.LumenScene.SurfaceCache.AtlasSize
r.LumenScene.SurfaceCache.AllowCardSharing
r.LumenScene.SurfaceCache.DetectCardSharingCompatibility
r.LumenScene.SurfaceCache.MeshCardsMinSize
r.LumenScene.SurfaceCache.MeshCardsMergeComponents
r.LumenScene.SurfaceCache.MeshCardsMergeInstances
r.LumenScene.DirectLighting.UpdateFactor
r.LumenScene.Radiosity.UpdateFactor
```

不可用的 CVar 会被记录为不可用，而不是导致整个报告失败。

## Lumen 表面缓存审查

Lumen Surface Cache Review 车道仅用于网格和材质内容的报告。它可以捕获精选的 Lumen CVar、评估 Lumen 配方、在 `visual_quality_report.md` 中对 Lumen 发现进行分组，并运行 **Lumen Deep Scan** 以获取仅限编辑器的 Asset Registry 元数据线索。它不会更改静态网格卡片设置、材质图、卡片共享标志、项目配置或 MRQ 预设。

## 预览应用支持（Expert Tools）

| 支持的目标 | 支持的模式 | 是否持久写入？ |
| --- | --- | --- |
| 控制台变量 | Preview Only, Editor Session Only | 无项目配置写入。 |
| 项目设置 | Cockpit 页面上的受治理应用抽屉 | 是（经显式批准时）。 |
| Post Process Volumes | 仅建议/导出 | 否。 |
| MRQ 预设 | 仅建议/导出 | 否。 |
| 资产 | 仅建议/导出 | 否。 |
| Lumen 网格/材质设置 | 仅建议/导出/人工审查 | 否。 |

## 报告文件

| 工作流 | 文件 |
| --- | --- |
| Snapshot | `quality_snapshot.json`, `quality_snapshot.md` |
| Recipe dry run | `recipe_evaluation.json`, `settings_diff.md` |
| Scanner | `visual_quality_report.json`, `visual_quality_report.md` |
| Lumen deep scan | `visual_quality_report.json`, `visual_quality_report.md` |
| Apply (session) | `visual_fidelity_apply_report.json`, `visual_fidelity_apply_report.md` |
| Persistent apply | VFD 配置备份/报告根目录下的受治理应用报告 |
| A/B comparison | `comparison_report.json`, `comparison_report.md` |
| Cinematic | `cinematic_quality_report.json`, `cinematic_quality_report.md`, `mrq_recommendation.md` |
| Schema validation | `schema_validation_report.json`, `schema_validation_report.md` |
| Diagnostics | `experimental_diagnostics_report.json`, `experimental_diagnostics_report.md` |
| Productization | `productization_readiness_report.json`, `productization_readiness_report.md` |

最新副本使用相同的名称，并在 `Saved/VisualFidelityDirector/reports/` 下加上 `latest_` 前缀。

预设 JSON 使用插件 `Schemas/` 文件夹下的 Schema，并保存到 `Saved/VisualFidelityDirector/profiles/`。
