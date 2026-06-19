# LLM Store

LLM Store is an Unreal Engine plugin for centrally managing AI providers, models, task routes, policies, costs, secrets, and optional external agents.

## Current Version

LLM Store `1.0.4` / Unreal plugin version `104`.

## Start Here

- [Documentation overview](Documentation/README.md): complete documentation index.
- [Quickstart](Documentation/QUICKSTART.md): first provider, model, and route setup.
- [Buyer guide](Documentation/BUYER_GUIDE.md): product fit, value, and common use cases.
- [User manual](Documentation/UserManual.md): editor workflow and UI usage.
- [Troubleshooting](Documentation/TROUBLESHOOTING.md): common setup and runtime issues.

## Key References

- [Provider reference](Documentation/ProviderReference.md)
- [Route policy reference](Documentation/RoutePolicyReference.md)
- [Secret backends](Documentation/SECRET_BACKENDS.md)
- [Cost tracking](Documentation/COST_TRACKING.md)
- [Agent authentication](Documentation/AGENT_AUTHENTICATION.md)
- [Integration guide](Documentation/INTEGRATION.md)
- [Commandlet and CI](Documentation/CommandletAndCI.md)
- [Changelog](CHANGELOG.md)

## Optional Freebie Scripts

Optional Bash helpers are documented as freebie scripts. They are not required for the default Fab-ready plugin, but they can extend a buyer's local project copy or internal source fork when a team explicitly wants that behavior.

| Script | Category | What It Adds | Start Here |
| --- | --- | --- | --- |
| [`enable_agent_automation.sh`](enable_agent_automation.sh) | Local source customization | Re-enables editor-side agent auth launch and automatic CLI auth-status checks in a local/internal source copy. | [Freebie script notes](Documentation/FREEBIE_SCRIPTS.md#enable_agent_automationsh) |

Do not include a patched local automation copy in a Fab upload. See [FREEBIE_SCRIPTS.md](Documentation/FREEBIE_SCRIPTS.md) for usage, safety notes, and the documentation rules for future scripts.

## Fab Product

LLM Store is available on Fab:

https://www.fab.com/listings/4e9c6062-e3e7-4113-93d1-f08d6e276020

## Support

For questions, setup help, and product support:

https://discord.gg/HycgjVkK4J
