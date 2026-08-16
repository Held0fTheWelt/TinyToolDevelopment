<!-- doc-provenance: product-facts.yml reconciled 2026-07-19; source AKDB:plugins/BestPracticesJournal/architecture.md; release 1.1.2 -->
# 设置参考

BPJ 设置决定了项目本地实践工件的存放位置以及可选存储投影的行为方式。

| 设置项 | 类型 | 默认值 | 效果 |
| --- | --- | --- | --- |
| `StorageBackend` | enum | `JsonArtifacts` | 选择 JSON 工件、本地 SQLite 模式或基于 Postgres 的工作室配置文件。 |
| `StorageScope` | enum | `ProjectSaved` | 选择项目、用户、工作区或自定义存储范围。 |
| `StorageRootOverride` | path | 空 | 需要自定义位置时覆盖本地工件根目录。 |
| `WorkspaceStorageRoot` | path | 空 | 将 BPJ 指向共享工作区工件根目录。 |
| `SQLiteDatabasePathOverride` | path | 空 | 覆盖本地专业模式的 SQLite 数据库文件路径。 |
| `SQLiteDatabaseFileName` | string | `bpj.sqlite` | 命名默认的本地 SQLite 数据库文件。 |
| `PostgresConnectionProfileName` | string | 配置文件定义 | 命名工作室 Postgres 设置使用的外部桥接配置文件。 |
| `PostgresDsnEnvironmentVariable` | string | `BPJ_POSTGRES_DSN` | 命名外部桥接工具使用的环境变量。 |
| `bEnableJsonCompatibilityExport` | boolean | true | 即使选择了另一种存储模式，也保持便携式 JSON 导出可用。 |
| `bEnableMarkdownProjection` | boolean | true | 写入可读的 Markdown 投影以供评审和交付。 |
| `bEnableIisDerivedIndex` | boolean | true | 当存在可选索引工作流时，允许派生的 IIS 检索导出。 |
| `JournalSourceFolders` | path array | 空 | 选择包含项目或单文件日志的本地目录，BPJ 可识别并在原地显示。 |

请将凭据保存在可分发插件文件之外。BPJ 不捆绑数据库服务器，也不持久化保存提供程序凭据。

## 存储安全

默认的 `JsonArtifacts` 后端通过在选定的存储根目录下写入便携式文件，保持 BPJ 的平易近人与易于评审。SQLite 和 Postgres 配置文件是用于本地专业或工作室工作流的可选存储选项；它们不会使数据库服务器成为插件包的一部分。

当下游工具、评审者或 CI 需要稳定的 JSON 工件时，请保持 `bEnableJsonCompatibilityExport` 启用。当人类用户需要可读的评审和交付文件时，请保持 `bEnableMarkdownProjection` 启用。

## 推荐默认值

- 首次使用和 Fab 安全包校验请使用 `JsonArtifacts` 和 `ProjectSaved`。
- 仅当项目拥有经过评审的本地工件策略时，才设置 `StorageRootOverride`。
- 保持 Markdown 投影启用，以便评审简报和结果。
- 当选择 SQLite 或 Postgres 时，保持 JSON 兼容性导出启用。
- 将 IIS 派生索引视为可选的派生输出，而非标准 BPJ 存储。

## 数据处理

选定的存储根目录可能包含项目路径、评审说明、证据描述、实现结果细节、校验报告路径和出处元数据。在将导出内容发送至项目外部之前，请先进行评审。
