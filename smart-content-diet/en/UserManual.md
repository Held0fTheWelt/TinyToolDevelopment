<!-- doc-provenance: AKDB:plugins/SmartContentDiet/architecture.md; docs/architecture/plugins/SmartContentDiet/product-facts.yml; reconciled 2026-07-16 -->
# User Manual

This manual summarizes the Smart Content Diet editor workflow and points to the detailed guides.

## Entry Point

Open **Tools → Content Tools → Smart Content Diet**. The window is a role-aware shell.

## Roles And Tabs

Set the role (Beginner / Engineer / Producer) and explanation level in **Settings** or the header
audience selector. Tab visibility follows the role:

| Tab | Beginner | Advanced (Engineer / Producer) |
| --- | --- | --- |
| Overview, Optimize, Findings, Settings | ✓ | ✓ |
| Preset | — | ✓ |
| Governance (Trend, Debt, Budget, Ownership, Deep Scan) | — | ✓ |
| Redundancy | — | ✓ (only with an external similarity provider) |

## Scan Depths

Choose in the header: **Quick Safe** (registry/metadata, no asset load), **Full** (loads assets),
**Deep** (deep material/mesh metrics; Governance → Deep Scan). Every analyzer run honors the selected
depth; the commandlet honors `-QuickSafe` / `-FullScan` / `-DeepScan`.

Broad scans use an AssetRegistry-first pipeline. SCD gathers candidates once, reads cheap texture/material metadata from tags where possible, compares tag-first, and deep-loads only the survivor set that needs object data. The read-only comparison stage can run in parallel; mutating QuickFixes still require explicit user or commandlet action.

Duplicate and alpha paths share helper code between scan findings and reductions. Texture/material alpha checks use the same material-instance opacity logic, and reduction early-outs use reduction-aligned duplicate keys so a safe consolidation is not skipped just because the stricter scan index did not group the assets.

## Core Workflow — Safe Optimization Loop (no AI)

1. Open the tool.
2. Pick scan depth (Quick Safe / Full / Deep).
3. Run the scan from the header.
4. Review **Overview**, then **Optimize → Safe Optimization Queue**.
5. **Preview Safe** → back up / source control → **Apply Safe**.
6. The shell re-scans automatically after a successful apply or single-asset fix.
7. Compare queue counts and the delta; JSON reports land under
   `Saved/SmartContentDiet/OptimizationQueue/<timestamp>/`.

## General Analysis Workflow

1. Run a scan (selection, folder, or project scope).
2. Review findings by severity, impact, dimension, and explainability chain.
3. Use **Preset** (advanced) to see how evaluation weights affect scores.
4. Use **Governance** (advanced) for trend, debt, budget, ownership, optional Deep Scan.
5. Apply QuickFixes only after confirming backup/source control.
6. Re-scan and validate in the target project context.

## Safety

Mutating actions modify project assets and are approval-gated by default. Run them only in a
backed-up, source-controlled, disposable workspace. See the safety notice in
[QUICKSTART.md](QUICKSTART.md).

## Editor Jobs And UCM

Recent editor work is recorded as job history for scans, validation, and optimization actions. When Unreal Capability Mesh is enabled, SCD exposes read-only job routes:

```text
scd.editor.jobs.list.v1
scd.editor.jobs.status.v1
```

Unified MCP Server can aggregate those routes through `jobs_list` / `jobs_status`; SCD itself does not depend on UMCP.

## Detailed Guides

- Editor shell, tabs, findings, QuickFixes, governance: [../Resources/UI_AND_BEHAVIOR.md](../Resources/UI_AND_BEHAVIOR.md).
- Safe Optimization Queue (buckets, safety rules, report schema): [../Resources/OPTIMIZATION_QUEUE.md](../Resources/OPTIMIZATION_QUEUE.md).
- Architecture: [../Resources/SMART_ANALYSIS_ARCHITECTURE.md](../Resources/SMART_ANALYSIS_ARCHITECTURE.md).
