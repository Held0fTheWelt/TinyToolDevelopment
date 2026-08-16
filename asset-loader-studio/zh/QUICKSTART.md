<!-- doc-provenance: product-facts.yml reconciled 2026-07-01; source AKDB:plugins/AssetLoaderStudio/architecture.md -->
# 快速入门

## 目标

打开 Asset Loader Studio，提交运行时加载请求，检查表快照，预览受控操作，并在预览允许后应用该操作。

## 首次运行

1. 启用 **Asset Loader Studio**，并根据提示重启 Unreal Editor。
2. 打开 **Tools > Tiny Tools > Asset Loader Studio**。
3. 对于正常的首次运行，选择 **Guided** 模式。如果您仅希望进行检查，请使用 **Simple** 模式。
4. 输入已知的全对象路径（例如 `/Game/Data/DT_Items.DT_Items`）或您有权控制的 DataAsset 路径，然后单击 **Inspect**。
5. 检查返回的作业状态、已加载路径、部分失败、依赖图和诊断信息。
6. 从您有权控制的 DataAsset 或 DataTable 捕获表快照。
7. 打开 **Validation**，在尝试修改之前解决缺失资产、重复行、无效引用或权限拒绝等问题。
8. 对任何创建、复制、重命名、重新定向、修复、保存、回滚或删除操作使用 **Preview Operation**。
9. 仅当预览报告允许的配置配置文件决策、可接受的风险级别，且目标正是您打算更改的资产时，才使用 **Apply Operation**。
10. 检查应用报告，并通过您正常的 Unreal/源代码控制工作流保存脏包。

## Blueprint 和运行时入口点

- `SubmitLoadRequest` 启动运行时加载请求并返回作业状态。
- `CaptureTableSnapshot` 读取结构化表数据以进行验证和图处理。
- `PreviewOperation` 在应用之前根据权限配置文件评估计划的修改。

保持 UCM 和 MCP 集成为可选；工作区和运行时子系统是独立的首次使用路径。
