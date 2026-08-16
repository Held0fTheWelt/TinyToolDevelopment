<!-- doc-provenance: product-facts.yml reconciled 2026-07-19; source AKDB:plugins/BestPracticesJournal/architecture.md; release 1.1.2 -->
# Third Party Software

Best Practices Journal does not bundle third-party runtimes, model providers, database servers, or external executables.

Optional SQLite or Postgres workflows are storage profiles and external environment choices. They are not shipped as bundled third-party software in the plugin package.

If a project uses SQLite, Postgres, IIS, UCM, UCI, PRS, or any other optional ecosystem component,
that component remains an external project or studio choice. BPJ's shipped package must still open,
validate, import, export, and review JSON artifacts without those components.

Optional providers and consumers are integration surfaces, not bundled software. Their absence should
show up as status or diagnostics, not as a BPJ startup or first-use failure.
