---
lang: ja
title: LightweightDummyActorSystem Troubleshooting
audience: [end_user]
owner_ref: plugin:LightweightDummyActorSystem
applies_to:
  component: LightweightDummyActorSystem
symptom: RegisterSubject fails or QueryReadiness returns a non-Ready status with issues.
recovery:
  steps:
    - Confirm the plugin is enabled under Edit > Plugins and restart the editor
    - Re-read the matching troubleshooting entry and apply the documented fix
    - Re-run the quick start smoke check
version:
  since: "1.0"
---
# トラブルシューティング

形式: 症状 → 原因 → 解決策

## 0. 有効化したのに何も起こらない

**症状:** `LightweightDummyActorSystem` を有効化して再起動した後、ダミーアクターが表示されず、Tiny Tools の製品ワークフローが自動的に実行されません。  
**原因:** LDAS は API/サービスパッケージです。サブジェクトは `ULDASWorldSubsystem` を介して登録されます。プロファイルと登録呼び出しがない限り、何も自動生成されません。  
**解決策:** `ULDASRepresentationProfile` データアセットを作成し、[QUICKSTART.md](QUICKSTART.md) の登録と `QueryReadiness` のワークド・サンプルを実行します。

## 1. `RegisterSubject` が false を返す

**症状:** 新しいサブジェクト ID の登録に失敗します。  
**原因:** 無効または重複したサブジェクト ID、またはサブシステムレジストリによって拒否された記述子/プロファイル。  
**解決策:** `FLDASSubjectId` のフィールドが完全で一意であることを確認します。プロファイルアセットが読み込まれていることを確認し、置き換える場合は `UnregisterSubject` の後に再試行します。

## 2. 準備状況が Ready ではない

**症状:** `QueryReadiness` が `Warning` または問題のあるブロッキング状態を返します。  
**原因:** 必要な準備状況プロバイダーの失敗、またはポリシー入力（距離/クールダウン）が満たされていない。  
**解決策:** `FLDASReadinessReport` の警告/問題を調べます。`ULDASRepresentationProfile` の距離、クールダウン、または `RequiredReadinessProviders` を調整します。昇格させる前にプロバイダーの失敗を解決します。

## 3. 昇格がクローズド・フェイルする

**症状:** `bFailClosedOnPromotionFailure` が true の場合、`RequestPromotion` は表現を進めません。  
**原因:** プロファイルは昇格失敗時にクローズド・フェイル動作を要求します。  
**解決策:** まず根本的な準備状況/ポリシーの失敗を修正します。意図的なソフト・フェイルが許容される場合にのみ、`bFailClosedOnPromotionFailure` をクリアします。

## 4. ランタイム昇格が拒否される

**症状:** 昇格リクエストがノーオペレーションになる一方、降格は正常に機能します。  
**原因:** プロファイルで `bAllowRuntimePromotion` が false です。  
**解決策:** ランタイム昇格を希望する場合、`ULDASRepresentationProfile` で `bAllowRuntimePromotion` を有効にします。

## 5. エディタのインスペクターにサブジェクトが表示されない

**症状:** PIE またはエディタワールドの作業後、インスペクター UI が空です。  
**原因:** そのワールドサブシステムにサブジェクトが登録されていない、または間違ったワールドコンテキストがインスペクションされています。  
**解決策:** インスペクターが観察しているのと同じ `UWorld` に対して登録されていることを確認します。マップの再読み込み後に再登録します。

## 6. 検証コマンドレットが契約エラーを報告する

**症状:** `ULDASValidateContractsCommandlet` が発見事項を持って終了します。  
**原因:** プロジェクトコンテンツ内のプロファイル/記述子/契約の不整合。  
**解決策:** コマンドレットの出力を読み、指定されたアセットを修正し、検証を再実行します。

## 7. WarCollection / Lightning / UCM ブリッジを期待している

**症状:** オプションのアダプター API が見つからない。  
**原因:** これらのブリッジはターゲット固有であり、MVP 1+2+3 の一部ではありません。  
**解決策:** 同梱のコア API のみを使用します。アダプターは将来のオプション統合として扱います。

## 関連ドキュメント

- [QUICKSTART.md](QUICKSTART.md)
- [UserManual.md](UserManual.md)
- [SettingsReference.md](SettingsReference.md)
- [FAQ.md](FAQ.md)
