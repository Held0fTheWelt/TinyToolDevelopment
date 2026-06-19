# Optional Freebie Scripts

This page catalogs optional Bash helpers that can extend a buyer's local LLM Store setup after purchase. These scripts are freebies: they are not required for the default Fab-ready plugin, and they should be run deliberately on a local project copy or internal source fork.

The goal of this page is discoverability. A user should be able to understand what each script changes, when it is appropriate, and what should stay out of a Fab upload before running anything.

## Script Catalog

| Script | Category | Purpose | Target Copy | Safety Notes |
| --- | --- | --- | --- | --- |
| [`../enable_agent_automation.sh`](../enable_agent_automation.sh) | Local source customization | Re-enables editor-side agent auth launch and automatic CLI auth-status checks. | A local `LLMStore` plugin folder in a project or internal source fork. | Supports `--dry-run`, creates backups by default, and is idempotent. Do not submit the patched copy as a Fab upload. |

## Categories

Use these categories for current and future freebie scripts:

| Category | Use For |
| --- | --- |
| Local source customization | Scripts that patch or extend a buyer's local plugin copy. |
| Setup/bootstrap | Scripts that create sample config, folders, or local setup files. |
| Diagnostics/reporting | Scripts that inspect a project and produce reports without changing plugin behavior. |
| CI/policy helpers | Scripts that help teams wire LLM Store into internal automation. |

## `enable_agent_automation.sh`

### What It Does

`enable_agent_automation.sh` patches a local LLM Store source copy so the editor can launch agent authentication commands and run automatic CLI auth-status checks. The Fab-ready plugin keeps agent authentication copy-only by default, so this helper is only for teams that explicitly want the stronger local automation behavior in their own project copy.

### When To Use It

Use this script when:

- the team owns the local plugin source copy or an internal fork
- editor-side agent auth launch is desired for Codex, Claude, Cursor, or custom adapters
- automatic CLI auth-status checks are acceptable in the local environment
- the changed source copy will be reviewed before it is committed or shared internally

Do not use this script when:

- preparing the official Fab upload package
- the project requires copy-only authentication behavior
- shell/process launch from the editor is not allowed by studio policy
- the target plugin folder is not backed up or version controlled

### Usage

From the LLM Store plugin folder:

```text
bash enable_agent_automation.sh --dry-run .
bash enable_agent_automation.sh .
```

From another folder:

```text
bash /path/to/LLMStore/enable_agent_automation.sh --dry-run /path/to/LLMStore
bash /path/to/LLMStore/enable_agent_automation.sh "D:\Path\To\Project\Plugins\LLMStore"
```

Options:

| Option | Meaning |
| --- | --- |
| `--dry-run` | Shows what would change without writing files. |
| `--no-backup` | Skips the backup folder creation. Use only when the target is already safely versioned. |
| `-h`, `--help` | Prints the script help. |

### Verification

After applying the script:

1. Rebuild the plugin or project.
2. Open `Tools -> LLM Store -> Agents`.
3. Open an agent's `Authenticate...` dialog.
4. Confirm the automation-specific action is visible only in the local patched copy.
5. Refresh agent status and confirm CLI status detection behaves as expected.

### Packaging Rule

The script itself may be offered as a freebie helper, but the patched output is a local customization. Do not upload the patched automation copy as the default Fab package unless the release policy has intentionally changed and the buyer-facing documentation, review notes, and changelog have been updated.

## Documentation Rule For Future Scripts

Every new freebie Bash script must be added to the catalog above and must document:

- script path
- category
- short purpose
- target plugin or project folder
- prerequisites
- usage examples
- options
- files or behavior it changes
- dry-run, backup, and idempotency behavior
- verification steps
- packaging or Fab submission restrictions

If a script changes source files, prefer a dry-run mode and default backup behavior. If a script only reports diagnostics, state that it is read-only.
