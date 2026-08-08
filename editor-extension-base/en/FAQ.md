# FAQ

## What is Editor Extension Base for?

It is a shared foundation for Tiny Tool Development editor UI plugins: reusable Editor Utility widgets, selection / checkout / save helpers, undo preparation utilities, and a lightweight runtime macros module.

## Is it an end-user tool?

No. It does not register a Tiny Tools product menu of its own. Feature plugins consume it as a dependency.

## Which Unreal modules does it load?

`EditorExtensionBase` (Editor) and `EditorExtensionRuntimeBase` (Runtime), as declared in `EditorExtensionBase.uplugin`.

## Does it require other Tiny Tool plugins?

No. It requires Unreal's **Editor Scripting Utilities** plugin (enabled in the descriptor). Scene, AI, or other Tiny Tool plugins are optional consumers, not setup requirements.

## How do I read the current Content Browser selection?

Call `UEditorManagerUtilityLibrary::GetSelectedAssetsForAction` from Blueprint or C++ after enabling the plugin. See [QUICKSTART.md](QUICKSTART.md).

## How should I open an undo transaction?

Own an `FScopedTransaction` in the caller. `BeginTransactionAndGetSelectedAssets` is deprecated as of Unreal Engine 5.4.

## Why do my widget Blueprints warn at runtime?

BindWidget slots such as buttons, text blocks, or icons are null. Ensure the Utility Widget Blueprint binds every required slot declared on the C++ base class.

## Does CheckoutAndSaveAssets always succeed?

No. It reports checkout and save outcomes through boolean out-parameters. Source-control or save failures surface there and in related result codes such as `SucceededWithCheckoutWarning`.

## Are there project-wide DeveloperSettings?

No. Configurable fields live on the shared widgets and utilities. See [SettingsReference.md](SettingsReference.md).

## Does the package include third-party software?

No. See [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## What engine versions are supported?

The packaged descriptor targets Unreal Engine 5.4.0 on Win64, Linux, and Mac for the editor module allow list.

## Where do I get support?

Use `mailto:support@tiny-tool-development.com` (descriptor `SupportURL`) or the support link on the Fab product page.

## Can I use only the runtime macros without the editor module?

Yes. `EditorExtensionRuntimeBase` is a separate runtime module intended to stay dependency-light for non-editor consumers.

## Does PrepareUndo modify assets immediately?

It prepares undo options for selected transactional assets and skips invalid selections with warnings. Persistence still goes through checkout/save helpers when you intentionally write.

## Can runtime macros pull editor-only modules?

No. Keep `EditorExtensionRuntimeBase` dependency-light. Editor widgets and selection helpers remain in the Editor module.
