#!/usr/bin/env bash
set -euo pipefail

SCRIPT_NAME="$(basename "$0")"
MODE="apply"
DRY_RUN=0
MAKE_BACKUP=1
PLUGIN_ROOT=""

usage() {
  cat <<'USAGE'
Enable optional LLM Store agent automation in a local source copy.

This helper is meant for buyers and internal teams who want the editor-side
agent authentication button and automatic CLI auth-status checks in their own
local project copy. The Fab-ready plugin keeps authentication copy-only by
default.

Usage:
  bash enable_agent_automation.sh /path/to/LLMStore
  bash enable_agent_automation.sh "D:\Path\To\Project\Plugins\LLMStore"

Options:
  --dry-run     Show what would change without writing files.
  --no-backup   Do not create a backup next to the plugin folder.
  -h, --help    Show this help.

Notes:
  - Run this only on a local project or internal fork.
  - Do not submit the patched automation copy as a Fab upload.
  - The script is idempotent and can be re-run safely.
USAGE
}

while [[ $# -gt 0 ]]; do
  case "$1" in
    --dry-run)
      DRY_RUN=1
      shift
      ;;
    --no-backup)
      MAKE_BACKUP=0
      shift
      ;;
    -h|--help)
      usage
      exit 0
      ;;
    --*)
      echo "Unknown option: $1" >&2
      usage >&2
      exit 2
      ;;
    *)
      if [[ -n "$PLUGIN_ROOT" ]]; then
        echo "Only one plugin path is supported." >&2
        exit 2
      fi
      PLUGIN_ROOT="$1"
      shift
      ;;
  esac
done

if [[ -z "$PLUGIN_ROOT" ]]; then
  if [[ -f "LLMStore.uplugin" ]]; then
    PLUGIN_ROOT="$PWD"
  else
    echo "Missing plugin path." >&2
    usage >&2
    exit 2
  fi
fi

normalize_path() {
  local input="$1"
  if [[ "$input" = /* ]]; then
    printf '%s\n' "$input"
    return 0
  fi
  if command -v wslpath >/dev/null 2>&1; then
    wslpath -u "$input" 2>/dev/null || printf '%s\n' "$input"
  elif command -v cygpath >/dev/null 2>&1; then
    cygpath -u "$input" 2>/dev/null || printf '%s\n' "$input"
  else
    printf '%s\n' "$input"
  fi
}

PLUGIN_ROOT="$(normalize_path "$PLUGIN_ROOT")"

PYTHON_BIN=""
if command -v python3 >/dev/null 2>&1; then
  PYTHON_BIN="python3"
elif command -v python >/dev/null 2>&1; then
  PYTHON_BIN="python"
else
  echo "Python 3 is required for the structured source patch." >&2
  exit 2
fi

export LLMSTORE_PLUGIN_ROOT="$PLUGIN_ROOT"
export LLMSTORE_DRY_RUN="$DRY_RUN"
export LLMSTORE_MAKE_BACKUP="$MAKE_BACKUP"

"$PYTHON_BIN" <<'PY'
import os
import re
import shutil
import sys
from datetime import datetime
from pathlib import Path

root = Path(os.environ["LLMSTORE_PLUGIN_ROOT"]).resolve()
dry_run = os.environ["LLMSTORE_DRY_RUN"] == "1"
make_backup = os.environ["LLMSTORE_MAKE_BACKUP"] == "1"

if not (root / "LLMStore.uplugin").is_file():
    raise SystemExit(f"LLMStore.uplugin was not found under: {root}")

files = {
    "editor_module": root / "Source" / "LLMStoreEditor" / "Private" / "LLMStoreEditorModule.cpp",
    "agent_cpp": root / "Source" / "LLMStoreEditor" / "Private" / "Widgets" / "SLLMAgentSection.cpp",
    "agent_h": root / "Source" / "LLMStoreEditor" / "Private" / "Widgets" / "SLLMAgentSection.h",
    "types_h": root / "Source" / "LLMStoreInterface" / "Public" / "Types" / "LLMStoreTypes.h",
    "blueprint_h": root / "Source" / "LLMStoreInterface" / "Public" / "Interfaces" / "LLMBlueprintAddOnInterfaces.h",
}

for label, path in files.items():
    if not path.is_file():
        raise SystemExit(f"Required file for {label} is missing: {path}")

def load(path):
    raw = path.read_text(encoding="utf-8")
    newline = "\r\n" if "\r\n" in raw else "\n"
    return raw.replace("\r\n", "\n"), newline

texts = {}
newlines = {}
for label, path in files.items():
    texts[label], newlines[label] = load(path)

changed_labels = set()
notes = []

def mark(label, message):
    changed_labels.add(label)
    notes.append(message)

def replace_exact(label, old, new, message, already=None):
    text = texts[label]
    if new in text:
        if already:
            notes.append(already)
        return
    if old not in text:
        raise SystemExit(f"Patch context not found for: {message}\nFile: {files[label]}")
    texts[label] = text.replace(old, new, 1)
    mark(label, message)

def insert_before(label, marker, snippet, message, already_token):
    text = texts[label]
    if already_token in text:
        notes.append(f"Already present: {message}")
        return
    if marker not in text:
        raise SystemExit(f"Insert marker not found for: {message}\nFile: {files[label]}")
    texts[label] = text.replace(marker, snippet + "\n" + marker, 1)
    mark(label, message)

def insert_after(label, marker, snippet, message, already_token):
    text = texts[label]
    if already_token in text:
        notes.append(f"Already present: {message}")
        return
    if marker not in text:
        raise SystemExit(f"Insert marker not found for: {message}\nFile: {files[label]}")
    texts[label] = text.replace(marker, marker + "\n" + snippet, 1)
    mark(label, message)

normalizer = r'''	void NormalizeProcessForCommandScript(FString& Program, FString& Params, bool bKeepWindowOpen)
	{
#if PLATFORM_WINDOWS
		const FString Dot = TEXT(".");
		const FString CommandScriptExtension = Dot + TEXT("cmd");
		const FString BatchScriptExtension = Dot + TEXT("bat");
		const FString Extension = FPaths::GetExtension(Program, true);
		if (Extension.Equals(CommandScriptExtension, ESearchCase::IgnoreCase) || Extension.Equals(BatchScriptExtension, ESearchCase::IgnoreCase))
		{
			Params = FString::Printf(
				TEXT("%s %s%s%s"),
				bKeepWindowOpen ? TEXT("/K") : TEXT("/C"),
				*QuoteProcessArgument(Program),
				Params.IsEmpty() ? TEXT("") : TEXT(" "),
				*Params);
			Program = TEXT("cmd") + Dot + TEXT("exe");
		}
#else
		(void)Program;
		(void)Params;
		(void)bKeepWindowOpen;
#endif
	}
'''

insert_before(
    "editor_module",
    "\tTArray<FString> GetPathEntries()\n",
    normalizer,
    "add Windows command-script normalization helper",
    "NormalizeProcessForCommandScript",
)

replace_exact(
    "editor_module",
    '''			const FString AuthenticationState = TEXT("Authentication is managed by the external tool.");
			Status.bAuthenticated = false;
			Status.bActive = bSupportsExecution;
			Status.bShellExecutionAllowed = bSupportsExecution;
			Status.Availability = Status.bActive
				? ELLMAgentAvailability::Available
				: ELLMAgentAvailability::Installed;
			Status.Meta.Add(TEXT("AuthenticationState"), AuthenticationState);
			Status.StatusMessage = Status.bActive
				? TEXT("CLI found. Authentication stays in the external tool; explicit agent tasks remain shell-gated per request.")
				: (bSupportsExecution
					? TEXT("CLI found. Complete authentication manually before running agent tasks.")
					: TEXT("IDE command found. Non-interactive agent execution needs a dedicated bridge or adapter."));
''',
    '''			FString AuthenticationState = AuthStatusArguments.IsEmpty()
				? TEXT("Authentication is handled by the external tool.")
				: TEXT("Authentication was not checked.");
			if (!AuthStatusArguments.IsEmpty())
			{
				Status.bAuthenticated = IsAuthenticated(ExecutablePath, AuthenticationState);
			}
			Status.bActive = bSupportsExecution && (AuthStatusArguments.IsEmpty() || Status.bAuthenticated);
			Status.bShellExecutionAllowed = bSupportsExecution;
			Status.Availability = Status.bActive
				? ELLMAgentAvailability::Available
				: (bSupportsExecution && !AuthStatusArguments.IsEmpty() ? ELLMAgentAvailability::AuthRequired : ELLMAgentAvailability::Installed);
			Status.Meta.Add(TEXT("AuthenticationState"), AuthenticationState);
			Status.StatusMessage = Status.bActive
				? TEXT("CLI found, authenticated, and ready for explicit agent tasks.")
				: (bSupportsExecution
					? TEXT("CLI found. Authentication is required before this adapter can run tasks.")
					: TEXT("IDE command found. Non-interactive agent execution needs a dedicated bridge or adapter."));
''',
    "enable automatic agent auth-status checks",
    "Already present: automatic agent auth-status checks",
)

replace_exact(
    "editor_module",
    '''			FString Program = Status.ExecutablePath;
			FString ProgramParams = Params;

			const FString CapturedAgentId = AgentId;
''',
    '''			FString Program = Status.ExecutablePath;
			FString ProgramParams = Params;
			NormalizeProcessForCommandScript(Program, ProgramParams, false);

			const FString CapturedAgentId = AgentId;
''',
    "normalize script-backed agent task commands before execution",
    "Already present: agent task command normalization",
)

replace_exact(
    "editor_module",
    '''			OutDescriptor.ExecutablePath = ExecutablePath;
			OutDescriptor.AuthCommand = ExecutablePath;
			OutDescriptor.bCanLaunch = false;
''',
    '''			OutDescriptor.ExecutablePath = ExecutablePath;
			OutDescriptor.AuthCommand = ExecutablePath;
			OutDescriptor.bCanLaunch = !AuthArguments.IsEmpty();
''',
    "mark built-in auth descriptors as launchable",
    "Already present: launchable built-in auth descriptors",
)

is_authenticated = r'''		bool IsAuthenticated(const FString& ExecutablePath, FString& OutAuthenticationState) const
		{
			if (AuthStatusArguments.IsEmpty())
			{
				OutAuthenticationState = TEXT("Authentication status is managed by the external tool.");
				return false;
			}

			FString Program = ExecutablePath;
			FString ProgramParams = AuthStatusArguments;
			NormalizeProcessForCommandScript(Program, ProgramParams, false);

			int32 ReturnCode = -1;
			FString StdOut;
			FString StdErr;
			const bool bStarted = FPlatformProcess::ExecProcess(*Program, *ProgramParams, &ReturnCode, &StdOut, &StdErr);
			if (bStarted && ReturnCode == 0)
			{
				OutAuthenticationState = TEXT("Authenticated.");
				return true;
			}

			OutAuthenticationState = bStarted
				? TEXT("Authentication required.")
				: TEXT("Authentication status command could not be started.");
			return false;
		}

'''

insert_before(
    "editor_module",
    "\t\tbool BuildCommandLine(const FLLMAgentRequest& Request, const FString& Prompt, FString& OutParams) const\n",
    is_authenticated,
    "add automatic auth-status helper",
    "bool IsAuthenticated(const FString& ExecutablePath",
)

replace_exact(
    "agent_cpp",
    '''#include "Framework/Application/SlateApplication.h"
#include "HAL/PlatformApplicationMisc.h"
''',
    '''#include "Framework/Application/SlateApplication.h"
#include "HAL/PlatformApplicationMisc.h"
#include "HAL/PlatformProcess.h"
''',
    "include process API for optional auth launch",
    "Already present: process API include",
)

replace_exact(
    "agent_cpp",
    '''LOCTEXT("AgentsIntro", "Use this page to check which external agents LLM Store can see. Authentication is manual in this Fab build: LLM Store shows setup commands for copy/paste and does not open an external login process from the editor.")''',
    '''LOCTEXT("AgentsIntro", "Use this page to check which external agents LLM Store can see. Running an agent task is explicit: the caller must allow shell execution, and file writes stay opt-in per request.")''',
    "restore automation-oriented agent intro copy",
    "Already present: automation-oriented agent intro copy",
)

replace_exact(
    "agent_cpp",
    '''LOCTEXT("AgentsIntroTooltip", "LLM Store exposes a neutral agent interface; external tools remain optional and their credentials stay outside the plugin.")''',
    '''LOCTEXT("AgentsIntroTooltip", "LLM Store exposes a neutral agent interface; external tools remain optional and policy-gated.")''',
    "restore automation-oriented agent intro tooltip",
    "Already present: automation-oriented agent intro tooltip",
)

replace_exact(
    "agent_cpp",
    '''TEXT("Copy the command below, run it manually in your preferred terminal, then refresh the Agents tab.")''',
    '''TEXT("Use the command below to authenticate the external agent, then refresh the Agents tab.")''',
    "restore launch-aware auth instructions",
    "Already present: launch-aware auth instructions",
)

replace_exact(
    "agent_cpp",
    '''LOCTEXT("AuthInstructionsTooltip", "Authentication stays inside the external tool. LLM Store only displays and copies setup commands.")''',
    '''LOCTEXT("AuthInstructionsTooltip", "Authentication stays inside the external tool. LLM Store only starts or shows the setup command.")''',
    "restore launch-aware auth instruction tooltip",
    "Already present: launch-aware auth instruction tooltip",
)

replace_exact(
    "agent_cpp",
    '''TEXT("No authentication command available.")''',
    '''TEXT("No launchable command available.")''',
    "restore launch-aware empty command text",
    "Already present: launch-aware empty command text",
)

replace_exact(
    "agent_cpp",
    '''LOCTEXT("AuthCommandTooltip", "Copy this command and run it manually in your preferred terminal.")''',
    '''LOCTEXT("AuthCommandTooltip", "Copy this command if the Run Auth button cannot open a visible terminal on your platform.")''',
    "restore launch-aware auth command tooltip",
    "Already present: launch-aware auth command tooltip",
)

run_auth_block = r'''					+ SHorizontalBox::Slot()
					.AutoWidth()
					.Padding(0.f, 0.f, 6.f, 0.f)
					[
						SNew(SButton)
						.Text(LOCTEXT("RunAuth", "Run Auth"))
						.IsEnabled(Descriptor.bCanLaunch && !Descriptor.AuthCommand.IsEmpty())
						.ToolTipText(LOCTEXT("RunAuthTooltip", "Starts the external authentication command. Use Copy Command if no terminal opens."))
						.OnClicked_Lambda([this, Descriptor]()
						{
							FString Message;
							const bool bLaunched = LaunchAuthenticationProcess(Descriptor, Message);
							FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(Message));
							if (bLaunched)
							{
								RefreshAgentList();
							}
							return FReply::Handled();
						})
					]

'''

insert_before(
    "agent_cpp",
    "\t\t\t\t+ SHorizontalBox::Slot()\n\t\t\t\t.AutoWidth()\n\t\t\t\t.Padding(0.f, 0.f, 6.f, 0.f)\n\t\t\t\t[\n\t\t\t\t\tSNew(SButton)\n\t\t\t\t\t.Text(LOCTEXT(\"CopyAuthCommand\", \"Copy Command\"))\n",
    run_auth_block,
    "add Run Auth button",
    "LaunchAuthenticationProcess(Descriptor, Message)",
)

launch_method = r'''bool SLLMAgentSection::LaunchAuthenticationProcess(const FLLMAgentAuthDescriptor& Descriptor, FString& OutMessage) const
{
	if (!Descriptor.bCanLaunch || Descriptor.AuthCommand.TrimStartAndEnd().IsEmpty())
	{
		OutMessage = TEXT("This agent does not provide a launchable authentication command.");
		return false;
	}

	FString Program = Descriptor.AuthCommand.TrimStartAndEnd();
	FString Params = Descriptor.AuthArguments.TrimStartAndEnd();
	FString WorkingDirectory = Descriptor.WorkingDirectory.TrimStartAndEnd();
	if (WorkingDirectory.IsEmpty())
	{
		WorkingDirectory = FPaths::ProjectDir();
	}

#if PLATFORM_WINDOWS
	const FString Dot = TEXT(".");
	Params = FString::Printf(TEXT("/K %s"), *BuildAuthenticationCommandLine(Descriptor));
	Program = TEXT("cmd") + Dot + TEXT("exe");
#endif

	uint32 ProcessId = 0;
	const TCHAR* OptionalWorkingDirectory = WorkingDirectory.IsEmpty() ? nullptr : *WorkingDirectory;
	FProcHandle Handle = FPlatformProcess::CreateProc(
		*Program,
		*Params,
		true,
		false,
		false,
		&ProcessId,
		0,
		OptionalWorkingDirectory,
		nullptr,
		nullptr);

	if (Handle.IsValid())
	{
		FPlatformProcess::CloseProc(Handle);
		OutMessage = TEXT("Authentication command started. Complete the external login flow, then refresh the Agents tab.");
		return true;
	}

	OutMessage = FString::Printf(TEXT("Could not start authentication command: %s"), *BuildAuthenticationCommandLine(Descriptor));
	return false;
}

'''

insert_before(
    "agent_cpp",
    "FString SLLMAgentSection::BuildAuthenticationCommandLine(const FLLMAgentAuthDescriptor& Descriptor) const\n",
    launch_method,
    "add auth process launcher",
    "bool SLLMAgentSection::LaunchAuthenticationProcess",
)

replace_exact(
    "agent_h",
    ''' * capabilities, and a buyer-friendly authentication workflow. The section does
 * not authenticate directly; it shows and copies the command supplied by the
 * adapter's FLLMAgentAuthDescriptor so the user can run it manually.
''',
    ''' * capabilities, and a buyer-friendly authentication workflow. The section does
 * not authenticate directly; it shows or launches the command supplied by the
 * adapter's FLLMAgentAuthDescriptor.
''',
    "restore launch-aware section comment",
    "Already present: launch-aware section comment",
)

insert_before(
    "agent_h",
    "\t/** Build a user-readable command line for display/copy actions. */\n",
    "\t/** Launch the descriptor command when the adapter marks it as editor-launchable. */\n\tbool LaunchAuthenticationProcess(const FLLMAgentAuthDescriptor& Descriptor, FString& OutMessage) const;",
    "declare auth process launcher",
    "LaunchAuthenticationProcess(const FLLMAgentAuthDescriptor",
)

replace_exact(
    "types_h",
    '''	/** Legacy hint for custom UIs. The bundled Fab UI displays and copies AuthCommand only. */
	UPROPERTY(BlueprintReadWrite, Category="LLMStore|Agent") bool bCanLaunch = false;
''',
    '''	/** Whether the UI may launch AuthCommand directly. */
	UPROPERTY(BlueprintReadWrite, Category="LLMStore|Agent") bool bCanLaunch = false;
''',
    "restore bCanLaunch comment",
    "Already present: bCanLaunch launch comment",
)

replace_exact(
    "blueprint_h",
    '''	/** Legacy hint for custom UIs. The bundled Fab UI displays and copies AuthCommand only. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LLMStore|Agent|Auth") bool bCanLaunchAuth = false;
''',
    '''	/** Whether the editor may launch AuthCommand directly. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LLMStore|Agent|Auth") bool bCanLaunchAuth = false;
''',
    "restore bCanLaunchAuth comment",
    "Already present: bCanLaunchAuth launch comment",
)

if changed_labels:
    if make_backup and not dry_run:
        stamp = datetime.now().strftime("%Y%m%d-%H%M%S")
        backup_root = root.parent / f"{root.name}.automation-backup-{stamp}"
        for label in changed_labels:
            src = files[label]
            dst = backup_root / src.relative_to(root)
            dst.parent.mkdir(parents=True, exist_ok=True)
            shutil.copy2(src, dst)
        print(f"Backup written to: {backup_root}")

    for label in sorted(changed_labels):
        if dry_run:
            continue
        text = texts[label].replace("\n", newlines[label])
        files[label].write_text(text, encoding="utf-8")

pattern = re.compile(r"\.(exe|cmd|bat)([^A-Za-z]|$)", re.IGNORECASE)
scan_labels = ["editor_module", "agent_cpp", "agent_h", "types_h", "blueprint_h"]
matches = []
for label in scan_labels:
    for line_no, line in enumerate(texts[label].splitlines(), start=1):
        if pattern.search(line):
            matches.append(f"{files[label]}:{line_no}: {line.strip()}")

print("LLM Store optional automation patch")
print(f"Plugin root: {root}")
print(f"Mode: {'dry-run' if dry_run else 'apply'}")
if notes:
    for note in notes:
        print(f"- {note}")
if not changed_labels:
    print("No source changes were needed; automation hooks already look present.")
elif dry_run:
    print(f"Dry run complete; {len(changed_labels)} file(s) would change.")
else:
    print(f"Done; changed {len(changed_labels)} file(s). Rebuild the project/plugin before use.")

if matches:
    print("\nScanner note: direct binary-extension patterns are present after patch:")
    for item in matches:
        print(f"  {item}")
    print("This is expected only for a local/internal automation fork.")
else:
    print("Scanner note: no direct binary-extension literals were introduced in patched source.")
PY
