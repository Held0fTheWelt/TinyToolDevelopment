# Agent Authentication

LLM Store can display optional agent adapters such as Codex, Claude, Cursor, or custom studio tools. Authentication remains with the external tool. LLM Store stores no agent credentials; it displays status, instructions, and a login command that users copy and run manually.

## Where Is It?

Open:

```text
Tiny Tools -> LLM Store -> Agents
```

Each registered agent can report:

- installation state
- authentication state
- active state
- detected tool path
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
- `Copy Command` for manual terminal execution
- help URL
- `Refresh Status`

The Fab build does not start external authentication processes from the editor. Copy the command, run it in your preferred terminal, complete the external login flow, then return to Unreal and refresh the status.

## Built-in Agent Ideas

### Codex

Typical command:

```text
codex login
```

The built-in adapter can check whether the Codex CLI command exists on `PATH`. It does not verify the login automatically in the Fab build.

### Claude Code

Typical command:

```text
claude auth login
```

The built-in adapter can check whether the Claude CLI command exists on `PATH`. It does not verify the login automatically in the Fab build.

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
    OutDescriptor.bCanLaunch = false;
    OutDescriptor.bInteractive = true;
    return true;
}
```

Custom adapters may set `bAuthenticated` and `Availability` when they can do so without surprising the user. The built-in Fab flow keeps authentication manual.

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
- `bCanLaunchAuth` (legacy hint for custom UIs; the bundled Fab UI copies only)

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
2. Open `Tiny Tools -> LLM Store -> Agents`.
3. Check whether the agent is detected.
4. Click `Authenticate...`.
5. Copy the command and run it manually.
6. Complete the external login.
7. Click `Refresh Status`.
8. Run a small test task.
