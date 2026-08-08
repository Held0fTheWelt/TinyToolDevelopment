---
lang: zh
title: LightweightDummyActorSystem Troubleshooting
audience: [end_user]
owner_ref: plugin:LightweightDummyActorSystem
applies_to:
  component: LightweightDummyActorSystem
symptom: RegisterSubject fails or QueryReadiness returns a non-Ready status with issues.
recovery:
  steps:
    - Confirm the plugin is enabled under Edit > Plugins and restart the editor
    - Re-read the matching troubleshooting entry and apply the documented fix
    - Re-run the quick start smoke check
version:
  since: "1.0"
---
# 故障排除

格式：症状 → 原因 → 解决方法。

## 0. 已启用但无任何反应

**症状：** 启用 `LightweightDummyActorSystem` 并重启后，未出现任何虚拟 Actor，且没有任何 Tiny Tools 产品工作流自动运行。  
**原因：** LDAS 是一个 API/服务包。主题通过 `ULDASWorldSubsystem` 进行注册；在没有配置档案和注册调用的情况下，不会自动生成任何内容。  
**解决方法：** 创建一个 `ULDASRepresentationProfile` 数据资产，并在 [QUICKSTART.md](QUICKSTART.md) 中运行注册 + `QueryReadiness` 工作示例。

## 1. `RegisterSubject` 返回 false

**症状：** 新主题 ID 的注册失败。  
**原因：** 主题 ID 无效或重复，或者描述符/档案被子系统注册表拒绝。  
**解决方法：** 验证 `FLDASSubjectId` 字段是否完整且唯一；确认档案资产已加载；如果进行替换，请在 `UnregisterSubject` 后重试。

## 2. 就绪状态不是 Ready

**症状：** `QueryReadiness` 返回 `Warning` 或带有问题的阻塞状态。  
**原因：** 必需的就绪提供程序失败，或者策略输入（距离/冷却时间）未满足。  
**解决方法：** 检查 `FLDASReadinessReport` 中的警告/问题；调整 `ULDASRepresentationProfile` 中的距离、冷却时间或 `RequiredReadinessProviders`；在提升之前解决提供程序故障。

## 3. 提升失败时处于关闭状态

**症状：** 当 `bFailClosedOnPromotionFailure` 为 true 时，`RequestPromotion` 未推进表示。  
**原因：** 配置档案在提升失败时请求失败关闭行为。  
**解决方法：** 首先修复根本的就绪/策略故障。仅在可接受有意的软失败时，才清除 `bFailClosedOnPromotionFailure`。

## 4. 运行时提升被拒绝

**症状：** 提升请求变为空操作，而降级仍然有效。  
**原因：** 配置档案上的 `bAllowRuntimePromotion` 为 false。  
**解决方法：** 当需要运行时提升时，在 `ULDASRepresentationProfile` 上启用 `bAllowRuntimePromotion`。

## 5. 编辑器检查器未显示任何主题

**症状：** 在 PIE 或编辑器世界工作后，检查器 UI 为空。  
**原因：** 从未在该世界子系统上注册主题，或者检查了错误的上下文。  
**解决方法：** 确认注册与检查器观察到的相同 `UWorld` 一致；在地图重新加载后重新注册。

## 6. 验证命令行工具报告合同错误

**症状：** `ULDASValidateContractsCommandlet` 退出并显示发现结果。  
**原因：** 项目内容中的档案/描述符/合同不匹配。  
**解决方法：** 阅读命令行工具输出，更正指定的资产，重新运行验证。

## 7. 期望 WarCollection / Lightning / UCM 桥接

**症状：** 可选适配器 API 似乎缺失。  
**原因：** 这些桥接仅针对特定目标，不属于 MVP 1+2+3 的一部分。  
**解决方法：** 仅使用随附的核心 API。将适配器视为未来的可选集成。

## 相关文档

- [QUICKSTART.md](QUICKSTART.md)
- [UserManual.md](UserManual.md)
- [SettingsReference.md](SettingsReference.md)
- [FAQ.md](FAQ.md)
