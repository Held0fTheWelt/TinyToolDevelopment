---
lang: ja
title: EditorExtensionBase Quick Start
audience: [end_user]
owner_ref: plugin:EditorExtensionBase
applies_to:
  component: EditorExtensionBase
preconditions:
  - Unreal Engine project open with the plugin package available
  - Edit > Plugins can enable EditorExtensionBase
expected_result:
  text: GetSelectedAssetsForAction returns the current Content Browser selection after the plugin is enabled.
version:
  since: "1.0"
---
# クイックスタート

このガイドでは、インストールから**実際の初回使用**までを解説します。具体的には、Editor Extension Base を有効化し、Blueprint Utility または C++ のエディタツールから共有のエディタヘルパーを呼び出す方法を示します。Editor Extension Base は他のエディタプラグイン向けのサポートレイヤーであり、スタンドアロンの Tiny Tools メニュー製品ではありません。

## このガイド完了後に得られるもの

プラグインが有効化され、`UEditorManagerUtilityLibrary::GetSelectedAssetsForAction`（または Blueprint から呼び出し可能な同等の関数）が現在の Content Browser の選択状態を正常に返す状態になります。

## 要件

- Unreal Engine 5.4 以降（記述子 `EngineVersion` 5.4.0）。
- Editor Scripting Utilities が有効になっていること（`EditorExtensionBase.uplugin` で依存関係として宣言済み）。
- サードパーティ製ソフトウェア、アカウント、または外部ランタイムは不要です。[THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md) を参照してください。

## 1. インストールと有効化

1. Fab ライブラリから **EditorExtensionBase** をプロジェクトに追加します（またはエンジンの Plugins ディレクトリにインストールします）。
2. **Edit → Plugins** を開き、**EditorExtensionBase** を有効化し、指示されたら再起動します。
3. **Editor Scripting Utilities** が有効化されたままになっていることを確認します。

## 2. モジュールの読み込み確認

再起動後、パッケージは以下の2つのモジュールを公開します。

| モジュール | タイプ | 役割 |
| --- | --- | --- |
| `EditorExtensionBase` | エディタ | ウィジェット、選択ヘルパー、アンドゥユーティリティ。 |
| `EditorExtensionRuntimeBase` | ランタイム | エディタ以外のコンシューマーにも安全な軽量マクロ。 |

## 3. 実例：現在の選択状態の読み取り

1. Content Browser で1つ以上のアセットを選択します。
2. このプラグインに依存する Editor Utility Widget またはエディタ C++ ツールから、以下を呼び出します。

```cpp
TArray<UObject*> Selected = UEditorManagerUtilityLibrary::GetSelectedAssetsForAction(nullptr);
```

3. 意図的に書き込みを行う場合、返されたオブジェクトに対して `CheckoutAndSaveAssets` で永続化または処理を行います。

```cpp
bool bCheckoutOk = false;
bool bSaveOk = false;
const bool bOk = UEditorManagerUtilityLibrary::CheckoutAndSaveAssets(
	Selected, bCheckoutOk, bSaveOk);
```

## 期待される結果

- `Selected` には Content Browser の選択状態が含まれます（何も選択されていない場合は空になります）。
- `CheckoutAndSaveAssets` を呼び出すと、ブール値の出力パラメータはチェックアウトと保存の結果を報告しますが、トランザクションを自動生成しません。`FScopedTransaction` のスコープは呼び出し側が管理します。

## 次のステップ

- ウィジェットとユーティリティのカタログについては [UserManual.md](UserManual.md) をお読みください。
- 共有ウィジェット上の編集可能なプロパティについては [SettingsReference.md](SettingsReference.md) をお読みください。
- BindWidget スロットや選択ヘルパーがログで警告を出す場合は [TROUBLESHOOTING.md](TROUBLESHOOTING.md) を参照してください。
