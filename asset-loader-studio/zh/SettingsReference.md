<!-- doc-provenance: product-facts.yml reconciled 2026-07-01; source AKDB:plugins/AssetLoaderStudio/architecture.md -->
# 设置参考

Asset Loader Studio 设置围绕治理配置文件、允许的根目录/类、审计策略和路由重写展开。

## 治理设置

| 设置 | 类型 | 默认值 | 作用 |
| --- | --- | --- | --- |
| `DefaultProfileId` | string | `guided_safe` | 当未提供路由或请求配置文件时，选择默认权限配置文件。 |
| `ProfileDirectories` | array | `Config/AssetLoaderStudio/Governance/Profiles` | 列出扫描权限配置文件 JSON 的文件夹。 |
| `AllowedRoots` | array | `/Game`, `/Engine` | 将修改目标限制为批准的 Unreal 根目录。 |
| `AllowedClasses` | array | 包默认值 | 配置时将修改目标限制为批准的类路径。 |
| `AuditRetentionDays` | integer | `30` | 控制审计日志在清理前保留的天数。 |
| `AuditLogDirectory` | string | `Saved/AssetLoaderStudio/Audit` | 存储预览和应用操作的持久化审计条目。 |
| `bAuditPreviewOperations` | boolean | `true` | 为操作预览写入审计条目。 |
| `bAuditApplyOperations` | boolean | `true` | 为应用操作写入审计条目。 |

## 权限配置文件字段

权限配置文件定义 `profile_id`、允许的操作、最大受影响资产/行数、允许的根目录/类、只读模式、试运行（dry-run）模式、应用确认、破坏性批准和审计保留。使用 `read_only` 进行检查，`guided_safe` 进行日常审核编辑，仅对可信批量工作使用 `expert`。

## 路由重写

可选的路由重写可以将 UCM 路由映射到更严格或更宽松的配置文件。路由重写不会替换本地预览/应用检查；它们仅选择这些检查所使用的配置文件。

## 实用默认值

- 从 `guided_safe` 开始进行经过审查的编辑器工作。
- 保持 `read_only` 用于探测、验证、表格导出以及不应修改资产的自动化检查。
- 仅对可信批量工作使用 `expert`，并保持破坏性批准显式化。
- 保持足够的审计保留期，以覆盖常规的发布审查窗口。
