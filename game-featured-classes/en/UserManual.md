# User Manual

GameFeaturedClasses currently provides a lightweight runtime plugin shell for project-specific featured gameplay classes.

## Current Package Behavior

| Area | Status in 1.0.1 |
| --- | --- |
| Runtime module (`GameFeaturedClasses`) | Shipped — startup/shutdown only. |
| Descriptor / packaging / icon / changelog | Shipped. |
| Featured gameplay classes | not yet available |
| Game Feature actions / feature set assets | not yet available |
| Runtime registry / interface boundary | not yet available |
| Editor workbench / repair / proof reports | not yet available |
| Tiny Tools automation routes | not yet available |

<!-- image slot: gfc-module-shell -->

## Source Map

- `Source/GameFeaturedClasses/GameFeaturedClasses.Build.cs` — module dependencies.
- `Source/GameFeaturedClasses/Public/GameFeaturedClasses.h` — `FGameFeaturedClassesModule` interface.
- `Source/GameFeaturedClasses/Private/GameFeaturedClasses.cpp` — startup and shutdown.

## How To Use The Shell Today

1. Enable the plugin (see [QUICKSTART.md](QUICKSTART.md)).
2. Keep project-specific featured classes in your own modules until this package ships them.
3. Do not document or depend on workbench menus that are not present in this build.

## Target Architecture (informative, not shipped)

Internal product architecture describes a future premium GameFeature Workbench where authors declare featured classes and feature sets, world-scoped actions register them, consumers resolve them through a registry/interface boundary, and maintainers scan a feature graph, preview governed repairs, and export proof reports. That behavior is **target-specified only** and must not be treated as buyer-available functionality in 1.0.1.

## Autarky

The module shell loads on its own. Future optional integrations with LightweightDummyActorSystem, Unreal Capability Mesh, or Project Intelligence Orchestrator are not setup requirements for this package.

## Related Documents

- [QUICKSTART.md](QUICKSTART.md)
- [SettingsReference.md](SettingsReference.md)
- [FAQ.md](FAQ.md)
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md)
- [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md)
