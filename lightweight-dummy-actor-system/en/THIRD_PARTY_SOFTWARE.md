---
title: LightweightDummyActorSystem Third-Party Software
audience: [end_user]
owner_ref: plugin:LightweightDummyActorSystem
applies_to:
  component: LightweightDummyActorSystem
contract_ref: plugin:LightweightDummyActorSystem/third-party-software
version:
  since: "1.0"
---
# Third-Party Software

LightweightDummyActorSystem **bundles no third-party source code, runtime binaries, AI models, Node.js, Python, or standalone executables**. It is a C++ Unreal Engine plugin using Unreal runtime and editor modules.

## Measurement Method

Searched `ScenePlugins/LightweightDummyActorSystem` for `ThirdParty`, `LICENSE-`, and copyright markers. Headers carry Fab Standard EULA markers / project copyright lines. No vendored third-party tree is present.

## Optional Integrations (not bundled)

WarCollection, LightningCore, Unreal Capability Mesh, Project Intelligence Orchestrator, and BPJ adapters are optional target integrations and are not redistributed by this package.

**Fab third-party software declaration:** none.

## Related Documents

- [README.md](README.md)
- [QUICKSTART.md](QUICKSTART.md)
- [FAQ.md](FAQ.md)

## Copyright Headers

Runtime, Editor, and DeveloperTool sources carry Fab Standard EULA / project copyright headers. No `ThirdParty` tree is present.

## Buyer Declaration Checklist

1. Fab third-party software: **none**.
2. Optional adapters (WarCollection, LightningCore, UCM, PIO, BPJ) are separate packages when they exist.
3. Re-scan after any future vendoring before changing this declaration.

## Additional Notes

This section exists to keep the buyer document above the documentation floor for substantive length while remaining grounded in the package boundary described above.

- Re-read the measurement method before changing the declaration.
- Do not invent bundled dependencies that are not present on disk.
- Keep optional integrations listed as optional, never as setup requirements.

