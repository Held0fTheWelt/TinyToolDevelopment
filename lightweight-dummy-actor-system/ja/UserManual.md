# ユーザーマニュアル

LightweightDummyActorSystem (LDAS) は、ダミーアクターワークフローのための自律的なランタイム表現サービスです。MVP 1+2+3 では、Runtime、Editor、DeveloperTool モジュールが提供されます。

## 実装された機能

| 機能 | 主要な型 |
| --- | --- |
| 被管理対象の登録 | `ULDASWorldSubsystem::RegisterSubject`、`RegisterSubjectFromProfile`、`UnregisterSubject` |
| 準備状況の照会 | `QueryReadiness` → `FLDASReadinessReport` |
| プロモーション / デモーション | `ELDASTransitionReason` を伴う `RequestPromotion`、`RequestDemotion` |
| ダミーの表現 | `ALDASLightweightDummyActor`、`ULDASDummyActorComponent` |
| プロファイルアセット | `ULDASRepresentationProfile` |
| 診断 | `ULDASDiagnosticsSubsystem` |
| エディタインスペクタ | `SLDASRepresentationInspector` |
| 検証 | `FLDASEditorValidationService`、`ULDASValidateContractsCommandlet` |

<!-- image slot: ldas-inspector -->

## ランタイムフロー

1. ワールドから `ULDASWorldSubsystem` を取得します。
2. 記述子または `ULDASRepresentationProfile` を用いて被管理対象を登録します。
3. 目的の表現種別に対する準備状況を照会します。
4. ポリシーと準備状況が許可する場合、プロモーションまたはデモーションを要求します。
5. 障害の調査時には、診断 / エディタインスペクタを参照します。

プロモーションとデモーションはポリシーによって制御されます。組み込みプロバイダー (`ULDASBuiltInReadinessProvider`、`ULDASBuiltInPromotionPolicy`、`ULDASBuiltInHeavyActorAdapter`) は既定の動作を提供します。プロジェクトは、対応するビルドにおいて追加のプロバイダーを登録できます。

## エディタのインターフェース

- 登録された被管理対象用の表現インスペクタ。
- 契約チェック用のエディタ検証サービス。
- オフライン検証実行用の開発者向けコマンドレット。

## 自律性とオプションの統合

コアの Runtime / Editor / DeveloperTool モジュールは、ピアの Tiny Tool プラグインなしで動作します。以下の機能は**ターゲット専用**であり、存在しない場合は適切に機能低下する必要があります：

- WarCollection 読み取り専用パイロットアダプタ
- マルチプレイヤーパイロット実証
- LightningCore エンティティブリッジ
- UCM / PIO / BPJ 自動化ブリッジ

これらのアダプターを、出荷されるコアのセットアップ要件として扱わないでください。

## 関連ドキュメント

- [QUICKSTART.md](QUICKSTART.md)
- [SettingsReference.md](SettingsReference.md)
- [FAQ.md](FAQ.md)
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md)
- [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md)
