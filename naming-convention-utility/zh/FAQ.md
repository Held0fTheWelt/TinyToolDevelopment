<!-- doc-provenance: product-facts.yml reconciled 2026-07-04; source AKDB:plugins/NamingConventionUtility/architecture.md -->
# 常见问题（FAQ）

## 该插件是真的重命名资产还是仅生成报告？

在您确认后，它会通过 `IAssetTools::RenameAssets` 真实地对资产进行重命名。

## 它会重命名文件夹吗？

不会。它只扫描文件夹并重命名其中的资产。

## 我可以在应用更改前进行预览吗？

可以。Workbench 会创建详细的重命名计划，并允许在应用之前导出报告。

## 如果两个资产重命名后名称相同会怎样？

冲突的两项都会自动从计划中排除，以防止覆盖。

## 它能识别纹理子类型吗？

可以，部分通过压缩格式和常见关键字（如 `normal`、`roughness`、`metallic` 等）进行识别。

## 它会修改 Blueprint 类的内部名称吗？

它重命名资产文件/包，不会重写内部代码。

## 我可以从电子表格导入规则吗？

可以，通过导入兼容的 DataTable 并使用内置的转换功能即可。

## 它会生成报告吗？

会，JSON 和 Markdown 格式的报告保存在 `Saved/NamingConventionUtility/Reports/` 下。

## 它会自动修复重定向器吗？

会，如果已启用该选项，在重命名后会自动执行重定向器修复步骤。
