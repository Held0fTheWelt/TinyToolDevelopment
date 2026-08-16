<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/LightweightEditorMode/architecture.md -->
# 故障排除

本指南涵盖常见问题及其可能的原因。

## 插件窗口缺失

检查以下各项：

- 插件已在 Edit > Plugins 中启用。
- 启用插件后重启了项目。
- 模块列在 .uproject 的 Plugins 数组中。
- 您运行的是编辑器，而不是 commandlet。

窗口应出现在 Tools > Performance > Lightweight Editor Mode 下。

## 模式未在启动时启用

启动启用会一直等待，直到存在编辑器视口客户端。在较慢的项目中，这可能在模块启动后需要片刻时间。

检查：

- Enable on Editor startup 已勾选。
- 插件已在项目中启用。
- 编辑器确实创建了关卡编辑器视口。
- 日志包含 "Scheduling Lightweight Mode auto-enable"。
- 日志随后包含 "Auto-enabling Lightweight Mode after editor viewports became available"。

如果在视口可用之前取消勾选该设置，定时器会自动取消。

## 屏幕百分比似乎没有变化

编辑器视口并不总是遵从 r.ScreenPercentage。Lightweight Editor Mode 使用特定于编辑器视口的 CVar：

- r.Editor.Viewport.ScreenPercentage
- r.Editor.Viewport.ScreenPercentageMode.RealTime
- r.Editor.Viewport.ScreenPercentageMode.NonRealTime

如果视口看起来仍没有变化，请检查：

- 所选配置文件的 ScreenPercentage 值。
- 视口是否使用了覆盖屏幕百分比的引擎路径。
- 是否有其他插件或控制台命令在 Lightweight Editor Mode 运行后更改了相同的编辑器 CVar。

## 禁用后视口保持 Unlit 状态

同会话恢复使用每个视口的备份。重启恢复只有保存的 LastViewModeBeforeLightweight 值。

尝试：

1. 打开插件窗口。
2. 点击 Disable Lightweight Mode。
3. 如果需要，手动将视口切换回 Lit。
4. 在同一会话中重新启用并禁用该模式，以确认正常恢复。

如果经常发生这种情况，请检查是否在模式仍启用的情况下关闭了编辑器。

崩溃或强制关闭后，主按钮可能会显示 Restore Lightweight State。点击它以运行保守的视口恢复并清除旧会话标记。

## 实时渲染保持禁用

实时禁用使用 Unreal 的临时实时重写系统。在同一个编辑器会话中，Disable 会移除 Lightweight 的重写，而不是更改视口保存的实时偏好设置。

如果实时渲染看起来仍然禁用，请检查是否有另一个编辑器系统激活了自己的实时重写。需要时从视口菜单手动重新启用实时渲染。

## Lumen 看起来仍处于启用状态

检查：

- 所选配置文件是否启用了 bDisableLumen。
- 项目是否确实在使用 Lumen。
- 在模式启用后，是否有其他插件或项目代码设置了 Lumen CVar。
- 自定义引擎分支是否重命名或删除了相关的 CVar。

插件针对：

- r.Lumen.DiffuseIndirect.Allow
- r.Lumen.Reflections.Allow

缺失的 CVar 会被跳过并在日志中记录为 Verbose 级别。

## 阴影看起来仍然开销很大

bDisableVirtualShadows 针对虚拟阴影贴图（Virtual Shadow Maps）：

- r.Shadow.Virtual.Enable

这并不能消除每个渲染器路径中所有可能的阴影开销。如果您的场景使用非虚拟阴影、自定义阴影系统、光线追踪阴影或插件渲染，可能需要额外的项目特定调优。

## 雾效果依然存在

bDisableVolumetricFog 设置：

- r.VolumetricFog = 0
- r.Fog = 0

某些材质、后期处理体积、天空系统或自定义大气效果可能仍会产生类似雾的外观。

## 编辑器画面质量看起来过低

使用不太激进的配置文件：

- 将 Extreme 切换为 Aggressive。
- 将 Aggressive 切换为 Balanced。
- 提高 ScreenPercentage。
- 提高 OverallQuality。
- 针对自定义配置文件禁用 Force Unlit。

在模式启用的情况下更改配置文件后，助手会自动刷新活动设置。

## 编辑器仍然很慢

Lightweight Editor Mode 专门解决编辑器视口渲染开销。它无法解决所有的编辑器性能问题。

其他可能的瓶颈：

- 资产编译。
- Shader 编译。
- 版本控制操作（Source Control）。
- Blueprint 的 Construction Script。
- Editor Utility Widget。
- 编辑器关卡中重型的 Tick 逻辑。
- 海量的 Actor 数量。
- 磁盘或杀毒软件开销。

使用 Unreal Insights、Stat 命令和常规的项目性能分析来诊断非渲染瓶颈。

## Disable 未恢复某个 CVar

恢复路径会移除插件标记的重写。如果在 Lightweight Editor Mode 激活期间有另一个系统更改了相同的 CVar，则该更新的值保持激活，而不是被旧备份覆盖。

检查输出日志中的 CVar 名称。插件会记录备份和恢复操作。

## Project Settings 页面隐藏或缺失

设置页面应出现在 Project Settings > Plugins > Lightweight Editor Mode 下。

如果缺失：

- 确认模块已加载。
- 确认 Settings 模块可用。
- 启用插件后重启编辑器。
- 检查是否有插件描述符或构建问题阻止了模块加载。

## 添加新的 CVar 后构建失败

常见原因：

- 添加了 CVar 名称常量但未一致使用。
- 设置已添加到配置文件结构体，但未添加到活动字段。
- 未针对新的配置文件更新 UI 的 switch 语句。
- 缺少 Unreal 类型的 include。
- UPROPERTY 元数据块内部的语法错误。

在更改源码后运行编辑器目标构建。

## 要检查的日志

在 Output Log 中搜索：

- [Module]
- [Lightweight]
- Backup CVar
- Restore CVar
- ApplyActiveSettings
- ApplyViewportSettings
- Lightweight mode ENABLED
- Lightweight mode DISABLED

日志设计得非常清晰明确，因此技术支持请求可以包含相关的日志序列。
