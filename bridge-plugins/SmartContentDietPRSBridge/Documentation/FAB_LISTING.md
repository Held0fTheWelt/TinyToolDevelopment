# Fab Listing Copy — SmartContentDiet PRS Bridge

Free companion bridge documentation. Not sold as a separate Fab product; ships with the Tiny Tool Development bridge-plugin set.

---

## Listing Title

SmartContentDiet PRS Bridge – SCD Placement Moves into PRS Plans

---

## Short Description

Optional free companion that adapts reviewed Smart Content Diet placement proposals into Project Restructure Service validation, dry-run, apply, and rollback contracts.

---

## Full Description

SmartContentDiet PRS Bridge connects Smart Content Diet and Project Restructure Service without merging their cores. SCD owns asset-health findings, optimization review, and user-confirmed placement proposals. PRS owns guarded plan validation, dry-run diffs, explicit apply gates, and rollback execution. The bridge only translates reviewed placement moves across the public interfaces.

Use this bridge when a project runs both products side by side but does not use Unreal Capability Mesh (UCM) for PRS placement workflows. UCM remains the preferred integration path in the full Tiny Tool Development stack.

**Pricing:** Free companion (requires Smart Content Diet and Project Restructure Service).

**Documentation:** See `README.md` in this plugin folder and the arc42 SAD under `docs/architecture/plugins/SmartContentDietPRSBridge/`.

---

## Key Points

- Adapter: `FSCDToPRSPlacementAdapter`
- Read-only health helper: `FSCDHealthForPRS`
- Preview PRS validation and dry-run before any mutation
- Apply only after SCD preview and user confirmation
- Unreal Engine 5.4, Runtime module, no bundled content
