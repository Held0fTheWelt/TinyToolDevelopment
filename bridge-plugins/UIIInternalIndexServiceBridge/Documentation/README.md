# UII Internal Index Service Bridge Documentation

## Audience

This documentation is for teams that have both Unreal Integration Intelligence and Internal Index Service installed and want UII handoff contracts imported into IIS through a controlled bridge without relying on UCM.

In the current Tiny Tool Development stack, Unreal Capability Mesh (UCM) is the preferred cross-product integration layer. This bridge documentation remains useful for no-UCM projects and as a reference for narrow direct adapters.

## Documents

- [Buyer guide](BUYER_GUIDE.md): who benefits from the bridge and where the product boundary sits.
- [Quickstart](QUICKSTART.md): install, enable, and run the handoff pipeline.
- [Blueprint usage](BLUEPRINT_USAGE.md): Blueprint nodes, Editor Utility recipes, reports, and guardrails.
- [Integration details](INTEGRATION.md): contract fields, runtime flow, and responsibility boundaries.
- [Source overview](SOURCE_OVERVIEW.md): source file map, pipeline phases, and editor/Python wrappers.
- [Troubleshooting](TROUBLESHOOTING.md): common handoff, import, catalog, and embedding failures.
- [Release checklist](RELEASE_CHECKLIST.md): checks before publishing or packaging this bridge.

## Boundary Summary

```text
Unreal Integration Intelligence
  owns Unreal truth extraction and handoff file generation

UII Internal Index Service Bridge
  owns file-level docking from UII contracts to IIS public APIs

Internal Index Service
  owns import, catalog, retrieval, context packs, and agent access
```

The bridge does not mutate the Unreal project and does not authorize migration or patching.
