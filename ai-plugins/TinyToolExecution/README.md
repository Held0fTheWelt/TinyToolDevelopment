# Tiny Tool Execution

> Internal online overview. This page separates the implemented UE 5.4+ runtime from the
> engine-specific Epic MCP adapter.

Tiny Tool Execution (TTER) is a transport-neutral discovery and invocation runtime for Unreal tools.
It groups tools into searchable toolsets, records invocation state, reports progress, supports
cooperative cancellation and deadlines, carries rich structured results, and exposes resources and
artifacts without becoming a second workflow or approval authority.

## Implemented from Unreal Engine 5.4

- Canonical tool and toolset registries with search and schema discovery.
- Invocation history, progress, cancellation, deadlines, diagnostics, and artifact tracking.
- Bounded structured content, safe reflected value projection, images/audio, resources, and links.
- UMCP protocol/resource/cancellation adapters through the optional editor integration bridge.
- Native adoption surfaces for several Tiny Tool products.
- A transport-neutral projection model used by the later Epic MCP bridge.

## Authority Boundaries

- Unified MCP Server owns local transport, bearer tokens, access profiles, and audit.
- Unreal Capability Mesh owns route planning, rules, dry-run, approvals, transforms, and governed
  execution.
- TTER owns discovery and the invocation lifecycle.
- The optional Tiny Tool Execution Integration Bridge translates and registers these surfaces; it
  owns no product data or policy.

Only the concrete Epic MCP adapter is Unreal Engine 5.8-specific. The shared TTER runtime and neutral
projection logic remain available from Unreal Engine 5.4.

See the [integration bridge](../../bridge-plugins/TinyToolExecutionIntegrationBridge/README.md).
