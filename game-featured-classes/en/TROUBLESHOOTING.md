---
title: GameFeaturedClasses Troubleshooting
audience: [end_user]
owner_ref: plugin:GameFeaturedClasses
applies_to:
  component: GameFeaturedClasses
symptom: Buyer expects a GameFeature workbench or featured classes that are not shipped in 1.0.1.
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

**Symptom:** After enabling GameFeaturedClasses and restarting, there is no Tiny Tools menu, no new Content Browser assets, and no workbench UI.  
**Cause:** Version `1.0.1` ships only the runtime module shell. Featured classes and editor surfaces are not yet available.  
**Fix:** Confirm the plugin is enabled under **Edit → Plugins**, then verify the `GameFeaturedClasses` module loads (see [QUICKSTART.md](QUICKSTART.md)). Expect no product menu until a later package ships it.

## 1. Looking for a GameFeature Workbench menu that is missing

**Symptom:** No Tiny Tools / workbench entry appears after enabling the plugin.  
**Cause:** Version 1.0.1 ships only the runtime module shell; editor workbench surfaces are not yet available.  
**Fix:** Use the plugin as a module boundary only. Do not expect workbench UI until a later package explicitly ships it.

## 2. No featured classes in Content Browser

**Symptom:** Enabling the plugin does not add gameplay class assets.  
**Cause:** The package does not include featured class or feature set content.  
**Fix:** Keep project classes in your own modules; treat featured-class shipping as future package work.

## 3. Plugin does not appear under Edit → Plugins

**Symptom:** Search for GameFeaturedClasses returns nothing.  
**Cause:** The plugin was not copied into the project or engine Plugins folder, or the descriptor was filtered out.  
**Fix:** Confirm `GameFeaturedClasses.uplugin` exists under the project `Plugins` tree (or engine Plugins), then restart the editor.

## 4. Module fails to load on an unsupported engine

**Symptom:** Enable succeeds in UI but the runtime module fails on compile/load.  
**Cause:** Engine version outside the packaged 5.4–5.8 matrix or binary mismatch.  
**Fix:** Use a supported engine branch matching the Fab build, or rebuild from source on that engine.

## 5. Expecting LightweightDummyActorSystem or PIO as a hard dependency

**Symptom:** Setup guides from other products imply GFC requires LDAS/UCM/PIO.  
**Cause:** Those integrations are optional target architecture, not runtime requirements for the shell.  
**Fix:** Enable only GameFeaturedClasses for the shell smoke check. Add peers later only when a shipped integration exists.

## 6. Where is the online documentation?

**Symptom:** Fab / descriptor DocsURL should resolve to a browser page.  
**Cause:** Online landing pages live outside the Fab package.  
**Fix:** Open `https://docs.tiny-tool-development.com/game-featured-classes/` (descriptor `DocsURL`) or use the in-package `Documentation/` set shipped with this plugin.

## Related Documents

- [QUICKSTART.md](QUICKSTART.md)
- [UserManual.md](UserManual.md)
- [FAQ.md](FAQ.md)
- [SettingsReference.md](SettingsReference.md)
