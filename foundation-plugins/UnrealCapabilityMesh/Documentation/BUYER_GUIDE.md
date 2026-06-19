# Buyer Guide

Unreal Capability Mesh is a foundation plugin for coordinating Unreal Engine editor plugins without adding direct compile-time dependencies between them.

## What Is Included

- Runtime C++ module with manifest contracts, setup loader, registries, route planner, rule engine, transform engine, invocation router, and diagnostics writer.
- Editor C++ module with a Tools menu panel for setup reload, discovery status, diagnostics, route dry runs, and adapter authoring.
- Developer module with automation fixtures and a test invoker.
- Sample manifests and test fixtures for capability, endpoint, schema, route, rule, and transform authoring.
- Documentation and release validation guidance.

## What UCM Does

- Loads setup manifests from `Config/UnrealCapabilityMesh`.
- Discovers declared capabilities and endpoint availability.
- Validates schemas, rules, routes, transforms, and adapters.
- Plans routes and explains whether side effects are allowed.
- Invokes generic endpoints through supported invocation modes.
- Writes local diagnostics to `Saved/UnrealCapabilityMesh`.

## What UCM Does Not Do

- It does not bundle AI models, Python runtimes, Node.js, or external executables.
- It does not contain product-specific bridge logic in C++.
- It does not automatically mutate project assets unless a declared endpoint and policy allow that behavior.
- It does not replace provider plugins. Provider plugins still own their actual feature logic.

## Intended Audience

UCM is meant for technical teams that need a stable, documented interoperability layer between editor tools, AI tooling, content pipeline plugins, and governance plugins.
