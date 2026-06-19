# Agent Authentication

LLM Store can display optional agent adapters such as Codex, Claude, Cursor, or custom studio tools. Authentication remains with the external tool. LLM Store stores no agent credentials; it displays status, instructions, and a login command that users can copy and run manually.

## Where Is It?

Open:

```text
Tools -> LLM Store -> Agents
```

Each registered agent can report:

- installation state
- authentication state
- active state
- executable path
- adapter version
- capabilities
- status message
- whether shell execution is allowed

## Authentication Dialog

The `Authenticate...` button opens a dialog for the selected agent.

The dialog can show:

- short setup instructions
- the concrete authentication command
- command arguments
- working directory
- `Copy Command` for manual execution
- help URL
- `Refresh Status`

The Fab-ready build does not launch external authentication commands from the editor. Use `Copy Command`, run the command in your preferred terminal, then refresh the agent status.

## Built-in Agent Ideas

### Codex

Typical command:

```text
codex login
```

The adapter can check whether the Codex CLI exists on `PATH` and whether a login appears available.

### Claude Code

Typical command:

```text
claude auth login
```

The adapter can check whether the Claude CLI exists on `PATH`.

### Cursor

Cursor is primarily an IDE integration. Non-interactive task execution requires a suitable bridge, for example a `cursor-agent` compatible command on `PATH`.

The auth dialog can open Cursor or display setup guidance. Whether automated tasks are possible depends on the registered adapter.

## C++ Adapter Contract

A C++ agent implements `ILLMAgentAddOn`.

It can provide authentication instructions:

```cpp
virtual bool GetAuthenticationDescriptor(FLLMAgentAuthDescriptor& OutDescriptor) const override
{
    OutDescriptor.AgentId = TEXT("codex");
    OutDescriptor.DisplayName = TEXT("Codex");
    OutDescriptor.AuthCommand = TEXT("codex");
    OutDescriptor.AuthArguments = TEXT("login");
    OutDescriptor.Instructions = TEXT("Sign in through the Codex CLI.");
    OutDescriptor.bCanLaunch = true;
    OutDescriptor.bInteractive = true;
    return true;
}
```

Status can set `bAuthenticated` and `Availability` when the adapter can perform a quick status check.

## Blueprint Adapter Contract

Blueprint agents derive from:

```text
ULLMBlueprintAgentAddOn
```

Set:

- `AgentId`
- `DisplayName`
- `SupportedTaskKinds`
- `Capabilities`
- `AuthCommand`
- `AuthArguments`
- `AuthInstructions`
- `AuthHelpUrl`
- `bCanLaunchAuth`

Alternatively override the `Get Authentication Descriptor` event.

## Security Notes

- LLM Store stores no Codex, Claude, Cursor, or other agent tokens.
- Agent execution is explicit.
- File writes require `bAllowFileWrites`.
- Shell execution requires `bAllowShellExecution`.
- Diff preview can be required through `bRequireDiffPreview`.
- Adapters are responsible for enforcing the request flags.

## Recommended Setup Flow

1. Install the agent CLI or IDE.
2. Open `Tools -> LLM Store -> Agents`.
3. Check whether the agent is detected.
4. Click `Authenticate...`.
5. Click `Copy Command` and run the command in your preferred terminal.
6. Complete the external login.
7. Click `Refresh Status`.
8. Run a small test task.
