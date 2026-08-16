<!-- doc-provenance: AKDB:plugins/VisualFidelityDirector/architecture.md; docs/architecture/plugins/VisualFidelityDirector/product-facts.yml; reconciled 2026-07-12 -->
# Visual Fidelity Director Documentation

This folder is the shipped buyer documentation for Visual Fidelity Director. The core workflow is
standalone: enable the plugin, open the cockpit, review fidelity profiles and composition axes, inspect
evidence, optionally approve governed config writes, and use Expert Tools for classic snapshot/recipe
workflows without needing another plugin or an external service.

Current package documentation is reconciled for version `2.0.0` and publication state
`In Publishment`.

## Start Here

- [QUICKSTART.md](QUICKSTART.md): install, enable, first cockpit refresh, and one profile comparison task.
- [UserManual.md](UserManual.md): every cockpit, evidence, and Expert Tools action.
- [SettingsReference.md](SettingsReference.md): controls, profile paths, Blueprint library functions,
  report outputs, and apply behavior.
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md): common problems and fixes.
- [FAQ.md](FAQ.md): compatibility, safety, MRQ, screenshots, and support answers.
- [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md): external dependency declaration.

## Cockpit Entry

Open Visual Fidelity Director from **Tiny Tools > Visual Fidelity Director** (Performance section).

The dock tab exposes three pages:

| Page | Purpose |
| --- | --- |
| **Cockpit** | Profile bar, multi-frame live metrics, nine composition axes, variant selector, intent sliders, axis detail with inheritance path, provenance, findings, profile comparison, and governed persistent apply. |
| **Evidence** | Eleven fixed lane evidence blocks mapped to composition axes. |
| **Expert Tools** | Integrated 1.x control panel for snapshots, recipes, scanner, preview apply, and legacy reports. |

## Profiles And Reports

Fidelity profiles live under:

```text
Saved/VisualFidelityDirector/profiles/
```

Reports from Expert Tools and validation workflows live under:

```text
Saved/VisualFidelityDirector/reports/
```

Recipe copies remain under:

```text
Saved/VisualFidelityDirector/recipes/
```

## Blueprint Surface

Runtime Blueprint callers use `UVFDCockpitBlueprintLibrary` (same C++ services as the cockpit UI).
A packaged showcase asset ships at `Content/Blueprints/BPF_VFD_API`.

## Safety Model

- Cockpit review, evidence, and comparison actions are read-only unless you use the governed apply drawer.
- **Governed persistent apply** writes only to `DefaultGameUserSettings.ini` Scalability groups,
  `DefaultEngine.ini` renderer settings, and `DefaultDeviceProfiles.ini`, and only after explicit
  per-destination approval with backup, verify, and rollback support.
- **Expert Tools > Preview Apply + Rollback** remains the session CVar preview path.
- Assets, materials, Post Process Volumes, MRQ presets, LevelSequences, Blueprints, and accessibility
  settings stay blocked.

## Schemas

Packaged runtime schema files live under `Schemas/` in the plugin root.

## Related Files

- [../README.md](../README.md): product overview.
- [../CHANGELOG.md](../CHANGELOG.md): release history.
