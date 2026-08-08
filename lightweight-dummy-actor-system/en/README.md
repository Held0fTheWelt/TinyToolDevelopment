# LightweightDummyActorSystem Documentation

LightweightDummyActorSystem (LDAS) is an autonomous runtime representation service for dummy-actor workflows. MVP 1+2+3 ships Runtime, Editor, and DeveloperTool modules: subject registration, readiness queries, promotion/demotion policy gates, dummy actor representation, diagnostics, editor inspector, and a validate commandlet.

Audience: gameplay and tools engineers who need lightweight dummy representations with policy-gated promotion/demotion without requiring peer Tiny Tool plugins for the core package.

## Capabilities (shipped)

- `RegisterSubject` / `RegisterSubjectFromProfile` / `UnregisterSubject`
- `QueryReadiness` → `FLDASReadinessReport`
- `RequestPromotion` / `RequestDemotion`
- `ULDASRepresentationProfile`, `ALDASLightweightDummyActor`, `ULDASDummyActorComponent`
- Editor inspector and `ULDASValidateContractsCommandlet`

## Get Started

1. Enable the plugin — see [QUICKSTART.md](QUICKSTART.md) worked example (register + query readiness).
2. Configure a `ULDASRepresentationProfile` Data Asset with real distance/cooldown values.
3. Read [UserManual.md](UserManual.md) and [SettingsReference.md](SettingsReference.md).

## Related Files

- [../README.md](../README.md) — product overview.
- [../CHANGELOG.md](../CHANGELOG.md) — release history.
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md) · [FAQ.md](FAQ.md) · [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md)
