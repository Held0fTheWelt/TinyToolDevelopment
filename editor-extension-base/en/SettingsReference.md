---
title: EditorExtensionBase Settings Reference
audience: [end_user]
owner_ref: plugin:EditorExtensionBase
applies_to:
  component: EditorExtensionBase
contract_ref: plugin:EditorExtensionBase/widget-properties
version:
  since: "1.0"
---
# Settings Reference

Editor Extension Base does **not** ship a `UDeveloperSettings` class or a project `.ini` settings object. Configurable values live on the shared Editor Utility Widget subclasses and utility objects as `UPROPERTY` fields.

## UEditorToolHeaderWidget

| Name | Type | Default | Effect |
| --- | --- | --- | --- |
| `TitleText` | `FText` | widget default | Display title shown in the header. |
| `SubtitleText` | `FText` | widget default | Secondary line under the title. |
| (BindWidget) title / subtitle blocks | widget refs | must be bound | Required slate/UMG slots; missing bindings warn at runtime. |

## UEditorUtilityButtonWidget

| Name | Type | Default | Effect |
| --- | --- | --- | --- |
| Button style properties | style fields on the widget | designer-set | Visual style for the shared button. |
| (BindWidget) `Button` / text block | widget refs | must be bound | Click target and label; null button or text logs a warning. |

## UEditorUtilityTabButtonWidget

| Name | Type | Default | Effect |
| --- | --- | --- | --- |
| Selected / unselected presentation | icon + state fields | designer-set | Controls tab selected appearance. |
| (BindWidget) button / icon slots | widget refs | must be bound | Missing selected/unselected icons log warnings. |

## UUndoableAssetActionUtility

| Name | Type | Default | Effect |
| --- | --- | --- | --- |
| Action description / asset fields | editanywhere utility fields | caller-set | Describe the undoable asset action the utility executes. |
| Result code | enum | runtime | Includes `SucceededWithCheckoutWarning` when checkout warnings accompany success. |

## UEditorUtilityTask_PrepareUndo

| Name | Type | Default | Effect |
| --- | --- | --- | --- |
| Selected asset inputs | editanywhere utility fields | caller-set | Assets considered for undo preparation; null/invalid/non-transactional assets are skipped with warnings. |

## What Is Not Present

| Expected surface | Status |
| --- | --- |
| `UEditorExtensionBaseSettings` DeveloperSettings | not yet available in source |
| `Config/DefaultEditorExtensionBase.ini` | not shipped |
| Project Preferences panel | not yet available |

## Related Documents

- [UserManual.md](UserManual.md) — behavioural catalogue.
- [QUICKSTART.md](QUICKSTART.md) — first selection helper call.
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md) — BindWidget and selection warnings.
