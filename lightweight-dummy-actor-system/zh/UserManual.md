# 用户手册

LightweightDummyActorSystem (LDAS) 是用于虚拟 Actor 工作流的自主运行时表示服务。MVP 1+2+3 版本包含 Runtime、Editor 和 DeveloperTool 模块。

## 已实现的功能

| 功能 | 主要类型 |
| --- | --- |
| 主体注册 | `ULDASWorldSubsystem::RegisterSubject`、`RegisterSubjectFromProfile`、`UnregisterSubject` |
| 就绪查询 | `QueryReadiness` → `FLDASReadinessReport` |
| 提升 / 降级 | `RequestPromotion`、`RequestDemotion`，附带 `ELDASTransitionReason` |
| 虚拟表示 | `ALDASLightweightDummyActor`、`ULDASDummyActorComponent` |
| 配置文件资产 | `ULDASRepresentationProfile` |
| 诊断 | `ULDASDiagnosticsSubsystem` |
| 编辑器检查器 | `SLDASRepresentationInspector` |
| 验证 | `FLDASEditorValidationService`、`ULDASValidateContractsCommandlet` |

<!-- image slot: ldas-inspector -->

## 运行时流程

1. 从世界系统中获取 `ULDASWorldSubsystem`。
2. 使用描述符或 `ULDASRepresentationProfile` 注册主体。
3. 查询所需表示类型的就绪状态。
4. 当策略和就绪状态允许时，请求提升或降级。
5. 在排查故障时，检查诊断信息或编辑器检查器。

提升和降级受策略控制。内置提供程序（`ULDASBuiltInReadinessProvider`、`ULDASBuiltInPromotionPolicy`、`ULDASBuiltInHeavyActorAdapter`）提供默认行为；项目可以在支持的构建中注册额外的提供程序。

## 编辑器界面

- 已注册主体的表示检查器。
- 用于合约检查的编辑器验证服务。
- 用于离线验证运行的开发者命令工具。

## 自治性与可选集成

核心 Runtime / Editor / DeveloperTool 模块无需对等 Tiny Tool 插件即可工作。以下功能仅针对目标平台，且在缺失时必须优雅降级：

- WarCollection 只读试点适配器
- 多人游戏试点证明
- LightningCore 实体桥接
- UCM / PIO / BPJ 自动化桥接

请勿将这些适配器视为已交付核心功能的设置要求。

## 相关文档

- [QUICKSTART.md](QUICKSTART.md)
- [SettingsReference.md](SettingsReference.md)
- [FAQ.md](FAQ.md)
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md)
- [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md)
