# Release Checklist

Use this checklist before publishing or handing off Lightweight Editor Mode.

## Source

- Copyright headers are present.
- Public headers explain each class contract.
- Private source comments describe non-obvious restore behavior.
- CVar constants are centralized in EditorLightweightMode.cpp.
- CVar backup happens before every plugin CVar set.
- CVar restore removes only the plugin override and keeps newer foreign values.
- Viewport backups are only captured for state the profile changes.
- Realtime viewport changes use temporary realtime overrides, not persistent
  SetRealtime calls.
- Startup auto-enable waits for editor viewports.
- Startup auto-enable restores stale viewport state before re-enabling.
- Shutdown removes the ticker and disables the mode if active.

## Settings

- Settings appear under Project Settings > Plugins > Lightweight Editor Mode.
- Profile values have clamp metadata where appropriate.
- AggressivenessLevel is clamped to 0..3.
- OverallQuality is clamped to 0..4.
- ScreenPercentage is clamped to 25..200.
- LastViewModeBeforeLightweight is visible for diagnostics but not treated as
  the main same-session restore source.
- bWasLightweightModeActiveLastSession is visible for diagnostics and cleared
  by Disable.

## UI

- Tiny Tools menu entry opens the tab.
- Tab title is correct.
- Combo box has Mild, Balanced, Aggressive, Extreme.
- Enable/Disable button label updates correctly.
- Startup checkbox saves correctly.
- Profile changes refresh the active mode when enabled.

## Behavior

- Enable backs up scalability.
- Enable backs up CVars before changing them.
- Enable captures viewport view mode before forcing Unlit.
- Enable adds temporary realtime overrides before disabling realtime rendering.
- New viewports opened while enabled receive the same viewport overrides.
- Disable restores viewport state.
- Disable restores scalability.
- Disable removes plugin CVar overrides.
- Disable clears session backups.
- Restart fallback only performs conservative viewport recovery and clears the
  stale session marker.

## Build

- Editor target builds successfully.
- No hot reload-only assumptions.
- No commandlet-only validation is treated as sufficient.
- No new compiler warnings were introduced.

## Documentation

- Documentation/README.md links to all major docs.
- User manual is current.
- Settings reference lists every setting.
- Technical overview matches current source behavior.
- Code documentation lists all source files.
- Troubleshooting includes startup, restore, CVar, and screen percentage cases.
- Buyer guide clearly says this is an editor workflow tool.
- Performance tuning guide explains profile tradeoffs.
- QA guide includes manual smoke tests.
- Compatibility and packaging guide mentions FilterPlugin.ini.
- FAQ is updated.
- Diagrams open correctly.

## Packaging

- FilterPlugin.ini includes documentation files.
- Readme.pdf is included.
- Changelog is included.
- Documentation folder is included.
- Icon resource is included.
- Intermediate, Saved, Binaries, and local generated files are excluded unless
  explicitly required by the packaging process.

## Final manual pass

- Open a heavy map.
- Enable Balanced.
- Switch to Aggressive while enabled.
- Open a second viewport while enabled and confirm Unlit/realtime overrides
  apply there too.
- Disable.
- Confirm the original editor state returns.
- Restart the editor with startup enable on.
- Confirm delayed auto-enable works.
- Simulate stale session marker and confirm Restore Lightweight State appears.
- Disable and confirm startup enable is cleared by explicit user disable.

## Release notes

Include:

- Engine version.
- Main feature summary.
- Any CVar compatibility notes.
- Known limitations.
- Support contact or issue process.
