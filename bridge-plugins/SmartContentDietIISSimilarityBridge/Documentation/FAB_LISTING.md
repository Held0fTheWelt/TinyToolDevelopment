# Fab Listing Copy — SmartContentDiet IIS Similarity Bridge

Free companion bridge documentation. Not sold as a separate Fab product; ships with the Tiny Tool Development bridge-plugin set.

---

## Listing Title

SmartContentDiet IIS Similarity Bridge – SCD Semantic Similarity via IIS

---

## Short Description

Optional free companion that registers the `iis-similarity` provider in Smart Content Diet and imports SCD health-evidence JSONL into IIS prepared chunks.

---

## Full Description

SmartContentDiet IIS Similarity Bridge connects Smart Content Diet and Internal Index Service without merging their cores. SCD keeps asset-health findings, review workflows, and similarity requests. IIS keeps indexing, retrieval, vector storage, and context packs. The bridge only adapts evidence and similarity calls across the public interfaces.

Use this bridge when a project runs both products side by side but does not use Unreal Capability Mesh (UCM) for the SCD/IIS workflow. UCM remains the preferred integration path in the full Tiny Tool Development stack.

**Pricing:** Free companion (requires Smart Content Diet and Internal Index Service).

**Documentation:** See `README.md` in this plugin folder and the arc42 SAD under `docs/architecture/plugins/SmartContentDietIISSimilarityBridge/`.

---

## Key Points

- Provider id: `iis-similarity`
- Imports SCD health-evidence JSONL into IIS prepared chunks
- Maps SCD health metadata to IIS chunk_kind and sensitivity tokens
- IIS stays read-only with respect to Unreal assets and source files
- Unreal Engine 5.4, Editor module, no bundled content
