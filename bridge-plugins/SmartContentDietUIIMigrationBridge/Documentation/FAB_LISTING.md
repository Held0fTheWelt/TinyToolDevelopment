# Fab Listing Copy — SmartContentDiet UII Migration Bridge

Free companion bridge documentation. Not sold as a separate Fab product; ships with the Tiny Tool Development bridge-plugin set.

---

## Listing Title

SmartContentDiet UII Migration Bridge – UII Migration Handoff into SCD Advice

---

## Short Description

Optional free companion that registers the `uii-migration` advisor in Smart Content Diet and translates UII migration handoff evidence into advisory SCD migration findings.

---

## Full Description

SmartContentDiet UII Migration Bridge connects Smart Content Diet and Unreal Integration Intelligence without merging their cores. SCD keeps asset-health review and migration-advice requests. UII keeps evidence export and migration handoff generation. The bridge only reads UII handoff availability, loads the latest handoff JSON, and maps guardrails into advisory SCD findings.

Use this bridge when a project runs both products side by side but does not use Unreal Capability Mesh (UCM) for SCD/UII migration-advice workflows. UCM remains the preferred integration path in the full Tiny Tool Development stack.

**Pricing:** Free companion (requires Smart Content Diet and Unreal Integration Intelligence).

**Documentation:** See `README.md` in this plugin folder and the arc42 SAD under `docs/architecture/plugins/SmartContentDietUIIMigrationBridge/`.

---

## Key Points

- Provider id: `uii-migration`
- Findings are advisory; migration decisions stay human-reviewed
- Preserves UII guardrails when SCD displays migration-related evidence
- Reports when UII has no handoff available instead of fabricating advice
- Unreal Engine 5.4, Editor module, no bundled content
