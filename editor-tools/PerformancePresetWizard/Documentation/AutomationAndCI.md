# Automation And CI

Performance Preset Wizard does not currently ship a commandlet. The most important automated validation path is Unreal's isolated `BuildPlugin` flow with strict includes enabled.

## Why BuildPlugin Matters

A plugin can compile inside a large project while still relying on headers or modules that are included transitively by unrelated files. `BuildPlugin` creates a cleaner package-style build and catches those problems earlier.

`-StrictIncludes` is especially important for marketplace plugins because it verifies that source files include the headers they use directly.

## Local Validation Command

```powershell
Engine\Build\BatchFiles\RunUAT.bat BuildPlugin -Plugin="D:\PluginProjectGit\Plugins\PerformancePresetWizard\PerformancePresetWizard.uplugin" -Package="D:\PluginProjectGit\Saved\PerformancePresetWizardBuildCheck" -TargetPlatforms=Win64 -StrictIncludes
```

Adjust the project path, engine path, and target platform for your machine.

## Expected Result

A successful build ends with a `BUILD SUCCESSFUL` message and creates a temporary packaged plugin under:

```text
Saved\PerformancePresetWizardBuildCheck
```

Delete that folder after validation if it was created only for local checking.

## Suggested CI Steps

Use a self-hosted runner with Unreal Engine installed.

1. Sync the repository.
2. Resolve engine path.
3. Run `RunUAT BuildPlugin`.
4. Upload the packaged plugin as an artifact if needed.
5. Fail the job on non-zero exit code.
6. Optionally verify that documentation exists in the packaged output.

## Example PowerShell Skeleton

```powershell
$EngineRoot = "C:\Program Files\Epic Games\UE_5.5"
$RepoRoot = "D:\PluginProjectGit"
$Plugin = Join-Path $RepoRoot "Plugins\PerformancePresetWizard\PerformancePresetWizard.uplugin"
$Package = Join-Path $RepoRoot "Saved\PerformancePresetWizardBuildCheck"

& "$EngineRoot\Engine\Build\BatchFiles\RunUAT.bat" BuildPlugin `
  -Plugin="$Plugin" `
  -Package="$Package" `
  -TargetPlatforms=Win64 `
  -StrictIncludes

if ($LASTEXITCODE -ne 0) {
  throw "PerformancePresetWizard BuildPlugin validation failed."
}
```

## Documentation Packaging Check

After a package build, confirm that these paths exist in the packaged plugin:

```text
Documentation\README.md
Documentation\UserManual.md
Documentation\CodeDocumentation.md
Documentation\Screenshots\01-workflow-overview.svg
PerformancePresetWizard_Changelog.txt
Readme.pdf
```

If the documentation is missing, check `Config/FilterPlugin.ini` and ensure it includes `/Documentation/...`.

## Future Automation Opportunities

The source is structured so future automation can reuse `PerformancePreset::ApplyPreset` without depending on Slate. Good future additions could include:

- A commandlet that validates CVar names in all preset assets.
- A JSON export for preset reviews.
- A CI report that lists unknown CVars by preset.
- A smoke test map that applies selected presets during editor automation.

Until those features exist, `BuildPlugin -StrictIncludes` plus manual editor smoke testing is the recommended release gate.

