# FAQ

## Does LogLevelEditor change my C++ log category declarations?

No. It does not rewrite source code. It discovers categories and uses Unreal's console command system to change active verbosity.

## Are changes permanent?

Only intentional overrides stored in the configured `ULogLevelDataAsset` are persistent. Runtime console changes without a DataAsset update are temporary.

## Why did a category disappear from the list?

It may be hidden by the permanent hide list, hidden by the temporary hide list, filtered by search text, or not found during the current scan scope.

## Why is a default level missing?

The scanner recognizes common Unreal macros. If a project uses custom wrapper macros or very unusual formatting, the category can still be found while the default level cannot be inferred.

## Can I include engine log categories?

Yes. Enable engine plugin and/or engine source scanning in settings. These scans can be larger, so they are optional.

## Does this work in packaged games?

No. LogLevelEditor is an editor plugin for development workflows.

## Can I share a logging setup with my team?

Yes. Store intentional overrides in the DataAsset and version it with your project. Keep temporary hides local.

## Why does the plugin retry applying saved levels on startup?

Unreal editor modules can start before the engine is ready to process console commands. The retry logic avoids losing saved overrides during early startup.

## What happens if a console command fails?

The UI and DataAsset are not updated as if the command succeeded. The failure is logged so the user is not given false feedback.

## Can I silence a category completely?

Use `NoLogging`, but remember that Unreal's category compile-time verbosity and runtime verbosity rules still apply.

## Does it support custom verbosity names?

No. It supports Unreal's standard verbosity names.

## Is the DataAsset required?

The UI can inspect and apply runtime changes, but persistent startup replay requires a configured DataAsset.

## Can the plugin detect categories from plugins?

Yes. Project plugins are part of the normal scan path. Engine plugins are optional.

## Is it safe for source control?

Yes when used intentionally. The main shared artifact is the DataAsset with persistent overrides. Temporary hide settings are transient.
