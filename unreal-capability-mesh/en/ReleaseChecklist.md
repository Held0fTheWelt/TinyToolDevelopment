# Release Checklist

> **Maintainer/publisher document — not buyer setup.** This is the pre-submission checklist for
> publishing UCM to Fab. Buyers do not need it; to install and use the plugin, see
> [QUICKSTART.md](QUICKSTART.md).

Use this checklist before Fab submission or resubmission.

## Source Compliance

- Every published source and build file has a top comment with publisher name and intended publication year.
- Source code does not hard-code partner plugin names or provider-specific capability ids.
- UCM modules retain UE 5.4 as the minimum supported engine version; C++20 settings also cover UE 5.6 engine-header compatibility.

## Documentation

- `README.md` exists in the plugin root.
- `Documentation/README.md` links to all buyer and technical documents.
- `CodeDocumentation.md` explains the C++ modules and main call flows.
- `TechnicalOverview.md` explains architecture, storage, safety, and diagnostics.
- `SettingsReference.md` explains manifest configuration.
- Troubleshooting and FAQ are present.

## Packaging

- `Config/FilterPlugin.ini` lists all extra packaged files outside the default BuildPlugin structure.
- `CHANGELOG.md` includes the current patch version.
- No local cache files are packaged.
- Test fixtures intended for review are explicitly listed in the filter.

## Validation

Run the validation tooling supplied with the development source, then create and smoke-test the
installed plugin package for the target engine and platform before upload.

## Editor Smoke Test

- [ ] `Tools -> Unreal Capability Mesh` opens the control panel.
- [ ] **Reload Setup** loads the active profile without errors.
- [ ] **Routes** page shows the Route Catalog grouped by plugin.
- [ ] Route Catalog expands/collapses plugin groups and individual route rows.
- [ ] **Approve all at own risk** toggles global experimental self automatic approval.
- [ ] Per-plugin and per-route approval toggles work when global approve-all is off.
- [ ] Non-approval-gated routes show `n/a` in the approval column.
- [ ] Status banner warns when experimental self automatic approval is active.
- [ ] `mesh_list_routes` reports `experimental_self_approval_*` fields for MCP clients.
