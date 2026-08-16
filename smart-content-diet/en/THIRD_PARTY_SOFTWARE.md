<!-- doc-provenance: AKDB:plugins/SmartContentDiet/architecture.md; docs/architecture/plugins/SmartContentDiet/product-facts.yml; reconciled 2026-07-16 -->
# Third-Party Software

Smart Content Diet **bundles no third-party source code, runtime binaries, AI models, Node.js,
Python, or standalone executables**. It is a C++ Unreal Engine editor plugin that uses only Unreal
Engine modules and standard Unreal APIs (asset registry, asset analysis, editor UI, commandlet).

The core scan → review → safe-fix loop runs entirely inside the editor with **no AI service and no
external tool**. Optional cross-plugin ecosystem routes (via **Unreal Capability Mesh (UCM)**) are
JSON-declared and do not add any third-party software to this package.

No external software, account, or runtime is required to install or use the plugin.

**Fab third-party software declaration:** no bundled third-party software.
