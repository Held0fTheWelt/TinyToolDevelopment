<!-- doc-provenance: product-facts.yml reconciled 2026-07-04; source AKDB:plugins/NamingConventionUtility/architecture.md -->
# 用户手册

本手册说明如何在 Unreal Editor 中配置和使用 Naming Convention Utility。

## 安装

1. 将插件添加到项目的 `Plugins` 文件夹中，或通过 Fab 安装。
2. 在 **Edit > Plugins** 中启用 **Naming Convention Utility**。
3. 如果提示，请重启编辑器。

## 配置 DataAsset

打开 **Edit > Project Settings > Plugins > Naming Convention Utility**。

关键设置项：

```text
NamingConventionDataAssetPath
```

默认值：

```text
/NamingConventionUtility/Editor/Data/DA_NamingConvention.DA_NamingConvention
```

您可以：

- 使用默认资产。
- 复制到项目中进行修改。
- 调整前缀与后缀。
- 从 Workbench 将内置预设复制到 DataAsset。
- 将兼容的 DataTable 转换为 DataAsset。

## 规则字段

每条规则包含：

- `FileTypeIdentifier`：目标 Unreal 资产类别。
- `NamingsToRemove`：添加前缀/后缀前要移除的字符串。
- `PreFix`：添加的前缀。
- `PostFix`：添加的后缀。

示例：

```text
FileTypeIdentifier = FTC_STATICMESH
NamingsToRemove = ["StaticMesh_", "Mesh_"]
PreFix = "SM_"
PostFix = ""
```

`OldWall` 将重命名为 `SM_OldWall`。

## Naming Workbench

Naming Workbench 是用于复核、编辑和应用规则的主界面。

功能包括：

- 选择文件夹。
- 选择 `epic_recommended`、`tiny_legacy` 或 `project_custom`。
- 递归扫描资产。
- 查看接受、合规或被忽略的行。
- 检查目标路径。
- 导出 JSON/Markdown 格式的报告。
- 通过计划哈希安全地应用修改。

## Content Browser 快捷操作

文件夹上下文菜单依然可用：

1. 右键单击文件夹。
2. 选择 **Apply Naming Conventions**。
3. 查看预览对话框。
4. 确认应用。
5. 保存受影响的包。

## 预览与排除原因

预览摘要包含：

- 扫描的资产总数。
- 计划重命名的数量。
- 忽略的资产数量。
- 新旧名称对照。
- 排除原因。

## 审计报告

导出和应用操作会在以下路径生成报告：

```text
Saved/NamingConventionUtility/Reports/
```

## DataTable 转换

插件可以将兼容的 DataTable 转换为配置的 DataAsset。

期望的行结构：

```text
FNamingConventionTableInformation
```

字段：

- `FileType`
- `ToolType`
- `Value`

## 纹理子类型检测

使用 `TC_Normalmap` 压缩格式和常见的名称关键字（如 `normal`、`albedo`、`roughness`、`metallic` 等）进行识别。

## 撤销与版本控制

资产重命名会影响包和引用关系。请先在小文件夹中测试，检查重定向器（redirectors），并保存修改后的包。

## 卸载插件

卸载插件前：

1. 完成或取消未完成的操作。
2. 保存所有包。
3. 禁用插件并重启编辑器。
