# FAQ

## Does the plugin rename assets or only report names?

It renames assets after you confirm the validated preview. The rename is performed through Unreal's `IAssetTools::RenameAssets`.

## Does it rename folders?

No. It scans selected folders recursively and renames assets inside them.

## Can I preview changes first?

Yes. The main workflow builds a rename plan and shows a confirmation summary before applying changes when confirmation is enabled.

## What happens when two assets would get the same name?

Both conflicting entries are skipped from the rename plan. The summary includes duplicate-target skip reasons.

## Can it detect texture types?

Partially. It uses compression settings and common name tokens for normal, diffuse, mask, roughness, metallic, opacity, and emissive textures. Unknown textures fall back to the generic texture rule.

## Does it change Blueprint class names?

It renames the asset. It does not rewrite C++ symbols or internal gameplay naming conventions.

## Can I use my own prefixes?

Yes. Edit the configured `UNamingConventionsDataAsset`.

## Can I import conventions from a spreadsheet?

Yes. Import a compatible DataTable and use the DataTable conversion context-menu entry.

## Is the default naming standard mandatory?

No. It is a starter preset. Studios should edit the DataAsset to match their own standard.

## Does it fix redirectors?

The main workflow can attempt redirector fixup after actual renames when the setting is enabled.

## Why was an asset skipped as unsupported?

The asset class is not mapped by the plugin's type detection. You can extend the source code to support additional classes.

## Why was a generated name invalid?

Unreal object names cannot contain certain characters such as spaces, slashes, dots, quotes, and other invalid object-name characters.

## Is it safe for large folders?

It is safer than a blind rename because it validates and previews a plan, but large renames still deserve source-control discipline and review.

## Does it work in packaged games?

No. It is an editor plugin.
