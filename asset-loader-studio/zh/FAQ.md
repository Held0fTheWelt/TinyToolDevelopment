<!-- doc-provenance: product-facts.yml reconciled 2026-07-01; source AKDB:plugins/AssetLoaderStudio/architecture.md -->
# 常见问题

## Asset Loader Studio 是独立的吗？

是的。编辑器工作区、运行时子系统、Blueprint 库、示例、治理配置文件和买家文档均可在无需 UCM、UMCP、MCP 或其他 Tiny Tool 插件的情况下独立工作。

## 它会替换 Unreal 的 Asset Manager 吗？

不会。它构建于 Unreal 资产路径、主资产 ID、表格、包和 Asset Registry 之上。它增加了结构化加载作业、诊断、表格快照、依赖图、预览和治理功能。

## 它能修改项目资产吗？

可以，但修改遵循预览优先原则。创建、复制、重命名、重定向（retarget）、修复、保存、回滚和删除操作必须通过权限配置文件检查，并在应用前予以审查。

## 审计记录存储在哪里？

默认审计目录为 `Saved/AssetLoaderStudio/Audit`。该路径可通过治理设置进行调整。

## 自动化路由是必需的吗？

不是。可选的 UCM/MCP 文件为受治理的自动化公开了相同的服务，但核心产品在没有它们的情况下依然可用。

## Asset Loader Studio 在 Fab 上上线了吗？

当前的包状态为 "In Publishment"（发布中）。在 Fab 门户页面本身正式发布之前，请将其视为已准备好进行 Fab 交付但尚未上线的状态。
