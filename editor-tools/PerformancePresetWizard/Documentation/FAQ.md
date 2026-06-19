# FAQ

## Is Performance Preset Wizard An Automatic Optimizer?

No. It is a preset authoring and application tool. It helps teams apply known performance profiles consistently, but it does not benchmark the current machine or choose settings automatically.

## Does It Work At Runtime?

Yes. Presets are authored and reviewed in the editor, but packaged games can manually apply them through `UPerformancePresetRuntimeSubsystem`, Blueprint, C++, or the included runtime selector widget. Runtime application is explicit in V1; saved selections are not auto-applied during `GameInstance` startup.

## Does Applying A Preset Save Project Settings?

No. Applying a preset changes the current engine/runtime state through scalability and CVar APIs. It does not rewrite unrelated project configuration files.

## Can I Undo An Apply?

In the editor wizard, use **Restore Previous** to restore the single snapshot captured before the last apply. At runtime, use `RestoreLatestBackup` or `RestoreBackupById` on the runtime subsystem.

## Does Restore Previous Keep A Full History?

The editor wizard keeps one immediate restore point. The runtime subsystem keeps a persisted newest-first backup history with a default limit of 10 entries.

## What Happens If A CVar Does Not Exist?

The plugin logs and counts it as missing, then continues applying the rest of the preset. This is useful when presets are shared across engine versions or optional renderer features.

## Why Are CVar Values Stored As Strings?

Unreal CVars can be integers, floats, booleans, or other textual values. A string field preserves the author's value without forcing the asset schema to know every CVar type.

## What Does Editor Only Mean?

An editor-only CVar override applies only in editor contexts. It is skipped outside editor contexts. Use this for development-only or editor-only switches.

## Can I Use Custom Project CVars?

Yes, as long as the CVar is registered with Unreal's console manager at apply time.

## Do Presets Detect The Current Platform?

No. The target platform field is a classification hint for humans and tools. It does not prevent a user from applying the preset elsewhere.

## Why Is There A Startup Preset?

Teams often want the editor to open in a known low-cost or review-ready state. The startup preset applies a selected preset after editor engine initialization.

## Can Startup Presets Slow Editor Startup?

The apply operation is lightweight, but loading the preset asset and applying expensive renderer settings can still have visible effects depending on the project. Use a simple startup preset for daily work.

## Are The Included Presets Production Defaults?

They are starting points and examples. Tune them for your project, content scale, renderer features, and target hardware.

## Can I Share Presets Between Projects?

Yes, but review CVar names and renderer assumptions after migration. A preset created for one engine version or plugin set can contain CVars that do not exist in another project.

## Does The Plugin Replace Device Profiles?

No. Device Profiles are still the correct place for platform policy. Performance Preset Wizard is best for authored runtime target presets, editor review profiles, QA scenarios, and explicit user/project performance modes.

## Does The Plugin Change Asset Quality Settings?

No. It applies scalability and CVar values. It does not modify textures, meshes, materials, LOD chains, or other content assets.

## Can I Add More Target Platform Options?

Yes, in source. Add enum values to `EPerformanceTargetPlatform`, update documentation, and consider whether sample presets should be added.

## How Do I Validate A Release Build?

Use Unreal's `BuildPlugin` automation with `-StrictIncludes`, then open the packaged plugin in a clean project and test both the editor workflow and the runtime subsystem in a non-editor target.

