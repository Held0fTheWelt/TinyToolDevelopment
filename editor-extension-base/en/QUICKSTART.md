---
title: EditorExtensionBase Quick Start
audience: [end_user]
owner_ref: plugin:EditorExtensionBase
applies_to:
  component: EditorExtensionBase
preconditions:
  - Unreal Engine project open with the plugin package available
  - Edit > Plugins can enable EditorExtensionBase
expected_result:
  text: GetSelectedAssetsForAction returns the current Content Browser selection after the plugin is enabled.
version:
  since: "1.0"
---
# Quick Start

This guide takes you from install to a **real first use**: enabling Editor Extension Base and calling a shared editor helper from a Blueprint Utility or C++ editor tool. Editor Extension Base is a support layer for other editor plugins — it is not a standalone Tiny Tools menu product.

## What You'll Have After This Guide

The plugin enabled, and a successful call to `UEditorManagerUtilityLibrary::GetSelectedAssetsForAction` (or the Blueprint-callable equivalent) returning the current Content Browser selection.

## Requirements

- Unreal Engine 5.4 or later (descriptor `EngineVersion` 5.4.0).
- Editor Scripting Utilities enabled (declared dependency in `EditorExtensionBase.uplugin`).
- No third-party software, account, or external runtime. See [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## 1. Install And Enable

1. Add **EditorExtensionBase** from your Fab library to the project (or install under the engine Plugins directory).
2. Open **Edit → Plugins**, enable **EditorExtensionBase**, and restart when asked.
3. Confirm **Editor Scripting Utilities** remains enabled.

## 2. Verify The Modules Loaded

After restart, the package exposes two modules:

| Module | Type | Role |
| --- | --- | --- |
| `EditorExtensionBase` | Editor | Widgets, selection helpers, undo utilities. |
| `EditorExtensionRuntimeBase` | Runtime | Lightweight macros safe for non-editor consumers. |

## 3. Worked Example: Read The Current Selection

1. Select one or more assets in the Content Browser.
2. From an Editor Utility Widget or editor C++ tool that depends on this plugin, call:

```cpp
TArray<UObject*> Selected = UEditorManagerUtilityLibrary::GetSelectedAssetsForAction(nullptr);
```

3. Persist or act on the returned objects with `CheckoutAndSaveAssets` when you intentionally write:

```cpp
bool bCheckoutOk = false;
bool bSaveOk = false;
const bool bOk = UEditorManagerUtilityLibrary::CheckoutAndSaveAssets(
	Selected, bCheckoutOk, bSaveOk);
```

## Expected Result

- `Selected` contains the Content Browser selection (or is empty when nothing is selected).
- When you call `CheckoutAndSaveAssets`, the boolean out-params report checkout and save outcomes without inventing a transaction for you — the caller owns `FScopedTransaction` scope.

## Next Steps

- Read [UserManual.md](UserManual.md) for the widget and utility catalogue.
- Read [SettingsReference.md](SettingsReference.md) for editable properties on the shared widgets.
- Use [TROUBLESHOOTING.md](TROUBLESHOOTING.md) when BindWidget slots or selection helpers warn in the log.
