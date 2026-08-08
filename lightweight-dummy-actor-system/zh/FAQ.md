# 常见问题解答

## LightweightDummyActorSystem 的作用是什么？

它为虚拟 Actor 工作流提供运行时表示服务，包括主题注册、虚拟 Actor 表示、提升与降级转换、诊断、编辑器检查器以及验证命令let。

## 是否可以在不使用其他 Tiny Tool 插件的情况下使用？

可以。Runtime、Editor 和 DeveloperTool 模块作为核心包实现。WarCollection、LightningCore、UCM、PIO 和 BPJ 适配器是可选的、针对特定目标的集成组件，对于已发布的核心行为并非必需。

## 支持哪些引擎版本？

打包发布矩阵针对 Win64、Linux 和 Mac 平台上的 Unreal Engine 5.4 至 5.8 版本，前提是模块允许列表允许这些平台。

## 它是否会自行修改项目资产？

不会。核心服务负责管理表示和转换状态。任何项目特定的修改或适配器行为应在所属项目工作流中进行审查。

## 如何获取支持？

请使用 Fab 产品页面上的支持链接。
