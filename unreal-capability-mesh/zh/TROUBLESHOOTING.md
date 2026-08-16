<!-- doc-provenance: AKDB:plugins/UnrealCapabilityMesh/architecture.md; docs/architecture/plugins/UnrealCapabilityMesh/product-facts.yml; reconciled 2026-07-19 -->
# 故障排除

## 设置加载失败

请检查 `Saved/UnrealCapabilityMesh/setup_validation_report.json`。

常见原因：

- 内建、已启用插件或项目设置根中缺少 `project_profile.json`
- `schema_version` 无效
- 清单路径拼写错误
- JSON 格式错误
- 缺少必需的数组（如 `capabilities` 或 `endpoints`）

首次使用时，项目本地配置文件是可选的。UCM 会将其内建的默认配置文件与已启用插件随附的配置文件进行合并。仅在明确重写或拥有项目路由时才需要创建项目配置文件，然后点击 `Reload Setup`。

## 功能未被发现

请检查：

- 功能清单是否在其所属设置根的配置文件中被引用
- 功能是否具有非空的 `capability_id`
- 端点 ID 是否存在
- 所需的插件名称是否已加载
- 所需的架构是否存在

如果该功能属于另一个插件，请确认该插件已启用且其包包含 `Config/UnrealCapabilityMesh/project_profile.json`。请勿将提供者定义复制到项目中作为变通方法；请重新加载设置并检查发现了哪些设置根。

## 项目报告重复定义警告

提供者拥有的相同功能、端点、架构或路由可能同时存在于插件本地配置文件和项目重写中。

除非项目有意重写该定义，否则请删除项目中重复的副本。项目配置文件通常应包含项目自有的策略更改或复合路由，而提供者契约应保留在插件本地。

## 启动后 TTER 未显示有效的 UCM 路由

请确认已启用可选的 Tiny Tool Execution Integration Bridge。其 Editor 模块会在 TTER 探测前重新加载 UCM 设置。在启用新提供者或编辑设置后，请点击 `Reload Setup` 并刷新工具探测。

## 路由被阻止

请打开 `Saved/UnrealCapabilityMesh/route_reports` 下的路由报告。路由规划器记录了解释与阻止原因。

常见原因：

- 没有规则允许汇总后的副作用
- 路由使用了 `project_mutation` 且默认规则阻止了该操作
- 资产修改需要批准或试运行
- 输入与输出架构不兼容

如果在 Route Catalog 批准列或配置文件中启用了 **实验性** 自自动批准，请在排查治理行为前将其禁用。大范围重写会跳过匹配的 Deny 规则、路由资产/项目修改检查、批准要求和试运行要求，因此可能会掩盖每个策略结果。

## 端点调用失败

请检查 `Saved/UnrealCapabilityMesh/invocation_reports`。

常见原因：

- 类路径无法解析
- 函数名称错误
- 参数绑定与函数参数不匹配
- 声明了调用模式，但尚无通用调用器支持该模式
- 提供者插件未加载

## 报告为空

请再次点击 `Reload Setup`。面板将重新加载清单并重新生成诊断。同时请确认项目配置路径为当前活跃项目，而非引擎或示例文件夹。

## 源码验证报告硬编码

源码验证可能会报告 UCM 代码中存在合作插件名称或特定于产品的功能 ID。请将特定于集成的字符串移至设置 JSON 中，而不是添加 C++ 分支。
