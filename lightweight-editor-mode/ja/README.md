<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/LightweightEditorMode/architecture.md -->
# Lightweight Editor Mode ドキュメント

Lightweight Editor Mode は、アーティスト、レベルデザイナー、テクニカルアーティスト、プログラマーが大規模なプロジェクトで作業する際に、エディタのレンダリング負荷を一時的に軽減できるようにする Unreal Engine エディタプラグインです。可逆的なエディタワークフローツールとして設計されており、ビューポートが重くなったときに有効化して編集を続け、作業が終わったら無効化して元のエディタ状態に戻すことができます。

このドキュメントセットは、マーケットプレイスに対応した高品質なエディタプラグインに期待される詳細さを備えています。購入者の期待、日常的な使用方法、設定、技術的挙動、検証、パッケージング、保守について網羅しています。

## ここから始める

- [UserManual.md](UserManual.md): 通常のエディタワークフローについて説明します。
- [BUYER_GUIDE.md](BUYER_GUIDE.md): プラグインの機能と対象ユーザーについて説明します。
- [SettingsReference.md](SettingsReference.md): 公開されている全設定を一覧表示します。
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md): 一般的なエディタの症例の診断に役立ちます。
- [TechnicalOverview.md](TechnicalOverview.md): ランタイム設計について解説します。
- [CodeDocumentation.md](CodeDocumentation.md): ソースファイルと動作の対応関係を示します。
- [PerformanceTuningReference.md](PerformanceTuningReference.md): プロファイルのチューニング方法を解説します。
- [ValidationAndQA.md](ValidationAndQA.md): テストおよびリリース検証手順を提供します。
- [CompatibilityAndPackaging.md](CompatibilityAndPackaging.md): エンジンおよびパッケージングに関する注意事項を網羅します。
- [FAQ.md](FAQ.md): よくある質問に回答します。
- [ReleaseChecklist.md](ReleaseChecklist.md): リリース前の最終チェックリストです。

## プラグインが変更する内容

有効にすると、Lightweight Editor Mode は以下のエディタ側最適化を適用できます。

- エディタビューポートのスクリーンパーセンテージ（Screen Percentage）の引き下げ。
- 全体的な拡張性品質（Scalability Quality）の引き下げ。
- Lumen ディフューズ間接照明および Lumen リフレクションの無効化。
- バーチャルシャドウマップ（Virtual Shadow Maps）の無効化。
- ボリュメトリックフォグおよび通常のフォグの無効化。
- エディタビューポートの Unlit（ライティングなし）表示モードへの強制切り替え。
- エディタビューポートでのリアルタイム描画の無効化。

正確な挙動は、選択されたプロファイルおよび Project Settings 内の編集可能なプロファイル設定によって決まります。

## コア設計の約束

本プラグインは意図的に可逆性を重視して設計されています。

- 拡張性設定を変更する前にバックアップします。
- プラグインの値を設定する前に、変更されるコンソール変数をバックアップします。
- アクティブセッション中のビューポートごとの表示モードとリアルタイム状態を保存します。
- 再起動後の復元用に永続的なフォールバック表示モードを保持します。
- モードが無効化されたとき、またはモジュールが終了したときにエディタ状態を復元します。

これにより、メインのプロジェクト設定を変更することなく、一時的なパフォーマンス改善を安全に行うことができます。

## クイックワークフロー

1. Edit > Plugins でプラグインを有効にします。
2. Tools > Performance > Lightweight Editor Mode を開きます。
3. プロファイル（Mild、Balanced、Aggressive、Extreme）を選択します。
4. Enable Lightweight Mode をクリックします。
5. Viewport 負荷が軽減された状態でエディタ作業を行います。
6. 最終的なライティング、マテリアル、キャプチャ作業の前に Disable Lightweight Mode をクリックします。

## ビジュアルガイド

Documentation/Screenshots フォルダには SVG 形式のワークフロー図が含まれています。

- [01-workflow-overview.svg](Screenshots/01-workflow-overview.svg)
- [02-profile-and-settings.svg](Screenshots/02-profile-and-settings.svg)
- [03-restore-flow.svg](Screenshots/03-restore-flow.svg)

これらの図はドキュメント用のアセットであり、ランタイム UI アセットではありません。

## エンジン対象範囲

本実装は Unreal Engine 5.4 スタイルのエディタ API およびレンダリングコンソール変数を対象としています。重要な実装上の注意点として、エディタビューポートはゲームや PIE レンダリングと同じスクリーンパーセンテージパスに確実には従わないため、本プラグインはエディタ専用のスクリーンパーセンテージ CVar を使用します。

## 安全上の注意

Lightweight Editor Mode はエディタのパフォーマンス向上ツールであり、出荷用ゲームのランタイム最適化システムではありません。最終的なライティング、シャドウ、フォグ、マテリアル、またはシネマティクス出力の最終検証パスとして本モードのみを使用しないでください。

リリース用のキャプチャやビジュアル承認の前には、必ず本モードを無効にし、意図したプロダクション品質設定でシーンを確認してください。
