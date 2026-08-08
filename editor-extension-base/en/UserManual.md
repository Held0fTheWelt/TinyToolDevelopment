# User Manual

Editor Extension Base packages shared Unreal Editor UI primitives and helper libraries so feature plugins can keep consistent selection, checkout, save, and undo behavior.

## Audience

- Plugin authors who build Editor Utility Widgets or editor tools.
- Teams standardizing Tiny Tool Development editor UX without copying widget boilerplate.

This plugin is **not** an end-user tool with its own Tiny Tools menu entry.

## Modules

| Module | Loading | Contents |
| --- | --- | --- |
| `EditorExtensionBase` | Editor / Default | Widgets, `UEditorManagerUtilityLibrary`, undo / asset-action utilities. |
| `EditorExtensionRuntimeBase` | Runtime / Default | Shared macros (`UsefulMacros.h`) and module entry. |

## Shared Widgets

<!-- image slot: eeb-widget-overview -->

| Class | Purpose |
| --- | --- |
| `UEditorToolHeaderWidget` | Header row with title / subtitle BindWidget slots and editable display text. |
| `UEditorUtilityButtonWidget` | Styled button with text block BindWidgets and click delegate. |
| `UEditorUtilityTabButtonWidget` | Tab-style button with selected / unselected icon slots. |
| `UTwoPaneUserWidget` | Two-pane layout container for editor utility screens. |

Widget Blueprint subclasses must bind the declared BindWidget slots; missing bindings log warnings under `LogEditorExtensionBase`.

## Editor Manager Utility Library

`UEditorManagerUtilityLibrary` extends `UEditorUtilityLibrary` with selection and persistence helpers:

| Function | Behavior |
| --- | --- |
| `GetSelectedAssetsForAction` | Returns the current selection, optionally anchored by a primary object. |
| `CheckoutAndSaveAssets` | Attempts source-control checkout and save; reports success via out-params. |
| `GetEditorWorld` | Returns the current editor world when available. |
| `BeginTransactionAndGetSelectedAssets` | **Deprecated in 5.4** — callers should own `FScopedTransaction` themselves. |

## Undo And Asset Actions

| Class | Behavior |
| --- | --- |
| `UEditorUtilityTask_PrepareUndo` | Editor utility task that prepares undo options for selected transactional assets; skips null, invalid, or non-transactional objects with warnings. |
| `UUndoableAssetActionUtility` | Encodes undoable asset action results, including `SucceededWithCheckoutWarning` when checkout warnings accompany success. |

## Design Rules

1. Keep feature-specific business logic in the consuming plugin.
2. Do not treat this plugin as a setup requirement for unrelated scene or AI plugins.
3. Prefer caller-owned transactions over the deprecated begin-transaction helper.

## Optional Integrations

Consuming Tiny Tool editor plugins may depend on Editor Extension Base for UI consistency. Those integrations are owned by the consumer; this package degrades to “helpers unavailable” only when it is not enabled — it does not substitute other plugins' behavior.

## Related Documents

- [QUICKSTART.md](QUICKSTART.md)
- [SettingsReference.md](SettingsReference.md)
- [FAQ.md](FAQ.md)
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md)
