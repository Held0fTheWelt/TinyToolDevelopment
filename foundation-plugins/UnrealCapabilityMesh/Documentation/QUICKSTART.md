# Quick Start

This guide takes you from a fresh install to a **working, visible result**: a discovered
capability inventory and a route you run yourself that returns a JSON response. No coding and no
manifest authoring are required — the plugin ships a ready-to-use default profile.

## What You'll Have After This Guide

The control panel open, the bundled **Default Capability Mesh Profile** loaded, capabilities
discovered, and one route (`sample.echo.route.v1`) executed with a JSON response and a saved
report you can open.

## Requirements

- Unreal Engine 5.4 (also validated on 5.6).
- Platform: Windows (Win64), Linux, or Mac.
- An Unreal **project** to enable the plugin in. UCM is a C++ editor plugin: in a C++ project it
  compiles on first editor start; in a Blueprint-only project, install it for a matching engine
  version (via your Fab library) so the editor can load its prebuilt editor modules.
- No third-party software, account, AI model, or external runtime is required. See
  [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## 1. Install And Enable

1. Acquire **Unreal Capability Mesh** from your Fab library and add it to your project
   (it appears under the project's `Plugins/` folder) or install it to the engine.
2. Open your project. In the editor, go to **Edit → Plugins**, search for
   `Unreal Capability Mesh`, and tick **Enabled**.
3. Restart the editor when prompted. (For a C++ project, let it compile on this first start.)

On first start UCM mirrors its bundled setup into your project at
`Config/UnrealCapabilityMesh/`. If that folder does not exist yet, UCM loads its bundled default
profile so the panel opens without errors.

## 2. Get It Working (First Result)

1. Open the control panel: **Tools → Unreal Capability Mesh**.
2. On the **Overview** page you should see the active profile **"Default Capability Mesh Profile"**.
3. Click **Reload Setup**. UCM loads the profile, validates the JSON setup, registers
   definitions, and runs discovery.
4. Open the **Capabilities** page — you now see the discovered capabilities (for example
   `mesh.sample.echo`) with their availability and side effects.
5. Open the **Diagnostics** page — it shows the setup validation and discovery messages from the
   reload. A clean reload means the plugin is working.

You have just gotten the product working using only what shipped in the package.

## 3. A Real Worked Example: Run A Route

UCM ships a safe, read-only sample route, `sample.echo.route.v1`, that calls an echo endpoint.
Use it to run your first end-to-end route.

1. Open the **Routes** page.
2. In the route id field, enter:

   ```text
   sample.echo.route.v1
   ```

3. Click **Dry Run**. UCM plans the route and confirms the `mesh.sample.echo` capability is
   available with `read_only` side effects and **no approval required**. The dry-run report is
   clean.
4. In the route input field, enter this JSON (these are the expected parameters — a route input
   envelope whose `request_json` field carries your payload):

   ```json
   {
     "request_json": "{\"message\":\"hello\"}"
   }
   ```

5. Click **Execute**.

**Expected output:** the route returns a JSON echo response of the form `{"echo": { ... }}` and
writes a route execution report. The endpoint is the shipped
`UCapabilityMeshTestInvoker::EchoJson` function, which wraps the request payload as
`{"echo":<request>}`.

The Routes page also contains the **Route Catalog** approval column for **EXPERIMENTAL** self automatic approval. Leave **Approve all at own risk** and all per-route switches off for this quick start. They are only for testing approval-gated routes on your own responsibility.

## 4. Where Results Live

All generated files are written under your project's `Saved/` folder:

```text
Saved/UnrealCapabilityMesh/
  setup_validation_report.json     ← reload validation
  capability_registry.json         ← registered capabilities
  discovery_report.md              ← human-readable discovery summary
  compatibility_matrix.json        ← capability/endpoint compatibility
  route_reports/                   ← dry-run plans
  route_execution_reports/         ← executed route inputs and outputs (your echo result)
```

Open `route_execution_reports/` to see the response from the route you just ran.

## 5. Next Steps

- Operate the panel and every function with its parameters: [UserManual.md](UserManual.md).
- Every profile field, policy, and output path: [SettingsReference.md](SettingsReference.md).
- Customize the setup: copy `Plugins/UnrealCapabilityMesh/Config/UnrealCapabilityMesh/` into
  `<YourProject>/Config/UnrealCapabilityMesh/`, edit `project_profile.json`, then click
  **Reload Setup** again.
- Connect another plugin: [INTEGRATION.md](INTEGRATION.md).
- Something not working: [TROUBLESHOOTING.md](TROUBLESHOOTING.md) and [FAQ.md](FAQ.md).

---

> **For maintainers / building from source (not required to use the plugin):** the development
> repository includes a validation gate at `Gates/capability_mesh_gate/run_capability_mesh_gate.py`.
> It is a developer tool for the source repo and is **not** part of the Fab package — you do not
> need Python or this gate to install or use UCM.
