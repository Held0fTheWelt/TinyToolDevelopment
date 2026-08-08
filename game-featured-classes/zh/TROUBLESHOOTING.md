---
lang: zh
title: GameFeaturedClasses Troubleshooting
audience: [end_user]
owner_ref: plugin:GameFeaturedClasses
applies_to:
  component: GameFeaturedClasses
symptom: Buyer expects a GameFeature workbench or featured classes that are not shipped in 1.0.1.
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

**症状：** 启用 `GameFeaturedClasses` 并重启后，未出现 Tiny Tools 菜单、新的 Content Browser 资源或工作台 UI。  
**原因：** 版本 `1.0.1` 仅包含运行时模块的框架。特色类（Featured classes）和编辑器界面尚未提供。  
**解决方法：** 确认在 **编辑 → 插件** 下已启用该插件，然后验证 `GameFeaturedClasses` 模块是否加载（参见 [QUICKSTART.md](QUICKSTART.md)）。在后续版本包发布之前，请勿期望出现产品菜单。

## 1. 寻找缺失的 GameFeature 工作台菜单

**症状：** 启用插件后，未出现 Tiny Tools / 工作台入口。  
**原因：** 版本 1.0.1 仅包含运行时模块的框架；编辑器工作台界面尚未提供。  
**解决方法：** 仅将插件用作模块边界。在后续版本包明确提供之前，请勿期望工作台 UI。

## 2. Content Browser 中无特色类

**症状：** 启用插件后，未添加游戏性类资源。  
**原因：** 该包不包含特色类或功能集内容。  
**解决方法：** 将项目类保留在您自己的模块中；将特色类的发布视为未来版本包的工作。

## 3. 插件未显示在 编辑 → 插件 下

**症状：** 搜索 `GameFeaturedClasses` 无结果。  
**原因：** 插件未复制到项目或引擎的 Plugins 文件夹中，或者描述符被过滤掉了。  
**解决方法：** 确认 `GameFeaturedClasses.uplugin` 存在于项目 `Plugins` 树（或引擎 Plugins）下，然后重启编辑器。

## 4. 在不支持的引擎上模块加载失败

**症状：** UI 中启用成功，但运行时模块在编译/加载时失败。  
**原因：** 引擎版本超出打包的 5.4–5.8 矩阵，或二进制文件不匹配。  
**解决方法：** 使用与 Fab 构建匹配的受支持引擎分支，或在该引擎上从源代码重新构建。

## 5. 期望 LightweightDummyActorSystem 或 PIO 作为硬性依赖

**症状：** 其他产品的手册暗示 GFC 需要 LDAS/UCM/PIO。  
**原因：** 这些集成是可选的目标架构，而非框架的运行时要求。  
**解决方法：** 仅启用 `GameFeaturedClasses` 以进行框架冒烟测试。仅在已发布的集成存在时，稍后添加对等组件。

## 6. 在线文档在哪里？

**症状：** Fab / 描述符 DocsURL 应解析为浏览器页面。  
**原因：** 在线着陆页位于 Fab 包之外。  
**解决方法：** 打开 `https://docs.tiny-tool-development.com/game-featured-classes/`（描述符 `DocsURL`）或使用随此插件打包的包内 `Documentation/` 集。

## 相关文档

- [QUICKSTART.md](QUICKSTART.md)
- [UserManual.md](UserManual.md)
- [FAQ.md](FAQ.md)
- [SettingsReference.md](SettingsReference.md)
