# GameFeaturedClasses Documentation

GameFeaturedClasses is a lightweight runtime plugin shell for project-specific featured gameplay classes. Version `1.0.1` ships the descriptor, packaging metadata, icon, changelog, and a runtime module boundary (`StartupModule` / `ShutdownModule`).

Audience: teams that need the GFC package boundary in a project today while featured classes and the premium GameFeature Workbench remain target architecture (not yet available in this package).

## Current Package

- Runtime module `GameFeaturedClasses` loads after enable + restart.
- No gameplay featured-class assets, Game Feature actions, registry, or editor workbench are shipped yet.
- No other Tiny Tool plugin is required for the shell.

## Get Started

1. Enable the plugin — see [QUICKSTART.md](QUICKSTART.md) worked example (module smoke check).
2. Read [UserManual.md](UserManual.md) for current vs target boundary.
3. Use [TROUBLESHOOTING.md](TROUBLESHOOTING.md) when a workbench menu is expected but missing.

## Related Files

- [../README.md](../README.md) — product overview.
- [../CHANGELOG.md](../CHANGELOG.md) — release history.
- [SettingsReference.md](SettingsReference.md) · [FAQ.md](FAQ.md) · [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md)
