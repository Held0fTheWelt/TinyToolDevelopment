<!-- doc-provenance: AKDB:plugins/UnrealCapabilityMesh/architecture.md; docs/architecture/plugins/UnrealCapabilityMesh/product-facts.yml; reconciled 2026-07-19 -->
# 快速入门

本指南将带您从全新安装走向**实际可见的结果**：发现的功能清单以及由您亲自运行并返回 JSON 响应的路由。无需编写代码，也无需撰写清单文件 —— 插件附带了一个开箱即用的默认配置文件。

## 完成本指南后您将获得

打开的控制面板、已加载的内建 **Default Capability Mesh Profile**、已发现的功能，以及一个已执行并返回 JSON 响应且生成了可打开报告的路由（`sample.echo.route.v1`）。

## 要求

- Unreal Engine 5.4 或更高版本。
- 平台：Windows (Win64)、Linux 或 Mac。
- 用于启用该插件的 Unreal **项目**。UCM 是一个 C++ 编辑器插件：在 C++ 项目中，它将在首次启动编辑器时进行编译；在仅 Blueprint 项目中，请通过 Fab 库安装与引擎版本匹配的插件，以便编辑器加载其预构建的编辑器模块。
- 无需第三方软件、账户、AI 模型或外部运行时。请参阅 [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md)。

## 1. 安装与启用

1. 从 Fab 库获取 **Unreal Capability Mesh** 并将其添加到您的项目中（它将出现在项目的 `Plugins/` 文件夹下），或者将其安装到引擎中。
2. 打开您的项目。在编辑器中，转到 **Edit → Plugins**，搜索 `Unreal Capability Mesh`，然后勾选 **Enabled**。
3. 收到提示时重新启动编辑器。（对于 C++ 项目，请允许其在首次启动时进行编译。）

UCM 可以在没有项目本地设置文件夹的情况下运行。它会加载内建的默认配置文件以及来自已启用提供者插件的插件本地配置文件。仅当项目明确需要重写或项目自有的复合路由时，才使用 `Config/UnrealCapabilityMesh/`。

## 2. 首次运行（获取结果）

1. 打开控制面板：**Tools → Unreal Capability Mesh**。
2. 在 **Overview** 页面上，您应该能看到当前活跃的配置文件 **"Default Capability Mesh Profile"**。
3. 点击 **Reload Setup**。UCM 会加载配置文件、验证 JSON 设置、注册定义并运行探测。
4. 打开 **Capabilities** 页面 —— 您现在可以看到已探明的功能（例如 `mesh.sample.echo`）及其可用性和副作用。
5. 打开 **Diagnostics** 页面 —— 它显示来自重新加载的设置验证和探测消息。干净无误的重新加载表示插件工作正常。

您刚刚仅凭包内自带的内容就完成了产品的运行。

## 3. 真实操作示例：运行路由

UCM 附带了一个安全、只读的示例路由 `sample.echo.route.v1`，用于调用 echo 端点。使用它来运行您的第一个端到端路由。

1. 打开 **Routes** 页面。
2. 在路由 ID 字段中输入：

   ```text
   sample.echo.route.v1
   ```

3. 点击 **Dry Run**。UCM 会规划路由并确认 `mesh.sample.echo` 功能可用，具有 `read_only` 副作用且**无需批准**。试运行（dry-run）报告干净无误。
4. 在路由输入字段中输入以下 JSON（这些是预期的参数 —— 包含 `request_json` 字段以携带载荷的路由输入包）：

   ```json
   {
     "request_json": "{\"message\":\"hello\"}"
   }
   ```

5. 点击 **Execute**。

**预期输出：** 该路由返回格式为 `{"echo": { ... }}` 的 JSON 回显响应，并写入路由执行报告。端点为随附的 `UCapabilityMeshTestInvoker::EchoJson` 函数，它将请求载荷包装为 `{"echo":<request>}`。

Routes 页面还包含用于 **实验性** 自自动批准的 **Route Catalog** 批准列。在本快速入门中，请保持 **Approve all at own risk** 和所有单路由开关处于关闭状态。它们仅用于在您自担风险的情况下测试需要批准的路由。

## 4. 结果存储位置

所有生成的文件均写入您项目的 `Saved/` 文件夹下：

```text
Saved/UnrealCapabilityMesh/
  setup_validation_report.json     ← 重新加载验证
  capability_registry.json         ← 已注册功能
  discovery_report.md              ← 可读的探测摘要
  compatibility_matrix.json        ← 功能/端点兼容性
  route_reports/                   ← 试运行计划
  route_execution_reports/         ← 已执行路由的输入与输出（您的回显结果）
```

打开 `route_execution_reports/` 即可查看您刚刚运行的路由的响应。

## 5. 后续步骤

- 操作面板及其各个功能与参数：[UserManual.md](UserManual.md)。
- 每个配置文件字段、策略与输出路径：[SettingsReference.md](SettingsReference.md)。
- 仅在需要时自定义设置：创建 `<YourProject>/Config/UnrealCapabilityMesh/project_profile.json` 或复制项目打算重写的特定清单，然后再次点击 **Reload Setup**。将提供者自有的清单保留在其插件中。
- 连接另一个插件：[INTEGRATION.md](INTEGRATION.md)。
- 遇到问题：参阅 [TROUBLESHOOTING.md](TROUBLESHOOTING.md) 和 [FAQ.md](FAQ.md)。

当 Tiny Tool Execution Integration Bridge 启用时，它会在编辑器启动期间 TTER 探测投影路由之前重新加载 UCM。编辑配置文件或启用提供者后，手动点击 **Reload Setup** 仍是常规操作。

---

> **面向维护者 / 从源码构建（使用插件无需此操作）：** 源码存储库验证工具仅供维护者使用，**不**属于 Fab 包的一部分。您无需 Python 或源码门控即可安装或使用 UCM。
