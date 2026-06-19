# Integration Guide

## Integration Principle

Do not add product-specific branches or partner plugin dependencies to UCM source. Add integrations through JSON manifests.

## Basic Integration Steps

1. Define the capability in a capability manifest.
2. Define its endpoint in an endpoint manifest.
3. Define or reuse input/output schemas.
4. Add rules for the side effects.
5. Add a route if the capability participates in a workflow.
6. Add transforms when one capability output must be adapted to another capability input.
7. Reference the manifests from `project_profile.json`.

## Reflection Endpoint

Use reflection endpoint mode when the target plugin exposes a static function, subsystem function, or CDO function that can be called from Unreal reflection.

Endpoint target fields commonly include:

- `class_path`
- `function_name`
- `subsystem_base_class`

## Modular Feature Endpoint

Use modular feature endpoint mode when the provider plugin registers a modular feature. UCM stores provider ids and feature names in manifests and routes calls through the generic invoker.

## File Contract Endpoint

Use file contract mode when a provider consumes and produces JSON files. This is useful when teams need a stable handoff contract without direct module dependencies.

## Adapters

Adapters describe third-party mappings without changing hub C++ code. The editor panel can create a minimal adapter manifest; technical users can then refine the JSON.

## Validate Your Integration

After referencing your manifests from `project_profile.json`, open
**Tools → Unreal Capability Mesh**, click **Reload Setup**, and check:

- **Diagnostics** page for setup validation and discovery messages.
- **Capabilities** page to confirm your capability is discovered and available.
- `Saved/UnrealCapabilityMesh/setup_validation_report.json` and `discovery_report.md` for details.

> **For maintainers:** the development repository also ships an anti-hardcoding source gate
> (`Gates/capability_mesh_gate/`). It checks the hub source, is not part of the Fab package, and
> is not needed to author or validate your own manifest integration.
