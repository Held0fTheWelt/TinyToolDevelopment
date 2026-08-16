<!-- doc-provenance: AKDB:plugins/SmartContentDiet/architecture.md; docs/architecture/plugins/SmartContentDiet/product-facts.yml; reconciled 2026-07-16 -->
# SmartContentDiet 文档

SmartContentDiet 扫描 Unreal Engine 项目资产，在上下文中解释优化发现，暴露治理视图，并提供经过审查的 QuickFix / 缩减工作流。默认的产品循环是 **扫描 → 审查 → 应用安全修复 → 重新扫描 → 测量改进** — 无需 AI 或外部工具。

## 安全须知

在应用 QuickFix、网格缩减、纹理/材质更改、资产审查移动/删除、基线更新或治理写入时，SmartContentDiet 可能会修改项目资产。请仅在已备份、受版本控制且可弃用的分支或工作区中使用。切勿在未受保护的源代码上运行。使用风险自负。

该功能在其声明的范围内经过精心实现，但不能替代备份、版本控制、代码/内容审查或特定于项目的验证。

## 文档地图

| 文档 | 目标受众 | 内容 |
|------|----------|------|
| [UI_AND_BEHAVIOR.md](../Resources/UI_AND_BEHAVIOR.md) | 美术、技术美术、制作人 | 编辑器 Shell、标签页、扫描工作流、发现、QuickFix、治理 |
| [OPTIMIZATION_QUEUE.md](../Resources/OPTIMIZATION_QUEUE.md) | 所有编辑器用户 | 安全优化队列、桶、应用/预览、前后增量 |
| [SMART_ANALYSIS_ARCHITECTURE.md](../Resources/SMART_ANALYSIS_ARCHITECTURE.md) | 工程师、集成人员 | 分析器、预设、影响、缩减、趋势、治理架构 |
| [DIMENSION_INTEGRATION_STATUS.md](../Resources/DIMENSION_INTEGRATION_STATUS.md) | 工程师 | FindingType、维度映射、转换器、UI 集成状态 |
| [SmartAnalysisResult_Usage.md](../Resources/SmartAnalysisResult_Usage.md) | 工程师 | 结果模型使用、自动修复元数据 |
| [CHANGELOG.md](../CHANGELOG.md) | 发布人员 | 版本历史 |

**初次使用？** 请从 [QUICKSTART.md](QUICKSTART.md) 开始，了解安装和安全扫描→修复循环。

## 已安装 Engine 的软件包

请使用针对已安装引擎版本生成的 Smart Content Diet BuildPlugin 软件包。该软件包保留了已安装构建所需的生成二进制文件和预编译元数据。复制或归档插件时请勿删除这些文件。

> **维护人员须知：** SCD 发布门控和发布/运行手册文档位于开发存储库中，**不**属于 Fab 软件包的一部分；安装或使用 SCD 不需要它们。

## 编辑器入口点

打开 **Tools → Content Tools → Smart Content Diet**。

### 角色感知 Shell

主窗口使用受众设置（初学者 / 工程师 / 制作人）来控制解释深度和哪些标签页可见。

| 标签页 | 初学者 | 高级（工程师 / 制作人 + 高级模式） |
|-----|----------|--------------------------------------------------|
| Overview | ✓ | ✓ |
| Optimize | ✓ | ✓ |
| Findings | ✓ | ✓ |
| Preset | — | ✓ |
| Governance | — | ✓ （Trend、Debt、Budget、Ownership、Deep Scan 作为子标签页） |
| Redundancy | — | ✓ 仅当注册了外部相似性提供程序时 |
| Settings | ✓ | ✓ |

可在 **Settings** 中或通过标头的受众选择器更改角色和解释级别。

### 扫描深度（标头）

| 深度 | 是否加载资产？ | 典型用途 |
|-------|---------------|-------------|
| **Quick Safe** （默认） | 否 — 注册表/元数据路径 | 首次运行，快速了解“我可以安全改进什么？” |
| **Full** | 是 — 完整分析器管道 | 可操作的网格/纹理/材质发现 |
| **Deep** | 是 — 包含深入的材质/静态网格指标 | 最慢；着色器统计和深入网格工作 |

标头组合框更新主扫描按钮标签（`Quick Safe Scan` / `Full Scan` / `Deep Scan`），并在控件下方显示深度提示。

**每次**分析器运行都会遵循所选深度：编辑器分析运行（Findings / Governance → Run analysis）将其传递给 `FSmartAnalysisOrchestrator`，治理状态行指定所使用的深度。**Commandlet 和 CI** 像以前一样遵循 `-QuickSafe`、`-FullScan` 和 `-DeepScan`。深入的材质/网格指标另外使用 Governance Deep Scan 工作流（`Governance → Deep Scan`），与 Commandlet 相同。

## 快速工作流

### UCM 生态系统路由

启用 Unreal Capability Mesh (UCM) 时，可以通过配置声明的路由而非直接的提供程序桥接来使用 SmartContentDiet。SCD 从不代码链接同伴插件，也从不在 `required_plugin_names` 或 `Build.cs` 中列出同伴插件；跨插件价值来自 JSON 路由，而不是代码依赖项。活动项目配置公开了 **12 个 SCD 能力**：

| 能力 | 种类 | 策略 |
| --- | --- | --- |
| `scd.migration.advice_from_handoff` | 咨询 | 只读 |
| `scd.scan.run` | 提供程序 | 只读 |
| `scd.findings.get` | 提供程序 | 只读 |
| `scd.findings.explain` | 提供程序 | 只读 |
| `scd.health.snapshot` | 提供程序 | 只读 |
| `scd.health.evidence` | 提供程序 | 只读 |
| `scd.governance.snapshot` | 提供程序 | 只读 |
| `scd.similarity.groups` | 相似性 | 只读 |
| `scd.similarity.ingest_groups` | 相似性 | 只读 |
| `scd.optimize.preview_safe` | 优化 | 只读 |
| `scd.optimize.apply_safe` | 优化 | **修改性 — 需要批准** |
| `scd.optimize.apply_fix` | 优化 | **修改性 — 需要批准** |

**性能下降契约。** 每个能力都返回共享的 `smart_content_diet.capability_mesh_endpoint.v1` 信封（`status` 为 `ok`/`degraded`/`error`）。缺少前提条件时，能力会降低功能而不是直接失败：optimize/findings 路由返回要求先运行 `scd.scan.run` 的 `error` 信封；在没有 `allow_destructive: true` 的情况下请求破坏性修复时，`scd.optimize.apply_fix` 返回 `degraded` 信封（无修改）。从不假定 SCD 连接到同伴 — UCM 探索报告引用另一个插件的路由（例如示例 `scd_ingest_from_iis.v1`、`iis.search.hybrid → scd.similarity.ingest_groups`）在缺少该同伴时为 *可用但插件未加载*，而每个仅限 SCD 的能力保持 *可用*。

**批准门控（及选项 3）。** 两个修改性路由带有 `requires_user_approval: true`，因此 UCM 会使用 `ApprovalRequired` 阻止它们，直到人工批准运行 — 在此之前不会触及任何资产。希望无人值守安全应用的运算符可以更改路由策略以删除批准要求（选项 3）；默认交付时带有批准门控。

PRS 放置工作流仍为 PRS 拥有的 UCM 路由。免费桥接仅适用于没有 UCM 的团队以及作为直接适配器的参考实现；主项目不需要它们。

### 独立安全优化循环（无 AI）

### 扫描正确性和性能

当前的分析器路径是 AssetRegistry 优先。它构建一次广泛的候选集，在加载资产之前读取标签元数据，并行化只读比较工作，并仅深层加载最终候选。带有时间戳/版本失效的每个资产元数据缓存可避免重复未更改的工作。

重复和 Alpha 分析与缩减引擎共享助手。缩减早期退出使用与缩减对齐的重复键（`DuplicateTextureReduction`、`DuplicateStaticMeshReduction`），因此安全整合检查与实际缩减器使用的指纹逻辑相匹配。纹理 Alpha 启发式方法集中在 `SCDMaterialAlpha` 中，以保持分析器和缩减行为一致。

编辑器作业历史记录可通过 UCM 路由（`scd.editor.jobs.list.v1`、`scd.editor.jobs.status.v1`）用于 UMCP 聚合，而无需向 SCD 添加 UMCP 依赖项。

1. 打开 Smart Content Diet。
2. 将扫描深度保持为 **Quick Safe** 或选择 **Full** / **Deep**。
3. 从标头运行扫描。
4. 审查 **Overview**，然后打开 **Optimize** → Safe Optimization Queue。
5. **Preview Safe** → **Apply Safe** （先进行备份/版本控制）。
6. 应用成功或从 **Findings** 细节中修复单个资产后，Shell 会自动重新扫描。
7. 在 Optimize 面板中比较队列计数和增量摘要；JSON 应用报告保存在 `Saved/SmartContentDiet/OptimizationQueue/<timestamp>/` 下。

有关桶定义、安全规则和报告 Schema，请参阅 [OPTIMIZATION_QUEUE.md](../Resources/OPTIMIZATION_QUEUE.md)。

### 一般分析工作流

1. 运行扫描（选择、文件夹或项目范围）。
2. 按严重性、影响、维度和可解释性链审查发现。
3. 使用 **Preset** （高级）了解评估权重如何影响得分。
4. 使用 **Governance** （高级）查看趋势、债务、预算、所有权、可选的 Deep Scan。
5. 仅在确认备份/版本控制后应用 QuickFix。
6. 重新扫描并在目标项目上下文中验证。

## Commandlet （CI / 无界面）

```powershell
UnrealEditor-Cmd.exe "<Project>.uproject" -run=SmartContentDiet `
  -QuickSafe -OptimizationQueueReport -Path=/Game -Limit=50 `
  -NoFail -unattended -nop4 -nosplash
```

应用安全队列行（仅限已备份的项目）：

```powershell
UnrealEditor-Cmd.exe "<Project>.uproject" -run=SmartContentDiet `
  -QuickSafe -ApplySafeQueue -OptimizationQueueReport -Path=/Game `
  -NoFail -unattended -nop4 -nosplash
```

| 标志 | 效果 |
|------|------|
| `-QuickSafe` | 注册表/依赖项扫描；不加载资产 |
| `-FullScan` | 加载资产并运行分析器（缺少 `-QuickSafe` 时的默认值） |
| `-DeepScan` | 最慢深度；深入的材质/网格指标 |
| `-OptimizationQueueReport` | 写入队列 JSON/Markdown（在 `-QuickSafe` 下自动启用） |
| `-ApplySafeQueue` | 仅应用 **Safe Now** 行；破坏性行将被拒绝 |
| `-Path=/Game/...` | 扫描范围 |
| `-NoFail` | 即使存在策略警告也退出 0（在 CI 中谨慎使用） |

Commandlet 在使用和运行开始时打印安全警告。基线更新和报告写入是修改工作区的操作。

## 成果位置（gitignored）

| 成果 | 路径 |
|----------|------|
| 优化队列应用报告 | `Saved/SmartContentDiet/OptimizationQueue/<timestamp>/apply_report.json` |
| Commandlet 队列报告 | `-ReportDir` / 默认在 `Saved/SmartContentDiet/` 下 |
| 发布验证输出 | 运行维护人员验证时的 `Saved/SCDValidation/` |

## 已实现的 QuickFix 范围（摘要）

SmartContentDiet 提供跨纹理、静态/骨骼网格、材质、动画、音频/VFX 卫生以及资产审查/整合的已审查 QuickFix。破坏性或跨资产操作需要显式确认，默认情况下不支持批处理安全。

完整目录: [UI_AND_BEHAVIOR.md § Optimization Packs](../Resources/UI_AND_BEHAVIOR.md#71-optimization-packs)。

## 发布验证

发布验证是维护人员的工作流。买家使用不需要本地门控脚本、主项目测试模块或特定于存储库的路径。
