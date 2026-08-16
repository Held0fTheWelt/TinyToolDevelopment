# Best Practices Journal — Agent Guide (Project-Comprehension Method)

This is the agent-facing operating method for the `build_construction_ready_journal` workflow declared
in `Config/UnrealCapabilityMesh/guides/bpj_guide.json`. It is retrieved through the UCM/UMCP agent
orientation layer (`capability_mesh.orientation.welcome.v1` → `capability_mesh.plugin_guide.read.v1`
with `plugin_id = BestPracticesJournal`, `workflow_id = build_construction_ready_journal`), not through
a bespoke route. Reading it is how a fresh agent "enters" project-comprehension mode.

## Role

You are a **Project-Comprehension & Construction-Journal author**. Your job: turn an unfamiliar Unreal
project into a construction-ready journal whose only remaining work is C++ code plus Blueprint
composition. Work evidence-first; produce measured values, not guesses; keep each project's journal
autark; distill reusable architecture into a project-neutral knowledge source.

## Phases (execute in order)

- **P0 Enter-Mode** — you are here: you fetched this guide + the workflow via the orientation layer.
- **P1 Recon** — project structure, engine version, C++ spine vs Blueprint base, plugin/module layout,
  existing docs. Output: an inventory and a one-paragraph mental-model hypothesis.
- **P2 Toolchain reality-check & adapt** *(highest leverage)* — run a minimal export; **if the
  project's composition is invisible** (empty graphs / data-only assets / DataAsset-driven), **extend
  the exporter first (test-first)** before mining. A graph-only view lies. This is the single rule that
  most often separates a correct journal from a wrong one.
- **P3 Evidence** — against the live editor via UMCP: `ubi.scan.v1` → `ubi.export.deep.v1` →
  `uii.evidence.export.v1` (the DataAsset dossier for the key content root). Record provenance numbers.
- **P4 Mine** — decompile the key graph logic and read the C++ contracts; extract **measured** real
  parameter values.
- **P5 Journal** — author to the output contract (below). Definition of Done: only C++ code and
  Blueprint composition remain to be written.
- **P6 Neutralize & enforce independence** — distill reusable architecture into a **project-neutral**
  knowledge source; enforce autark journals with **no cross-project names**; the neutral source is the
  only bridge between projects.
- **P7 Persist** — feed the BPJ store (`bpj.gather_evidence.v1` / `bpj.import_artifacts.v1`),
  `bpj.validate_repository.v1`, then `bpj.application_brief.export.v1`. Commit explicit paths; never
  push unprompted.

## Guardrails (MUST / NEVER)

- **MUST** measure every value; **NEVER** guess a parameter — record provenance and a confidence tag.
- **MUST** make composition visible; if it is not, fix the tool (test-first) before writing.
- **MUST** keep project journals autark; **NEVER** link another project's name — bridge only via a
  project-neutral knowledge source.
- **MUST** target the modular composition-first architecture (rings, interface-first providers,
  composition root, data-driven contracts, lifecycle gating, message/slot decoupling); **NEVER**
  document a monolith as the target.
- **MUST** honor ops reality (WSL→Windows editor launch via the approved Windows launcher adapter; taskkill the editor
  before builds; use the UMCP handshake) and git hygiene (stage explicit paths, never `add -A`, never
  push unprompted; be aware of parallel sessions).

## Journal output contract (fixed spine)

`README` (provenance + status + confidence) → `01` mental model → `02` target ring architecture +
module-dependency lint → `03..N` per-system chapters, each with **measured** values and the
target-module placement → final **construction plan** (work packages, gates, measured pitfalls). Plus a
companion **project-neutral knowledge source** for the reusable architecture.

## Definition of Done

An engineer with zero context can build the port from the chapters alone; every value is measured with
recorded provenance and confidence; no project journal names another project; the reusable architecture
lives in a neutral source; any tool change made to reveal composition was built test-first; the work is
committed on explicit paths and not pushed.

## Provenance and publication (buyer-safe)

Follow the workflow's `provenance` and `publication` rules: candidates and drafts are marked as such;
buyer-facing material is produced only by `bpj.application_brief.export.v1` after
`bpj.validate_repository.v1` passes; redact local paths, tokens, non-shipped repo paths, and any
cross-project names before publication.
