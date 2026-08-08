---
title: EditorExtensionBase Third-Party Software
audience: [end_user]
owner_ref: plugin:EditorExtensionBase
applies_to:
  component: EditorExtensionBase
contract_ref: plugin:EditorExtensionBase/third-party-software
version:
  since: "1.0"
---
# Third-Party Software

Editor Extension Base **bundles no third-party source code, runtime binaries, AI models, Node.js, Python, or standalone executables**. It is a C++ Unreal Engine plugin built on Unreal Editor modules and Editor Scripting Utilities.

## Measurement Method

Searched `GovernanceDevelopmentPlugins/EditorExtensionBase` for `ThirdParty`, `LICENSE-`, and copyright markers. Headers identify Tiny Tool Development / Fab EULA. No vendored third-party tree is present.

## Engine Dependencies (not bundled)

| Dependency | Bundled? | Notes |
| --- | --- | --- |
| Unreal Engine Editor modules | No | Provided by the engine installation. |
| Editor Scripting Utilities | No | Enabled via `.uplugin` `Plugins` entry; Epic-owned plugin. |

## Optional Integrations

Feature plugins may depend on Editor Extension Base for shared widgets. Those consumers are separate packages and are not redistributed here.

**Fab third-party software declaration:** none.

## Related Documents

- [README.md](README.md)
- [QUICKSTART.md](QUICKSTART.md)
- [FAQ.md](FAQ.md)

## Copyright Headers

Editor and runtime sources use Tiny Tool Development / Fab Standard EULA headers. No additional license files were found under a `ThirdParty` directory.

## Buyer Declaration Checklist

1. Declare **no** bundled third-party software for Fab.
2. Editor Scripting Utilities remains an Epic engine plugin dependency, not a bundled third-party tree.
3. Re-run the search after any future vendoring change before updating this file.
