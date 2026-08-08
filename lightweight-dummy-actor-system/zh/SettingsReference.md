---
lang: zh
title: LightweightDummyActorSystem Settings Reference
audience: [end_user]
owner_ref: plugin:LightweightDummyActorSystem
applies_to:
  component: LightweightDummyActorSystem
contract_ref: plugin:LightweightDummyActorSystem/profile-properties
version:
  since: "1.0"
---
# 设置参考

`LightweightDummyActorSystem` **不**提供 `UDeveloperSettings` / 项目首选项对象。可配置的值位于数据资产、组件和结构体中，如下所列（基于公共头文件）。

## ULDASRepresentationProfile (`UDataAsset`)

| 名称 | 类型 | 默认值 | 效果 |
| --- | --- | --- | --- |
| `Descriptor` | `FLDASRepresentationDescriptor` | 空 | 应用于主题记录的基础表示描述符。 |
| `PromoteDistance` | `float` | `0.0` | 提升策略使用的距离输入。 |
| `DemoteDistance` | `float` | `0.0` | 降级策略使用的距离输入。 |
| `PromotionCooldownSeconds` | `float` | `1.0` | 提升之间的冷却时间。 |
| `bAllowRuntimePromotion` | `bool` | `true` | 当为 false 时，配置文件禁止运行时提升请求。 |
| `bFailClosedOnPromotionFailure` | `bool` | `false` | 当为 true 时，提升失败将导致关闭失败。 |
| `RequiredReadinessProviders` | `TArray<FName>` | 空 | 必须满足的命名就绪提供程序。 |

## ULDASDummyActorComponent

| 名称 | 类型 | 默认值 | 效果 |
| --- | --- | --- | --- |
| Profile / 主题绑定字段 | editanywhere 组件属性 | 调用者设置 | 将组件绑定到 LDAS 主题表示。 |
| 复制快照 | 复制属性 | 运行时 | 携带带有 `OnRep` 通知的快照状态。 |

## ALDASLightweightDummyActor

| 名称 | 类型 | 默认值 | 效果 |
| --- | --- | --- | --- |
| 可见组件 | 组件引用 | 已构造 | 场景/调试表示组件。 |
| LDAS 绑定字段 | editanywhere | 调用者设置 | 将 Actor 链接到 LDAS 主题数据。 |

## FLDASTransitionRecord / 快照结构体

过渡和快照结构体公开了用于主题 ID、表示类型、时间戳和就绪问题列表的 editanywhere 字段。将它们视为数据契约而非全局设置；默认值位于 `Public/Structs/` 下的头文件中的结构体默认值。

## 不存在的内容

| 表面 | 状态 |
| --- | --- |
| `ULDASDeveloperSettings` | 尚不可用 |
| `Config/DefaultLightweightDummyActorSystem.ini` 设置对象 | 未作为买家设置面板提供 |
| WarCollection / Lightning / UCM 桥接设置 | 仅目标可选适配器 |

## 相关文档

- [UserManual.md](UserManual.md)
- [QUICKSTART.md](QUICKSTART.md)
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md)
