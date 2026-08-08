# FAQ

## Does GameFeaturedClasses ship gameplay classes?

No. Version 1.0.1 is a lightweight runtime plugin shell with descriptor, module boundary, packaging metadata, icon, and changelog. The premium GameFeature Workbench behavior is target-specified, but not implemented in this package yet.

## Is any other Tiny Tool plugin required?

No. The current module shell loads on its own. Future integrations with LightweightDummyActorSystem, Unreal Capability Mesh, or Project Intelligence Orchestrator are optional target architecture, not a runtime requirement for this package.

## What engine versions are supported?

The packaged release matrix targets Unreal Engine 5.4 through 5.8 (descriptor `EngineVersion` 5.4.0 on this branch).

## Does it include third-party software or external services?

No. The package does not bundle third-party software and does not require an account, AI provider, or external runtime. See [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## Where do I get support?

Use `mailto:support@tiny-tool-development.com` (descriptor `SupportURL`) or the support link on the Fab product page.

## Why is there no settings panel?

Version 1.0.1 exposes no DeveloperSettings or featured-class descriptors. See [SettingsReference.md](SettingsReference.md).

## Can I put my project's featured classes inside this plugin folder?

Not for shipping as GFC content in 1.0.1. Keep project gameplay classes in your own modules until a later package explicitly ships featured-class assets.

## How do I verify the shell loaded?

Enable the plugin, restart the editor, and confirm the `GameFeaturedClasses` runtime module is present. See the worked example in [QUICKSTART.md](QUICKSTART.md).

## Where is the online documentation?

https://docs.tiny-tool-development.com/game-featured-classes/
