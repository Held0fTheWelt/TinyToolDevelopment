# Performance Preset Wizard

Performance Preset Wizard lets Unreal teams author, review, apply, and restore reusable performance presets. Presets combine scalability buckets with optional CVar overrides so editor users, runtime code, Blueprints, and automation can share one explicit performance contract.

Not a verbatim copy of shipped docs.

## What It Does

- Defines performance presets as `UPerformancePresetAsset` assets.
- Applies scalability and CVar values only after users can review intended effects.
- Captures previous settings so editor and runtime workflows can restore.
- Includes runtime subsystem, storage provider, and selector widget surfaces.
- Offers optional UCM/UMCP tools for list, read-state, apply, restore, and job status workflows.

## Best Entry Points

- Use the shipped `Documentation/QUICKSTART.md` for first editor apply/restore flow.
- Use `Documentation/RuntimeUsage.md` for packaged-game integration.
- Use `Documentation/SettingsReference.md` and `Documentation/TROUBLESHOOTING.md` for startup, runtime library, backup, and CVar behavior.

Fab listing: <https://www.fab.com/listings/39d1e5ea-4135-4197-91de-4c2193eb0d9c>
