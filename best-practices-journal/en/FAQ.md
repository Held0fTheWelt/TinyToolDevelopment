<!-- doc-provenance: product-facts.yml reconciled 2026-07-19; source AKDB:plugins/BestPracticesJournal/architecture.md; release 1.1.2 -->
# FAQ

## Is BPJ a generic note-taking tool?

No. BPJ is for evidence-backed engineering practices with applicability, trade-offs, failure modes, provenance, review state, and outcome history.

## When should something stay a candidate?

Keep it as a candidate when evidence, applicability, trade-offs, failure modes, provenance, or review
state are incomplete. Candidates can be useful, but they should not be treated as accepted guidance.

## Does BPJ change project files?

No. BPJ can create application briefs and import outcomes, but project mutation belongs to approved downstream tools or human workflows.

## What belongs in an application brief?

Use a brief for target context, recommended adaptation, constraints, evidence references, required
validation, and approval status. Do not use it as a patch plan or mutation command.

## Does BPJ require IIS, SDA, UCI, PRS, UCM, or LLM Store?

No. BPJ is standalone. Optional Tiny Tool plugins can provide evidence, indexing, documentation, implementation, or route workflows, but they are not required for core use.

## Can BPJ call AI or decide implementation steps?

No. BPJ may store evidence or intent created by another reviewed workflow, but it does not own AI
execution, retrieval, patch planning, apply, rollback, or final validation.

## Where is data stored?

The default profile uses project-local JSON artifacts under the BPJ storage root. Optional SQLite or external studio profiles can be configured for larger workflows.

## What data can be sensitive?

Practice records, evidence, briefs, outcomes, and reports may contain local paths, project names,
review notes, validation output, rights notes, or provider diagnostics. Review and redact exports
before sharing.

## Where do I find logs and reports?

Reports are saved below `Saved/BestPracticesJournal/reports/`. Runtime, editor, and commandlet
diagnostics use `LogBestPracticesJournal` in the Unreal log. Saved artifacts remain the durable
evidence.

## Can I share practices with a team?

Yes, after review. Treat exports as project-local until they have been sanitized for private paths, confidential notes, and rights-sensitive evidence.

## Can missing optional providers break the journal?

No. Missing providers should appear as status or diagnostics only. Manual records, local evidence,
validation, export, and outcome import must remain available.

## Should failed outcomes be imported?

Yes. Failed, rejected, partial, and no-op outcomes are important because they can weaken,
contradict, specialize, or supersede the practice. Hiding them makes the journal less trustworthy.
