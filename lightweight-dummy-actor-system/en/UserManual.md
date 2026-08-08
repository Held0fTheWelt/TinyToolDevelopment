# User Manual

LightweightDummyActorSystem (LDAS) is an autonomous runtime representation service for dummy-actor workflows. MVP 1+2+3 ships Runtime, Editor, and DeveloperTool modules.

## Capabilities Implemented

| Capability | Primary types |
| --- | --- |
| Subject registration | `ULDASWorldSubsystem::RegisterSubject`, `RegisterSubjectFromProfile`, `UnregisterSubject` |
| Readiness query | `QueryReadiness` → `FLDASReadinessReport` |
| Promotion / demotion | `RequestPromotion`, `RequestDemotion` with `ELDASTransitionReason` |
| Dummy representation | `ALDASLightweightDummyActor`, `ULDASDummyActorComponent` |
| Profile asset | `ULDASRepresentationProfile` |
| Diagnostics | `ULDASDiagnosticsSubsystem` |
| Editor inspector | `SLDASRepresentationInspector` |
| Validation | `FLDASEditorValidationService`, `ULDASValidateContractsCommandlet` |

<!-- image slot: ldas-inspector -->

## Runtime Flow

1. Obtain `ULDASWorldSubsystem` from the world.
2. Register a subject with a descriptor or a `ULDASRepresentationProfile`.
3. Query readiness for the desired representation kind.
4. Request promotion or demotion when policy and readiness allow it.
5. Inspect diagnostics / editor inspector when investigating failures.

Promotion and demotion are policy-gated. Built-in providers (`ULDASBuiltInReadinessProvider`, `ULDASBuiltInPromotionPolicy`, `ULDASBuiltInHeavyActorAdapter`) supply default behavior; projects may register additional providers in supported builds.

## Editor Surfaces

- Representation inspector for registered subjects.
- Editor validation service for contract checks.
- Developer commandlet for offline validation runs.

## Autarky And Optional Integrations

Core Runtime / Editor / DeveloperTool modules work without peer Tiny Tool plugins. The following remain **target-only** and must degrade gracefully when absent:

- WarCollection read-only pilot adapter
- Multiplayer pilot proof
- LightningCore entity bridge
- UCM / PIO / BPJ automation bridges

Do not treat those adapters as setup requirements for the shipped core.

## Related Documents

- [QUICKSTART.md](QUICKSTART.md)
- [SettingsReference.md](SettingsReference.md)
- [FAQ.md](FAQ.md)
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md)
- [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md)
