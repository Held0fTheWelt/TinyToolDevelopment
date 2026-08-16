<!-- doc-provenance: product-facts.yml reconciled 2026-07-01; source AKDB:plugins/AssetLoaderStudio/architecture.md -->
# Asset Loader Studio 用户手册

从 **Tiny Tools -> Asset Loader Studio -> Asset Loader Studio** 打开工作区。

Asset Loader Studio 围绕一个核心审查循环构建：检查、验证、预览、应用、审计。您可以停留在检查阶段，或者在当前权限配置文件允许时继续执行受治理的编辑。

工作区包含七个视图：

- **Graph** 显示资产、行、字段、引用和诊断节点。
- **Table** 显示感知架构的 DataAsset/DataTable 行和可编辑字段。
- **Validation** 说明缺失引用、无效路径、重复 ID 和权限阻止。
- **Jobs** 显示最新的运行时加载请求状态。
- **Inspector** 显示当前模式、权限配置文件、上次预览和上次应用报告。
- **History** 保存近期工作区操作。
- **Governance** 显示当前配置文件、路由重写、审计状态和配置文件操作。

模式控制修改权限：

- **Simple** 使用只读配置文件（read-only）。
- **Guided** 允许经批准的分步安全编辑。
- **Expert** 允许更广泛的批量/持久化预览，但在应用前仍需要批准。

输入完整对象路径（例如 `/Game/Data/DT_Items.DT_Items`）后使用 **Inspect**。使用行、字段和新值输入来预览结构化字段更新。**Apply** 仅执行上次批准的预览，并将更改的包标记为未保存（dirty）以供明确保存。

## 审查循环

1. 检查源资产。
2. 检查图/表状态和诊断信息。
3. 选择符合所需权限级别的配置文件。
4. 预览操作并验证目标、计划哈希、受影响数量、风险和恢复指南。
5. 仅应用您刚刚审查过的预览。
6. 检查应用报告和审计历史。
7. 审查后手动保存已修改的包。
