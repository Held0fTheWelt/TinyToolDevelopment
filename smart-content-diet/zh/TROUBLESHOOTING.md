<!-- doc-provenance: AKDB:plugins/SmartContentDiet/architecture.md; docs/architecture/plugins/SmartContentDiet/product-facts.yml; reconciled 2026-07-16 -->
# 疑难解答

## 我启用了插件但看不到它

打开 **Tools → Content Tools → Smart Content Diet**。如果缺少菜单项，请在 *Edit → Plugins* 中确认插件已启用，并且您已重新启动编辑器。

## 我期望的标签页（Preset / Governance / Redundancy）不可见

标签页可见性具有角色感知能力。**Preset** 和 **Governance** 针对 **Engineer / Producer**（高级模式）显示；**Redundancy** 仅在注册了外部相似性提供程序时显示。请在 **Settings** 或标头受众选择器中更改您的角色/解释级别。

## 扫描返回很少或没有结果

**Quick Safe** 仅使用注册表/元数据路径（无资产加载），因此某些发现需要更繁重的处理。将标头深度切换为 **Full**（加载资产）或 **Deep**（深入材质/网格指标）并再次运行。

## “先运行扫描” / 空发现或优化

发现和优化操作需要完成扫描。请先从标头运行扫描，然后打开 **Findings** 或 **Optimize**。

## 应用被阻止或要求批准

默认情况下，修改性操作带有批准门控，必须在已备份、受版本控制且可弃用的工作区中运行。请确认您的备份/版本控制，然后批准操作。破坏性修复还需要显式选择（相关路由上的 `allow_destructive: true`）。

## 应用报告在哪里？

```text
Saved/SmartContentDiet/OptimizationQueue/<timestamp>/
```

## 跨插件路由显示“可用但插件未加载”

这是预期的并且安全的：SCD 从不硬性要求同伴插件。当缺失该同伴时，引用另一个插件的路由（例如 IIS 相似性摄取）被报告为 *可用但插件未加载*，而每个仅限 SCD 的能力保持可用。
