# Editor Extension Base Documentation

Editor Extension Base is a shared Unreal Editor foundation for Tiny Tool Development UI plugins. It ships reusable Editor Utility widgets, Content Browser selection / checkout / save helpers, undo preparation utilities, and a lightweight runtime macros module.

Audience: plugin authors and teams that need consistent editor UX without copying widget and selection boilerplate. This package is a support layer — it does not register its own Tiny Tools product menu.

## Features

- Shared Editor Utility widgets (header, button, tab button, two-pane layout).
- `UEditorManagerUtilityLibrary` selection, checkout/save, and editor-world helpers.
- Undo preparation and undoable asset-action utilities.
- Runtime module (`EditorExtensionRuntimeBase`) with shared macros for non-editor consumers.

## Get Started

1. Enable the plugin (and Editor Scripting Utilities) — see [QUICKSTART.md](QUICKSTART.md).
2. Call `GetSelectedAssetsForAction` from an Editor Utility or C++ editor tool.
3. Read [UserManual.md](UserManual.md) and [SettingsReference.md](SettingsReference.md) for the full catalogue.

## Related Files

- [../README.md](../README.md) — product overview.
- [../CHANGELOG.md](../CHANGELOG.md) — release history.
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md) · [FAQ.md](FAQ.md) · [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md)
