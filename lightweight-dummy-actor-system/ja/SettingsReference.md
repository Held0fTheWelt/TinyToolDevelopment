---
lang: ja
title: LightweightDummyActorSystem Settings Reference
audience: [end_user]
owner_ref: plugin:LightweightDummyActorSystem
applies_to:
  component: LightweightDummyActorSystem
contract_ref: plugin:LightweightDummyActorSystem/profile-properties
version:
  since: "1.0"
---
# 設定リファレンス

`LightweightDummyActorSystem` は `UDeveloperSettings` / プロジェクトのプリファレンスオブジェクトを**同梱していません**。設定可能な値は、以下のリストにあるデータアセット、コンポーネント、構造体に格納されています（パブリックヘッダーに基づきます）。

## ULDASRepresentationProfile (`UDataAsset`)

| 名前 | 型 | デフォルト | 効果 |
| --- | --- | --- | --- |
| `Descriptor` | `FLDASRepresentationDescriptor` | 空 | 対象レコードに適用される基本表現記述子。 |
| `PromoteDistance` | `float` | `0.0` | プロモーションポリシーで使用される距離入力。 |
| `DemoteDistance` | `float` | `0.0` | デモーションポリシーで使用される距離入力。 |
| `PromotionCooldownSeconds` | `float` | `1.0` | プロモーション間のクールダウン時間。 |
| `bAllowRuntimePromotion` | `bool` | `true` | 偽の場合、プロファイルによってランタイムのプロモーションリクエストが許可されません。 |
| `bFailClosedOnPromotionFailure` | `bool` | `false` | 真の場合、プロモーションの失敗はクローズドな失敗として扱われます。 |
| `RequiredReadinessProviders` | `TArray<FName>` | 空 | 満たす必要がある名前付きの準備状態プロバイダー。 |

## ULDASDummyActorComponent

| 名前 | 型 | デフォルト | 効果 |
| --- | --- | --- | --- |
| プロファイル / 対象バインディングフィールド | editanywhere コンポーネントプロパティ | 呼び出し側設定 | コンポーネントを LDAS 対象表現にバインドします。 |
| レプリケートされたスナップショット | レプリケートプロパティ | ランタイム | `OnRep` 通知とともにスナップショット状態を伝達します。 |

## ALDASLightweightDummyActor

| 名前 | 型 | デフォルト | 効果 |
| --- | --- | --- | --- |
| 可視コンポーネント | コンポーネント参照 | 構築時 | シーン/デバッグ表現コンポーネント。 |
| LDAS バインディングフィールド | editanywhere | 呼び出し側設定 | アクターを LDAS 対象データにリンクします。 |

## FLDASTransitionRecord / スナップショット構造体

トランジションおよびスナップショット構造体は、対象 ID、表現種別、タイムスタンプ、および準備状態の問題リストに対して editanywhere フィールドを公開します。これらをグローバル設定ではなくデータ契約として扱ってください。デフォルト値は `Public/Structs/` 配下のヘッダー内の構造体デフォルト値です。

## 存在しないもの

| 表面 | 状態 |
| --- | --- |
| `ULDASDeveloperSettings` | まだ利用不可 |
| `Config/DefaultLightweightDummyActorSystem.ini` 設定オブジェクト | バイヤー設定パネルとして同梱されていません |
| WarCollection / Lightning / UCM ブリッジ設定 | ターゲット専用オプションアダプター |

## 関連ドキュメント

- [UserManual.md](UserManual.md)
- [QUICKSTART.md](QUICKSTART.md)
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md)
