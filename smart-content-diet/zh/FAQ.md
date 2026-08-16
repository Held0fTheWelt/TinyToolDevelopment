<!-- doc-provenance: AKDB:plugins/SmartContentDiet/architecture.md; docs/architecture/plugins/SmartContentDiet/product-facts.yml; reconciled 2026-07-16 -->
# 常见问题解答

**Smart Content Diet 是否需要 AI、账户或其他插件？**
不需要。核心循环（扫描 → 审查 → 应用安全修复 → 重新扫描 → 测量）完全在编辑器内运行，无需 AI 服务、账户或第三方插件。虽然存在通过 **Unreal Capability Mesh (UCM)** 的可选生态集成路径，但并非必需。

**运行是否安全？**
扫描和预览操作均为只读。应用修复、缩减、移动或删除操作 **会修改项目资产** — 请务必仅在已备份、受源代码控制且可丢弃的工作区中执行此类操作。修改类操作默认需经过审批流程。请自行承担使用风险。

**支持哪些引擎版本？**
Unreal Engine 5.4 及以上版本。它是一个编辑器插件。

**快速安全扫描（Quick Safe）、完整扫描（Full）和深度扫描（Deep）之间有什么区别？**
快速安全扫描仅使用注册表/元数据（无需加载资产，速度快）。完整扫描会加载资产以获取可操作的网格体/纹理/材质发现结果。深度扫描进一步包含深度材质/静态网格体指标，速度最慢。

**为什么我看不到预设（Preset）或治理（Governance）选项卡？**
它们是高级（工程师/制作人）选项卡。请在设置或标题栏中切换角色。

**我可以在 CI/无头模式下运行它吗？**
可以。命令行工具支持 `-QuickSafe` / `-FullScan` / `-DeepScan`、`-OptimizationQueueReport` 和 `-ApplySafeQueue`（仅在已备份的项目上应用）。

**它是否捆绑了第三方软件？**
没有。请参阅 [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md)。

**我如何获取支持？**
请使用 Fab 产品页面上的支持链接。
