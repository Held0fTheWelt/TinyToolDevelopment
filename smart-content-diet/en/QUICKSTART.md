<!-- doc-provenance: AKDB:plugins/SmartContentDiet/architecture.md; docs/architecture/plugins/SmartContentDiet/product-facts.yml; reconciled 2026-07-16 -->
# Quick Start

This guide takes you from install to a **real result**: a scan of your project's assets with
optimization findings, and (optionally) a reviewed safe fix applied with before/after reporting.
Smart Content Diet's core loop works on its own — **no AI, peer plugin, or external tool required**.

> **⚠ Safety first.** Applying fixes, reductions, asset moves/deletes, baseline updates, or
> governance writes **modifies project assets**. Only do so in a **backed-up, source-controlled,
> disposable** workspace — never on unprotected source. Scanning and previewing are read-only and
> safe.

## What You'll Have After This Guide

The tool open in your chosen role, a Quick Safe scan completed with findings, and an understanding of
how to preview and apply safe optimizations and read the before/after delta.

## Requirements

- Unreal Engine 5.4+ editor with a project that has content assets.
- No third-party software, account, AI model, or external runtime. See
  [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## 1. Install And Enable

1. Add **SmartContentDiet** from your Fab library to the project (or install to the engine).
2. Open **Edit → Plugins**, enable **SmartContentDiet**, and restart when asked.

## 2. Open The Tool And Pick A Role (First Result)

1. Open **Tools → Content Tools → Smart Content Diet**.
2. In the header audience selector (or **Settings**), pick your role:
   - **Beginner** — Overview, Optimize, Findings, Settings; more explanation.
   - **Engineer / Producer (advanced)** — adds Preset and Governance (Trend, Debt, Budget,
     Ownership, Deep Scan), and Redundancy when an external similarity provider is registered.
3. Leave **scan depth** on **Quick Safe** (default — registry/metadata only, no asset loading; fast).
4. Click **Quick Safe Scan** in the header.

**Expected output:** the scan completes and the **Overview** tab summarizes findings (what can be
safely improved). This is read-only.

## 3. A Real Worked Example: Preview And Apply A Safe Fix

> Back up / commit your project first (see the safety note above).

1. Open the **Optimize** tab → **Safe Optimization Queue**.
2. Click **Preview Safe** to see the queued safe optimizations and the projected before/after delta
   (still read-only).
3. Click **Apply Safe** to apply the safe queue. After a successful apply (or a single-asset fix from
   a **Findings** detail), the shell **re-scans automatically**.
4. Compare the queue counts and delta summary in the Optimize panel.

**Expected output:** safe optimizations are applied and a JSON apply report is written under:

```text
Saved/SmartContentDiet/OptimizationQueue/<timestamp>/
```

## 4. Scan Depths

| Depth | Loads assets? | Use |
| --- | --- | --- |
| **Quick Safe** (default) | No | Fast "what can I safely improve?" |
| **Full** | Yes | Actionable mesh/texture/material findings |
| **Deep** | Yes | Slowest; deep material/static-mesh metrics (Governance → Deep Scan) |

The header button label and hint update with the selected depth, which every analyzer run honors.

## 5. Next Steps

- Editor shell, tabs, findings, governance: [../Resources/UI_AND_BEHAVIOR.md](../Resources/UI_AND_BEHAVIOR.md).
- Safe Optimization Queue (buckets, safety rules, report schema):
  [../Resources/OPTIMIZATION_QUEUE.md](../Resources/OPTIMIZATION_QUEUE.md).
- Settings and roles: [SettingsReference.md](SettingsReference.md).
- Problems: [TROUBLESHOOTING.md](TROUBLESHOOTING.md) and [FAQ.md](FAQ.md).

> **Optional / advanced:** SCD also offers a headless commandlet for CI (`-QuickSafe`, `-FullScan`,
> `-DeepScan`, `-OptimizationQueueReport`, `-ApplySafeQueue`) and — only if you also own
> **Unreal Capability Mesh (UCM)** — optional setup-declared ecosystem routes. Neither is needed
> for the editor workflow above; see the [documentation index](README.md).
