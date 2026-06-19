# SmartContentDiet Documentation

SmartContentDiet scans Unreal Engine project assets, explains optimization
findings in context, exposes governance views, and offers reviewed QuickFix /
reduction workflows. The default product loop is **scan → review → apply safe
fixes → re-scan → measure improvement** — without requiring AI or external tools.

## Safety Notice

SmartContentDiet can modify project assets when QuickFixes, mesh reductions,
texture/material changes, asset review moves/deletes, baseline updates, or
governance writes are applied. Use it only in a backed-up, source-controlled,
disposable branch or workspace. Never run it on unprotected source. Use at your
own risk.

The functionality is implemented carefully within its stated scope, but it does
not replace backups, source control, code/content review, or project-specific
validation.

## Documentation Map

| Document | Audience | Contents |
|----------|----------|----------|
| [UI_AND_BEHAVIOR.md](../Resources/UI_AND_BEHAVIOR.md) | Artists, tech artists, producers | Editor shell, tabs, scan workflow, findings, QuickFixes, governance |
| [OPTIMIZATION_QUEUE.md](../Resources/OPTIMIZATION_QUEUE.md) | All editor users | Safe Optimization Queue, buckets, apply/preview, before/after delta |
| [SMART_ANALYSIS_ARCHITECTURE.md](../Resources/SMART_ANALYSIS_ARCHITECTURE.md) | Engineers, integrators | Analyzers, presets, impact, reduction, trend, governance architecture |
| [DIMENSION_INTEGRATION_STATUS.md](../Resources/DIMENSION_INTEGRATION_STATUS.md) | Engineers | FindingType, dimension mapping, converter, UI integration status |
| [SmartAnalysisResult_Usage.md](../Resources/SmartAnalysisResult_Usage.md) | Engineers | Result model usage, auto-fix metadata |
| [CHANGELOG.md](../CHANGELOG.md) | Release operators | Version history |

**New here?** Start with [QUICKSTART.md](QUICKSTART.md) for install and the safe scan→fix loop.

> **For maintainers:** the SCD release gate and release/runbook documents live in the development
> repository and are **not** part of the Fab package; you do not need them to install or use SCD.

## Editor Entry Point

Open **Tools → Content Tools → Smart Content Diet**.

### Role-aware shell

The main window uses audience settings (Beginner / Engineer / Producer) to control
explanation depth and which tabs are visible.

| Tab | Beginner | Advanced (Engineer / Producer + advanced mode) |
|-----|----------|--------------------------------------------------|
| Overview | ✓ | ✓ |
| Optimize | ✓ | ✓ |
| Findings | ✓ | ✓ |
| Preset | — | ✓ |
| Governance | — | ✓ (Trend, Debt, Budget, Ownership, Deep Scan as sub-tabs) |
| Redundancy | — | ✓ only when an external similarity provider is registered |
| Settings | ✓ | ✓ |

Change role and explanation level in **Settings** or via the audience selector in
the header.

### Scan depths (header)

| Depth | Loads assets? | Typical use |
|-------|---------------|-------------|
| **Quick Safe** (default) | No — registry/metadata path | First run, fast “what can I safely improve?” |
| **Full** | Yes — full analyzer pipeline | Actionable mesh/texture/material findings |
| **Deep** | Yes — includes deep material/static mesh metrics | Slowest; shader-stat and deep mesh work |

The header combo updates the primary scan button label (`Quick Safe Scan` /
`Full Scan` / `Deep Scan`) and shows a depth hint below the controls.

The selected depth is honored by **every** analyzer run: editor analysis runs
(Findings / Governance → Run analysis) pass it to `FSmartAnalysisOrchestrator`,
and the governance status line names the depth that was used. **Commandlet and
CI** honor `-QuickSafe`, `-FullScan`, and `-DeepScan` as before. The deep
material/mesh metrics additionally use the Governance Deep Scan workflow
(`Governance → Deep Scan`), same as the commandlet.

## Quick Workflows

### UCM ecosystem routes

When Unreal Capability Mesh (UCM) is enabled, SmartContentDiet can be used
through setup-declared routes instead of direct provider bridges. SCD never links a
peer plugin and never lists one in `required_plugin_names` or `Build.cs`;
cross-plugin value comes from JSON routes, not code dependencies. The active
project profile exposes **12 SCD capabilities**:

| Capability | Kind | Policy |
| --- | --- | --- |
| `scd.migration.advice_from_handoff` | advisory | read-only |
| `scd.scan.run` | provider | read-only |
| `scd.findings.get` | provider | read-only |
| `scd.findings.explain` | provider | read-only |
| `scd.health.snapshot` | provider | read-only |
| `scd.health.evidence` | provider | read-only |
| `scd.governance.snapshot` | provider | read-only |
| `scd.similarity.groups` | similarity | read-only |
| `scd.similarity.ingest_groups` | similarity | read-only |
| `scd.optimize.preview_safe` | optimization | read-only |
| `scd.optimize.apply_safe` | optimization | **mutating — requires approval** |
| `scd.optimize.apply_fix` | optimization | **mutating — requires approval** |

**Degradation contract.** Every capability returns the shared
`smart_content_diet.capability_mesh_endpoint.v1` envelope (`status` of
`ok`/`degraded`/`error`). Capabilities reduce, rather than fail, when a
precondition is missing: the optimize/findings routes return an `error` envelope
asking you to run `scd.scan.run` first; `scd.optimize.apply_fix` returns a
`degraded` envelope (no mutation) when a destructive fix is requested without
`allow_destructive: true`. Connecting SCD to a peer is never assumed — a route
that references another plugin (e.g. the example `scd_ingest_from_iis.v1`,
`iis.search.hybrid → scd.similarity.ingest_groups`) is reported by UCM discovery
as *available but plugin not loaded* when that peer is absent, while every
SCD-only capability stays *available*.

**Approval gate (and Option 3).** The two mutating routes carry
`requires_user_approval: true`, so UCM blocks them with `ApprovalRequired` until a
human approves the run — no asset is touched before then. Operators who want
unattended safe-apply can flip the route policy to drop the approval requirement
(Option 3); the default ships approval-gated.

PRS placement workflows remain PRS-owned UCM routes. Freebie Bridges remain
available only for teams without UCM and as reference implementations for direct
adapters; they are not required in the main project.

### Standalone safe optimization loop (no AI)

### Scan correctness and performance

The current analyzer path is AssetRegistry-first. It builds the broad candidate set once, reads tag metadata before loading assets, parallelizes read-only comparison work, and deep-loads only final candidates. A per-asset metadata cache with timestamp/version invalidation avoids repeating unchanged work.

Duplicate and alpha analysis share helpers with the reduction engine. Reduction early-outs use reduction-aligned duplicate keys (`DuplicateTextureReduction`, `DuplicateStaticMeshReduction`) so safe consolidation checks match the fingerprint logic used by the actual reducer. Texture alpha heuristics are centralized in `SCDMaterialAlpha` to keep analyzer and reduction behavior aligned.

Editor job history is available through UCM routes (`scd.editor.jobs.list.v1`, `scd.editor.jobs.status.v1`) for UMCP aggregation without adding a UMCP dependency to SCD.

1. Open Smart Content Diet.
2. Leave scan depth on **Quick Safe** or choose **Full** / **Deep**.
3. Run the scan from the header.
4. Review **Overview**, then open **Optimize** → Safe Optimization Queue.
5. **Preview Safe** → **Apply Safe** (backup / source control first).
6. After a successful apply or a single-asset fix from **Findings** detail, the
   shell re-scans automatically.
7. Compare queue counts and the delta summary in the Optimize panel; JSON apply
   reports land under `Saved/SmartContentDiet/OptimizationQueue/<timestamp>/`.

See [OPTIMIZATION_QUEUE.md](../Resources/OPTIMIZATION_QUEUE.md) for bucket
definitions, safety rules, and report schema.

### General analysis workflow

1. Run a scan (selection, folder, or project scope).
2. Review findings by severity, impact, dimension, and explainability chain.
3. Use **Preset** (advanced) to understand how evaluation weights affect scores.
4. Use **Governance** (advanced) for trend, debt, budget, ownership, optional Deep Scan.
5. Apply QuickFixes only after confirming backup/source control.
6. Re-scan and validate in the target project context.

## Commandlet (CI / headless)

```powershell
UnrealEditor-Cmd.exe "D:\Path\Project.uproject" -run=SmartContentDiet `
  -QuickSafe -OptimizationQueueReport -Path=/Game -Limit=50 `
  -NoFail -unattended -nop4 -nosplash
```

Apply safe queue rows (backed-up project only):

```powershell
UnrealEditor-Cmd.exe "D:\Path\Project.uproject" -run=SmartContentDiet `
  -QuickSafe -ApplySafeQueue -OptimizationQueueReport -Path=/Game `
  -NoFail -unattended -nop4 -nosplash
```

| Flag | Effect |
|------|--------|
| `-QuickSafe` | Registry/dependency scan; does not load assets |
| `-FullScan` | Load assets and run analyzers (default when `-QuickSafe` absent) |
| `-DeepScan` | Slowest depth; deep material/mesh metrics |
| `-OptimizationQueueReport` | Write queue JSON/Markdown (auto-enabled with `-QuickSafe`) |
| `-ApplySafeQueue` | Apply **Safe Now** rows only; destructive rows are rejected |
| `-Path=/Game/...` | Scan scope |
| `-NoFail` | Exit 0 even when policy warnings exist (use with care in CI) |

The commandlet prints the safety warning at usage and run start. Baseline
updates and report writes are workspace-mutating operations.

## Artifact Locations (gitignored)

| Artifact | Path |
|----------|------|
| Optimization queue apply report | `Saved/SmartContentDiet/OptimizationQueue/<timestamp>/apply_report.json` |
| Commandlet queue report | `-ReportDir` / default under `Saved/SmartContentDiet/` |
| Release gate output | `Saved/SCDValidation/` (via `Gates/scd_gate/run_scd_gate.py`) |

## Implemented QuickFix Scope (summary)

SmartContentDiet offers reviewed QuickFixes across texture, static/skeletal mesh,
material, animation, audio/VFX hygiene, and asset review/consolidation. Destructive
or cross-asset actions require explicit confirmation and are not batch-safe by
default.

Full catalog: [UI_AND_BEHAVIOR.md § Optimization Packs](../Resources/UI_AND_BEHAVIOR.md#71-optimization-packs).

## Release Validation

```powershell
cd D:\TinyToolDevelopment\Git
python Gates/scd_gate/run_scd_gate.py `
  --profile release --strict `
  --config Gates/scd_gate/config.json
```

Copy `config.example.json` to `config.json` and set absolute `engine_root` and
`project_file` paths for your machine.
