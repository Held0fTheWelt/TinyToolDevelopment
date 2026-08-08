---
lang: ja
title: LightweightDummyActorSystem Quick Start
audience: [end_user]
owner_ref: plugin:LightweightDummyActorSystem
applies_to:
  component: LightweightDummyActorSystem
preconditions:
  - Unreal Engine project open with the plugin package available
  - Edit > Plugins can enable LightweightDummyActorSystem
expected_result:
  text: Subject registers through ULDASWorldSubsystem and QueryReadiness returns a readiness report.
version:
  since: "1.0"
---
# クイックスタート

このガイドでは、**LightweightDummyActorSystem (LDAS)** のインストール方法と、同梱のランタイム API を使用して最初の動作するサブジェクト登録を行う手順を解説します。MVP 1+2+3 が実装されています：ランタイムコア、トランジションコア、エディタインスペクタ、および検証コマンドレット。

## このガイド完了後に得られるもの

プラグが有効化され、`ULDASWorldSubsystem::RegisterSubject` / `RegisterSubjectFromProfile` を介してサブジェクトが登録され、確認可能な準備状況クエリが利用可能になります。

## 要件

- Unreal Engine 5.4–5.8（パッケージ化されたマトリクス；Win64/Linux/Mac でモジュールの許可リストが許可する場合）。
- コアパッケージには他の Tiny Tool プラグインは必要ありません。
- サードパーティ製ソフトウェア、アカウント、または外部ランタイムは不要です。[THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md) を参照してください。

## 1. インストールと有効化

1. Fab から **LightweightDummyActorSystem** を取得し、プロジェクトに追加します。
2. **編集 → プラグイン** を開き、**LightweightDummyActorSystem** を有効化し、求められたら再起動します。
3. ランタイム、エディタ、DeveloperTool モジュールが読み込まれることを確認します（`LightweightDummyActorSystem`、`LightweightDummyActorSystemEditor`、`LightweightDummyActorSystemDeveloper`）。

## 2. 表現プロファイルの作成

1. Content Browser で、クラス `ULDASRepresentationProfile` のデータアセットを作成します。
2. グラウンドプロファイルのフィールドを設定します。例：

| フィールド | 例の値 | 意味 |
| --- | --- | --- |
| `PromoteDistance` | `2500.0` | プロモーションポリシーの入力で使用される距離閾値。 |
| `DemoteDistance` | `3000.0` | デモーションポリシーの入力で使用される距離閾値。 |
| `PromotionCooldownSeconds` | `1.0` | プロモーション間の最小秒数。 |
| `bAllowRuntimePromotion` | `true` | ランタイムでのプロモーションリクエストを許可する。 |
| `bFailClosedOnPromotionFailure` | `false` | true の場合、プロモーション失敗はクローズドエラーとして扱われる。 |
| `RequiredReadinessProviders` | （空または指定されたプロバイダ名） | プロモート前に必要な追加の準備状況プロバイダ。 |

## 3. 実例：登録とクエリ

ゲームプレイコードまたはワールドサブシステムにアクセス可能なエディタユーティリティから：

```cpp
UWorld* World = /* 現在のワールド */;
ULDASWorldSubsystem* LDAS = World->GetSubsystem<ULDASWorldSubsystem>();

FLDASSubjectId SubjectId;
// プロジェクトのバインディングに必要な SubjectId フィールドを埋める。

FLDASRepresentationDescriptor Descriptor;
// デスクリプタフィールドを埋めるか、データアセットを使用して RegisterSubjectFromProfile を使用する。

const bool bRegistered = LDAS->RegisterSubjectFromProfile(SubjectId, ProfileAsset);
const FLDASReadinessReport Report = LDAS->QueryReadiness(
	SubjectId, ELDASRepresentationKind::Heavy /* または意図に応じて Dummy */);
```

## 期待される結果

- サブジェクト ID が受け入れられた場合、`bRegistered` は true になります。
- `QueryReadiness` は、ステータスが `Ready`、`Warning`、または問題エントリを含むブロック状態の `FLDASReadinessReport` を返します。静かな成功は返されません。

## 4. 契約の検証（オプション）

エディタ/コマンドレットホストからパッケージ化された検証コマンドレット `ULDASValidateContractsCommandlet` を実行し、プロジェクトの契約整合性を確認します。

## 次のステップ

- [UserManual.md](UserManual.md) — サブシステム、アクター、コンポーネント、トランジション。
- [SettingsReference.md](SettingsReference.md) — プロファイルとコンポーネントのプロパティ。
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md) — 準備状況とプロモーションの失敗。
