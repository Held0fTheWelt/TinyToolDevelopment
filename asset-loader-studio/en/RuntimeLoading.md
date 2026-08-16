# Runtime Loading

Asset Loader Studio exposes `UAssetLoaderStudioRuntimeSubsystem` and
`UAssetLoaderStudioBlueprintLibrary` for load requests.

Supported request inputs:

- `soft_object_paths`
- `primary_asset_ids`
- `bundles`
- `target_class_path`
- `timeout_seconds`
- `allow_partial_success`

Results include status, progress, loaded paths, partial failures, diagnostics, and stable JSON
serialization. Invalid paths, empty requests, unresolved primary assets, and load-handle failures are
reported as structured diagnostics with next actions.

## Typical Flow

1. Build a request with a stable `request_id` and at least one source: soft object path, primary
   asset id, or bundle.
2. Submit the request through Blueprint, C++, the editor workspace, or the optional JSON route.
3. Poll job status until it reports completion, cancellation, timeout, or failure.
4. Read `loaded_paths`, `partial_failures`, and diagnostics instead of scraping logs.
5. Use the dependency graph or table snapshot when you need to inspect what the loaded assets point to.

Set `allow_partial_success` when a batch may continue after individual path failures. Keep timeouts
short for editor review and longer for deliberate bulk checks.
