---
title: LightweightDummyActorSystem Settings Reference
audience: [end_user]
owner_ref: plugin:LightweightDummyActorSystem
applies_to:
  component: LightweightDummyActorSystem
contract_ref: plugin:LightweightDummyActorSystem/profile-properties
version:
  since: "1.0"
---
# Settings Reference

LightweightDummyActorSystem does **not** ship a `UDeveloperSettings` / project Preferences object. Configurable values live on Data Assets, components, and structs as listed below (grounded in public headers).

## ULDASRepresentationProfile (`UDataAsset`)

| Name | Type | Default | Effect |
| --- | --- | --- | --- |
| `Descriptor` | `FLDASRepresentationDescriptor` | empty | Base representation descriptor applied to the subject record. |
| `PromoteDistance` | `float` | `0.0` | Distance input used by promotion policy. |
| `DemoteDistance` | `float` | `0.0` | Distance input used by demotion policy. |
| `PromotionCooldownSeconds` | `float` | `1.0` | Cooldown between promotions. |
| `bAllowRuntimePromotion` | `bool` | `true` | When false, runtime promotion requests are disallowed by profile. |
| `bFailClosedOnPromotionFailure` | `bool` | `false` | When true, promotion failure fails closed. |
| `RequiredReadinessProviders` | `TArray<FName>` | empty | Named readiness providers that must be satisfied. |

## ULDASDummyActorComponent

| Name | Type | Default | Effect |
| --- | --- | --- | --- |
| Profile / subject binding fields | editanywhere component properties | caller-set | Binds the component to LDAS subject representation. |
| Replicated snapshot | replicated property | runtime | Carries snapshot state with `OnRep` notification. |

## ALDASLightweightDummyActor

| Name | Type | Default | Effect |
| --- | --- | --- | --- |
| Visible components | component refs | constructed | Scene/debug representation components. |
| LDAS binding field | editanywhere | caller-set | Links the actor to LDAS subject data. |

## FLDASTransitionRecord / snapshot structs

Transition and snapshot structs expose editanywhere fields for subject id, representation kind, timestamps, and readiness issue lists. Treat them as data contracts rather than global settings; defaults are struct defaults in headers under `Public/Structs/`.

## What Is Not Present

| Surface | Status |
| --- | --- |
| `ULDASDeveloperSettings` | not yet available |
| `Config/DefaultLightweightDummyActorSystem.ini` settings object | not shipped as a buyer settings panel |
| WarCollection / Lightning / UCM bridge settings | target-only optional adapters |

## Related Documents

- [UserManual.md](UserManual.md)
- [QUICKSTART.md](QUICKSTART.md)
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md)
