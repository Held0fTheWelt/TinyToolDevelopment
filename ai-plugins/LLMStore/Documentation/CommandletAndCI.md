# Commandlet and CI

LLM Store includes a CI policy check so teams can validate AI governance automatically.

## Goal

The CI check prevents a project from accidentally building or shipping with disallowed LLM routes.

Typical questions:

- May this build configuration use cloud providers?
- Does every production route have a local or mock fallback?
- Does a route use a disabled provider?
- Is a model missing?
- Does a route violate a provider whitelist?

## Commandlet

Run the commandlet through UnrealEditor-Cmd:

```text
UnrealEditor-Cmd.exe Project.uproject -run=LLMStoreCIPolicy -Config=Shipping
```

Windows example with an explicit engine path:

```text
"D:\Engines\UE_5.4\Engine\Binaries\Win64\UnrealEditor-Cmd.exe" "D:\Project\Project.uproject" -run=LLMStoreCIPolicy -Config=Shipping -Unattended -NoSplash -NoSound
```

## Exit Code

CI should fail if the commandlet returns a failure code.

Failure states can include:

- route references a missing model
- model references a missing provider
- provider is disabled
- build rule forbids cloud but route uses cloud
- build rule requires local/mock but route has no matching path
- provider type is not allowed

## BuildRules

Rules live in `FLLMStoreConfig.BuildRules`.

Example:

```json
{
  "BuildConfiguration": "Shipping",
  "bAllowCloud": false,
  "bRequireLocalOrMock": true,
  "AllowedProviderTypes": ["ollama", "llamacpp", "mock"]
}
```

## Recommended CI Stages

| Stage | Purpose |
| --- | --- |
| Config parse | `Config/LLMStore.json` can be loaded. |
| Route policy | Routes do not violate build rules. |
| Automation tests | `Automation RunTests LLMStore`. |
| Provider smoke | Optional real tests against local servers. |
| Package | Project or plugin builds successfully. |

## GitHub Actions Example

An example workflow is included at:

```text
Documentation/CI/GitHubActions-LLMStorePolicy.yml
```

Adjust engine path, project name, and build configuration for your project.

## Local Preflight

Before pushing:

```text
UnrealEditor-Cmd.exe Project.uproject -run=LLMStoreCIPolicy -Config=Shipping -Unattended -NoSplash -NoSound
```

Then:

```text
UnrealEditor-Cmd.exe Project.uproject -NullRHI -Unattended -NoSplash -NoSound -ExecCmds="Automation RunTests LLMStore; Quit" -TestExit="Automation Test Queue Empty"
```

## Cloud in Development, Local in Shipping

Common setup:

```text
Development:
  cloud allowed
  local providers recommended

Shipping:
  cloud forbidden
  local or mock fallback required
```

This lets a team stay productive during development while preventing shipped builds from depending on unexpected cloud services.

## Provider Smoke Tests

Not every CI pipeline should test live cloud providers.

Useful variants:

- always test `mock`
- test local providers only on self-hosted runners
- test cloud providers only in a separate manually triggered pipeline
- provide cloud keys through CI secrets

## Reports

The current CI policy primarily emits human-readable errors. Future JSON reports can cover:

- route inventory
- policy violations
- provider coverage
- cost rule coverage

