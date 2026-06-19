# Troubleshooting

## The Context Menu Does Not Appear

Check:

- The plugin is enabled.
- The editor was restarted after enabling.
- You are right-clicking a Content Browser folder for the folder action.
- You are selecting a compatible DataTable for the conversion action.

## The Tool Says No Assets Will Be Renamed

Possible reasons:

- All assets already match the configured conventions.
- Asset types are unsupported.
- The configured DataAsset is empty.
- The selected folder does not contain assets recursively.
- All generated names would be invalid or conflicting.

Review the skip examples in the preview dialog.

## A Texture Got The Generic `T_` Prefix

Texture subtype detection is heuristic. If the texture name and compression settings do not indicate a specific purpose, the plugin uses the generic texture rule.

Fixes:

- Rename the source texture with clearer tokens before running the utility.
- Adjust your rules to use generic `T_` for all textures.
- Extend the token rules in source for your studio suffixes.

## A Rename Failed After Confirmation

Unreal asset renames can fail because of:

- Existing references.
- Source-control checkout issues.
- Locked packages.
- Existing assets not visible during planning.
- Editor state changes between preview and apply.

Check the Output Log and the final applied count.

## Redirectors Remain

The plugin attempts redirector fixup only after actual renames and only when enabled.

If redirectors remain:

- Run **Fix Up Redirectors in Folder** manually.
- Check source-control checkout state.
- Save affected packages.
- Make sure referenced assets are not locked.

## DataTable Conversion Wiped My Target Asset

The conversion asks for confirmation before replacing entries and uses an undo transaction. Use Unreal Undo immediately if the replacement was unintended.

Recommended workflow:

- Duplicate the DataAsset before major imports.
- Keep the asset in source control.
- Review the DataTable rows before conversion.

## Duplicate Prefix Rows Behave Unexpectedly

When multiple prefix rows exist for the same file type, the later row wins. The plugin logs a warning.

Clean up the DataTable so each file type has at most one prefix and one postfix row.

## Names With Spaces Are Skipped

Generated Unreal object names must be valid object names. Spaces and many punctuation characters are rejected.

Fix the rule values or remove invalid fragments from `NamingsToRemove`.

## The Wrong Asset Type Was Detected

Some assets are class hierarchies where order matters. The plugin checks more specific classes before broad ones where possible.

If your asset type is not supported, extend `ResolveFileTypeFromAsset`.

## Source Control Shows Many Renames

That is expected after a batch rename. Review the operation as a dedicated change.

Recommended:

- Start from a clean workspace.
- Apply to a small folder first.
- Commit naming cleanup separately.

## Support Information To Collect

When reporting an issue, include:

- Unreal Engine version.
- Plugin version.
- Selected folder path.
- Configured DataAsset path.
- Example asset old name and expected new name.
- Preview summary.
- Relevant Output Log warnings.
