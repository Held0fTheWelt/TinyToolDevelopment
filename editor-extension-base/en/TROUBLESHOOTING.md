---
title: EditorExtensionBase Troubleshooting
audience: [end_user]
owner_ref: plugin:EditorExtensionBase
applies_to:
  component: EditorExtensionBase
symptom: Editor utility BindWidget slots are null or selection helpers warn in the log.
recovery:
  steps:
    - Confirm the plugin is enabled under Edit > Plugins and restart the editor
    - Re-read the matching troubleshooting entry and apply the documented fix
    - Re-run the quick start smoke check
version:
  since: "1.0"
---
# Troubleshooting

Format: Symptom → Cause → Fix.

## 0. I enabled it and nothing happened

**Symptom:** After enabling EditorExtensionBase and restarting, there is no new Tiny Tools menu and no obvious UI change.  
**Cause:** This plugin is a shared foundation layer; it does not register a product menu of its own.  
**Fix:** Verify the plugin is enabled under **Edit → Plugins**, then call `UEditorManagerUtilityLibrary::GetSelectedAssetsForAction` from an Editor Utility Widget or C++ editor tool (see [QUICKSTART.md](QUICKSTART.md)). Absence of a new menu is expected.

## 1. Plugin enables but helper Blueprints cannot find the library

**Symptom:** Blueprint nodes for `Editor Manager Utility Library` are missing after enable.  
**Cause:** Editor module did not load, or the Editor Utility asset was compiled before the plugin was enabled.  
**Fix:** Confirm **EditorExtensionBase** is enabled under **Edit → Plugins**, restart the editor, then refresh/recompile the Editor Utility Blueprint.

## 2. `EditorUtilityButtonWidget: Button is null`

**Symptom:** Log `LogEditorExtensionBase` warns that the button is null.  
**Cause:** The Utility Widget Blueprint subclass did not bind the required BindWidget button slot.  
**Fix:** Open the widget Blueprint, bind the button slot declared on `UEditorUtilityButtonWidget`, compile, and re-open the tool.

## 3. `EditorUtilityButtonWidget: Text block is null`

**Symptom:** Warning that the text block BindWidget is null.  
**Cause:** Label text block is unbound in the Blueprint.  
**Fix:** Bind the text block slot on the C++ base, set the display text, compile.

## 4. `EditorUtilityTabButtonWidget: SelectedIcon is null` / `UnselectedIcon is null`

**Symptom:** Tab button warns about missing icons.  
**Cause:** Selected or unselected icon slots are unbound or assets are missing.  
**Fix:** Assign and bind both icon slots; verify the soft/object references resolve.

## 5. `EditorUtilityTask_PrepareUndo: No assets selected`

**Symptom:** Undo preparation logs that no assets were selected.  
**Cause:** Content Browser selection is empty when the task runs.  
**Fix:** Select transactional assets first, then run the prepare-undo utility.

## 6. Assets skipped as not transactional

**Symptom:** Warnings that an asset is not transactional / not a `UObject` / not valid.  
**Cause:** The prepare-undo task only accepts valid transactional `UObject` assets.  
**Fix:** Restrict the selection to assets that support editor transactions; skip non-asset or transient objects.

## 7. Deprecated begin-transaction helper still in use

**Symptom:** Deprecation warnings referencing `BeginTransactionAndGetSelectedAssets`.  
**Cause:** Call sites still use the UE 5.4-deprecated helper.  
**Fix:** Replace with `GetSelectedAssetsForAction` plus a caller-owned `FScopedTransaction`, and use `CheckoutAndSaveAssets` for persistence.

## 8. Checkout succeeded with warnings

**Symptom:** Result code `SucceededWithCheckoutWarning` or checkout out-param false while some files saved.  
**Cause:** Source control returned warnings during checkout.  
**Fix:** Inspect source-control status for the assets, resolve locks/conflicts, retry `CheckoutAndSaveAssets`.

## Related Documents

- [QUICKSTART.md](QUICKSTART.md)
- [UserManual.md](UserManual.md)
- [SettingsReference.md](SettingsReference.md)
- [FAQ.md](FAQ.md)
