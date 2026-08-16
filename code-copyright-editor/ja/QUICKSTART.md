<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/CodeCopyrightEditor/architecture.md -->
# クイックスタート

このガイドでは、インストールから**実際の結果**を得るまでの手順を説明します。選択したソースファイルに一貫した著作権表示が適用され、開いて確認できるスキャンレポートが生成されます。Code Copyright Editor は完全に単体で動作します — 他のプラグインは不要です。

## このガイドを完了した後に得られるもの

所有者/ライセンスが設定され、ファイルごとのステータスでコードベースがスキャンされ、選択したファイルに対して制御された書き換えが適用されます。さらに `Saved/CodeCopyrightEditor/` 配下に JSON スキャンレポートが生成されます。

## 要件

- Unreal Engine 5 エディター（プラグインはエディター内で動作し、パッケージ化されたゲームでは動作しません）。
- スキャン対象のソース/プラグインフォルダを含む C++ または Blueprint プロジェクト。
- サードパーティ製ソフトウェア、アカウント、または外部ランタイムは不要です。[THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md) を参照してください。

## 1. インストールと有効化

1. Fab ライブラリから **Code Copyright Editor** をプロジェクトに追加します（またはエンジンにインストールします）。
2. エディターで **Edit → Plugins** を開き、**Code Copyright Editor** を有効にして、指示に従って再起動します。

## 2. ツールを開く (最初の結果)

1. **Tools → Code Tools → Code Copyright Editor** を開きます。
2. **Configure** タブで、アイデンティティとライセンス（所有者、ライセンス識別子、テンプレート、スキャン範囲）を設定します。**Save** をクリックします。
3. **Scan & Review** タブに切り替え、**Scan Files** をクリックします。

対象となる各ファイルがステータスバッジ（`OK`, `MISSING`, `REPLACE`, `PROTECTED`, …）とともに表示されます。スキャンによってファイルが書き換えられることはありません — これは安全なプレビューです。

## 3. 実践的な例: 選択したファイルへの通知の適用

1. **Scan & Review** で **Select Changeable** をクリックします — これにより、安全に書き換え可能な行（`MISSING`, `REPLACE`）のみがチェックされます。`PROTECTED` および `CONFLICT` ファイルは変更されません。
2. 最初に単一の行を選択し、プレビューで**既存**の通知と**提案**された通知を比較します。
3. (推奨) **Configure** タブで **Create Backup Before Write** を有効にし、事前に作業内容をソース管理にコミットしておきます。
4. **Apply Selected** をクリックして確認します。ツールはチェックされた変更可能なファイルのみを書き換え、その後再スキャンを実行します。

**期待される出力:** 適用されたファイルはステータス `UPDATED` に遷移し、適用結果と新しいスキャンが表示されます。**Apply & Reports** で **Export JSON** をクリックします。

## 4. 結果の保存場所

```text
Saved/CodeCopyrightEditor/LastCopyrightScan.json
```

**Update Project Notice** を使用して、プロジェクトレベルの通知（ソースの書き換えなし）を更新することもできます。これは *Project Settings → Project → Description → Legal → Copyright Notice* に書き込まれます。

## 5. 次のステップ

- 完全なワークフローと各タブ/アクション: [UserManual.md](UserManual.md)。
- すべてのテンプレートトークン (`{CopyrightText}`, `{LicenseIdentifier}`, `{FileMetadataBlock}`, …): [SettingsReference.md](SettingsReference.md)。
- 設定項目: [SettingsReference.md](SettingsReference.md)。
- トラブルシューティング: [TROUBLESHOOTING.md](TROUBLESHOOTING.md) および [FAQ.md](FAQ.md)。
