<!-- doc-provenance: AKDB:plugins/VisualFidelityDirector/architecture.md; docs/architecture/plugins/VisualFidelityDirector/product-facts.yml; reconciled 2026-07-12 -->
# Troubleshooting

## I Enabled The Plugin And Nothing Happened

Cause: VFD opens from a menu entry; it does not display a startup window.

Fix:

1. Restart Unreal Editor after enabling the plugin.
2. Open **Tiny Tools > Visual Fidelity Director**.
3. If the menu is still missing, confirm the plugin is enabled in **Edit > Plugins**.

## Live Metrics Unavailable

Cause: Live metrics require an available editor viewport measurement context. Some platforms, headless
sessions, or early editor ticks may not expose GPU pass data.

Fix:

1. Click **Refresh** after the viewport is visible.
2. Wait for the multi-frame sampling window to complete (several editor ticks).
3. Treat `-1` or explicit unavailable strings as honest degradation — VFD does not invent numbers.

## No Profiles Appear In The Profile Bar

Cause: No fidelity profiles exist yet under `Saved/VisualFidelityDirector/profiles/`.

Fix:

1. Import or duplicate a profile through your project workflow, or migrate from a built-in recipe using
   Expert Tools and project tooling.
2. Click **Refresh** on the Cockpit page.

## Governed Apply Skipped Everything

Cause: No destinations were checked, the compiled diff already matches, or the destination is blocked.

Fix:

1. Click **Build Destinations** first.
2. Review each summary and check approval only for intended destinations.
3. Confirm the active profile compiles with changes (`Compile Preview`).

## Profile Comparison Shows No Diff

Cause: The two profiles compile to the same desired state for all axes, or one profile failed validation.

Fix:

1. Validate both profiles compile without errors.
2. Change a variant or intent level on one profile and refresh.

## The Control Panel / Expert Tools Opens But No Report Is Written

Cause: The project `Saved` folder may be read-only or unavailable.

Fix:

1. Switch to **Expert Tools** and click **Open Output Folder**.
2. Confirm the project can write to `Saved/VisualFidelityDirector/`.
3. Try **Export Snapshot** again and read the **Status** row.

## Preview Apply Skipped Everything

Cause: The selected recipe may contain export-only recommendations, the recommended value may already
match the current value, or the CVar may be unavailable in this engine context.

Fix:

1. Export a recipe dry run first.
2. Open `settings_diff.md`.
3. Check the **Mode**, **Supported**, and **Risk** columns.

## A CVar Says Unavailable

Cause: Some CVars are engine-version, renderer, platform, or context dependent.

Fix: Treat the recommendation as manual review. VFD records unavailable values instead of failing the
whole workflow.

## MRQ Recommendations Did Not Change My Preset

Cause: MRQ preset mutation is intentionally not supported.

Fix: Open `mrq_recommendation.md` and apply any cinematic settings manually after review.

## Lumen Recommendation Did Not Change A Mesh Or Material

Cause: Lumen mesh-card settings, material graphs, and material card-sharing flags are intentionally
manual-review only.

Fix: Export **Lumen Deep Scan** or a Lumen recipe dry-run, then inspect reports and apply mesh or
material changes manually only after visual validation.

## The Experimental Diagnostics Look Too Coarse

Cause: The diagnostics report is a metadata-based review-routing heatmap. It is not a pixel-derived
frame-difference heatmap and does not capture motion vectors.

Fix: Use snapshot and scanner reports for structured review; capture visual evidence manually when needed.

## Blueprint Library Apply Wrote Nothing

Cause: `ApplyPersistentConfiguration` requires `Request.bUserApproved` and approved destination summaries.

Fix: Call `PreviewPersistentDestinations` first, mark only intended destinations approved in the request,
then call apply with `bUserApproved=true`.
