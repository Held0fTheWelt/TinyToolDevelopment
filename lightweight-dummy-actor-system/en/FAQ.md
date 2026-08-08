# FAQ

## What does LightweightDummyActorSystem do?

It provides a runtime representation service for dummy-actor workflows, including subject registration, dummy actor representation, promotion and demotion transitions, diagnostics, an editor inspector, and a validate commandlet.

## Is it usable without other Tiny Tool plugins?

Yes. The Runtime, Editor, and DeveloperTool modules are implemented as the core package. WarCollection, LightningCore, UCM, PIO, and BPJ adapters are optional target-specified integrations and are not required for the shipped core behavior.

## What engine versions are supported?

The packaged release matrix targets Unreal Engine 5.4 through 5.8 on Win64, Linux, and Mac where the module allow lists permit those platforms.

## Does it mutate project assets by itself?

No. The core service manages representation and transition state. Any project-specific mutation or adapter behavior should be reviewed in the owning project workflow.

## Where do I get support?

Use the support link on the Fab product page.
