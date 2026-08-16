<!-- doc-provenance: product-facts.yml reconciled 2026-07-04; source AKDB:plugins/NamingConventionUtility/architecture.md -->
# 故障排除

## 上下文菜单未出现

请检查：

- 插件已启用。
- 编辑器已重启。
- 您在 Content Browser 的文件夹上右键单击。

## 工具显示不会重命名任何资产

可能的原因：

- 所有资产均已符合命名规范。
- 资产类型不受支持。
- 配置的 DataAsset 为空。
- 生成的名称无效。

## Workbench 提示计划已过期（Stale）

扫描后发生了更改（切换了文件夹、修改了规则等）。请重新点击 **Scan**。

## 无法修改内置预设

`epic_recommended` 和 `tiny_legacy` 为只读预设。请使用 **Copy to Project** 将规则复制到您的自定义预设中。

## 纹理资产获得了通用的 `T_` 前缀

子类型的自动检测基于启发式规则。如果名称中的关键字不够明确，将应用通用规则。

## 确认后重命名失败

常见原因：

- 存在引用关系。
- 版本控制锁定问题。
- 包文件只读或被锁定。

请检查输出日志（Output Log）。

## 获取支持时需提供的各种信息

- Unreal Engine 版本。
- 插件版本。
- 选定文件夹路径。
- 配置的 DataAsset 路径。
