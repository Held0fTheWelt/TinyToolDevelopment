<!-- doc-provenance: product-facts.yml reconciled 2026-07-01; source AKDB:plugins/AssetLoaderStudio/architecture.md -->
# 故障排除

## 缺失资产

使用带有对象后缀的完整对象路径，例如 `/Game/Data/DA_Item.DA_Item`。如果验证报告 `ALS.Table.MissingReferencedAsset`，请将该字段重定向到现有资产或将其清空。

## 错误路径

`ALS.InvalidSoftObjectPath` 和 `ALS.Table.InvalidReferencePath` 表示该路径无法解析为 Unreal 对象路径。请从内容浏览器（Content Browser）中重新复制引用。

## 应用失败

应用操作需要经允许的预览和批准令牌。在编辑器工作区中，Apply 按钮会批准上次预览。在自动化流程中，请将 `approval_token` 设置为预览 ID 或 `approved`。

## 权限拒绝

使用 `asset_loader_studio.state.read.v1` 检查当前活跃的配置文件。常见的拒绝原因为只读模式、仅试运行模式、受影响行/资产限制、超出 `allowed_roots` 的根目录，或缺少破坏性权限。

## 保存失败

通用应用操作会将包标记为未保存（dirty）并返回恢复指南。在审查修改后的资产后，通过 Unreal 编辑器保存提示或源代码控制工作流进行保存。

## 空行或重复行

包含空或重复行 ID 的 DataTable 无法安全映射到稳定的行操作。请在所属表格中重命名或修复这些行，然后重新截取快照。

## 破坏性操作被阻止

删除和其他破坏性操作需要允许它们的配置文件以及显式的破坏性批准令牌。建议先预览计划，保存备份或源代码控制状态，然后仅应用经过审查的预览。
