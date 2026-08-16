# Secret Backends

LLM Store never stores provider API keys in `Config/LLMStore.json`.

Lookup order is always:

1. Environment variable override.
2. Configured secret backend.
3. Empty string when the key is missing.

## Environment Variables

Environment variables are useful for CI and local developer overrides.

Format:

```text
LLMSTORE_<PROVIDER_ID>_KEY
```

Provider ids are normalized to uppercase and non-alphanumeric separators become underscores.

Example:

```text
ProviderId: openai-main
Variable: LLMSTORE_OPENAI_MAIN_KEY
```

## Encrypted File

`EncryptedFile` is the default backend.

Location:

```text
Saved/LLMStore/secrets.bin
```

This backend requires no external tools and is convenient for local development. Do not commit files from `Saved/LLMStore`.

## Windows Credential Manager

`WindowsCredentialManager` stores provider keys through the Windows Credential Manager API.

Good fit:

- Windows-only teams
- local developer machines
- projects that should avoid even encrypted project-local secret files

## macOS Keychain

`MacOSKeychain` uses the system `security` command.

Good fit:

- macOS developer machines
- teams already relying on Keychain for secrets

The user must have permission to access the relevant keychain entry.

## 1Password

`OnePassword` uses the `op` CLI.

`Vault` should be set unless `Meta` contains a full provider-specific `op://...` reference.

Example:

```text
Backend: OnePassword
Vault: Studio Secrets
KeyPrefix: LLMStore
```

Provider-specific override:

```text
SecretBackend.Meta["openai-main"] = "op://Studio Secrets/LLMStore openai-main/credential"
```

The developer or CI runner must already be signed in through the 1Password CLI.

## Azure Key Vault

`AzureKeyVault` uses the Azure CLI `az`.

`Vault` is the Key Vault name.

Example:

```text
Backend: AzureKeyVault
Vault: my-studio-vault
KeyPrefix: llmstore
```

LLM Store calls Azure CLI commands to get, set, or clear secrets. The developer or runner must already be authenticated with Azure.

## Secret Naming

Generated secret names use:

```text
<KeyPrefix>-<ProviderId>
```

Spaces and underscores are normalized to dashes for external secret names.

If `SecretBackend.Meta` contains an entry for a provider id, that value is used directly. This is useful for existing 1Password references or Azure secret names.

## CI Recommendation

For CI, the environment variable override is usually the simplest option because it needs no file and no interactive login.

Example:

```text
LLMSTORE_OPENAI_MAIN_KEY=${{ secrets.OPENAI_API_KEY }}
```

For shipping checks that should not call cloud providers, do not set cloud keys and enforce build rules instead.

