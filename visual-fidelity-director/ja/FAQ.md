<!-- doc-provenance: AKDB:plugins/VisualFidelityDirector/architecture.md; docs/architecture/plugins/VisualFidelityDirector/product-facts.yml; reconciled 2026-07-12 -->
# よくある質問 (FAQ)

## VFD は Unreal のレンダラーやアンチエイリアスを置き換えますか？

いいえ。Unreal の既存のレンダリングシステムの上に位置する、診断、プロファイル、エビデンス、比較、レシピ、試行評価、スキャナー、および推奨事項のレイヤーです。

## 2.0.0 で何が変わりましたか？

バージョン `2.0.0` では、プロファイル中心のコックピット（バリアントセレクター、継承パス、プロベナンス、検出事項、プロファイル比較、ガバナンス管理された永続適用、マルチフレームライブメトリクス）、`UVFDCockpitBlueprintLibrary`、およびパッケージ化された Blueprint ショーケースアセットが追加されました。統合された Expert Tools ページは 1.x のスナップショットおよびレシピワークフローを維持しています。

## AI やクラウドサービスが必要ですか？

いいえ。VFD には外部 AI、クラウド、Python、Node.js、またはアカウントの要件はありません。

## 他の Tiny Tool プラグインが必要ですか？

いいえ。コアワークフローは独立しています。

## サポートされている Unreal のバージョンは何ですか？

Visual Fidelity Director は、対応する Engine ブランチデスクリプタを通じて Unreal Engine 5.4 から 5.8 をサポートし、Win64、Linux、Mac を許可します。

## プロジェクトを変更できますか？

デフォルトでは変更しません。ガバナンス管理された永続適用は、明示的に承認された場合にのみ 3 つの設定送信先（`DefaultGameUserSettings.ini` の Scalability グループ、`DefaultEngine.ini` のレンダラー設定、`DefaultDeviceProfiles.ini` の Device Profiles）に書き込みます。Expert Tools **Preview Apply + Rollback** は、サポートされているエディタセッション CVar を一時的に設定して復元できます。アセット、マテリアル、Post Process Volume、MRQ プリセットは変更されません。

## Lumen Deep Scan はメッシュやマテリアルを変更しますか？

いいえ。Lumen Deep Scan はスナップショットおよび Asset Registry メタデータからレビュー検出事項を書き出します。Static Mesh カード設定、マテリアルグラフ、マテリアルカード共有フラグ、プロジェクト設定、MRQ プリセットの変更は行いません。

## スクリーンショットをキャプチャしますか？

将来のワークフローでスクリーンショットパスが提供されない限り、Expert Tools A/B ワークフローはメタデータのみの比較レポートを書き出します。レポートを使用して決定事項を関連付け、必要に応じて視覚的エビデンスを手動でキャプチャしてください。

## 一部の検出事項が「中程度の信頼度」になっているのはなぜですか？

多くの視覚的アーティファクトはコンテンツや動きに依存します。VFD は事実とヒューリスティックを分離しているため、メタデータを証明として扱うことなく手動レビューを割り振ることができます。

## プロファイルとレポートはどこに保存されますか？

```text
Saved/VisualFidelityDirector/profiles/
Saved/VisualFidelityDirector/reports/
Saved/VisualFidelityDirector/recipes/
```

## Blueprint から VFD を使用できますか？

はい。`UVFDCockpitBlueprintLibrary` はプロファイル、エビデンス、機能、ガバナンス適用の関数を公開しています。配線例については `Content/Blueprints/BPF_VFD_API` を参照してください。

## サポートの問い合わせ先はどこですか？

プラグインデスクリプタに記載されているサポートメールをご利用ください:
`support@tiny-tool-development.com`

Discord: `#support`（公開時の製品リストを参照）。
