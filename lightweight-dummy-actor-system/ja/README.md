# LightweightDummyActorSystem ドキュメント

LightweightDummyActorSystem (LDAS) は、ダミーアクターワークフローのための自律的なランタイム表現サービスです。MVP 1+2+3 では、Runtime、Editor、DeveloperTool モジュールが提供されます。これには、サブジェクト登録、準備状況クエリ、昇格/降格ポリシーのゲート、ダミーアクターの表現、診断、エディタインスペクタ、および検証コマレットが含まれます。

対象読者: コアパッケージに対してピアの Tiny Tool プラグインを必要とせず、ポリシーによる昇格/降格制御付きの軽量なダミー表現を必要とするゲームプレイおよびツールエンジニア。

## 機能 (提供済み)

- `RegisterSubject` / `RegisterSubjectFromProfile` / `UnregisterSubject`
- `QueryReadiness` → `FLDASReadinessReport`
- `RequestPromotion` / `RequestDemotion`
- `ULDASRepresentationProfile`、`ALDASLightweightDummyActor`、`ULDASDummyActorComponent`
- エディタインスペクタおよび `ULDASValidateContractsCommandlet`

## 始め方

1. プラグインを有効にする — [QUICKSTART.md](QUICKSTART.md) の作業例（登録と準備状況クエリ）を参照してください。
2. 実際の距離/クールダウン値を持つ `ULDASRepresentationProfile` データアセットを設定します。
3. [UserManual.md](UserManual.md) および [SettingsReference.md](SettingsReference.md) をお読みください。

## 関連ファイル

- [../README.md](../README.md) — プロダクト概要。
- [../CHANGELOG.md](../CHANGELOG.md) — リリース履歴。
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md) · [FAQ.md](FAQ.md) · [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md)
