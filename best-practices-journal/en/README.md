<!-- doc-provenance: product-facts.yml reconciled 2026-07-19; source AKDB:plugins/BestPracticesJournal/architecture.md; release 1.1.2 -->
# Best Practices Journal Documentation

Best Practices Journal helps teams govern reusable engineering practices directly inside the Unreal
Editor. It stores practice knowledge, provenance, review state, implementation intent, and outcome
history under a BPJ-owned local artifact root.

Version 1.1.2 supports Unreal Engine 5.4 and later. Imported evidence and provider output remain
reviewable candidates until explicit human promotion; no external producer can accept a practice.

BPJ is standalone. Optional ecosystem providers can supply evidence, candidates, outcomes, or handoff
destinations, but the journal, validation, search, export, and outcome loop must remain usable when
every optional provider is absent.

## Main Concepts

- Practice records describe reusable engineering guidance, context, trade-offs, applicability, failure modes, and review state.
- Practice candidates are drafts or provider-derived proposals that still require review.
- Evidence records connect practices to project-local proof, provenance, rights notes, and confidence.
- Application briefs describe intent for adapting a reviewed practice to a specific target.
- Outcome imports record whether downstream work validated, weakened, contradicted, specialized, or superseded a practice.
- Redaction and guardrail policies keep shared records intentional.
- Storage backends let BPJ run as JSON artifacts, local SQLite, or a Postgres-backed studio profile.

## Product Boundary

BPJ owns practice records, candidates, evidence references, review state, application briefs,
implementation outcome imports, deterministic exports, schema validation, redaction, guardrails, and
local reports. It does not own patch planning, dry-run/apply, rollback, final implementation
validation, AI execution, or source/asset mutation.

Application briefs are intent-only handoff artifacts. Downstream tools or human workflows must still
perform their own planning, approval, mutation, validation, and rollback steps.

## Acceptance Contract

An accepted practice should not be just a slogan. Before acceptance or broad reuse, record:

- Problem, context, and solution.
- Why it works and where it applies.
- Preconditions, adaptation rules, trade-offs, and failure modes.
- Evidence references, provenance, rights notes, and confidence.
- Review status, reviewer notes, and outcome history when available.

Weak or missing fields should be treated as validation findings, not as harmless formatting issues.

## Brief And Outcome Contract

Application briefs may include practice identity, target context, recommended adaptation, constraints,
allowed and forbidden action categories, validation requirements, expected outputs, evidence
references, approval state, and compatibility notes. They must not include copied implementation code
or grant mutation authority.

Outcome imports update history and practice confidence. A failed or rejected outcome is useful data:
it should be imported instead of hidden, because it may weaken, contradict, specialize, or supersede
the original practice.

## Local Artifacts And Logging

BPJ writes project-local artifacts below `Saved/BestPracticesJournal/`, including `practices`,
`candidates`, `evidence`, `application_briefs`, `implementation_outcomes`, `reports`, `schemas`,
`logs`, and `provider_inbox`. Unreal diagnostics use `LogBestPracticesJournal`; durable operator
evidence should be taken from the saved JSON/Markdown artifacts rather than transient log lines.

## Buyer Docs

- [Quickstart](QUICKSTART.md)
- [User Manual](UserManual.md)
- [Settings Reference](SettingsReference.md)
- [Troubleshooting](TROUBLESHOOTING.md)
- [FAQ](FAQ.md)
- [Third Party Software](THIRD_PARTY_SOFTWARE.md)
- [Storage Backends](StorageBackends.md)

## Operator Surfaces

- Editor workbench: create, review, search, brief, import outcomes, and inspect integration status.
- Saved artifacts: JSON/Markdown records under `Saved/BestPracticesJournal/`.
- Commandlets: validation, artifact import, and sample export for automation and release checks.
- Optional routes/providers: replaceable integration surfaces that must not become first-use requirements.

## Workflows

1. Open `Tools > Best Practices Journal`.
2. Create or import practice records.
3. Attach evidence and review status.
4. Validate and review the record before acceptance.
5. Produce an intent-only application brief when implementation context is known.
6. Import outcomes after downstream work is complete.

## Related Files

- [../README.md](../README.md): quick start.
- [../CHANGELOG.md](../CHANGELOG.md): release history.
- [StorageBackends.md](StorageBackends.md): JSON, SQLite, and Postgres storage modes.
