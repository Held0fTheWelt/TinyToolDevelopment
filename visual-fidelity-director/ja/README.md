<!-- doc-provenance: AKDB:plugins/VisualFidelityDirector/architecture.md; docs/architecture/plugins/VisualFidelityDirector/product-facts.yml; reconciled 2026-07-12 -->
# Visual Fidelity Director ドキュメント

このフォルダには、Visual Fidelity Director に同梱されている購入者向けドキュメントが含まれています。コアワークフローは独立して機能します。プラグインを有効にし、コックピットを開き、フィデリティプロファイルとコンポジション軸を確認し、エビデンスを検査し、必要に応じてガバナンス設定の書き込みを承認し、他のプラグインや外部サービスを必要とせずにクラシックなスナップショット/レシピワークフロー用の Expert Tools を使用できます。

現在のパッケージドキュメントはバージョン `2.0.0` および公開状態 `In Publishment` に整合されています。

## ここから始める

- [QUICKSTART.md](QUICKSTART.md): インストール、有効化、最初のコックピット更新、および 1 つのプロファイル比較タスク。
- [UserManual.md](UserManual.md): コックピット、エビデンス、Expert Tools のすべてのアクション。
- [SettingsReference.md](SettingsReference.md): コントロール、プロファイルパス、Blueprint ライブラリ関数、レポート出力、および適用動作。
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md): よくある問題と解決策。
- [FAQ.md](FAQ.md): 互換性、安全性、MRQ、スクリーンショット、サポートに関する回答。
- [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md): 外部依存関係の宣言。

## コックピットのエントリ

**Tiny Tools > Visual Fidelity Director**（Performance セクション）から Visual Fidelity Director を開きます。

ドックタブには 3 つのページがあります:

| ページ | 目的 |
| --- | --- |
| **Cockpit** | プロファイルバー、マルチフレームライブメトリクス、9 つのコンポジション軸、バリアントセレクター、インテントスライダー、継承パス付き軸詳細、プロベナンス、検出事項、プロファイル比較、およびガバナンス管理された永続適用。 |
| **Evidence** | コンポジション軸にマッピングされた 11 の固定レーンエビデンスブロック。 |
| **Expert Tools** | スナップショット、レシピ、スキャナー、プレビュー適用、およびレガシーレポート用の統合された 1.x コントロールパネル。 |

## プロファイルとレポート

フィデリティプロファイルの保存先:

```text
Saved/VisualFidelityDirector/profiles/
```

Expert Tools および検証ワークフローのレポート保存先:

```text
Saved/VisualFidelityDirector/reports/
```

レシピのコピー保存先:

```text
Saved/VisualFidelityDirector/recipes/
```

## Blueprint サーフェス

ランタイム Blueprint 呼び出し元は `UVFDCockpitBlueprintLibrary`（コックピット UI と同じ C++ サービス）を使用します。パッケージ化されたショーケースアセットが `Content/Blueprints/BPF_VFD_API` に同梱されています。

## 安全性モデル

- コックピットの確認、エビデンス、および比較アクションは、ガバナンス適用ドロワーを使用しない限り読み取り専用です。
- **ガバナンス管理された永続適用** は、`DefaultGameUserSettings.ini` の Scalability グループ、`DefaultEngine.ini` のレンダラー設定、および `DefaultDeviceProfiles.ini` にのみ書き込みます。これは、バックアップ、検証、およびロールバックをサポートした上で、送信先ごとの明示的な承認を得た後でのみ実行されます。
- **Expert Tools > Preview Apply + Rollback** は、セッション CVar プレビューパスのままです。
- アセット、マテリアル、Post Process Volume、MRQ プリセット、LevelSequence、Blueprint、およびアクセシビリティ設定はブロックされたままです。

## スキーマ

パッケージ化されたランタイムスキーマファイルは、プラグインのルートにある `Schemas/` 配下に保存されています。

## 関連ファイル

- [../README.md](../README.md): 製品の概要。
- [../CHANGELOG.md](../CHANGELOG.md): リリース履歴。
