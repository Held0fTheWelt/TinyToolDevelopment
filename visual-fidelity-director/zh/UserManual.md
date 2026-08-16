<!-- doc-provenance: AKDB:plugins/VisualFidelityDirector/architecture.md; docs/architecture/plugins/VisualFidelityDirector/product-facts.yml; reconciled 2026-07-12 -->
# 用户手册

Visual Fidelity Director 是一个本地 Unreal Editor 工具。`2.0.0` 版本以以预设为中心的驾驶舱为核心，同时保留了用于快照和配方工作流的集成 1.x Expert Tools 面板。

## 打开工具

使用 **Tiny Tools > Visual Fidelity Director**。

停靠标签页提供 **Cockpit**、**Evidence** 和 **Expert Tools** 页面。

可选：**Edit > Editor Configurations > Visual Fidelity Director Editor Settings** 打开插件编辑器偏好设置（可在设置中禁用菜单快捷方式）。

## Cockpit 页面

### 状态横幅

显示来自活动预设编译和验证状态的就绪标语和详细文本。

### 操作卡

| 操作 | 预期输出 |
| --- | --- |
| **Refresh** | 重新加载预设，重新编译活动预设预览，重新启动多帧指标采样，并刷新轴条。 |
| **Compile Preview** | 重新编译活动预设的所需设置目标，而不写入配置。 |
| **Open Reports** | 在 OS 文件浏览器中打开本地 VFD 报告文件夹。 |

### 预设栏

选择活动保真度预设。该栏显示验证状态以及从 `Saved/VisualFidelityDirector/profiles/` 加载的已知预设。

### 指标栏

显示多帧实时编辑器指标（帧、游戏线程、渲染线程、GPU、瓶颈以及可用时的每个轴的成本份额）。`-1` 或显式不可用字符串的值表示在当前编辑器上下文中无法进行测量 — VFD 绝不伪造数字。

### 轴条

每个合成轴条包括：

- 轴标签和就绪颜色；
- **Variant** 组合框（不可用的变体保持可见，但禁用并带有兼容性证据）；
- **Intent** 滑块（`0.00`–`1.00`）；
- 活动轴细节抽屉的选择高亮。

### 轴细节抽屉

对于所选的轴：

- **继承路径** — 从根祖先到活动预设的有序链；
- **出处** — 编译设置的字段级行（目标、值、来源）；
- **发现** — 控件本地的编译和兼容性发现。

### 预设对比卡

选择第二个预设并检查每个轴的编译所需状态的差分。使用与 Blueprint 库相同的比较运行时。

### 受治理的应用抽屉

| 操作 | 预期输出 |
| --- | --- |
| **Build Destinations** | 用于 Scalability、renderer ini 和 Device Profile 目标的只读摘要。 |
| **Apply Approved** | 仅通过 备份 → 写入 → 验证 → 回滚清单 写入已勾选且经用户批准的目标。 |
| **Rollback** | 从回滚清单恢复上次备份的文件。 |

被阻止的目标（资产、材质、MRQ、无障碍、仅审查轴）绝不会显示为可写目标。

## Evidence 页面

显示 11 个固定车道证据块（Lumen 和其他审查车道），其中包含声明的轴映射、置信度和人工审查限制。此页面为只读。

## Expert Tools 页面

用于遗留工作流的集成 1.x 控制面板：

### Intent Mixer

每个滑块接受 `0.00` 到 `1.00`，仅影响配方测试评估，直到您导出或应用。

| 滑块 | 含义 |
| --- | --- |
| Image Stability | 偏好更平稳的亚像素细节和更少的闪烁。 |
| Motion Clarity | 偏好在运动内容中更少的拖尾/重影。 |
| Fine Detail Preservation | 偏好更清晰的表观细节。 |
| Specular Calmness | 偏好高光/光泽区域更少的闪烁。 |
| UI Crispness | 偏好 HUD/UMG 清晰度。 |
| Cinematic Accumulation | 偏好最终渲染样本积累。 |
| Performance Headroom | 偏好更低成本的建议。 |

### 内置配方

与 `1.0.0` 版本相同的 15 个内置配方 ID（参见 [SettingsReference.md](SettingsReference.md)）。

### Expert Tools 操作

| 操作 | 预期输出 |
| --- | --- |
| Export Snapshot (Expert Tools) | `quality_snapshot.json/.md` 以及最新副本。 |
| Export Recipe Dry Run (Expert Tools) | `recipe_evaluation.json` 和 `settings_diff.md`；无修改。 |
| Duplicate Recipe | 在 `Saved/VisualFidelityDirector/recipes/` 下的项目拥有的 JSON。 |
| Import Recipe | 从导入的 JSON 更新活动配方和滑块。 |
| Export Scanner Report | `visual_quality_report.json/.md`。 |
| Lumen Deep Scan (Expert Tools) | Lumen 表面缓存元数据发现；无网格/材质修改。 |
| Preview Apply + Rollback (Expert Tools) | 带回滚的会话 CVar 预览；`visual_fidelity_apply_report.*`。 |
| Export A/B Report | `comparison_report.json/.md`。 |
| Export Cinematic Report | `cinematic_quality_report.*` 和 `mrq_recommendation.md`。 |
| Validate Schemas | `schema_validation_report.*`。 |
| Export Diagnostics | `experimental_diagnostics_report.*`。 |
| Productization Report | `productization_readiness_report.*`。 |
| Open Output Folder | 打开报告根目录。 |

## Blueprint 库

`UVFDCockpitBlueprintLibrary` 公开了与驾驶舱相同的无界面服务：

- 加载、解析、验证和编译保真度预设；
- 对比预设；
- 检测管道能力；
- 构建证据状态；
- 预览、应用和回滚受治理的持久配置。

打包展示资产: `Content/Blueprints/BPF_VFD_API`。

## 安全模型

- 驾驶舱审查、证据、对比和目标预览都是只读的。
- 受治理的持久应用是驾驶舱唯一的修改路径，需要每个目标获得显式批准。
- Expert Tools 预览应用仍仅限于带有回滚的会话 CVar。
- VFD 不会更改资产、材质、Post Process Volumes、MRQ 预设和无障碍设置。

## 报告与预设

```text
Saved/VisualFidelityDirector/profiles/
Saved/VisualFidelityDirector/reports/
Saved/VisualFidelityDirector/recipes/
```

将输出视为本地/私有，因为它们可能包含项目名称、CVar 值和质量方向。
