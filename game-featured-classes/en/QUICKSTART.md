---
title: GameFeaturedClasses Quick Start
audience: [end_user]
owner_ref: plugin:GameFeaturedClasses
applies_to:
  component: GameFeaturedClasses
preconditions:
  - Unreal Engine project open with the plugin package available
  - Edit > Plugins can enable GameFeaturedClasses
expected_result:
  text: GameFeaturedClasses runtime module is enabled and loads after editor restart.
version:
  since: "1.0"
---
# Quick Start

This guide installs and enables **GameFeaturedClasses** and verifies that the runtime module loads. Version `1.0.1` is a **module shell**: it ships the descriptor, packaging metadata, icon, and changelog. It does **not** yet ship gameplay classes, Game Feature actions, or an editor workbench.

## What You'll Have After This Guide

The plugin enabled in your project, with the `GameFeaturedClasses` runtime module present in the module list after editor restart.

## Requirements

- Unreal Engine 5.4–5.8 (packaged release matrix).
- No other Tiny Tool plugin is required for the shell.
- No third-party software, account, or external runtime. See [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## 1. Install And Enable

1. Acquire **GameFeaturedClasses** from Fab and add it to the project (or install under the engine Plugins directory).
2. Open **Edit → Plugins**, search for **GameFeaturedClasses**, enable it, and restart when asked.

## 2. Confirm The Module Boundary

After restart, verify the runtime module is loaded (Output Log / module manager). The public module interface is `FGameFeaturedClassesModule` in `Source/GameFeaturedClasses/Public/GameFeaturedClasses.h` with `StartupModule` / `ShutdownModule` only.

## 3. Worked Example: Shell Smoke Check

1. Create or open a project on Unreal Engine 5.4+.
2. Enable the plugin as above and restart.
3. In the Output Log, filter for module startup noise for `GameFeaturedClasses` after load.

There is no featured-class registry UI and no sample Game Feature action to run in this package version. Calling non-existent workbench menus is expected to fail because those surfaces are **not yet available**.

## Expected Result

- Plugin shows as enabled under **Edit → Plugins**.
- Runtime module starts and shuts down without requiring peer Tiny Tool plugins.
- No gameplay featured-class assets appear in Content Browser from this package (none are shipped).

## Next Steps

- Read [UserManual.md](UserManual.md) for the current vs target boundary.
- Read [FAQ.md](FAQ.md) for scope questions.
- Treat premium GameFeature Workbench behavior as target architecture until a later package ships those classes and editor surfaces.

## Boundaries To Remember

- Do not add project gameplay classes into this plugin folder expecting them to ship as GFC content in 1.0.1.
- Do not enable peer plugins solely to “unlock” a workbench that is not packaged yet.
- When a later version ships featured classes, update this quick start with real class names and a worked example from that release.
