---
title: GameFeaturedClasses Settings Reference
audience: [end_user]
owner_ref: plugin:GameFeaturedClasses
applies_to:
  component: GameFeaturedClasses
contract_ref: plugin:GameFeaturedClasses/module-shell-settings
version:
  since: "1.0"
---
# Settings Reference

GameFeaturedClasses 1.0.1 does **not** ship DeveloperSettings, config `.ini` objects, or editable featured-class descriptors. The runtime module exposes no `UPROPERTY` settings surface beyond the empty module interface.

## Shipped Surfaces

| Name | Type | Default | Effect |
| --- | --- | --- | --- |
| Plugin enablement | Editor Plugins UI | disabled until buyer enables | Loads `GameFeaturedClasses` runtime module. |
| `FGameFeaturedClassesModule::StartupModule` | module hook | engine-invoked | Module startup; no buyer settings. |
| `FGameFeaturedClassesModule::ShutdownModule` | module hook | engine-invoked | Module shutdown; no buyer settings. |

## Not Yet Available

| Expected setting surface | Status |
| --- | --- |
| Featured class descriptor assets | not yet available |
| Feature set assets | not yet available |
| Registry / resolution settings | not yet available |
| Editor workbench preferences | not yet available |
| `UGameFeaturedClassesSettings` DeveloperSettings | not yet available |
| `Config/DefaultGameFeaturedClasses.ini` | not shipped |

No settings rows are invented here. When later package versions add real `UPROPERTY` / DeveloperSettings fields, this reference must be updated from source in the same change.

## Related Documents

- [UserManual.md](UserManual.md) — current vs target boundary.
- [QUICKSTART.md](QUICKSTART.md) — enablement smoke check.
- [FAQ.md](FAQ.md)

## Packaging Metadata (not runtime settings)

The `.uplugin` descriptor carries `Version` / `VersionName` for packaging. Those fields are plugin metadata, not runtime DeveloperSettings, and must not be edited casually from buyer docs workflows.

## Update Rule

Any future settings row in this file must cite the header path and property name from source in the same documentation change.
