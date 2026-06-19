# Settings Reference

## Role / Audience

Set in **Settings** or the header audience selector. Controls explanation depth and tab visibility:

- **Beginner** — Overview, Optimize, Findings, Settings.
- **Engineer / Producer (advanced)** — adds Preset and Governance (Trend, Debt, Budget, Ownership,
  Deep Scan); Redundancy appears only when an external similarity provider is registered.

## Scan Depth (header)

| Depth | Loads assets? | Notes |
| --- | --- | --- |
| `Quick Safe` (default) | No | Registry/metadata path; fast first pass. |
| `Full` | Yes | Full analyzer pipeline; actionable mesh/texture/material findings. |
| `Deep` | Yes | Deep material/static-mesh metrics; uses Governance → Deep Scan; slowest. |

The selected depth is honored by every analyzer run (editor and commandlet).

Quick Safe is the AssetRegistry-first path: broad scans avoid hard-loading assets unless a candidate survives cheap metadata checks. Full and Deep may load assets for actionable analyzer detail.

## Output Locations

```text
Saved/SmartContentDiet/OptimizationQueue/<timestamp>/   ← safe-queue apply reports
```

## Approval / Safety

Mutating capabilities (`scd.optimize.apply_safe`, `scd.optimize.apply_fix`) are **approval-gated by
default**. Destructive fixes require explicit `allow_destructive: true`. Run mutations only in a
backed-up, source-controlled, disposable workspace.

## Commandlet (CI / headless)

Switches: `-QuickSafe`, `-FullScan`, `-DeepScan`, `-OptimizationQueueReport`, `-ApplySafeQueue`,
`-Path=`, `-Limit=`, `-NoFail`, plus the standard `-unattended -nop4 -nosplash`. Apply switches
should target backed-up projects only.

## Optional Ecosystem Routes

When **Unreal Capability Mesh (UCM)** is enabled, SCD exposes read-only provider capabilities and
two approval-gated mutating optimize routes through JSON-declared UCM routes. SCD never links a peer
plugin in code; this integration is entirely optional. See the [documentation index](README.md) and
[../Resources/SMART_ANALYSIS_ARCHITECTURE.md](../Resources/SMART_ANALYSIS_ARCHITECTURE.md).

SCD also exposes read-only editor job routes (`scd.editor.jobs.list.v1`, `scd.editor.jobs.status.v1`) for UMCP aggregation through UCM.

For deeper analyzer/preset/governance settings, see
[../Resources/SMART_ANALYSIS_ARCHITECTURE.md](../Resources/SMART_ANALYSIS_ARCHITECTURE.md).
