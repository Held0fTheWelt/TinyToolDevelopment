# Lightning Core

Lightning Core is an advanced-preview, dependency-light runtime ECS foundation for Tiny Tool Development experiments. It provides generational entities, fragment registration, chunk storage, command buffers, arenas, a small world facade, and stats without editor UI or project gameplay policy.

Not a verbatim copy of shipped docs.

## What It Does

- Creates and destroys generational entity handles with stale-handle checks.
- Registers trivial fragment payload metadata and tag fragments.
- Stores archetype-backed entities in chunk-oriented fragment columns.
- Records supported command-buffer payloads for create, destroy, and set-fragment-value playback.
- Reports entity, fragment, archetype, chunk, command, payload, and arena counters.

## Best Entry Points

- Use the shipped `Documentation/QUICKSTART.md` for first C++ runtime integration.
- Use `Documentation/UserManual.md` for beta scope, supported primitives, and future-work boundaries.
- Use `Documentation/SettingsReference.md` and `Documentation/TROUBLESHOOTING.md` for construction values and common beta limitations.
