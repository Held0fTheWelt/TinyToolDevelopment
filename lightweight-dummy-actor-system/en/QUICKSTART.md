---
title: LightweightDummyActorSystem Quick Start
audience: [end_user]
owner_ref: plugin:LightweightDummyActorSystem
applies_to:
  component: LightweightDummyActorSystem
preconditions:
  - Unreal Engine project open with the plugin package available
  - Edit > Plugins can enable LightweightDummyActorSystem
expected_result:
  text: Subject registers through ULDASWorldSubsystem and QueryReadiness returns a readiness report.
version:
  since: "1.0"
---
# Quick Start

This guide installs **LightweightDummyActorSystem (LDAS)** and walks through the first working subject registration using the shipped runtime API. MVP 1+2+3 is implemented: runtime core, transition core, editor inspector, and validate commandlet.

## What You'll Have After This Guide

The plugin enabled, and a subject registered through `ULDASWorldSubsystem::RegisterSubject` / `RegisterSubjectFromProfile` with a readiness query you can inspect.

## Requirements

- Unreal Engine 5.4–5.8 (packaged matrix; Win64/Linux/Mac where module allow lists permit).
- No other Tiny Tool plugin is required for the core package.
- No third-party software, account, or external runtime. See [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## 1. Install And Enable

1. Acquire **LightweightDummyActorSystem** from Fab and add it to the project.
2. Open **Edit → Plugins**, enable **LightweightDummyActorSystem**, and restart when asked.
3. Confirm Runtime, Editor, and DeveloperTool modules load (`LightweightDummyActorSystem`, `LightweightDummyActorSystemEditor`, `LightweightDummyActorSystemDeveloper`).

## 2. Create A Representation Profile

1. In the Content Browser, create a Data Asset of class `ULDASRepresentationProfile`.
2. Set grounded profile fields, for example:

| Field | Example value | Meaning |
| --- | --- | --- |
| `PromoteDistance` | `2500.0` | Distance gate used by promotion policy inputs. |
| `DemoteDistance` | `3000.0` | Distance gate used by demotion policy inputs. |
| `PromotionCooldownSeconds` | `1.0` | Minimum seconds between promotions. |
| `bAllowRuntimePromotion` | `true` | Allows runtime promotion requests. |
| `bFailClosedOnPromotionFailure` | `false` | When true, promotion failure fails closed. |
| `RequiredReadinessProviders` | (empty or named providers) | Extra readiness providers required before promote. |

## 3. Worked Example: Register And Query

From gameplay code or an editor utility that can reach the world subsystem:

```cpp
UWorld* World = /* current world */;
ULDASWorldSubsystem* LDAS = World->GetSubsystem<ULDASWorldSubsystem>();

FLDASSubjectId SubjectId;
// Fill SubjectId fields required by your project binding.

FLDASRepresentationDescriptor Descriptor;
// Fill descriptor fields or use RegisterSubjectFromProfile with the Data Asset.

const bool bRegistered = LDAS->RegisterSubjectFromProfile(SubjectId, ProfileAsset);
const FLDASReadinessReport Report = LDAS->QueryReadiness(
	SubjectId, ELDASRepresentationKind::Heavy /* or Dummy per your intent */);
```

## Expected Result

- `bRegistered` is true when the subject id is accepted.
- `QueryReadiness` returns a `FLDASReadinessReport` whose status is `Ready`, `Warning`, or a blocking status with issue entries — never a silent invent-success.

## 4. Validate Contracts (optional)

Run the packaged validate commandlet `ULDASValidateContractsCommandlet` from an editor/commandlet host to check contract consistency for the project.

## Next Steps

- [UserManual.md](UserManual.md) — subsystems, actor, component, transitions.
- [SettingsReference.md](SettingsReference.md) — profile and component properties.
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md) — readiness and promotion failures.
