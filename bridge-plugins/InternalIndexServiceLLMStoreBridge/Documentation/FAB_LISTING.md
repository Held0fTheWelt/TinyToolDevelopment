# Fab Listing Copy — Internal Index Service LLM Store Bridge

Free companion bridge documentation. Not sold as a separate Fab product; ships with the Tiny Tool Development bridge-plugin set.

---

## Listing Title

Internal Index Service LLM Store Bridge – IIS Embeddings via LLM Store Routes

---

## Short Description

Optional free companion that registers the `llmstore` IIS embedding executor and routes embedding jobs through LLM Store governance without copying provider secrets into IIS.

---

## Full Description

Internal Index Service LLM Store Bridge connects Internal Index Service and LLM Store without merging their cores. IIS keeps import, indexing, vector storage, search, context packs, and read-only evidence access. LLM Store keeps provider routing, secrets, runtime policy, fallback, cost, and route governance. The bridge only adapts neutral IIS embedding requests and responses to LLM Store embedding routes.

Use this bridge when a project runs both products side by side and needs direct IIS embedding execution through governed LLM Store routes. Unreal Capability Mesh (UCM) remains the broader orchestration layer in the full stack; this bridge is a narrow adapter.

**Pricing:** Free companion (requires Internal Index Service and LLM Store).

**Documentation:** See `README.md` in this plugin folder and the arc42 SAD under `docs/architecture/plugins/InternalIndexServiceLLMStoreBridge/`.

---

## Key Points

- Registers IIS embedding executor id `llmstore`
- Provider keys and policy stay in LLM Store; the bridge does not persist secrets
- Restores the previous IIS executor id on unload and editor shutdown
- Blueprint diagnostics for route resolution and smoke tests
- Unreal Engine 5.4, Runtime module, no bundled content
