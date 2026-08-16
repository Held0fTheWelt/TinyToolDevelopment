<!-- doc-provenance: product-facts.yml reconciled 2026-07-19; source AKDB:plugins/BestPracticesJournal/architecture.md; release 1.1.2 -->
# Quickstart

## Goal

Create a standalone, project-local practice journal, capture evidence, review a practice, export an
implementation-intent brief, and import an outcome without changing project source or assets.

## First Run

1. Enable **Best Practices Journal** in the Unreal Editor plugin browser.
2. Restart the editor when prompted.
3. Open **Tools > Best Practices Journal**.
4. Create a practice candidate first if the guidance is not reviewed yet.
5. Fill in problem, context, solution, applicability, trade-offs, preconditions, and failure modes.
6. Attach local evidence or a manual evidence note with provenance and rights notes.
7. Validate the record and add reviewer notes before treating it as accepted guidance.
8. Use **Search practices** to find the record again by topic, tag, or evidence note.
9. Create an application brief for a specific target and review the JSON/Markdown export.
10. Import an implementation outcome after downstream work is complete.

BPJ is standalone: optional evidence providers, UCM routes, IIS, SDA, UCI, or PRS can enrich the workflow, but the core journal, review, export, and outcome loop work without any other Tiny Tool plugin.

## Verify The Result

After the first run, review the saved artifacts under `Saved/BestPracticesJournal/`:

- `practices/` contains practice records.
- `application_briefs/` contains intent-only handoff files.
- `implementation_outcomes/` contains imported outcome records.
- `reports/` contains validation, import, and operator reports.

These files are the durable evidence for review and handoff. Unreal log output is useful for
diagnostics, but it is not the source of record.

## Boundary Check

An application brief should describe intent, target context, constraints, required validation, and
approval state. It should not contain copied implementation code, patch instructions, rollback steps,
or permission for BPJ to modify project files.

## Good First Practice

Start with a small practice that has real evidence, such as a project-specific logging convention or
review checklist. Avoid writing a broad rule like "write better code" unless you can add context,
failure modes, examples of evidence, and validation requirements.

## Good First Outcome

After a downstream workflow tries the brief, import an outcome even if nothing changed. `rejected`,
`failed`, `partial`, and `no_op` outcomes are useful because they stop BPJ from presenting an
overgeneralized practice as proven.
