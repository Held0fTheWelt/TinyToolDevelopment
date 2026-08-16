<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/LightweightEditorMode/architecture.md -->
# Lightweight Editor Mode 文档

Lightweight Editor Mode 是一款 Unreal Engine 编辑器插件，旨在让美术师、关卡设计师、技术美术和程序员在处理大型重型项目时，能够临时降低编辑器的渲染开销。它被设计为一个可逆的编辑器工作流工具：当视口表现过于沉重时开启它，继续进行编辑，完成后关闭它即可恢复到之前的编辑器状态。

本文档集具备出色的专业深度。涵盖了买家期望、日常使用、设置参考、技术行为、验证、打包和维护等内容。

## 从这里开始

- [UserManual.md](UserManual.md)：解释日常的编辑器工作流程。
- [BUYER_GUIDE.md](BUYER_GUIDE.md)：解释插件的功能和适用人群。
- [SettingsReference.md](SettingsReference.md)：列出所有公开的设置项。
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md)：帮助诊断常见的编辑器问题。
- [TechnicalOverview.md](TechnicalOverview.md)：描述运行时设计。
- [CodeDocumentation.md](CodeDocumentation.md)：将源码文件映射到具体行为。
- [PerformanceTuningReference.md](PerformanceTuningReference.md)：帮助调优配置文件。
- [ValidationAndQA.md](ValidationAndQA.md)：提供测试和发布验证步骤。
- [CompatibilityAndPackaging.md](CompatibilityAndPackaging.md)：涵盖引擎与打包注意事项。
- [FAQ.md](FAQ.md)：解答常见问题。
- [ReleaseChecklist.md](ReleaseChecklist.md)：发布前的最终检查清单。

## 插件做出的更改

开启后，Lightweight Editor Mode 可以应用以下编辑器侧的优化：

- 降低编辑器视口屏幕百分比（Screen Percentage）。
- 降低整体可伸缩性质量（Scalability Quality）。
- 禁用 Lumen 漫反射间接光照和 Lumen 反射。
- 禁用虚拟阴影贴图（Virtual Shadow Maps）。
- 禁用体积雾和常规雾。
- 强制编辑器视口进入 Unlit（无光照）视图模式。
- 禁用编辑器视口中的实时渲染（Realtime）。

具体行为取决于所选的配置文件以及 Project Settings 中可编辑的配置文件设置。

## 核心设计承诺

本插件在设计上完全保证可逆性：

- 在修改可伸缩性设置之前进行备份。
- 在设置插件值之前备份修改过的控制台变量（CVars）。
- 保存当前会话中每个视口的视图模式和实时状态。
- 保存持久的备用视图模式，以便在重启后恢复。
- 当模式被禁用或模块关闭时，恢复编辑器状态。

这使得插件非常适合快速缓解性能压力，同时保持主项目配置完好无损。

## 快速工作流

1. 在 Edit > Plugins 中启用插件。
2. 打开 Tools > Performance > Lightweight Editor Mode。
3. 选择一个配置文件：Mild、Balanced、Aggressive 或 Extreme。
4. 点击 Enable Lightweight Mode。
5. 在降低视口开销的状态下在编辑器中进行工作。
6. 在进行最终的光照、材质或捕获工作之前，点击 Disable Lightweight Mode。

## 视觉指南

Documentation/Screenshots 文件夹包含 SVG 工作流图表：

- [01-workflow-overview.svg](Screenshots/01-workflow-overview.svg)
- [02-profile-and-settings.svg](Screenshots/02-profile-and-settings.svg)
- [03-restore-flow.svg](Screenshots/03-restore-flow.svg)

这些图表是文档资源，而非运行时 UI 资源。

## 引擎支持范围

实现目标针对 Unreal Engine 5.4 风格的编辑器 API 和渲染控制台变量。最实现细节是编辑器视口并不总是可靠地遵循与游戏或 PIE 渲染相同的屏幕百分比路径，因此插件使用了特定于编辑器的屏幕百分比 CVar。

## 安全注意事项

Lightweight Editor Mode 是一个编辑器性能工具，而非打包游戏的运行时优化系统。不应将其作为最终光照、阴影、雾、材质或影视级输出的唯一验证路径。

在进行发布捕获或视觉审核之前，请禁用该模式并在预期的生产质量设置下检查场景。
