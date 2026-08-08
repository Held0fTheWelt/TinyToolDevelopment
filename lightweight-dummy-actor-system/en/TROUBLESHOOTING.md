---
title: LightweightDummyActorSystem Troubleshooting
audience: [end_user]
owner_ref: plugin:LightweightDummyActorSystem
applies_to:
  component: LightweightDummyActorSystem
symptom: RegisterSubject fails or QueryReadiness returns a non-Ready status with issues.
recovery:
  steps:
    - Confirm the plugin is enabled under Edit > Plugins and restart the editor
    - Re-read the matching troubleshooting entry and apply the documented fix
    - Re-run the quick start smoke check
version:
  since: "1.0"
---
# Troubleshooting

Format: Symptom → Cause → Fix.

## 0. I enabled it and nothing happened

**Symptom:** After enabling LightweightDummyActorSystem and restarting, no dummy actors appear and no Tiny Tools product workflow runs by itself.  
**Cause:** LDAS is an API/service package. Subjects register through `ULDASWorldSubsystem`; nothing auto-spawns without a profile and a registration call.  
**Fix:** Create a `ULDASRepresentationProfile` Data Asset and run the register + `QueryReadiness` worked example in [QUICKSTART.md](QUICKSTART.md).

## 1. `RegisterSubject` returns false

**Symptom:** Registration fails for a new subject id.  
**Cause:** Invalid or duplicate subject id, or descriptor/profile rejected by the subsystem registry.  
**Fix:** Verify `FLDASSubjectId` fields are complete and unique; confirm the profile asset is loaded; retry after `UnregisterSubject` if replacing.

## 2. Readiness status is not Ready

**Symptom:** `QueryReadiness` returns `Warning` or a blocking status with issues.  
**Cause:** Required readiness providers failed, or policy inputs (distance/cooldown) are not satisfied.  
**Fix:** Inspect `FLDASReadinessReport` warnings/issues; adjust `ULDASRepresentationProfile` distances, cooldown, or `RequiredReadinessProviders`; resolve provider failures before promoting.

## 3. Promotion fails closed

**Symptom:** `RequestPromotion` does not advance representation when `bFailClosedOnPromotionFailure` is true.  
**Cause:** Profile requests fail-closed behavior on promotion failure.  
**Fix:** Fix the underlying readiness/policy failure first. Only clear `bFailClosedOnPromotionFailure` when intentional soft-fail is acceptable.

## 4. Runtime promotion rejected

**Symptom:** Promotion requests no-op while demotion still works.  
**Cause:** `bAllowRuntimePromotion` is false on the profile.  
**Fix:** Enable `bAllowRuntimePromotion` on `ULDASRepresentationProfile` when runtime promotion is desired.

## 5. Editor inspector shows no subjects

**Symptom:** Inspector UI is empty after PIE or editor world work.  
**Cause:** Subjects were never registered on that world subsystem, or the wrong world context is inspected.  
**Fix:** Confirm registration against the same `UWorld` the inspector observes; re-register after map reload.

## 6. Validate commandlet reports contract errors

**Symptom:** `ULDASValidateContractsCommandlet` exits with findings.  
**Cause:** Profile/descriptor/contract mismatches in project content.  
**Fix:** Read the commandlet output, correct the named assets, re-run validation.

## 7. Expecting WarCollection / Lightning / UCM bridges

**Symptom:** Optional adapter APIs appear missing.  
**Cause:** Those bridges are target-only and not part of MVP 1+2+3.  
**Fix:** Use the shipped core APIs only. Treat adapters as future optional integrations.

## Related Documents

- [QUICKSTART.md](QUICKSTART.md)
- [UserManual.md](UserManual.md)
- [SettingsReference.md](SettingsReference.md)
- [FAQ.md](FAQ.md)
