---
lang: zh
title: LightweightDummyActorSystem Quick Start
audience: [end_user]
owner_ref: plugin:LightweightDummyActorSystem
applies_to:
  component: LightweightDummyActorSystem
preconditions:
  - Unreal Engine project open with the plugin package available
  - Edit > Plugins can enable LightweightDummyActorSystem
expected_result:
  text: Subject registers through ULDASWorldSubsystem and QueryReadiness returns a readiness report.
version:
  since: "1.0"
---
# 快速入门

本指南将安装 **LightweightDummyActorSystem (LDAS)**，并演示如何使用随附的运行时 API 注册第一个可工作的主题（Subject）。MVP 1+2+3 已实现：运行时核心、转换核心、编辑器检查器以及验证命令let（Commandlet）。

## 完成本指南后您将拥有

启用插件，并通过 `ULDASWorldSubsystem::RegisterSubject` / `RegisterSubjectFromProfile` 注册一个主题，您可以检查其就绪查询（Readiness Query）。

## 要求

- Unreal Engine 5.4–5.8（打包矩阵；在模块允许列表允许的 Win64/Linux/Mac 平台上）。
- 核心包不需要其他 Tiny Tool 插件。
- 无需第三方软件、账户或外部运行时。请参阅 [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md)。

## 1. 安装并启用

1. 从 Fab 获取 **LightweightDummyActorSystem** 并将其添加到项目中。
2. 打开 **编辑 → 插件**，启用 **LightweightDummyActorSystem**，并在提示时重启。
3. 确认运行时、编辑器和 DeveloperTool 模块已加载（`LightweightDummyActorSystem`、`LightweightDummyActorSystemEditor`、`LightweightDummyActorSystemDeveloper`）。

## 2. 创建表示配置文件

1. 在 Content Browser 中，创建类为 `ULDASRepresentationProfile` 的数据资产（Data Asset）。
2. 设置基础配置文件字段，例如：

| 字段 | 示例值 | 含义 |
| --- | --- | --- |
| `PromoteDistance` | `2500.0` | 提升策略输入使用的距离阈值。 |
| `DemoteDistance` | `3000.0` | 降级策略输入使用的距离阈值。 |
| `PromotionCooldownSeconds` | `1.0` | 两次提升之间的最小秒数。 |
| `bAllowRuntimePromotion` | `true` | 允许运行时提升请求。 |
| `bFailClosedOnPromotionFailure` | `false` | 当为 true 时，提升失败将导致关闭失败。 |
| `RequiredReadinessProviders` | （空或命名提供程序） | 提升前所需的额外就绪提供程序。 |

## 3. 示例：注册和查询

从游戏代码或能够访问世界子系统的编辑器实用工具中：

```cpp
UWorld* World = /* 当前世界 */;
ULDASWorldSubsystem* LDAS = World->GetSubsystem<ULDASWorldSubsystem>();

FLDASSubjectId SubjectId;
// 填写项目绑定所需的 SubjectId 字段。

FLDASRepresentationDescriptor Descriptor;
// 填写描述符字段，或使用 RegisterSubjectFromProfile 配合数据资产。

const bool bRegistered = LDAS->RegisterSubjectFromProfile(SubjectId, ProfileAsset);
const FLDASReadinessReport Report = LDAS->QueryReadiness(
	SubjectId, ELDASRepresentationKind::Heavy /* 或根据您的意图使用 Dummy */);
```

## 预期结果

- 当主题 ID 被接受时，`bRegistered` 为 true。
- `QueryReadiness` 返回一个 `FLDASReadinessReport`，其状态为 `Ready`、`Warning` 或带有问题条目的阻塞状态——绝不会是静默的成功。

## 4. 验证契约（可选）

从编辑器/命令let 主机运行打包的验证命令let `ULDASValidateContractsCommandlet`，以检查项目的契约一致性。

## 后续步骤

- [UserManual.md](UserManual.md) — 子系统、Actor、组件、转换。
- [SettingsReference.md](SettingsReference.md) — 配置文件和组件属性。
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md) — 就绪和提升失败。
