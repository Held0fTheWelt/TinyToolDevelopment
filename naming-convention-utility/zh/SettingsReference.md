<!-- doc-provenance: product-facts.yml reconciled 2026-07-04; source AKDB:plugins/NamingConventionUtility/architecture.md -->
# 设置参考

Naming Convention Utility 在 `UNamingConventionUtility_Settings` 中保存项目级设置。

## 设置对象

源文件：

```text
Source/NamingConventionUtility/Public/NamingConventionUtility_Settings.h
```

编辑器位置：

```text
Edit > Project Settings > Plugins > Naming Convention Utility
```

## NamingConventionDataAssetPath

类型：

```text
FSoftObjectPath
```

默认值：

```text
/NamingConventionUtility/Editor/Data/DA_NamingConvention.DA_NamingConvention
```

用途：

- 指向包含重命名规则的 DataAsset。
- 用于文件夹重命名工作流。
- 作为 DataTable 转换的目标。

## bConfirmBeforeApplyingConventions

默认值：

```text
true
```

用途：

- 在应用批量重命名之前显示预览并提示确认。

## bFixRedirectorsAfterRename

默认值：

```text
true
```

用途：

- 尝试在重命名后自动修复选定文件夹中的重定向器。

## DataAsset: NamingConventions

每条条目定义针对某个 `EFileTypeIdentifier` 的规则。

字段：

- `FileTypeIdentifier`：目标资产类型。
- `NamingsToRemove`：要移除的旧文本片段。
- `PreFix`：要添加的前缀。
- `PostFix`：要添加的后缀。

## Workbench 预设

Workbench 提供了三个选项：

- `epic_recommended`：符合 Epic 指南的只读规则。
- `tiny_legacy`：兼容 1.0.x 的只读规则。
- `project_custom`：在 `NamingConventionDataAssetPath` 中指定的自定义文件。

## 报告

生成于：

```text
Saved/NamingConventionUtility/Reports/
```
