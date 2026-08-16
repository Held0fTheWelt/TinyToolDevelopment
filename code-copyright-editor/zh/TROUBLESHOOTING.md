<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/CodeCopyrightEditor/architecture.md -->
# 故障排除

本页面列出了常见问题和实用解决方案。

## 工具未出现在 Tools 菜单中

检查：

- 项目是否已启用该插件。
- 启用插件后是否重启了 Unreal Editor。
- 插件是否针对当前的 Unreal Engine 版本进行了编译。

预期菜单路径：

```text
Tools > Code Tools > Code Copyright Editor
```

## Project Settings 页面缺失

检查：

- 插件模块是否已成功加载。
- 项目使用的是编辑器构建（Editor build），而非打包后的运行时构建。
- 插件是否已安装在项目或引擎的插件文件夹中。

## 扫描未找到任何文件

检查：

- `ScanRootPaths` 包含存在文件夹。
- 文件使用了受支持的扩展名。
- 排除的路径片段没有设置得过于宽泛。

## 文件被标记为 PROTECTED

扫描器找到了类似于声明的文本，但与自有标记不匹配，或者与受保护标记相匹配。

解决方案：

- 如果是第三方或 Epic 代码，请保持文件原样。
- 将供应商文件夹添加到排除项中。
- 仅当文件确实属于您的项目时，才添加自有标记。

## 写入错误 (Write Errors)

常见原因：

- 文件为只读。
- 文件被另一个进程锁定。
- 版本控制需要检出（Checkout）。
- 用户账号缺少写入权限。

修复文件状态，然后重新运行扫描/应用。
