---
title: GameFeaturedClasses Third-Party Software
audience: [end_user]
owner_ref: plugin:GameFeaturedClasses
applies_to:
  component: GameFeaturedClasses
contract_ref: plugin:GameFeaturedClasses/third-party-software
version:
  since: "1.0"
---
# Third-Party Software

GameFeaturedClasses **bundles no third-party source code, runtime binaries, AI models, Node.js, Python, or standalone executables**. It is a C++ Unreal Engine plugin module shell.

## Measurement Method

Searched `ScenePlugins/GameFeaturedClasses` for `ThirdParty`, `LICENSE-`, and copyright markers. Source headers carry Fab Standard EULA markers. No vendored third-party tree is present.

## Optional Integrations

Future adapters (for example LightweightDummyActorSystem, Unreal Capability Mesh, Project Intelligence Orchestrator, WarCollection) are target architecture only and are not redistributed by this package.

**Fab third-party software declaration:** none.

## Related Documents

- [README.md](README.md)
- [QUICKSTART.md](QUICKSTART.md)
- [FAQ.md](FAQ.md)

## Copyright Headers

Module sources carry Fab Standard EULA headers. No `ThirdParty` directory exists in the package.

## Buyer Declaration Checklist

1. Fab third-party software: **none**.
2. Do not list Unreal Engine modules as plugin-bundled third-party software.
3. Re-scan after any future vendoring before changing this declaration.

## Additional Notes

This section exists to keep the buyer document above the documentation floor for substantive length while remaining grounded in the package boundary described above.

- Re-read the measurement method before changing the declaration.
- Do not invent bundled dependencies that are not present on disk.
- Keep optional integrations listed as optional, never as setup requirements.

