# Lightning

Lightning is an advanced-preview Unreal Engine C++ runtime plugin with two modules in one installation.
`LightningCore` provides dependency-light, data-oriented runtime primitives, while
`LightningUnrealBridge` keeps UObject, Actor, diagnostics, and optional pooling behavior outside the
core.

Not a verbatim copy of shipped docs. This online page is an overview and ecosystem-routing surface.

## Standalone Workflow

1. Install and enable Lightning in an Unreal Engine 5.4 C++ project.
2. Add `LightningCore` to the game module.
3. Run the shipped `LightningQuickstartActor`.
4. Confirm the Output Log reports one live entity and the round-tripped position payload.
5. Add `LightningUnrealBridge` only when the project needs Unreal owner or Actor representation
   behavior.

No other Tiny Tool plugin, Mass, network service, account, or external pool asset is required.

## What It Provides

- Generational entity handles and trivial fragment registration.
- Archetype/chunk storage, queries, systems, serialized schedules, and deferred command playback.
- Enableable masks, dirty versions, plain representation-transition requests, arenas, and statistics.
- Weak Unreal owner binding, input gather, retry-safe dirty output apply, and structured diagnostics.
- `None`, `SpawnDestroy`, `Pool`, and `ExternalProvider` representation policies.
- Explicit pool-provider and `ILightningPoolable` reset contracts.

## Current Boundary

Version 0.1.0 is beta runtime infrastructure. It does not include an editor workbench,
Blueprint-first ECS workflow, Mass replacement, replication/prediction, GameFeature bootstrap, or
project-specific gameplay adapter. Internal benchmark evidence is not a public performance claim.

Descriptor platforms are Win64, Linux, and Mac; the current recorded BuildPlugin proof is Unreal
Engine 5.4 / Win64.

## Optional Ecosystem Synergies

Lightning stays standalone. Other Tiny Tool products may consume its public contracts in separate
project adapters, but those integrations are not part of the Lightning Fab package and must not add
their dependencies to `LightningCore`.

Examples include project-specific gameplay adapters, governed capability routes, documentation
evidence, or asset-workflow integrations. Each remains optional and separately owned.

## Publication and Support

- Product page: <https://tiny-tool-development.com/tools/lightning>
- Support: <https://discord.gg/HycgjVkK4J>
- Formal support email: <support@tiny-tool-development.com>
- Planned Fab license: Standard License, per-seat code-plugin terms
- Planned 0.1.0 prices: Personal USD 0.00; Professional USD 0.00

Real Unreal Editor captures for the public gallery are still pending. The plugin icon is not treated
as workflow evidence.
