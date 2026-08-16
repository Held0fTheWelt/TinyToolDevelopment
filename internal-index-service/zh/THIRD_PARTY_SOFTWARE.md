<!-- doc-provenance: SAD architecture.md sections 2,7,8; facts product-facts.yml; reconciled 2026-07-16 -->
# 第三方软件

Internal Index Service 随附了以下第三方源代码。请将插件提交标记为包含第三方软件，并在 Epic 第三方软件声明表格中包含此条目。

| 软件 | 版本 | 许可证 | 源码 | 插件内路径 | 用途 |
| --- | --- | --- | --- | --- | --- |
| hnswlib | 0.9.0 | Apache License 2.0 | https://github.com/nmslib/hnswlib | `Source/ThirdParty/hnswlib` | 用于本地向量搜索的仅头文件（header-only）C++ 近似最近邻索引后端。 |

打包的插件在 `Source/ThirdParty/hnswlib` 下包含上游 `LICENSE` 文件和 `NOTICE.md`。
