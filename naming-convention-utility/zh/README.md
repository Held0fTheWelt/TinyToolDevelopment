<!-- doc-provenance: product-facts.yml reconciled 2026-07-04; source AKDB:plugins/NamingConventionUtility/architecture.md -->
# Naming Convention Utility 文档

Naming Convention Utility 是一款 Unreal Engine 编辑器插件，旨在为 Content Browser 中选定文件夹下的资产批量应用一致的前缀和后缀。它可以识别资产类型、构建重命名计划、验证目标名称、在可停靠的 Naming Workbench（重命名工作台）中预览计划更改，并通过编辑器资产工具对选定的 Unreal 资产执行实际重命名。

本文件夹包含随插件附带的完整文档。

## 从这里开始

- [BUYER_GUIDE.md](BUYER_GUIDE.md)：买家概述、使用场景和适用性。
- [QUICKSTART.md](QUICKSTART.md)：从安装到完成重命名的快速指南。
- [UserManual.md](UserManual.md)：关于配置、扫描、编辑、报告和应用规范的完整工作流程。
- [FAQ.md](FAQ.md)：针对 Fab 的常见问题与解答。

## 参考指南

- [SettingsReference.md](SettingsReference.md)：设置项、DataAsset 字段和推荐配置。
- [TechnicalOverview.md](TechnicalOverview.md)：维护者的架构和安全模型。
- [CodeDocumentation.md](CodeDocumentation.md)：代码结构、契约和扩展点。
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md)：常见问题及解决方案。
- [ReleaseChecklist.md](ReleaseChecklist.md)：发布前的验证清单。

## 包含的资源

- `../Readme.pdf`：传统的自述文件。
- `../Content/Editor/Data/DA_NamingConvention.uasset`：默认命名规范 DataAsset。
- `../Content/Editor/Data/DT_NamingConvention.uasset`：示例/数据源 DataTable。
- `../Resources/NamingConvention.csv`：CSV 导入参考。
- `../Resources/NamingConvention.json`：JSON 导入参考。
- `../Resources/NamingConvention_EpicRecommended.csv`：Epic 推荐规范导入参考。
- `../Resources/NamingConvention_TinyLegacy.csv`：1.0.x 兼容规范导入参考。
- `../Resources/FileTypeValues.txt`：文件类型枚举参考。
- `../Resources/ToolTypeValues.txt`：DataTable 工具类型参考。

## 快速工作流程

1. 启用插件，必要时重启编辑器。
2. 打开 Project Settings，检查配置的命名规范 DataAsset。
3. 通过插件菜单或文件夹上下文菜单打开 Naming Workbench。
4. 选择 **Epic Recommended**、**Tiny Legacy** 或 **Project Custom** 预设。
5. 扫描文件夹，查看符合率、排除原因和目标路径。
6. 选择要应用的已接受行，导出报告或在复核后应用。
7. Unreal 完成重命名操作后，保存受影响的资产/包。

## 安全模型

插件将重命名操作视为高风险操作。在调用 Unreal 的重命名工具之前，它会构建计划并排除有风险的项。

计划检查项包括：

- 不支持的资产类型。
- 缺失对应规范规则。
- 生成的名称为空或无效。
- 无效的目标对象路径。
- 目标资产已存在。
- 磁盘上已存在目标包文件。
- 同一批次中目标路径重复。
- 因重叠文件夹选择导致的源资产重复。

Workbench 会在应用计划前显示预览，使用经过核对的计划哈希保护应用过程，并在 `Saved/NamingConventionUtility/Reports/` 下写入 JSON/Markdown 报告。

## 本工具修改的内容

插件通过 `IAssetTools::RenameAssets` 重命名 Unreal 资产。

它不会执行以下操作：

- 在资产系统之外重命名原始文件。
- 修改导入的源文件。
- 修改 C++ 类名。
- 修改生成代码中的 Blueprint 类名。
- 代替您决定工作室的命名策略。

## 默认命名系列

默认 DataAsset 包含常见的 Unreal 前缀，例如：

- 纹理：`T_`, `T_N_`, `T_D_`
- 材质：`M_`, `MI_`, `MF_`
- 静态网格与骨骼：`SM_`, `SK_`, `SKEL_`
- Blueprint 与控件：`BP_`, `BPI_`, `BPF_`, `WB_`
- 特效：`NS_`, `NE_`, `PS_`
- 数据与曲线：`DT_`, `CT_`, `CF_`, `CV_`, `CLC_`

Workbench 还包含：

- `epic_recommended`：符合 Epic 官方指南的前缀。
- `tiny_legacy`：兼容 1.0.x 的默认样式。
- `project_custom`：存储在 DataAsset 中的自定义规则。

您可以根据规范修改或替换 DataAsset。Workbench 还可以将内置预设复制到项目的 DataAsset 中。

## 重要限制

- 纹理子类型的自动识别结合了压缩设置和命名关键字。
- 无法识别的资产类型将被忽略。
- 由于引用、版本控制或文件锁定，Unreal 可能会弹出提示框或重命名失败。
- 批量重命名大型文件夹前，请务必仔细检查预览。

## 法律声明

Naming Convention Utility 是一款生产力工具。它有助于执行命名规范，但不能保证某套规范适用于所有工作室或管线。
