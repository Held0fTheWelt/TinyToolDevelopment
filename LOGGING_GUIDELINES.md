# Logging Guidelines

Logging is treated as an operator-facing status surface for Tiny Tool Development plugins. A user should be able to open the Unreal log, filter a focused category with LogLevelEditor, and understand what the tool is doing without digging through source code.

## Category Rules

- Use a product-specific log category for every plugin module or high-volume feature area.
- Do not use `LogTemp` in product code, commandlets, bridges, or release-facing tools.
- Use `DEFINE_LOG_CATEGORY_STATIC(Category, Log, All)` for single-file/private categories.
- Use `DECLARE_LOG_CATEGORY_EXTERN(Category, Log, All)` plus `DEFINE_LOG_CATEGORY(Category)` when a category is shared by multiple files.
- Keep category names stable across releases so saved LogLevelEditor filters remain useful.

## Verbosity Rules

- `Error`: the requested operation failed or produced an invalid result that needs action.
- `Warning`: the operation continued with a fallback, skipped input, missing optional data, or degraded behavior.
- `Display`: explicit user/operator actions and important successful state transitions.
- `Log`: normal module lifecycle and routine low-noise progress.
- `Verbose`: diagnostic details useful while investigating a workflow.
- `VeryVerbose`: per-item loops, repeated decisions, or high-volume traces.

## Message Shape

Prefer messages that include:

- The action or subsystem, for example `IIS MCP endpoint started`.
- The result, for example `succeeded`, `failed`, `skipped`, or `fallback`.
- Important paths, ports, counts, route ids, provider ids, or report paths.
- Enough context to diagnose state from the log alone.

Avoid messages that only say `done`, `failed`, or `unknown` without the artifact or reason.

## Current AI Plugin Categories

- `LogLLMStoreCIPolicy` - LLM Store CI policy commandlet.
- `LogInternalIndexServiceInterface` - IIS public/runtime contracts module.
- `LogInternalIndexService` - IIS runtime/indexing module.
- `LogInternalIndexServiceEditor` - IIS editor, dashboard, tools menu, MCP lifecycle.
- `LogProjectRestructureServiceInterface` - PRS interface module.
- `LogProjectRestructureService` - PRS runtime module.
- `LogProjectRestructureServiceEditor` - PRS editor module.
- `LogUnrealIntegrationIntelligenceRuntime` - UII runtime module.
- `LogUnrealIntegrationIntelligenceEditor` - UII editor/evidence/export workflows.
- `LogUnrealIntegrationIntelligenceDeveloper` - UII developer module.

## Current Editor Tool Categories

- `LogLightweightEditorModeModule` - Lightweight Editor Mode module lifecycle.
- `LogLightweightEditorMode` - Lightweight Editor Mode runtime/editor CVar behavior.
- `LogLogLevelEditor` - LogLevelEditor runtime verbosity management and UI.
- `LogPerformancePresetWizard` - Performance Preset Wizard module/UI state.
- `LogPerformancePreset` - Performance preset application details.
- `LogEditorExtensionBase` - shared editor utility widgets and base task state.
- `LogNamingConventionUtility` - Naming Convention Utility rename workflows.
- `LogCodeCopyrightCheckCommandlet` - Code Copyright Editor CI commandlet.

## Review Checklist

- No `UE_LOG(LogTemp, ...)` remains in release-facing plugin code.
- Every commandlet has a commandlet-specific or product-specific category.
- Startup/shutdown logs are not noisy.
- User-triggered actions log at `Display` or `Log` with enough state.
- Failures include the failed path, provider, route, port, report, or reason.
- High-volume loops use `Verbose` or `VeryVerbose`.
- Category names are discoverable and filterable in LogLevelEditor.
