<!-- doc-provenance: product-facts.yml reconciled 2026-07-19; source AKDB:plugins/BestPracticesJournal/architecture.md; release 1.1.2 -->
# 第三方软件

Best Practices Journal 不包含第三方运行时、模型提供程序、数据库服务器或外部可执行文件。

可选的 SQLite 或 Postgres 工作流属于存储配置文件和外部环境选择。它们不作为插件包内捆绑的第三方软件分发。

如果项目使用了 SQLite、Postgres、IIS、UCM、UCI、PRS 或任何其他可选生态系统组件，该组件仍属于外部项目或工作室的选择。在没有这些组件的情况下，BPJ 的分发包也必须能够打开、校验、导入、导出和评审 JSON 工件。

可选提供程序和消费程序是集成界面，而非捆绑软件。它们的缺失应当仅表现为状态或诊断，而不应导致 BPJ 启动失败或首次使用出错。
