<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/LightweightEditorMode/architecture.md -->
# トラブルシューティング

本ガイドでは、一般的な問題と発生し得る原因について解説します。

## プラグインウィンドウが表示されない

以下を確認してください。

- Edit > Plugins でプラグインが有効になっていること。
- プラグイン有効化後にプロジェクトを再起動したこと。
- .uproject ファイルの Plugins 配列にモジュールが記述されていること。
- コマンドレットではなく、エディタを実行していること。

ウィンドウは Tools > Performance > Lightweight Editor Mode の下に表示されます。

## 起動時にモードが有効化されない

起動時の有効化は、エディタビューポートクライアントが生成されるまで待機します。動作の重いプロジェクトでは、モジュール起動から少し時間がかかる場合があります。

以下を確認してください。

- Enable on Editor startup がチェックされていること。
- プロジェクトでプラグインが有効になっていること。
- エディタがレベルエディタビューポートを実際に生成したこと。
- ログに "Scheduling Lightweight Mode auto-enable" が含まれていること。
- その後、ログに "Auto-enabling Lightweight Mode after editor viewports became available" が含まれていること。

ビューポートが利用可能になる前に設定のチェックを外すと、タイマーは自動的にキャンセルされます。

## スクリーンパーセンテージが変更されないように見える

エディタビューポートは必ずしも r.ScreenPercentage に従うとは限りません。Lightweight Editor Mode はエディタビューポート専用の CVar を使用します。

- r.Editor.Viewport.ScreenPercentage
- r.Editor.Viewport.ScreenPercentageMode.RealTime
- r.Editor.Viewport.ScreenPercentageMode.NonRealTime

ビューポートが依然として変化しないように見える場合は、以下を確認してください。

- 選択されているプロファイルの ScreenPercentage の値。
- ビューポートがスクリーンパーセンテージをオーバーライドするエンジンパスを使用しているかどうか。
- Lightweight Editor Mode の実行後に、別のプラグインやコンソールコマンドが同じエディタ CVar を変更しているかどうか。

## 無効化後もビューポートが Unlit のままになる

同一セッション内の復元ではビューポートごとのバックアップが使用されます。再起動後のフォールバックには、保存された LastViewModeBeforeLightweight の値のみが存在します。

以下を試してください。

1. プラグインウィンドウを開きます。
2. Disable Lightweight Mode をクリックします。
3. 必要に応じて、手動でビューポートを Lit に戻します。
4. 同一セッション内で再度モードを有効化および無効化し、通常の復元が行われることを確認します。

これが頻繁に発生する場合は、モードが有効なままエディタが終了していないか確認してください。

クラッシュや強制終了の後は、メインボタンに Restore Lightweight State が表示される場合があります。それをクリックして保守的なビューポート復元を実行し、古いセッションマークをクリアしてください。

## リアルタイム描画が無効のままになる

リアルタイムの無効化には、Unreal の一時的なリアルタイムオーバーライドシステムが使用されます。同一エディタセッション内では、Disable はビューポートの保存されたリアルタイム設定を変更する代わりに、Lightweight によるオーバーライドを削除します。

リアルタイムが依然として無効に見える場合は、他のエディタシステムが独自にリアルタイムオーバーライドを有効にしているかどうかを確認してください。必要に応じてビューポートメニューから手動でリアルタイムを再有効化してください。

## Lumen が有効なままに見える

以下を確認してください。

- 選択されたプロファイルで bDisableLumen が有効になっているか。
- プロジェクトが実際に Lumen を使用しているか。
- モード有効化後に、別のプラグインやプロジェクトコードが Lumen CVar を設定していないか。
- カスタムエンジンブランチで該当の CVar がリネームまたは削除されていないか。

プラグインが対象とする CVar:

- r.Lumen.DiffuseIndirect.Allow
- r.Lumen.Reflections.Allow

存在しない CVar はスキップされ、Verbose レベルでログに記録されます。

## シャドウの負荷が高いままに見える

bDisableVirtualShadows はバーチャルシャドウマップ（Virtual Shadow Maps）を対象としています。

- r.Shadow.Virtual.Enable

これは、すべてのレンダラーパスにおけるあらゆるシャドウコストを無効化するわけではありません。シーンで非バーチャルシャドウ、カスタムシャドウシステム、レイトレースシャドウ、またはプラグインによるレンダリングを使用している場合、プロジェクトに応じた追加のチューニングが必要になる場合があります。

## フォグが消えない

bDisableVolumetricFog は以下を設定します。

- r.VolumetricFog = 0
- r.Fog = 0

マテリアル、ポストプロセスボリューム、スカイシステム、またはカスタム大気エフェクトによっては、フォグに似た見た目が残る場合があります。

## エディタの画質が低すぎる

アグレッシブ度の低いプロファイルを使用してください。

- Extreme から Aggressive に変更する。
- Aggressive から Balanced に変更する。
- ScreenPercentage を上げる。
- OverallQuality を上げる。
- カスタムプロファイルで Force Unlit を無効化する。

モードが有効な状態でプロファイルを変更すると、ヘルパーが自動的にアクティブな設定を更新します。

## エディタが依然として重い

Lightweight Editor Mode はエディタビューポートの描画負荷を対象としています。エディタのすべてのパフォーマンス問題を解決できるわけではありません。

その他のボトルネックの可能性:

- アセットのコンパイル。
- シェーダーのコンパイル。
- ソースコントロール操作。
- Blueprint のコンストラクションスクリプト。
- Editor Utility Widget。
- エディタワールド内の重い Tick ロジック。
- 大量のアクター数。
- ディスクやウイルス対策ソフトによるオーバーヘッド。

レンダリング以外のボトルネックを診断するには、Unreal Insights、Stat コマンド、および通常のプロジェクトプロファイリングを使用してください。

## Disable を実行しても CVar が復元されない

復元処理は、プラグインのタグ付きオーバーライドを削除します。Lightweight Editor Mode がアクティブな間に別のシステムが同じ CVar を変更した場合、古いバックアップで上書きされる代わりに、その新しい値が維持されます。

CVar 名について出力ログを確認してください。プラグインはバックアップと復元の操作をログに記録します。

## Project Settings ページが表示されない・見つからない

設定ページは Project Settings > Plugins > Lightweight Editor Mode の下に表示されます。

表示されない場合:

- モジュールがロードされているか確認します。
- Settings モジュールが利用可能か確認します。
- プラグイン有効化後にエディタを再起動します。
- プラグイン記述子やビルドの問題でモジュールのロードが妨げられていないか確認します。

## 新しい CVar 追加後にビルドが失敗する

よくある原因:

- CVar 名の定数を追加したが、一貫して使用されていない。
- プロファイル構造体に設定を追加したが、アクティブフィールドに追加していない。
- 新しいプロファイルに対して UI の switch 文が更新されていない。
- Unreal の型に必要な include が不足している。
- UPROPERTY メタデータブロック内の構文エラー。

ソース変更後はエディタターゲットのビルドを実行してください。

## 確認すべきログ

Output Log で以下を検索してください。

- [Module]
- [Lightweight]
- Backup CVar
- Restore CVar
- ApplyActiveSettings
- ApplyViewportSettings
- Lightweight mode ENABLED
- Lightweight mode DISABLED

ログは意図的に詳細に出力されるため、サポート依頼時に該当するシーケンスをそのまま提示できます。
