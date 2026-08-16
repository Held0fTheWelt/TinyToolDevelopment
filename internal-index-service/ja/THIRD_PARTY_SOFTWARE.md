<!-- doc-provenance: SAD architecture.md sections 2,7,8; facts product-facts.yml; reconciled 2026-07-16 -->
# サードパーティソフトウェア

Internal Index Service は、以下のサードパーティソースコードを同梱しています。プラグインの提出時にサードパーティソフトウェアが含まれていることをマークし、Epic のサードパーティソフトウェア宣言フォームにこのエントリを含めてください。

| ソフトウェア | バージョン | ライセンス | ソース | プラグイン内のパス | 用途 |
| --- | --- | --- | --- | --- | --- |
| hnswlib | 0.9.0 | Apache License 2.0 | https://github.com/nmslib/hnswlib | `Source/ThirdParty/hnswlib` | ローカルベクトル検索用のヘッダーのみの C++ 近似最近傍インデックスバックエンド。 |

パッケージ化されたプラグインには、`Source/ThirdParty/hnswlib` の下にオリジナルの `LICENSE` ファイルと `NOTICE.md` が含まれています。
