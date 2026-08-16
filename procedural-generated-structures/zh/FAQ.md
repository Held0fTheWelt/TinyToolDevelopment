<!-- doc-provenance: AKDB:plugins/ProceduralGeneratedStructures/architecture.md; docs/architecture/plugins/ProceduralGeneratedStructures/product-facts.yml; reconciled 2026-06-21 -->
# 常见问题解答 (FAQ)

**本插件需要任何其他插件吗？**
不需要。它完全独立工作。

**它包含网格体吗？**
不包含。您提供自己的 `UStaticMesh` 资产；本插件实例化它们。

**支持哪些引擎版本？**
Unreal Engine 5.4+ (Win64, Linux, Mac)。该模块是 Runtime，因此 Actor 在编辑器和打包的游戏中都可以工作。

**它是否捆绑了第三方软件、Python 或 AI 模型？**
没有。参阅 [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md)。

**显式实例和行生成有什么区别？**
显式实例是确切的变换（通常从现有组件捕获）并按原样重放。行生成根据数据资产上定义的行数和每个维度的移动变换来程序化创建实例。

**我可以在运行时构建，而不只是在编辑器中构建吗？**
可以。Actor 具备运行时能力，可以同步构建或跨 Tick 构建 (`bUseAsyncBuild`)。

**如何在大型结构上避免帧卡顿？**
启用 `bUseAsyncBuild` 并调整 `InstancesPerFrame`。

**我可以在修改组件之前预览重新构建将执行的操作吗？**
可以。使用 `GetBuildPlan` 或重新构建预览路线。该计划会报告目标组件、阻塞问题、修改意图和修剪后的确切实例数。

**工具可以显示异步构建进度吗？**
可以。`GetEstimatedBuildInstanceCount`、`GetAddedBuildInstanceCount` 和 `GetBuildProgress` 为编辑器工具、Blueprint 和自动化路线公开进度。

**我在哪里报告问题或获取支持？**
使用 Fab 产品页面上的支持链接。
