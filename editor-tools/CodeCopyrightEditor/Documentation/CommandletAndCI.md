# Commandlet And CI

Code Copyright Editor includes a commandlet named `CodeCopyrightCheck`. It runs the same scanner used by the editor UI and can be used from a local terminal or continuous integration.

## Basic Command

```powershell
UnrealEditor-Cmd.exe "D:\Path\To\Project.uproject" -run=CodeCopyrightCheck -unattended -nop4 -nosplash -NoShaderCompile -ReportDir="Saved\CodeCopyrightEditor\Reports"
```

Use the Unreal Engine version that matches the project.

## Switches

| Switch | Purpose |
| --- | --- |
| `-Fix` | Rewrite changeable files before producing the final report. |
| `-ReportDir=<Path>` | Write reports to a project-relative or absolute directory. |
| `-FailOnProtected` | Treat protected foreign notices as CI failures. |
| `-NoJson` | Skip `CodeCopyrightReport.json`. |
| `-NoSpdx` | Skip `CodeCopyrightReport.spdx`. |
| `-NoReuse` | Skip `REUSE-Report.md`. |
| `-NoFail` | Always return exit code `0` after writing reports. |
| `-Help` | Print commandlet usage. |

## Exit Behavior

By default, CI fails when the scan finds:

- Changeable notices.
- Conflicts.
- Read errors.
- Write errors.

Protected notices are reported but do not fail CI unless `-FailOnProtected` is used.

Use `-NoFail` when you want reports without blocking the pipeline.

## Local PowerShell

```powershell
& "D:\Engines\UE_5.4\Engine\Binaries\Win64\UnrealEditor-Cmd.exe" `
  "D:\Path\To\Project.uproject" `
  -run=CodeCopyrightCheck `
  -unattended `
  -nop4 `
  -nosplash `
  -NoShaderCompile `
  -ReportDir="Saved\CodeCopyrightEditor\Reports"
```

With fixing:

```powershell
& "D:\Engines\UE_5.4\Engine\Binaries\Win64\UnrealEditor-Cmd.exe" `
  "D:\Path\To\Project.uproject" `
  -run=CodeCopyrightCheck `
  -unattended `
  -nop4 `
  -nosplash `
  -NoShaderCompile `
  -ReportDir="Saved\CodeCopyrightEditor\Reports" `
  -Fix
```

## Local Shell

```bash
"/opt/UnrealEngine/Engine/Binaries/Linux/UnrealEditor-Cmd" \
  ./MyProject.uproject \
  -run=CodeCopyrightCheck \
  -unattended \
  -nop4 \
  -nosplash \
  -NoShaderCompile \
  -ReportDir="Saved/CodeCopyrightEditor/Reports" \
  -FailOnProtected
```

Additional commandlet switches can be appended to the direct `UnrealEditor-Cmd` call.

## GitHub Actions Starter

A starter workflow is included at:

```text
Plugins/CodeCopyrightEditor/Documentation/CI/GitHubActions-CodeCopyrightCheck.yml
```

It assumes:

- A self-hosted runner.
- Unreal Engine installed on the runner.
- A valid `UE_EDITOR_CMD` path.
- A valid `UPROJECT` path.

Adjust the workflow paths to match the machine that runs the job.

## Suggested CI Policies

### Report Only

Use during adoption:

```text
-NoFail
```

This writes reports but does not block pull requests.

### Gate On Owned Notice Drift

Use after templates are stable:

```text
<no special switch>
```

This fails when owned files are missing or out of sync.

### Strict Protected Notice Policy

Use only when your team wants protected files to block release:

```text
-FailOnProtected
```

This is useful for teams that require manual review of every protected or third-party notice.

### Automated Formatting Pass

Use carefully:

```text
-Fix
```

This rewrites changeable files. Use source control and review the resulting diff.

## Generated Reports

The commandlet can write:

- `CodeCopyrightReport.json`
- `CodeCopyrightReport.spdx`
- `REUSE-Report.md`

See [ReportsAndCompliance.md](ReportsAndCompliance.md) for details.

## Common CI Problems

| Problem | Cause | Fix |
| --- | --- | --- |
| Commandlet is not found | Plugin is not enabled, not built, or not loaded for the project. | Enable/rebuild the plugin and rerun with the matching editor. |
| CI finds more files than local scan | Different checkout or scan roots. | Compare project config and runner paths. |
| Reports are missing | Report directory cannot be created or written. | Check permissions and artifact path. |
| Build fails before commandlet runs | Unreal project or plugin compile issue. | Build the project first and inspect UnrealBuildTool output. |
| `PROTECTED` files are reported | Foreign or third-party notices were detected. | Review manually or exclude known vendor folders. |
