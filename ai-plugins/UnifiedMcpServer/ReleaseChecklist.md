# Release Checklist

Use this checklist before a Fab upload or internal release.

## Build

- [ ] UE 5.4 build succeeds.
- [ ] UE 5.5 build succeeds if targeted.
- [ ] UE 5.6 build succeeds.
- [ ] No C++17 override remains in active plugin/bridge modules.
- [ ] `git diff --check` is clean.

## Runtime Smoke

- [ ] Plugin can be enabled in a clean project.
- [ ] Project Settings page shows Unified MCP Server settings.
- [ ] `Tools -> AI -> Universal MCP -> Start Unified MCP Server` starts the endpoint.
- [ ] Handshake file is written under `Saved/UnifiedMcpServer/agent`.
- [ ] `initialize` returns server info.
- [ ] `ping` returns an empty result.
- [ ] `tools/list` works with no providers.
- [ ] `tools/list` shows `mesh_*` tools when Unreal Capability Mesh is loaded.
- [ ] `tools/list` shows provider tools when a direct provider plugin is installed.
- [ ] `tools/call` routes to a provider tool.
- [ ] `Tools -> AI -> Universal MCP -> Rotate MCP Token` invalidates the old token.
- [ ] `Tools -> AI -> Universal MCP -> Open Control Panel` shows the Connected Functions tree.
- [ ] Plugin groups expand/collapse without rebuilding the entire list.
- [ ] Tool rows expand/collapse to lazy-load input/output schema tables.
- [ ] Flattened `mesh_route_*` tools appear under owning plugins in Connected Functions when UCM is loaded.
- [ ] **Refresh** in the control panel forces a full connected-function reload.
- [ ] `Tools -> AI -> Universal MCP -> Stop Unified MCP Server` removes the handshake file.

## Security

- [ ] Server remains disabled by default.
- [ ] Server binds to `127.0.0.1`.
- [ ] Requests without bearer token return unauthorized.
- [ ] Token is not committed or packaged.
- [ ] Request logs do not include private tool arguments unless intentionally added by a provider.

## Documentation

- [ ] `README.md` is current.
- [ ] `BUYER_GUIDE.md` explains value and limits.
- [ ] `QUICKSTART.md` describes first connection.
- [ ] `UserManual.md` describes settings and menu workflow.
- [ ] `TechnicalOverview.md` matches implementation.
- [ ] `INTEGRATION.md` explains provider registration.
- [ ] `SettingsReference.md` documents all settings.
- [ ] `CodeDocumentation.md` documents source layout.
- [ ] `FAQ.md` covers buyer questions.
- [ ] `TROUBLESHOOTING.md` covers common failure modes.

## Packaging

- [ ] `Config/FilterPlugin.ini` includes `/Documentation/...`.
- [ ] `Config/FilterPlugin.ini` includes `/CHANGELOG.md`.
- [ ] No generated `Saved/UnifiedMcpServer` files are included.
- [ ] No external executables are included.
- [ ] Fab technical information matches the shipped feature set.
