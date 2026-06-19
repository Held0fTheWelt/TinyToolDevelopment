# Troubleshooting

## The Plugin Does Not Appear In The Tools Menu

Check that the plugin is enabled in **Edit > Plugins** and restart the editor if Unreal requested a restart.

If the plugin is enabled but the menu entry is still missing, check the Output Log for module startup errors. Missing editor dependencies or compile errors can prevent the module from registering its tab spawner.

## No Presets Are Listed

Use **Refresh** in the wizard.

If the list remains empty:

- Confirm that preset assets are `UPerformancePresetAsset` data assets.
- Confirm that the assets are in a mounted content folder.
- Save newly created assets before expecting them in asset registry queries.
- Check whether the plugin content folder is visible in the Content Browser.

## A Preset Cannot Be Applied

Make sure a preset is selected. The wizard applies only the currently selected asset.

If the asset was deleted or moved after selection, refresh the list and select it again.

## Some CVars Are Reported Missing

The CVar name did not resolve through Unreal's console manager.

Possible causes:

- Typo in the CVar name.
- CVar belongs to a plugin or renderer feature that is disabled.
- CVar exists only in another Unreal Engine version.
- CVar is registered later than the apply moment.
- CVar is editor-only or platform-specific.

Missing CVars are reported but do not stop the rest of the preset from applying.

## CVars Are Counted As Invalid

Invalid entries have an empty name or empty value after trimming.

Examples:

```text
=1
r.ScreenPercentage=
```

Fix the line in the bulk editor or remove the empty entry from the array.

## Bulk CVar Text Does Not Apply

Check the line format:

```text
Name=Value
Name=Value,editor
```

Common mistakes:

- Missing `=`.
- Extra notes on the same line that are not comments.
- Using `:` instead of `=`.
- Leaving a trailing comma other than `,editor`.

Use comment lines for notes:

```text
# Good: notes on their own line.
r.ScreenPercentage=85
```

## Restore Previous Is Unavailable

Restore is available only after applying a preset in the current editor session. The restore point is kept in memory and is cleared after a restore succeeds.

Applying another preset replaces the previous restore point.

## Startup Preset Does Not Apply

Check:

- **Apply Preset On Editor Startup** is enabled.
- **Startup Preset** points to a valid preset asset.
- The asset can be loaded after editor startup.
- The Output Log does not show startup warnings.

If the preset asset was moved, re-select it in Project Settings and save settings.

## Quality Values Look Wrong

The plugin uses Unreal's `0..4` quality scale:

- `0`: Low
- `1`: Medium
- `2`: High
- `3`: Epic
- `4`: Cinematic

If a raw asset value outside this range is introduced by external tooling, the applier clamps it before applying.

## Applying A Preset Changes More Than Expected

Unreal's scalability system can internally map one quality level to multiple renderer CVars. This is normal engine behavior. Performance Preset Wizard calls Unreal's scalability API rather than manually setting every underlying scalability CVar.

Review your project's scalability settings and device profiles if the resulting behavior is surprising.

## The Plugin Builds In The Project But Fails BuildPlugin

Run the isolated plugin build with strict includes. A full project build can hide missing includes through transitive headers.

```powershell
Engine\Build\BatchFiles\RunUAT.bat BuildPlugin -Plugin="D:\PluginProjectGit\Plugins\PerformancePresetWizard\PerformancePresetWizard.uplugin" -Package="D:\PluginProjectGit\Saved\PerformancePresetWizardBuildCheck" -TargetPlatforms=Win64 -StrictIncludes
```

If strict includes fail, add explicit includes to the file that uses the type and update module dependencies when the used type lives in another module.

## Documentation Is Missing From A Packaged Plugin

Check `Config/FilterPlugin.ini`. It should include:

```ini
[FilterPlugin]
/Readme.pdf
/PerformancePresetWizard_Changelog.txt
/Documentation/...
```

Without the documentation filter entry, marketplace packages may omit the Markdown guides.

## Sample Assets Are Missing

Make sure plugin content is visible in the Content Browser:

1. Open the Content Browser settings.
2. Enable **Show Plugin Content**.
3. Search for `DA_`.

If the assets are not in the packaged plugin, review the plugin package output and `.uplugin` content settings.

