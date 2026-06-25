# Fab Listing Copy — UII Internal Index Service Bridge

Free companion bridge documentation. Not sold as a separate Fab product; ships with the Tiny Tool Development bridge-plugin set.

---

## Listing Title

UII Internal Index Service Bridge – UII Handoff into IIS Import

---

## Short Description

Optional free companion that reads UII handoff contracts from disk and docks prepared evidence into Internal Index Service through IIS public APIs.

---

## Full Description

UII Internal Index Service Bridge connects Unreal Integration Intelligence and Internal Index Service without merging their cores. UII keeps Unreal evidence extraction and handoff artifact generation. IIS keeps import, cataloging, retrieval, context packs, embedding jobs, and agent access. The bridge only performs file-level docking from the standard UII handoff contract into IIS workflows.

Use this bridge when a project runs both products side by side but does not use Unreal Capability Mesh (UCM) for UII-to-IIS handoff. UCM remains the preferred integration path in the full Tiny Tool Development stack.

**Pricing:** Free companion (requires Unreal Integration Intelligence and Internal Index Service).

**Documentation:** See `README.md` in this plugin folder and the arc42 SAD under `docs/architecture/plugins/UIIInternalIndexServiceBridge/`.

---

## Key Points

- Reads `Saved/UnrealIntegrationIntelligence/iis_handoff/iis_import_contract.json`
- Chains import, catalog, bounded embedding jobs, smoke search, context packs, and agent contract export
- Evidence-only guardrails in every docking report
- Blueprint, Python, C++, and editor menu entry points share one pipeline
- Unreal Engine 5.4, Runtime module, no bundled content
