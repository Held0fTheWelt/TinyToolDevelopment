# Troubleshooting

## The Tool Does Not Show My Category

Check:

- The category is declared or defined in a scanned source path.
- The file extension is `.h`, `.hpp`, `.cpp`, or `.inl`.
- The category is not hidden by permanent or temporary hide settings.
- The scan has completed or is still processing.
- The macro is one of the supported Unreal log macro forms.

If your project wraps Unreal log macros in a custom macro, the scanner may need an extension.

## The Default Verbosity Is Missing Or Wrong

The scanner can only infer defaults from recognizable macro arguments. Some categories may still be listed with an empty or fallback default.

Fixes:

- Use standard Unreal macro formatting where possible.
- Add a persistent override if you need a known value.
- Extend scanner parsing if the project uses custom wrappers.

## Changing A Verbosity Does Nothing

Possible causes:

- The category is not registered by a loaded module yet.
- Unreal rejected the console command.
- Runtime code changed the category again after the editor command.
- A typo or unusual category name exists in the DataAsset.

Check the Output Log for `LogLogLevelEditor` messages.

## Saved Verbosity Is Not Applied On Startup

Check:

- `LogLevelDataAsset` points to a valid asset.
- The DataAsset contains override entries.
- The category exists by the time startup replay runs.
- No runtime code overrides the value later.

The plugin retries startup application per category. Already-applied overrides are not held back by entries that are invalid or not registered yet, but an unregistered category still cannot be applied until Unreal knows that category.

## My DataAsset Contains Too Many Entries

The DataAsset should contain intentional overrides only. Reset rows to detected defaults to remove unnecessary entries.

## Temporary Hide Values Came Back

Temporary hide values are transient and should not persist across sessions. Use `LogChannelsToHide` for permanent hiding.

## Scanning Takes Too Long

Disable engine plugin and engine source scanning unless needed.

Recommended normal setup:

```text
bAlsoListEnginePluginChannels = false
bAlsoListEngineSourceChannels = false
```

## Output Log Is Still Noisy

Some systems can log through multiple categories. Search for related category prefixes and adjust each relevant channel.

Also remember that `Warning`, `Error`, and `Fatal` messages may still appear depending on the selected verbosity and Unreal logging rules.

## The Plugin Opens But Shows No DataAsset Overrides

The scanner and the DataAsset are separate:

- Scanner: discovers available categories.
- DataAsset: stores persistent overrides.

An empty DataAsset is normal when no persistent overrides are configured.

## Source Control Keeps Showing My DataAsset Changed

You probably changed persistent overrides. Either keep the changes as team policy or reset rows to defaults before committing.

## Support Information To Collect

When reporting an issue, include:

- Unreal Engine version.
- Plugin version.
- Whether engine source/plugin scanning is enabled.
- Example log category declaration.
- Relevant `LogLogLevelEditor` output.
- Whether the category exists in the configured DataAsset.
