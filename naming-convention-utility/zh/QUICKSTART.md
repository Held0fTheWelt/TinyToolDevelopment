<!-- doc-provenance: product-facts.yml reconciled 2026-07-04; source AKDB:plugins/NamingConventionUtility/architecture.md -->
# 快速入门指南

本指南将带您从安装一步步完成实际重命名：在预览和确认后，文件夹中的资产将根据您的命名规则进行重命名。Naming Convention Utility 可独立运行。

## 完成本指南后您将获得

复核后的命名规则、在 Naming Workbench 中完成扫描的文件夹，以及通过 Unreal 资产系统成功重命名的资产（例如 `OldWall` -> `SM_OldWall`）。

## 前提条件

- 安装了 Unreal Engine 5 编辑器，并拥有包含待重命名资产的项目。
- 无需第三方软件、账户或额外的运行时环境。请参阅 [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md)。

## 1. 安装与启用

1. 从 Fab 库将 **Naming Convention Utility** 添加到您的项目，或安装到引擎中。
2. 打开 **Edit > Plugins**，启用 **Naming Convention Utility**，并在提示时重启编辑器。

## 2. 复核规则

1. 打开 **Edit > Project Settings > Plugins > Naming Convention Utility**。
2. 核心设置是 **NamingConventionDataAssetPath**，默认指向自带的 `/NamingConventionUtility/Editor/Data/DA_NamingConvention`。
3. 打开该 DataAsset 查看自定义规则。每条规则包含 `FileTypeIdentifier`、`NamingsToRemove`、`PreFix` 和 `PostFix`。

示例：

```text
FileTypeIdentifier = FTC_STATICMESH
NamingsToRemove    = ["StaticMesh_", "Mesh_"]
PreFix             = "SM_"
PostFix            = ""
```

推荐操作：将默认 DataAsset 复制到您项目的 Content 文件夹中，并将 `NamingConventionDataAssetPath` 指向该副本。

## 3. 在 Naming Workbench 中扫描

1. 通过插件菜单，或在 Content Browser 中右键单击文件夹打开 Naming Workbench。
2. 选择预设配置：
   - **Epic Recommended**：符合 Epic 官方指南的规范。
   - **Tiny Legacy**：1.0.x 版本的默认样式。
   - **Project Custom**：配置的 DataAsset 规则。
3. 点击 **Scan**。Workbench 将显示接受的重命名项、已符合规范的资产、被忽略的资产以及规范符合率。

## 4. 应用重命名

1. 在接受的列表中找到名为 `OldWall` 的静态网格体。
2. 确认目标路径以 `SM_OldWall.SM_OldWall` 结尾。
3. 保持该行的勾选状态。
4. 可选：点击 **Export** 导出预览报告。
5. 点击 **Apply** 并确认。

预期结果：`OldWall` 变为 `SM_OldWall`；Unreal 完成重命名。请保存受影响的包文件。

## 5. 常见的排除原因

如果资产类型不受支持、没有对应的规则、名称已经符合规范、生成的名称无效，或者目标路径已存在，则该重命名将被自动忽略。

## 6. 后续步骤

- 完整工作流程和 DataTable 转换：[UserManual.md](UserManual.md)。
- 设置选项：[SettingsReference.md](SettingsReference.md)。
- 问题排查：[TROUBLESHOOTING.md](TROUBLESHOOTING.md) 和 [FAQ.md](FAQ.md)。
