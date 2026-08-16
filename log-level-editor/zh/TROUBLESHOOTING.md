<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/LogLevelEditor/architecture.md -->
# 故障排除

## 工具未显示我的类别

检查：

- 类别已在扫描的源码路径中声明或定义。
- 文件扩展名为 `.h`、`.hpp`、`.cpp` 或 `.inl`。
- 类别未被永久或临时隐藏设置隐藏。
- 扫描已完成或仍在处理中。
- 宏属于支持的 Unreal 日志宏形式之一。

## 默认详细级别缺失或错误

扫描器只能从可识别的宏参数中推断默认值。某些类别可能仍会显示为空或备用默认值。

修复方法：

- 尽可能使用标准的 Unreal 宏格式。
- 如果需要已知值，请添加持久重写。

## 更改详细级别毫无反应

可能的原因：

- 类别尚未被已加载的模块注册。
- Unreal 拒绝了该控制台命令。
- 运行时代码在编辑器命令之后再次更改了该类别。

检查 Output Log 中的 `LogLogLevelEditor` 消息。

## 保存的详细级别在启动时未应用

检查：

- `LogLevelDataAsset` 指向有效的资产。
- DataAsset 包含重写条目。
- 在运行启动重试重放时，该类别已存在。

## 我的 DataAsset 包含了太多条目

DataAsset 应仅包含有意的重写。将各行重置为检测到的默认值以移除不必要的条目。

## 临时隐藏的值重新出现了

临时隐藏值是挥发性的（Transient），不会跨会话保留。如需永久隐藏，请使用 `LogChannelsToHide`。

## 扫描耗时太长

除非需要，否则禁用引擎插件和引擎源码扫描。

推荐的常规设置：

```text
bAlsoListEnginePluginChannels = false
bAlsoListEngineSourceChannels = false
```

## Output Log 依然很吵

某些系统可能会通过多个类别记录日志。搜索相关的类别前缀并调整每个相关通道。

## 插件可以打开但不显示 DataAsset 重写

扫描器和 DataAsset 是分离的：

- 扫描器：发现可用的类别。
- DataAsset：存储持久重写。

在未配置持久重写时，DataAsset 为空是完全正常的。

## 版本控制一直显示我的 DataAsset 已更改

您可能修改了持久重写。要么将其作为团队规范保留，要么在提交前将各行重置为默认值。

## 需收集的技术支持信息

报告问题时，请包含：

- Unreal Engine 版本。
- 插件版本。
- 是否启用了引擎源码/插件扫描。
- 日志类别声明示例。
- 相关的 `LogLogLevelEditor` 输出。
