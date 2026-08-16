<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/LightweightEditorMode/architecture.md -->
# 設定リファレンス

Lightweight Editor Mode は設定を EditorPerProjectUserSettings に保存し、Project Settings > Plugins > Lightweight Editor Mode 以下に公開します。

## 設定モデル

設定オブジェクトは 3 つのレイヤーで構成されています。

- 起動時の動作や選択されたプロファイルインデックスなどのハイレベルオプション。
- モードが有効な際に消費されるアクティブなランタイム値。
- 編集可能な 4 つのプロファイル構造体: Mild、Balanced、Aggressive、Extreme。

Slate UI は、モードを有効化または更新する前に、選択されたプロファイルをアクティブなランタイム値にコピーします。

## ハイレベルオプション

### bEnableOnStartup

エディタ起動時に Lightweight Editor Mode を自動的に有効化します。

実装上の注意点:

- モジュールは StartupModule の実行直後には有効化されません。
- 短いタイマーを起動します。
- タイマーは GEditor がエディタビューポートクライアントを保持するまで待機します。
- ビューポートが使用可能になってからモードが有効化されます。
- 前回のエディタセッションが Lightweight Mode がアクティブなまま終了した場合、自動有効化の前に古いセッションの復元処理が実行されます。

これにより、エディタ起動初期におけるビューポート変更の取りこぼしを防ぎます。

### AggressivenessLevel

現在選択されているプロファイルインデックスを保持します。

| 値 | プロファイル |
| --- | --- |
| 0 | Mild |
| 1 | Balanced |
| 2 | Aggressive |
| 3 | Extreme |

値は有効な範囲内にクランプされます。

## アクティブなランタイム値

これらの値は FEditorLightweightMode によって適用されます。

### OverallQuality

Unreal の拡張性品質レベル（単一指定）です。

| 値 | 意味 |
| --- | --- |
| 0 | Low（低） |
| 1 | Medium（中） |
| 2 | High（高） |
| 3 | Epic（最高） |
| 4 | Cinematic（シネマティック） |

プラグインは適用前にこの値を 0..4 の範囲にクランプします。

### ScreenPercentage

エディタビューポートの描画、および PIE / ゲームプレビューパスのターゲットスクリーンパーセンテージです。

| 範囲 | 意味 |
| --- | --- |
| 25..59 | 非常にアグレッシブ、低画質 |
| 60..79 | パフォーマンス重視の編集 |
| 80..99 | バランス重視の編集 |
| 100 | フル内部解像度 |
| 101..200 | スーパーサンプリング（軽量モードでは通常不要） |

プラグインはこの値を 25..200 の範囲にクランプします。

重要な実装上の詳細: エディタビューポートはエディタ専用のスクリーンパーセンテージ CVar を使用します。プラグインは以下を設定します。

- r.Editor.Viewport.ScreenPercentage
- r.Editor.Viewport.ScreenPercentageMode.RealTime
- r.Editor.Viewport.ScreenPercentageMode.NonRealTime

また、CVar が関連する PIE およびゲームプレビューパス用に r.ScreenPercentage も設定します。

### bDisableLumen

モードがアクティブな間、Lumen ディフューズ間接照明および Lumen リフレクションを無効化します。

CVar:

- r.Lumen.DiffuseIndirect.Allow = 0
- r.Lumen.Reflections.Allow = 0

プロファイルで無効化に設定されている場合、プラグインはタグ付きオーバーライドを削除して、これらの CVar の既存のバックアップを復元します。Lightweight Mode がアクティブな間に他のソースが同じ CVar を変更した場合、その新しい値が維持されます。

### bDisableVirtualShadows

バーチャルシャドウマップ（Virtual Shadow Maps）を無効化します。

CVar:

- r.Shadow.Virtual.Enable = 0

これにより、重い Nanite や広大なワールドシーンの応答性を向上させることができますが、シャドウの外観が大きく変化します。

### bDisableVolumetricFog

ボリュメトリックフォグおよび通常のフォグを無効化します。

CVar:

- r.VolumetricFog = 0
- r.Fog = 0

フォグがエディタのフレームタイムを圧迫している雰囲気にこだわったシーンで有効です。

### bForceUnlitViewports

モードがアクティブな間、エディタビューポートを Unlit（ライティングなし）に切り替えます。

プラグインは切り替え前にビューポートごとの元の表示モードを保存します。同一エディタセッション内でモードが無効化されると、元の表示モードが復元されます。

### bDisableViewportRealtime

モードがアクティブな間、エディタビューポートのリアルタイム描画をオフにします。

プラグインは、ビューポートの保存された永続的なリアルタイム設定を変更する代わりに、Unreal の一時的なリアルタイムオーバーライドシステムを使用します。無効化されると、自身のオーバーライドを解除します。

## プロファイルごとの値

各プロファイルには同じフィールドが含まれています。

- OverallQuality
- ScreenPercentage
- bDisableLumen
- bDisableVirtualShadows
- bDisableVolumetricFog
- bForceUnlitViewports
- bDisableViewportRealtime

プロファイルは Project Settings で編集可能です。プロファイルを変更しても、UI がそのプロファイルをアクティブ値にコピーしない限り、即座には適用されません。

## LastViewModeBeforeLightweight

この隠し表示設定は、モードを有効化する前に観測された最後の表示モードを保存します。エディタ再起動後の永続的なフォールバックとして使用されます。

同一セッション内での復元は、まずビューポートごとのバックアップを使用します。再起動後の復元ではそれらのメモリ内バックアップを使用できないため、Unlit ビューポートを適切な非 Unlit モードに戻すためにのみフォールバック値が使用されます。

## bWasLightweightModeActiveLastSession

この表示可能な診断設定は、エディタの前回終了前に Lightweight Mode がアクティブであったかどうかを記録します。Enable がオーバーライドの適用を開始したときに設定され、Disable によってクリアされます。

再起動後にこれが true のままの場合、UI は Restore Lightweight State を提示し、起動時の自動有効化は古いビューポート状態を復元してから再度有効化を行います。

## デフォルトプロファイルの意図

| プロファイル | 意図 |
| --- | --- |
| Mild | ビジュアルコンテキストを維持しつつわずかな負荷軽減 |
| Balanced | 一般的な編集作業用の推奨デフォルト |
| Aggressive | 応答性を最優先する重いシーンの編集 |
| Extreme | 緊急時または超低スペック環境での編集 |

## 推奨されるカスタマイズ

アート重視のチームの場合、Mild を非破壊的にし、Lit 表示を有効のままにしてください。広大なワールドやノート PC でのワークフローの場合、Balanced をよりアグレッシブに設定します。技術的なデバッグ用には、レンダリングの問題をすぐに検査できるよう、Unlit を強制しないプロファイルを少なくとも 1 つ維持してください。
