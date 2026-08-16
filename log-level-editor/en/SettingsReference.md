<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/LogLevelEditor/architecture.md -->
# Settings Reference

LogLevelEditor stores its configuration in `ULogLevelEditor_Settings`.

## Settings Object

Source file:

```text
Source/LogLevelEditor/Public/LogLevelEditor_Settings.h
```

Config scope:

```text
EditorPerProjectUserSettings
```

This means many settings are user/editor scoped rather than gameplay runtime settings.

## LogLevelDataAsset

Type:

```text
TSoftObjectPtr<ULogLevelDataAsset>
```

Default:

```text
/LogLevelEditor/DA_LogLevelVerbosity.DA_LogLevelVerbosity
```

Purpose:

- Stores persistent per-category verbosity overrides.
- Is loaded by the module at startup.
- Is updated by the widget after successful command execution.

Recommendation:

- Use the provided default asset for small projects.
- Create a project-specific copy if you want strict source-control ownership.
- Keep only intentional policy or support presets in shared source control.

## bAutoSaveLogLevelDataAsset

Default:

```text
true
```

Purpose:

- Saves the DataAsset after persistent override changes.
- Reduces the chance that a user forgets to save the asset after changing log policy.

Recommendation:

- Keep enabled for most teams.
- Disable only when you want manual asset-save control.

## bShowToolbarButton

Default:

```text
true
```

Purpose:

- Shows the Log Level Editor shortcut in the Level Editor toolbar.
- The **Tools → Log Tools → Log Level Editor** menu entry remains available when this shortcut is hidden.

Recommendation:

- Disable when you prefer opening the tool only as a dockable tab from the menu.

## bAlsoListEnginePluginChannels

Default:

```text
false
```

Purpose:

- Includes engine plugin source directories in the scanner.

Tradeoff:

- More complete results.
- Longer scan time and more categories in the UI.

Recommendation:

- Enable temporarily when debugging an engine plugin.
- Keep disabled for normal project-focused workflows.

## bAlsoListEngineSourceChannels

Default:

```text
false
```

Purpose:

- Includes engine source directories in the scanner.

Tradeoff:

- Very broad visibility.
- Potentially much larger scans.

Recommendation:

- Use only for engine-level debugging.

## bTemporaryHideLogLevels

Default:

```text
false
```

Purpose:

- Enables the session-only hide list.

Storage:

- Transient.
- Not persisted to config.

Recommendation:

- Use for local focus while debugging.

## LogChannelsToHideTemporary

Purpose:

- Category names hidden only for the current editor session.

Example:

```text
LogTemp
LogSlate
LogDerivedDataCache
```

## LogChannelsToHide

Purpose:

- Category names hidden across sessions.

Recommendation:

- Use sparingly. Permanent hiding can make it harder to discover relevant logs later.

## Practical Baseline

For most projects:

```text
bAutoSaveLogLevelDataAsset = true
bAlsoListEnginePluginChannels = false
bAlsoListEngineSourceChannels = false
bTemporaryHideLogLevels = false
```

Then enable broader scan scopes only when needed.
