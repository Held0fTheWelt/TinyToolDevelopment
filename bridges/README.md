# UCM Bridge Catalog

Collects every cross-plugin UCM bridge and connects the two plugins each one joins. Source of truth: `catalog.json` (+ `bridge-rules.json` for the governance rule). Governed by SAD-TTD-0002 §6 and the Plugin Ecosystem & Bridge Topology SAD; built UCM-first per ADR-INT-0001. Bridges are optional and never shipped in Fab packages.

| Bridge | Plugin A | Plugin B | Mechanism | Route / contract | Since |
|---|---|---|---|---|---|
| BRIDGE-SCD-IIS-0001 | SmartContentDiet | InternalIndexService | UCM route | `scd.migration.advice_from_handoff` / `scd-iis-advice.v1` | 1.0.3 |
