<!-- doc-provenance: AKDB:plugins/SmartContentDiet/architecture.md; docs/architecture/plugins/SmartContentDiet/product-facts.yml; reconciled 2026-07-16 -->
# FAQ

**Does Smart Content Diet require AI, an account, or another plugin?**
No. The core loop (scan → review → apply safe fixes → re-scan → measure) runs entirely in the editor
with no AI service, account, or peer plugin. Optional ecosystem routes via **Unreal Capability
Mesh (UCM)** exist but are never required.

**Is it safe to run?**
Scanning and previewing are read-only. Applying fixes/reductions/moves/deletes **modifies project
assets** — only do so in a backed-up, source-controlled, disposable workspace. Mutating routes are
approval-gated by default. Use at your own risk.

**What engine versions are supported?**
Unreal Engine 5.4+. It is an editor plugin.

**What's the difference between Quick Safe, Full, and Deep scans?**
Quick Safe uses registry/metadata only (no asset loading, fast). Full loads assets for actionable
mesh/texture/material findings. Deep adds deep material/static-mesh metrics and is the slowest.

**Why can't I see the Preset or Governance tabs?**
They are advanced (Engineer / Producer) tabs. Switch role in Settings or the header.

**Can I run it in CI / headless?**
Yes. A commandlet supports `-QuickSafe` / `-FullScan` / `-DeepScan`, `-OptimizationQueueReport`, and
`-ApplySafeQueue` (apply only on backed-up projects).

**Does it bundle third-party software?**
No. See [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

**Where do I get support?**
Use the support link on the Fab product page.
