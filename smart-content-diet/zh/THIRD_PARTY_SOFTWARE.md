<!-- doc-provenance: AKDB:plugins/SmartContentDiet/architecture.md; docs/architecture/plugins/SmartContentDiet/product-facts.yml; reconciled 2026-07-16 -->
# 第三方软件

Smart Content Diet **未捆绑第三方源代码、运行时二进制文件、AI 模型、Node.js、Python 或独立可执行文件**。它是一个 C++ Unreal Engine 编辑器插件，仅使用 Unreal Engine 模块和标准 Unreal API（资产注册表、资产分析、编辑器 UI、Commandlet）。

核心扫描 → 审查 → 安全修复循环完全在编辑器内部运行，**无需 AI 服务，也无需外部工具**。可选的跨插件生态系统路由（通过 **Unreal Capability Mesh (UCM)**）通过 JSON 声明，不会向此软件包添加任何第三方软件。

安装或使用该插件不需要外部软件、帐户或运行时。

**Fab 第三方软件声明：** 未捆绑第三方软件。
