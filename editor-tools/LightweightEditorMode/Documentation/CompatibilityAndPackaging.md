# Compatibility And Packaging

This document covers compatibility assumptions, packaging notes, and release
structure for Lightweight Editor Mode.

## Engine compatibility

The implementation targets Unreal Engine 5.4 editor APIs and renderer console
variables.

The plugin relies on:

- IModuleInterface.
- ToolMenus.
- Global tab manager / Nomad tabs.
- Slate widgets.
- ISettingsModule.
- GEditor and FEditorViewportClient.
- Scalability::FQualityLevels.
- IConsoleManager and IConsoleVariable.
- FTSTicker for delayed startup enable.

## Renderer CVar compatibility

The plugin currently targets these CVars:

- r.Editor.Viewport.ScreenPercentage
- r.Editor.Viewport.ScreenPercentageMode.RealTime
- r.Editor.Viewport.ScreenPercentageMode.NonRealTime
- r.ScreenPercentage
- r.Lumen.DiffuseIndirect.Allow
- r.Lumen.Reflections.Allow
- r.Shadow.Virtual.Enable
- r.VolumetricFog
- r.Fog

Custom engine branches can rename, remove, or override CVars. Missing CVars are
logged and skipped.

## Platform scope

The plugin is an editor plugin. It is not intended to add runtime code to a
packaged game.

Primary validation should focus on editor targets:

- Win64 editor target.
- Any additional editor target the project supports.

## Descriptor expectations

The .uplugin descriptor should identify the module as Editor type. The project
.uproject should enable the plugin when the sample project is intended to ship
with the plugin active.

## FilterPlugin.ini

FilterPlugin.ini should include:

- Readme.pdf
- LightweightEditorMode_Changelog.txt
- Documentation files
- Documentation CI sample
- Documentation visual assets

This ensures marketplace or plugin packaging includes the documentation bundle.

## Packaging checklist

Before packaging:

1. Build the editor target.
2. Run git diff --check for the plugin.
3. Confirm Documentation/README.md links.
4. Confirm Readme.pdf and changelog are present.
5. Confirm the plugin descriptor metadata is current.
6. Confirm no temporary binaries, saved files, or intermediate files are added.
7. Package with Unreal's plugin packaging workflow.
8. Inspect the packaged output for source, config, resources, and docs.

## Marketplace content expectations

A buyer should receive:

- Plugin source.
- Plugin descriptor.
- Config filter.
- Icon resource.
- Readme and changelog.
- Documentation folder with user, technical, troubleshooting, and release docs.

## Source distribution

The source code is intentionally documented. Public headers describe the module,
settings, UI, and runtime helper contracts. Private source files document
implementation-level invariants such as CVar priority handling and restore
sequencing.

## Avoid packaging generated state

Do not include:

- Binaries from local test builds unless the packaging process intentionally
  generates them.
- Intermediate folders.
- Saved folders.
- DerivedDataCache.
- Local editor user config unrelated to the plugin defaults.

## Support matrix guidance

For each release, document:

- Tested Unreal Engine version.
- Tested operating system.
- Tested target editor platform.
- Known custom engine limitations.
- Any CVar changes between engine versions.

## Upgrade notes

When moving to a newer Unreal Engine version:

1. Build without code changes.
2. Check for compile errors from editor API changes.
3. Check CVar existence in the Output Log.
4. Verify editor viewport screen percentage still responds.
5. Verify Lumen and virtual shadow toggles still map to valid CVars.
6. Update documentation if Unreal renamed behavior.

