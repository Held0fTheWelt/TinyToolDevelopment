# Tiny Tool Execution Integration Bridge

This optional editor-only companion connects Tiny Tool Execution, Unified MCP Server, and Unreal
Capability Mesh while preserving each product's authority.

## What It Does

- Registers TTER discovery, invocation, resource, and cancellation adapters with UMCP.
- Reloads UCM setup before route discovery so provider-owned plugin manifests are visible after
  installed-plugin startup.
- Projects UCM routes into TTER tool descriptors.
- Accepts natural top-level route arguments and supplies the endpoint `request_json` envelope when a
  reflected route expects it.
- Unregisters every adapter and projection cleanly during shutdown.

## Requirements

- Unreal Engine 5.4+.
- Tiny Tool Execution.
- Unified MCP Server.
- Unreal Capability Mesh.

## Authority Boundary

UMCP continues to own transport, authentication, access policy, and audit. UCM continues to own route
planning, rules, dry-run, approval, transforms, and execution. TTER owns tool discovery and invocation
lifecycle. The bridge performs translation and registration only.

The bridge is not a standalone product and is not required for the core value of any of the three
products.
