<!-- doc-provenance: AKDB:plugins/SmartContentDiet/architecture.md; docs/architecture/plugins/SmartContentDiet/product-facts.yml; reconciled 2026-07-16 -->
# サードパーティ製ソフトウェア

Smart Content Diet には**サードパーティのソースコード、ランタイムバイナリ、AI モデル、Node.js、Python、またはスタンドアロン実行可能ファイルは一切含まれていません**。本製品は、Unreal Engine モジュールおよび標準 Unreal API（アセットレジストリ、アセット分析、エディタ UI、Commandlet）のみを使用する C++ Unreal Engine エディタプラグインです。

コアであるスキャン → レビュー → 安全な修正のループは、**AI サービスや外部ツールなし**で完全エディタ内部で動作します。オプションのプラグイン間エコシステムルート（**Unreal Capability Mesh (UCM)** 経由）は JSON 宣言されており、本パッケージにサードパーティ製ソフトウェアを追加することはありません。

プラグインのインストールや使用に、外部ソフトウェア、アカウント、またはランタイムは必要ありません。

**Fab サードパーティ製ソフトウェア宣言:** 同梱のサードパーティ製ソフトウェアなし。
