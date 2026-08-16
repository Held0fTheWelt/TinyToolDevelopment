<!-- doc-provenance: AKDB:plugins/VisualFidelityDirector/architecture.md; docs/architecture/plugins/VisualFidelityDirector/product-facts.yml; reconciled 2026-07-12 -->
# FAQ

## Does VFD Replace Unreal's Renderer Or Anti-Aliasing?

No. It is a diagnosis, profile, evidence, comparison, recipe, dry-run, scanner, and recommendation layer
above Unreal's existing rendering systems.

## What Changed In 2.0.0?

Version `2.0.0` adds the profile-centric cockpit (variant selector, inheritance path, provenance,
findings, profile comparison, governed persistent apply, multi-frame live metrics), `UVFDCockpitBlueprintLibrary`,
and packaged Blueprint showcase assets. The integrated Expert Tools page keeps the 1.x snapshot and recipe workflow.

## Does It Require AI Or Cloud Services?

No. VFD has no external AI, cloud, Python, Node.js, or account requirement.

## Does It Need Other Tiny Tool Plugins?

No. The core workflow is standalone.

## What Unreal Version Is Targeted?

Visual Fidelity Director supports Unreal Engine 5.4 through 5.8 through the matching engine-branch descriptor and allows Win64, Linux, and Mac.

## Can It Modify My Project?

By default, no. Governed persistent apply can write only three config destinations when you explicitly
approve them: Scalability groups in `DefaultGameUserSettings.ini`, renderer settings in
`DefaultEngine.ini`, and Device Profiles in `DefaultDeviceProfiles.ini`. Expert Tools **Preview Apply +
Rollback** can temporarily set supported editor-session CVars and then restore them. Assets, materials,
Post Process Volumes, and MRQ presets are not mutated.

## Does Lumen Deep Scan Change Meshes Or Materials?

No. The Lumen deep scan writes review findings from snapshot and Asset Registry metadata. It does not
change Static Mesh card settings, material graphs, material card-sharing flags, project config, or
MRQ presets.

## Does It Capture Screenshots?

The Expert Tools A/B workflow writes metadata-only comparison reports unless a future workflow supplies
screenshot paths. Use reports to link decisions and capture visual evidence manually when needed.

## Why Are Some Findings "Medium Confidence"?

Many visual artifacts are content- and motion-dependent. VFD separates facts from heuristics so you
can route manual review without treating metadata as proof.

## Where Do Profiles And Reports Go?

```text
Saved/VisualFidelityDirector/profiles/
Saved/VisualFidelityDirector/reports/
Saved/VisualFidelityDirector/recipes/
```

## Can I Use VFD From Blueprints?

Yes. `UVFDCockpitBlueprintLibrary` exposes profile, evidence, capability, and governed apply functions.
See `Content/Blueprints/BPF_VFD_API` for wired examples.

## Who Do I Contact For Support?

Use the support email listed in the plugin descriptor:
`support@tiny-tool-development.com`.

Discord: `#support` (see product listing when published).
