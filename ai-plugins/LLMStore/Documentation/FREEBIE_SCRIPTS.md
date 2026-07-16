# Optional LLM Store Automation Helper

`enable_agent_automation.sh` is an optional helper for buyers and internal teams that maintain a
local LLM Store source copy. It enables editor-side agent authentication controls and automatic
CLI authentication-status checks that are intentionally not part of the default Fab-ready package
behavior.

## Requirements

- A local project plugin copy or internal source fork of LLM Store.
- Bash through Linux, macOS, WSL, Git Bash, or a comparable environment.
- Python 3 for the structured source patch.

## Safe Preview

Run a dry-run first:

```bash
bash enable_agent_automation.sh --dry-run /path/to/LLMStore
```

The target directory must contain `LLMStore.uplugin`. On Windows under WSL or Git Bash, a Windows
path may also be supplied and is normalized when the environment provides `wslpath` or `cygpath`.

## Apply

```bash
bash enable_agent_automation.sh /path/to/LLMStore
```

The script creates a timestamped backup by default, validates all required source files before
writing, and is designed to be idempotent. Use `--no-backup` only when another verified backup or
version-control checkpoint already exists.

## Boundary

Apply this helper only to a local project copy or internal fork. Do not submit the patched
automation copy as a Fab upload. Provider secrets and CLI credentials remain owned by the external
provider tooling; review the generated source diff before compiling or sharing the modified plugin.
