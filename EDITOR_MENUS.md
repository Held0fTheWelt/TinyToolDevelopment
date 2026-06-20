# Editor Menu Layout

Tiny Tool Development editor plugins register their primary workflows under the Unreal Editor **Tools** menu. Settings shortcuts for most products remain under **Edit → Configurations**.

This page summarizes the current menu layout after the 2026 editor-menu consolidation.

## Tools Menu Overview

```text
Tools
├── Unreal Capability Mesh                     (top-level tab spawner entry)
├── … engine sections …
├── Code Tools
│   └── Code Copyright Editor
├── Performance
│   ├── Lightweight Editor Mode
│   └── Performance Preset Wizard
├── Log Tools
│   └── Log Level Editor
├── Content Tools
│   └── Smart Content Diet
├── Track Tools
│   └── Async Spline Builder
├── AI
│   ├── Universal MCP ▸
│   │   ├── Start Unified MCP Server
│   │   ├── Stop Unified MCP Server
│   │   └── Rotate MCP Token
│   ├── Internal Index Service ▸
│   │   ├── Open Internal Index Service
│   │   └── Quick Actions (Build Index, Open Index Folder)
│   ├── Unreal Integration Intelligence ▸
│   └── Project Restructure Service
├── Smart Documentation
│   └── Smart Documentation Assistant
└── LLM Store                                   (top-level tab spawner entry)
```

## Quick Paths

| Product | Menu path |
| --- | --- |
| Unified MCP Server | **Tools → AI → Universal MCP** |
| Internal Index Service | **Tools → AI → Internal Index Service** |
| Code Copyright Editor | **Tools → Code Tools → Code Copyright Editor** |
| Lightweight Editor Mode | **Tools → Performance → Lightweight Editor Mode** |
| Performance Preset Wizard | **Tools → Performance → Performance Preset Wizard** |
| Log Level Editor | **Tools → Log Tools → Log Level Editor** |
| Smart Content Diet | **Tools → Content Tools → Smart Content Diet** |
| Async Spline Builder | **Tools → Track Tools → Async Spline Builder** |
| Unreal Capability Mesh | **Tools → Unreal Capability Mesh** |
| LLM Store | **Tools → LLM Store** |
| Smart Documentation Assistant | **Tools → Smart Documentation → Smart Documentation Assistant** |

## Notes

- **Universal MCP** groups Unified MCP Server lifecycle actions in one submenu under the shared **AI** section.
- **Internal Index Service** lives in the same **AI** section and exposes a submenu for the control panel and quick index actions.
- **Unreal Capability Mesh** registers only once through its nomad tab spawner. There is no duplicate entry under Smart Documentation.
- Editor tools that previously lived under **Window** (Code Copyright Editor, performance tools, Log Level Editor, Smart Content Diet, Async Spline Builder) now register under **Tools** with the section names above.
- Product-specific docs may also mention **Edit → Configurations** shortcuts for project settings.

## Per-Product References

- [Unified MCP Server](ai-plugins/UnifiedMcpServer/README.md)
- [Internal Index Service](ai-plugins/InternalIndexService/Documentation/UserManual.md)
- [Code Copyright Editor](editor-tools/CodeCopyrightEditor/Documentation/UserManual.md)
- [Lightweight Editor Mode](editor-tools/LightweightEditorMode/Documentation/UserManual.md)
- [Performance Preset Wizard](editor-tools/PerformancePresetWizard/Documentation/UserManual.md)
- [Log Level Editor](editor-tools/LogLevelEditor/Documentation/UserManual.md)
- [Smart Content Diet](editor-tools/SmartContentDiet/Documentation/README.md)
- [Async Spline Builder](scene-tools/AsyncSplineBuilder/Documentation/UserManual.md)
- [Unreal Capability Mesh](foundation-plugins/UnrealCapabilityMesh/Documentation/UserManual.md)
