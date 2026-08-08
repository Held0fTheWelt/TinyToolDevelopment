# 常见问题解答

## GameFeaturedClasses 是否包含游戏性类？

不包含。版本 1.0.1 是一个轻量级的运行时插件外壳，包含描述符、模块边界、打包元数据、图标和更新日志。高级 GameFeature Workbench 行为由目标指定，但尚未在此包中实现。

## 是否需要其他 Tiny Tool 插件？

不需要。当前的模块外壳可独立加载。与 LightweightDummyActorSystem、Unreal Capability Mesh 或 Project Intelligence Orchestrator 的未来集成是可选的目标架构，并非此包的运行时要求。

## 支持哪些引擎版本？

打包发行矩阵针对 Unreal Engine 5.4 至 5.8（此分支上的描述符 `EngineVersion` 为 5.4.0）。

## 是否包含第三方软件或外部服务？

不包含。该包不捆绑第三方软件，也不需要账户、AI 提供商或外部运行时。请参阅 [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md)。

## 如何获取支持？

请使用 `mailto:support@tiny-tool-development.com`（描述符 `SupportURL`）或 Fab 产品页面上的支持链接。

## 为什么没有设置面板？

版本 1.0.1 未暴露任何 DeveloperSettings 或 featured-class 描述符。请参阅 [SettingsReference.md](SettingsReference.md)。

## 我可以将项目的 featured classes 放在此插件文件夹中吗？

在 1.0.1 中，作为 GFC 内容分发时不可以。请保留项目游戏性类在您自己的模块中，直到后续包明确分发 featured-class 资产。

## 如何验证外壳已加载？

启用插件，重启编辑器，并确认存在 `GameFeaturedClasses` 运行时模块。请参阅 [QUICKSTART.md](QUICKSTART.md) 中的工作示例。

## 在线文档在哪里？

https://docs.tiny-tool-development.com/game-featured-classes/
