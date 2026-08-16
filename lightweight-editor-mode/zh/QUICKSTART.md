<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/LightweightEditorMode/architecture.md -->
# 快速入门

本指南将带您从安装一步步实现**直观的效果**：获得一个响应更快、运行更流畅的编辑器视口，且支持一键完全恢复。Lightweight Editor Mode 独立运行，无需安装其他插件。

## 完成本指南后您将获得

开启可逆的“轻量化”编辑配置文件（更流畅的视口），并掌握按需切换配置文件和恢复原始编辑器状态的操作方法。

## 要求

- Unreal Engine 5 编辑器（本插件仅影响编辑器视口，绝不影响打包后的游戏运行时）。
- 无需第三方软件、账号或运行时，详见 [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md)。

## 1. 安装并启用

1. 从 Fab 库将 **Lightweight Editor Mode** 添加到项目中（或安装到引擎中）。
2. 打开 **Edit → Plugins**，启用 **Lightweight Editor Mode**，并在提示时重启编辑器。

## 2. 打开工具（初次效果）

1. 打开 **Tools → Performance → Lightweight Editor Mode**。此时将打开一个可停靠的选项卡，其中包含配置文件下拉菜单、切换按钮和 *Enable on Editor startup* 复选框。
2. 选择 **Balanced** 配置文件（推荐的默认选项）。
3. 点击 **Enable Lightweight Mode**。

**预期输出：** 视口立即更新 — Balanced 模式降低了屏幕百分比和可伸缩性，禁用了高开销光照，并强制使用 Unlit（无光照）/ 非实时模式。编辑器响应速度立刻得到提升。

## 3. 实际操作示例：切换配置文件并恢复

1. 在模式启用的情况下，将配置文件下拉菜单更改为 **Aggressive**。视口将刷新为更激进的设置（更低的屏幕百分比、低可伸缩性、无高开销阴影/雾）。开启前的原始状态依然会被完整保留。
2. 点击 **Disable Lightweight Mode**。

**预期输出：** 编辑器恢复您备份的可伸缩性级别、控制台变量重写、视口视图模式和实时状态 — 完全回到初始状态。

> 配置文件专为响应速度优化，而非画面精细度，因此开启时视口分辨率较低、无光照且阴影较少。**在进行光照检查或截屏前，请务必禁用该模式。**

## 4. 自定义配置文件

打开 **Project Settings → Plugins → Lightweight Editor Mode**，可编辑 Mild / Balanced / Aggressive / Extreme 各配置文件的数据。所选配置文件将在应用模式前复制到活动值中。详见 [PerformanceTuningReference.md](PerformanceTuningReference.md)。

## 5. 可选：启动时自动启用

勾选 **Enable on Editor startup**，以便在下次启动且编辑器视口创建完成后自动开启该模式。

## 6. 后续步骤

- 完整配置文件行为及推荐工作流：[UserManual.md](UserManual.md)。
- 所有设置参考：[SettingsReference.md](SettingsReference.md)。
- 常见问题（如重启后状态未更新 → *Restore Lightweight State*）：
  [TROUBLESHOOTING.md](TROUBLESHOOTING.md) 与 [FAQ.md](FAQ.md)。
