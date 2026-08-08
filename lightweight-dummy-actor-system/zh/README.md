# LightweightDummyActorSystem 文档

LightweightDummyActorSystem (LDAS) 是用于虚拟 Actor 工作流的自主运行时表示服务。MVP 1+2+3 版本包含 Runtime、Editor 和 DeveloperTool 模块：主题注册、就绪状态查询、晋升/降级策略门控、虚拟 Actor 表示、诊断、编辑器检查器以及验证命令let。

目标受众：需要轻量级虚拟表示且具备策略门控的晋升/降级功能，但无需为核心包依赖对等 Tiny Tool 插件的游戏玩法和工具工程师。

## 功能（已发布）

- `RegisterSubject` / `RegisterSubjectFromProfile` / `UnregisterSubject`
- `QueryReadiness` → `FLDASReadinessReport`
- `RequestPromotion` / `RequestDemotion`
- `ULDASRepresentationProfile`、`ALDASLightweightDummyActor`、`ULDASDummyActorComponent`
- 编辑器检查器与 `ULDASValidateContractsCommandlet`

## 入门指南

1. 启用插件——请参阅 [QUICKSTART.md](QUICKSTART.md) 中的操作示例（注册 + 查询就绪状态）。
2. 使用真实的距离/冷却值配置 `ULDASRepresentationProfile` 数据资产。
3. 阅读 [UserManual.md](UserManual.md) 和 [SettingsReference.md](SettingsReference.md)。

## 相关文件

- [../README.md](../README.md) — 产品概述。
- [../CHANGELOG.md](../CHANGELOG.md) — 发布历史。
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md) · [FAQ.md](FAQ.md) · [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md)
