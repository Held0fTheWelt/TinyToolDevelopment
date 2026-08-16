<!-- doc-provenance: product-facts.yml reconciled 2026-07-19; source AKDB:plugins/BestPracticesJournal/architecture.md; release 1.1.2 -->
# User Manual

Best Practices Journal is an editor workbench for evidence-backed engineering practice governance.
It is decision support and review memory, not a patch planner, source editor, AI executor, or asset
mutation tool.

## Core Workflow

1. Capture a practice or candidate from a manual note, evidence reference, or optional provider.
2. Add applicability, trade-offs, failure modes, provenance, rights notes, and review metadata.
3. Validate the record before accepting or exporting it.
4. Search practices when choosing guidance for a task or review.
5. Create an application brief for a reviewed practice or explicit candidate.
6. Hand the brief to a human workflow, UCI, PRS, or another approved executor.
7. Import implementation outcome reports to record whether the practice was validated, weakened, contradicted, specialized, or superseded.

## Practice Record Quality

Use BPJ for practices that can survive review. A useful record includes:

- A concrete problem and target context.
- A solution stated as reusable guidance, not copied implementation code.
- Why the guidance works, where it applies, and where it fails.
- Trade-offs, preconditions, adaptation rules, and failure modes.
- Evidence references, provenance, rights notes, confidence, and review status.

If those fields are unknown, keep the item as a candidate or draft. Do not promote it to accepted
guidance just because the summary sounds plausible.

## Public Operations

- **Create practice record** stores a reviewed or draft practice with evidence, context, trade-offs, and review state.
- **Create practice candidate** stores a draft or provider-derived proposal until it is explicitly reviewed.
- **Attach evidence** links local/manual/provider proof without copying restricted implementation code.
- **Search practices** returns matching practice records from the BPJ-owned artifact store.
- **Create application brief** exports an intent-only handoff for a specific target context.
- **Import implementation outcome** closes the loop after implementation or rejection.

## Application Briefs

A brief should help another workflow plan safely. It can include target project/module/scope,
recommended adaptation, reasoning, constraints, allowed and forbidden action categories, validation
requirements, expected outputs, evidence references, approval state, and compatibility notes.

A brief must not act as BPJ's permission to mutate files. If the downstream tool applies changes, it
must own scope resolution, dry-run planning, approval, mutation gates, validation, rollback, and its
own outcome report.

## Outcome Imports

Import every meaningful outcome, including failed, rejected, partial, and no-op results. Outcomes
update practice history, confidence, review notes, and evolution links. They do not rewrite the
original practice as universally correct.

Use outcome fields for changed-file references, validation report paths, lessons learned,
recommended journal updates, warnings, errors, and links to external plans or reports.

## Optional Providers

Optional evidence, candidate, outcome, handoff, indexing, route, or implementation providers can
enrich BPJ. They must remain replaceable. If a provider is missing, continue with manual records,
local evidence, JSON/Markdown artifacts, and BPJ validation.

## Capability Mesh (MCP)

Agents without file access can close the review-first journal lifecycle over UMCP:

- `bpj.gather_candidates.v1` — scan provider inbox folders (including `project_intelligence_orchestrator` from PIO handoff).
- `bpj.repository.list.v1` — list practice, candidate, evidence, brief, and outcome ids.
- `bpj.practice.read.v1` — read one serialized record inline.
- `bpj.candidate.promote.v1` — promote a reviewed candidate (requires user approval on the route).
- `bpj.import_artifacts.v1` — import PIO candidate envelopes (`schema` / `schema_version` starting with `bpj.implementation_intent_candidates.`).

Provider inbox path: `Saved/BestPracticesJournal/provider_inbox/candidates/<provider_id>/`.

## Commandlets

Commandlets are useful for validation, artifact import, and sample export, but they are not mandatory
first-use steps. Use saved reports in `Saved/BestPracticesJournal/reports/` as durable evidence for
automation. Logs summarize what happened; saved artifacts remain the record.

## Boundaries

BPJ records knowledge and intent. It does not mutate source files, assets, Build.cs files, project descriptors, or external plugin code. Downstream execution owners must run their own preview, approval, validation, and rollback gates.

## Local Evidence And Logs

BPJ stores durable review evidence under `Saved/BestPracticesJournal/`. Use the JSON/Markdown files
in `reports`, `application_briefs`, `implementation_outcomes`, and `schemas` when sharing or
auditing a workflow. The Unreal log category `LogBestPracticesJournal` is for operator diagnostics
and commandlet summaries; it is not the source of record for accepted practices.
