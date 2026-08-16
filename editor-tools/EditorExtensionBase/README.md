# Editor Extension Base

> Not a verbatim copy of shipped docs. This online page is an overview and routing surface; shipped buyer docs stay in the plugin package.

This folder is the GitHub docs landing page for Editor Extension Base. The public overview lives at [docs.tiny-tool-development.com/editor-extension-base/](https://docs.tiny-tool-development.com/editor-extension-base/), while the shipped buyer docs stay in the plugin package.

Editor Extension Base is a shared Unreal Editor foundation for Tiny Tool Development UI plugins. It ships reusable Editor Utility widgets, Content Browser selection / checkout / save helpers, undo preparation utilities, and a lightweight runtime macros module.

It is a support layer — it does not register its own Tiny Tools product menu. Feature plugins consume it for consistent editor UX.

## Get It / Routing

- Fab: Not listed yet (internal / foundation package)
- Online docs URL (descriptor `DocsURL`): https://docs.tiny-tool-development.com/editor-extension-base/
- Package docs: shipped inside the plugin package as `Documentation/QUICKSTART.md`,
  `Documentation/UserManual.md`, `Documentation/SettingsReference.md`,
  `Documentation/TROUBLESHOOTING.md`, `Documentation/FAQ.md`, and
  `Documentation/THIRD_PARTY_SOFTWARE.md`.
- Category: Editor Tools
- Descriptor version: `1.0.2` (`EngineVersion` 5.4.0)

## Synergies & Bridges

Optional consumers may depend on Editor Extension Base for shared widgets. Those integrations are owned by the consuming plugin and must degrade gracefully when this package is absent. Cross-plugin synergy write-ups live only on this online documentation surface (Fab Autark §11) — never as a required setup step in a buyer package.

Examples of optional synergy topics (not setup requirements):

- Editor tools that reuse `UEditorToolHeaderWidget` / button / two-pane bases for consistent Tiny Tools chrome.
- Selection helpers (`GetSelectedAssetsForAction`, `CheckoutAndSaveAssets`) shared across governance plugins.

## Media

Product slides and screenshots for this foundation layer are not yet published. Use the in-package Quick Start for the first selection-helper smoke check.
