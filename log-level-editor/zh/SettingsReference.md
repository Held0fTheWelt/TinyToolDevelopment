<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/LogLevelEditor/architecture.md -->
# 设置参考

LogLevelEditor 将其配置存储在 `ULogLevelEditor_Settings` 中。

## 设置对象

源码文件：

```text
Source/LogLevelEditor/Public/LogLevelEditor_Settings.h
```

配置作用域：

```text
EditorPerProjectUserSettings
```

这意味着许多设置属于用户/编辑器作用域，而不是 Gameplay 运行时设置。

## LogLevelDataAsset

类型：

```text
TSoftObjectPtr<ULogLevelDataAsset>
```

默认值：

```text
/LogLevelEditor/DA_LogLevelVerbosity.DA_LogLevelVerbosity
```

用途：

- 存储按类别划分的持久详细级别重写。
- 在启动时由模块加载。
- 在命令成功执行后由 Widget 更新。

推荐做法：

- 对于小型项目，请使用提供的默认资产。
- 如果希望在版本控制中建立严格的所有权，请创建特定于项目的副本。

## bAutoSaveLogLevelDataAsset

默认值：

```text
true
```

用途：

- 在持久重写更改后自动保存 DataAsset。
- 减少用户在修改日志规范后忘记保存资产的可能性。

## bShowToolbarButton

默认值：

```text
true
```

用途：

- 在 Level Editor 工具栏中显示 Log Level Editor 快捷方式。
- 隐藏此快捷方式时，菜单项 **Tools → Log Tools → Log Level Editor** 依然可用。

## bAlsoListEnginePluginChannels

默认值：

```text
false
```

用途：

- 在扫描器中包含引擎插件源码目录。

权衡：

- 得到更完整的结果。
- 扫描时间更长，UI 中的类别更多。

## bAlsoListEngineSourceChannels

默认值：

```text
false
```

用途：

- 在扫描器中包含引擎源码目录。

权衡：

- 极广的可见性。
- 扫描规模可能大幅增加。

## bTemporaryHideLogLevels

默认值：

```text
false
```

用途：

- 启用仅限会话生效的隐藏列表。

存储：

- 挥发性（Transient）。
- 不持久化到配置中。

## LogChannelsToHideTemporary

用途：

- 仅针对当前编辑器会话隐藏的类别名称。

示例：

```text
LogTemp
LogSlate
LogDerivedDataCache
```

## LogChannelsToHide

用途：

- 跨会话隐藏的类别名称。

推荐做法：

- 谨慎使用。永久隐藏可能会导致以后难以发现相关的日志。

## 实用基线配置

对于大多数项目：

```text
bAutoSaveLogLevelDataAsset = true
bAlsoListEnginePluginChannels = false
bAlsoListEngineSourceChannels = false
bTemporaryHideLogLevels = false
```
