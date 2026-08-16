<!-- doc-provenance: AKDB:plugins/UnrealCapabilityMesh/architecture.md; docs/architecture/plugins/UnrealCapabilityMesh/product-facts.yml; reconciled 2026-07-19 -->
# クイックスタート

このガイドでは、新規インストールから**機能する目に見える結果**（検出された機能インベントリと、自分で実行して JSON レスポンスを取得するルート）までを案内します。コーディングやマニフェストの作成は不要です。プラグインにはすぐに使用できるデフォルトプロファイルが付属しています。

## このガイドの完了後に得られるもの

コントロールパネルが開き、バンドルされた **Default Capability Mesh Profile** がロードされ、機能が検出され、1つのルート（`sample.echo.route.v1`）が実行されて JSON レスポンスと開くことができる保存済みレポートが得られます。

## 要件

- Unreal Engine 5.4 以降。
- プラットフォーム: Windows (Win64)、Linux、または Mac。
- プラグインを有効にする Unreal **プロジェクト**。UCM は C++ エディタープラグインです。C++ プロジェクトでは最初のエディター起動時にコンパイルされます。Blueprint のみのプロジェクトでは、エディターが事前に構築されたエディターモジュールをロードできるように、適合するエンジンバージョン用にインストール（Fab ライブラリ経由）してください。
- サードパーティ製ソフトウェア、アカウント、AI モデル、または外部ランタイムは不要です。[THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md) を参照してください。

## 1. インストールと有効化

1. Fab ライブラリから **Unreal Capability Mesh** を取得し、プロジェクトに追加する（プロジェクトの `Plugins/` フォルダ配下に表示されます）か、エンジンにインストールします。
2. プロジェクトを開きます。エディターで **Edit → Plugins** に移動し、`Unreal Capability Mesh` を検索して **Enabled** にチェックを入れます。
3. 指示されたらエディターを再起動します。（C++ プロジェクトの場合、この最初の起動時にコンパイルさせます。）

UCM はプロジェクトローカルのセットアップフォルダがなくても動作できます。バンドルされたデフォルトプロファイルと、有効化されたプロバイダープラグインからのプラグインローカルプロファイルをロードします。プロジェクトが意図的にオーバーライドやプロジェクト所有の複合ルートを必要とする場合にのみ `Config/UnrealCapabilityMesh/` を使用してください。

## 2. 最初の動作確認（最初の結果）

1. コントロールパネルを開きます: **Tools → Unreal Capability Mesh**。
2. **Overview** ページに、アクティブプロファイル **"Default Capability Mesh Profile"** が表示されているはずです。
3. **Reload Setup** をクリックします。UCM はプロファイルをロードし、JSON セットアップを検証し、定義を登録し、検出を実行します。
4. **Capabilities** ページを開きます。検出された機能（例: `mesh.sample.echo`）とその利用可能性および副作用が表示されます。
5. **Diagnostics** ページを開きます。リロードによるセットアップ検証および検出メッセージが表示されます。エラーのないリロードは、プラグインが正常に動作していることを意味します。

パッケージに同梱されているものだけで、製品の動作確認が完了しました。

## 3. 実際の作業例: ルートの実行

UCM には、安全で読み取り専用のサンプルルート `sample.echo.route.v1` が付属しており、エコーエンドポイントを呼び出します。これを使用して最初のエンドツーエンドルートを実行します。

1. **Routes** ページを開きます。
2. ルート ID フィールドに以下を入力します:

   ```text
   sample.echo.route.v1
   ```

3. **Dry Run** をクリックします。UCM はルートを計画し、`mesh.sample.echo` 機能が `read_only` の副作用で使用可能であり、**承認が不要**であることを確認します。ドライランレポートにエラーはありません。
4. ルート入力フィールドに以下の JSON を入力します（これらは想定されるパラメータです。`request_json` フィールドにペイロードを保持するルート入力エンベロープです）:

   ```json
   {
     "request_json": "{\"message\":\"hello\"}"
   }
   ```

5. **Execute** をクリックします。

**期待される出力:** ルートは `{"echo": { ... }}` の形式で JSON エコーレスポンスを返し、ルート実行レポートを書き込みます。エンドポイントは、リクエストペイロードを `{"echo":<request>}` としてラップする出荷済みの `UCapabilityMeshTestInvoker::EchoJson` 関数です。

Routes ページには、**実験的** なセルフ自動承認のための **Route Catalog** 承認列も含まれています。このクイックスタートでは **Approve all at own risk** および個別のルートスイッチをオフのままにしてください。これらは自己責任で承認ゲート付きルートをテストするためだけのものです。

## 4. 結果の保存場所

生成されたすべてのファイルは、プロジェクトの `Saved/` フォルダ配下に書き込まれます:

```text
Saved/UnrealCapabilityMesh/
  setup_validation_report.json     ← リロード検証
  capability_registry.json         ← 登録された機能
  discovery_report.md              ← 人間が読める検出サマリー
  compatibility_matrix.json        ← 機能/エンドポイントの互換性
  route_reports/                   ← ドライラン計画
  route_execution_reports/         ← 実行されたルートの入力と出力（エコー結果）
```

`route_execution_reports/` を開くと、実行したルートからのレスポンスを確認できます。

## 5. 次のステップ

- パネルと各機能をパラメータとともに操作する: [UserManual.md](UserManual.md)。
- すべてのプロファイルフィールド、ポリシー、および出力パス: [SettingsReference.md](SettingsReference.md)。
- 必要な場合のみセットアップをカスタマイズする: `<YourProject>/Config/UnrealCapabilityMesh/project_profile.json` を作成するか、プロジェクトがオーバーライドする特定のマニフェストをコピーして、再度 **Reload Setup** をクリックします。プロバイダー所有のマニフェストは各プラグイン内に残します。
- 別のプラグインを接続する: [INTEGRATION.md](INTEGRATION.md)。
- 正常に動作しない場合: [TROUBLESHOOTING.md](TROUBLESHOOTING.md) および [FAQ.md](FAQ.md)。

Tiny Tool Execution Integration Bridge が有効になっている場合、エディター起動時に TTER が投影されたルートを検出する前に UCM をリロードします。プロファイルの編集やプロバイダーの有効化を行った後の通常のアクションは、手動での **Reload Setup** です。

---

> **メンテナー / ソースからのビルドの場合（プラグインの使用には不要）:** ソースリポジトリの検証ツールはメンテナー専用であり、Fab パッケージには含まれて**いません**。UCM のインストールや使用に Python やソースゲートは不要です。
