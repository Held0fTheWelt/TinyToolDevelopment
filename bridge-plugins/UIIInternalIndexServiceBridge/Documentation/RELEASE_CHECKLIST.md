# Release Checklist

## Repository Hygiene

- `Binaries/` is absent.
- `Intermediate/` is absent.
- `Saved/` is absent.
- No local logs are committed.
- No project-specific evidence files are committed.
- No provider secrets, API keys, or local endpoint tokens are committed.
- Documentation is included:
  - `README.md`
  - `Documentation/README.md`
  - `Documentation/BUYER_GUIDE.md`
  - `Documentation/QUICKSTART.md`
  - `Documentation/INTEGRATION.md`
  - `Documentation/TROUBLESHOOTING.md`

## Boundary Checks

- IIS does not depend on UII.
- UII extraction is not implemented in the bridge.
- The bridge reads handoff files and calls IIS public APIs.
- The bridge does not mutate assets, Blueprints, source files, or project settings.
- The bridge does not generate migration decisions.
- The bridge does not generate patches.
- The bridge does not execute chat/completion routes.

## Build Checks

Build in a host project containing IIS and the bridge:

```bat
D:\Engines\UE_5.4\Engine\Binaries\ThirdParty\DotNet\6.0.302\windows\dotnet.exe ^
  D:\Engines\UE_5.4\Engine\Binaries\DotNET\UnrealBuildTool\UnrealBuildTool.dll ^
  UnrealEditor Win64 Development ^
  -Project=D:\YourHost\YourHost.uproject ^
  -NoHotReload -NoUBTMakefiles
```

Expected:

- runtime bridge module builds;
- editor bridge module builds;
- Tools menu entries register;
- Python bridge functions compile.

## Functional Smoke Check

1. Generate or provide a compatible UII handoff contract.
2. Run import-only pipeline.
3. Run import + catalog pipeline.
4. Optional: run full pipeline with a small `MaxEmbeddingJobs`.
5. Confirm docking report writes JSON and Markdown.
6. Confirm mutation flags are false.

