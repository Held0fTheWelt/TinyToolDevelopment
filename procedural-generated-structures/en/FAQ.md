<!-- doc-provenance: AKDB:plugins/ProceduralGeneratedStructures/architecture.md; docs/architecture/plugins/ProceduralGeneratedStructures/product-facts.yml; reconciled 2026-06-21 -->
# FAQ

**Does this plugin require any other plugin?**
No. It works entirely on its own.

**Does it include meshes?**
No. You supply your own `UStaticMesh` assets; the plugin instances them.

**What engine versions are supported?**
Unreal Engine 5.4+ (Win64, Linux, Mac). The module is Runtime, so the actor works in the editor and
in packaged games.

**Does it bundle third-party software, Python, or AI models?**
No. See [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

**What's the difference between explicit instances and row generation?**
Explicit instances are exact transforms (often captured from existing components) and are replayed
as-is. Row generation procedurally creates instances from row counts and per-dimension movement
transforms defined on the data asset.

**Can I build at runtime, not just in the editor?**
Yes. The actor is runtime-capable and can build synchronously or across ticks (`bUseAsyncBuild`).

**How do I avoid frame hitches on big structures?**
Enable `bUseAsyncBuild` and tune `InstancesPerFrame`.

**Can I preview what a rebuild will do before mutating components?**
Yes. Use `GetBuildPlan` or the rebuild preview route. The plan reports target components, blocking
issues, mutation intent, and exact post-prune instance counts.

**Can tools show async build progress?**
Yes. `GetEstimatedBuildInstanceCount`, `GetAddedBuildInstanceCount`, and `GetBuildProgress` expose
progress for editor tools, Blueprints, and automation routes.

**Where do I report issues or get support?**
Use the support link on the Fab product page.
