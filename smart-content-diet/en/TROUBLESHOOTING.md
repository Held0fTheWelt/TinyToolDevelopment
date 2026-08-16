<!-- doc-provenance: AKDB:plugins/SmartContentDiet/architecture.md; docs/architecture/plugins/SmartContentDiet/product-facts.yml; reconciled 2026-07-16 -->
# Troubleshooting

## I enabled the plugin but don't see it

Open **Tools → Content Tools → Smart Content Diet**. If the menu entry is missing, confirm the
plugin is enabled in *Edit → Plugins* and that you restarted the editor.

## A tab I expected (Preset / Governance / Redundancy) isn't visible

Tab visibility is role-aware. **Preset** and **Governance** appear for **Engineer / Producer**
(advanced mode); **Redundancy** appears only when an external similarity provider is registered.
Change your role/explanation level in **Settings** or the header audience selector.

## The scan returns little or nothing

**Quick Safe** uses the registry/metadata path only (no asset loading), so some findings need a
heavier pass. Switch the header depth to **Full** (loads assets) or **Deep** (deep material/mesh
metrics) and run again.

## "Run scan first" / empty findings or optimize

Findings and optimize actions require a completed scan. Run a scan from the header first, then open
**Findings** or **Optimize**.

## Apply is blocked or asks for approval

Mutating actions are approval-gated by default and must run in a backed-up, source-controlled,
disposable workspace. Confirm your backup/source control, then approve the action. Destructive fixes
additionally require explicit opt-in (`allow_destructive: true` on the relevant route).

## Where are the apply reports?

```text
Saved/SmartContentDiet/OptimizationQueue/<timestamp>/
```

## A cross-plugin route shows "available but plugin not loaded"

That is expected and safe: SCD never hard-requires a peer plugin. Routes that reference another
plugin (e.g. an IIS similarity ingest) report as *available but plugin not loaded* when that peer is
absent, while every SCD-only capability stays available.
