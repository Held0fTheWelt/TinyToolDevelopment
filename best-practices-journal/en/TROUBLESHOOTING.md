<!-- doc-provenance: product-facts.yml reconciled 2026-07-19; source AKDB:plugins/BestPracticesJournal/architecture.md; release 1.1.2 -->
# Troubleshooting

## Practice Validation Failed

**Cause:** The record is missing required context, applicability, evidence, trade-offs, failure modes, provenance, review state, or rights notes.

**Fix:** Open the practice, complete the missing fields, and validate again before accepting or exporting it.

## Practice Feels Too Generic

**Cause:** The record is written like a slogan or style preference instead of a reusable practice with
context and evidence.

**Fix:** Add the problem, target context, why it works, where it does not apply, trade-offs,
preconditions, failure modes, evidence refs, and validation requirements. Keep it as a candidate
until those fields are clear.

## Brief Guardrail Rejected

**Cause:** The application brief looks like an execution plan, lacks a reviewed source practice, contains copied implementation code, or tries to grant mutation authority.

**Fix:** Rewrite the brief as intent only. Include target context, recommended adaptation, constraints, required validation, and approval state, then let the downstream executor create its own plan.

## Outcome Import Reduced Confidence

**Cause:** The imported outcome reported failure, regression, rejection, partial success, or lessons
that contradict the original practice.

**Fix:** Keep the outcome. Update review notes, add a specialization or superseding practice if
needed, and avoid deleting negative evidence just to keep the original recommendation tidy.

## Provider Missing

**Cause:** Optional candidate, evidence, implementation outcome, or handoff providers are absent or disabled.

**Fix:** Continue with manual/local records or enable the optional provider. Provider absence is non-fatal for the standalone journal workflow.

## Provider Report Looks Redacted

**Cause:** BPJ redacts provider diagnostics before writing integration reports so prompts, tokens,
paths, and secret-like fields do not leak through shared artifacts.

**Fix:** Use the redacted report for sharing. Inspect local provider tooling only when you are allowed
to handle the raw diagnostics.

## Storage Backend Unavailable

**Cause:** The selected storage backend cannot open the configured path or external profile.

**Fix:** Return to `JsonArtifacts`, verify local paths, or correct the external database profile outside the shipped plugin package.

## Commandlet Output Is Hard To Find

**Cause:** The commandlet log only summarizes the operation; the saved report is the durable result.

**Fix:** Inspect `Saved/BestPracticesJournal/reports/` for validation and import reports. Filter
Unreal logs by `LogBestPracticesJournal` when you need surrounding diagnostics.
