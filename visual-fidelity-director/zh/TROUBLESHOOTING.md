<!-- doc-provenance: AKDB:plugins/VisualFidelityDirector/architecture.md; docs/architecture/plugins/VisualFidelityDirector/product-facts.yml; reconciled 2026-07-12 -->
# 疑难解答

## 我启用了插件，但什么也没发生

原因：VFD 从菜单项打开；它不显示启动窗口。

修复方法：

1. 启用插件后重新启动 Unreal Editor。
2. 打开 **Tiny Tools > Visual Fidelity Director**。
3. 如果菜单仍然缺失，请在 **Edit > Plugins** 中确认已启用该插件。

## 实时指标不可用

原因：实时指标需要可用的编辑器视口测量上下文。某些平台、无界面会话或早期编辑器 Tick 可能不会公开 GPU Pass 数据。

修复方法：

1. 在视口可见后单击 **Refresh**。
2. 等待多帧采样窗口完成（多个编辑器 Tick）。
3. 将 `-1` 或显式不可用字符串视为如实降级 — VFD 绝不伪造数字。

## 预设栏中没有显示预设

原因：`Saved/VisualFidelityDirector/profiles/` 下尚不存在保真度预设。

修复方法：

1. 通过项目工作流导入或复制预设，或使用 Expert Tools 和项目工具从内置配方进行迁移。
2. 单击 Cockpit 页面上的 **Refresh**。

## 受治理的应用跳过了所有内容

原因：未勾选任何目标、已编译的差异已匹配或目标被阻止。

修复方法：

1. 先单击 **Build Destinations**。
2. 审查每个摘要并仅对预期的目标勾选批准。
3. 确认活动预设通过更改进行了编译（`Compile Preview`）。

## 预设对比显示没有差异

原因：两个预设针对所有轴编译为相同的所需状态，或者某个预设未通过验证。

修复方法：

1. 验证两个预设均已编译且没有错误。
2. 更改某个预设上的变体或意图级别并刷新。

## 打开了控制面板 / Expert Tools，但未写入任何报告

原因：项目的 `Saved` 文件夹可能是只读的或不可用。

修复方法：

1. 切换到 **Expert Tools** 并单击 **Open Output Folder**。
2. 确认项目可以写入 `Saved/VisualFidelityDirector/`。
3. 再次尝试 **Export Snapshot** 并读取 **Status** 行。

## 预览应用跳过了所有内容

原因：所选配方可能仅包含仅导出建议、建议值可能已与当前值匹配，或者 CVar 在此引擎上下文中不可用。

修复方法：

1. 先导出配方测试评估。
2. 打开 `settings_diff.md`。
3. 检查 **Mode**、**Supported** 和 **Risk** 列。

## CVar 显示不可用

原因：某些 CVar 依赖于引擎版本、渲染器、平台或上下文。

修复方法：将建议视为人工审查。VFD 会记录不可用的值，而不是使整个工作流失败。

## MRQ 建议没有更改我的预设

原因：意图不支持 MRQ 预设修改。

修复方法：打开 `mrq_recommendation.md` 并将在审查后手动应用任何电影级设置。

## Lumen 建议没有更改网格或材质

原因：Lumen 网格卡片设置、材质图和材质卡片共享标志被有意设计为仅供人工审查。

修复方法：导出 **Lumen Deep Scan** 或 Lumen 配方测试，然后检查报告，并在仅在视觉验证后手动应用网格或材质更改。

## 实验性诊断看起来太粗糙

原因：诊断报告是基于元数据的审查路由热力图。它不是基于像素的帧差异热力图，也不捕获运动矢量。

修复方法：使用快照和扫描器报告进行结构化审查；必要时手动捕获视觉证据。

## Blueprint 库应用未写入任何内容

原因：`ApplyPersistentConfiguration` 需要 `Request.bUserApproved` 和批准的目标摘要。

修复方法：先调用 `PreviewPersistentDestinations`，在请求中仅将预期目标标记为已批准，然后调用带有 `bUserApproved=true` 的应用。
