<!-- doc-provenance: AKDB:plugins/VisualFidelityDirector/architecture.md; docs/architecture/plugins/VisualFidelityDirector/product-facts.yml; reconciled 2026-07-12 -->
# クイックスタートガイド

このガイドでは、インストールから**実際の成果**（Visual Fidelity Director コックピットを開き、プロファイルビューを更新して並べて比較するまで）をご案内します。

## このガイドの終了時に得られるもの

Unreal Editor で VFD コックピットが開き、ライブメトリクスのサンプリングが開始され、1 つのコンポジション軸がバリアントとプロベナンスの詳細とともに確認され、2 つ目のプロファイルとの比較が実行されます。

## 要件

- Win64、Linux、または Mac 上の Unreal Engine 5.4 エディタ。
- エディタプラグインをロードできるプロジェクト。
- サードパーティ製ソフトウェア、アカウント、AI サービス、その他の Tiny Tool プラグインは不要です。

## 1. インストールと有効化

1. Fab ライブラリから **VisualFidelityDirector** をプロジェクトに追加するか、Engine にインストールします。
2. **Edit > Plugins** を開きます。
3. **Visual Fidelity Director** を検索します。
4. プラグインを有効にし、プロンプトが表示されたら Unreal Editor を再起動します。

ソースのみのプラグインパッケージを C++ プロジェクトにインストールする場合は、次のエディタ起動時に Unreal にプロジェクトモジュールをコンパイルさせてください。

## 2. コックピットを開く

1. **Tiny Tools > Visual Fidelity Director** を開きます。
2. **Cockpit** ページがアクティブ（デフォルト）であることを確認します。
3. ステータスバナー、プロファイルセレクター、メトリクスバーを確認します。

期待される出力:

- ドックタブのタイトルは **Visual Fidelity Director** です。
- プロファイルバーには、`Saved/VisualFidelityDirector/profiles/` からロードされた既知のプロファイルと組み込み/プロジェクトコンテキストが一覧表示されます。
- メトリクスバーは数エディタティック（マルチフレームサンプリング）にわたって満たされるか、明示的な利用不可ステータスを表示します。

## 3. 実践例: 1 つの軸を確認する

1. Cockpit アクションカードの **Refresh** をクリックします。
2. 任意のコンポジション軸ストリップ（例: **Anti-Aliasing** または **Upscaling**）を選択します。
3. 軸詳細ドロワーで以下を確認します:
   - ルートプロファイルからアクティブプロファイルへの **継承パス**。
   - コンパイルされた設定の **プロベナンス** 行。
   - その軸の **コントロールローカルの検出事項**。
4. 複数のパイプラインバリアントが利用可能な場合は、**Variant** コンボを変更します。利用できないバリアントは表示されたままですが、互換性エビデンスとともに無効化されます。

期待される出力:

- インテントスライダーの更新に選択したバリアントが反映されます。
- 選択した軸のプロベナンスと検出事項が更新されます。
- ガバナンス適用または Expert Tools プレビュー適用を使用しない限り、プロジェクトファイルは変更されません。

## 4. 実践例: 2 つのプロファイルを比較する

1. Cockpit ページの **Profile Comparison** カードまでスクロールします。
2. ドロップダウンから **Compare against** プロファイルを選択します。
3. 軸ごとの差分サマリーを確認します。

期待される出力:

- 異なる軸が設定レベルの詳細とともに一覧表示されます。
- 一致する軸には差分行が表示されません。
- 比較には、`UVFDCockpitBlueprintLibrary::CompareFidelityProfiles` と同じランタイムコンパレータが使用されます。

## 5. オプション: Expert Tools スナップショット

1. **Expert Tools** ページに切り替えます。
2. **Export Snapshot** をクリックします。

期待される出力:

- `Saved/VisualFidelityDirector/reports/<timestamp>/quality_snapshot.json` が存在します。
- 最新のコピーが `Saved/VisualFidelityDirector/reports/` 配下に表示されます。

このパスは、レポート優先の確認を好むユーザーのために 1.x のスナップショットおよびレシピワークフローを保持します。

## 6. オプション: ガバナンス管理された永続適用

プロジェクト設定ファイルを書き込む意図がある場合にのみ続行してください。

1. Cockpit ページで、適用ドロワーの **Build Destinations** をクリックします。
2. 各送信先サマリー（Scalability、renderer ini、Device Profiles）を確認します。
3. 受け入れる送信先のみ承認をチェックします。
4. **Apply Approved** をクリックします。

期待される出力:

- VFD 設定バックアップルート配下にタイムスタンプ付きバックアップとロールバックマニフェストが作成されます。
- 検証結果を含む適用レポート。
- 検証に失敗した場合、**Rollback** がバックアップされたファイルを復元します。

## 7. 成果物の保存場所

```text
Saved/VisualFidelityDirector/profiles/
Saved/VisualFidelityDirector/reports/<timestamp>/
Saved/VisualFidelityDirector/recipes/
```

## 8. 次のステップ

- 完全な操作リスト: [UserManual.md](UserManual.md)
- コントロールと Blueprint 関数: [SettingsReference.md](SettingsReference.md)
- トラブルシューティング: [TROUBLESHOOTING.md](TROUBLESHOOTING.md)
- 互換性と安全性に関する回答: [FAQ.md](FAQ.md)
