<!-- doc-provenance: SAD architecture.md sections 1,2,7,8; facts product-facts.yml; reconciled 2026-07-16 -->
# FAQ（よくある質問）

## IIS はプロジェクトを変更しますか？

いいえ。IIS は検索専用（retrieval-only）です。生成されたインデックス/レポートファイルを書き込みますが、エージェントアクションとしてソース、Blueprint、アセット、または設定の変更を適用することはありません。

## IIS には MCP サーバーが含まれていますか？

いいえ、現在のリリースには含まれていません。MCP トランスポートは Unified MCP Server によって提供されます。IIS エージェントの操作は、IIS が所有する MCP サーバーやブリッジプラグインではなく、プロジェクトの Capability Mesh ルートを介して公開されます。

## データはどこに保存されますか？

デフォルト：

```text
Saved/InternalIndexService
```

プロジェクト設定でルートフォルダを上書きできます。

## IIS はプロジェクトデータをクラウドに送信しますか？

LLM Store 内のエンベディングエグゼキュータルートがクラウドプロバイダを使用している場合にのみ送信されます。検索、カタログ、インポート、およびレポートファイルはローカルに保存されます。

## なぜベクトル検索結果がないのですか？

ベクトル検索にはエンベディングが必要です。LLM Store を介してエンベディングルートを構成した後、エンベディングジョブを構築して実行してください。

## hnswlib は何に使用されますか？

hnswlib は、オプションの `hnsw` 近似最近傍ベクトルバックエンドを推進します。`Source/ThirdParty/hnswlib` の下にソースコードとして同梱されています。

## なぜ MCP ツールリストに IIS ツールがないのですか？

以下のプラグインが有効になっているか確認してください：

- Internal Index Service
- Unified MCP Server
- Unreal Capability Mesh

プロジェクトの Capability Mesh プロファイルに IIS エージェントルート（`iis.agent.*.v1`）がリストされていることを確認し、IIS エージェントコントラクトを書き込み/更新してから、`mesh_reload_setup` を呼び出すか MCP クライアントを更新してください。

## C++ から IIS を呼び出せますか？

はい。`FInternalIndexServiceModule::Get().GetService()` および `IInternalIndexService` インターフェースを使用してください。

## Blueprint から IIS を呼び出せますか？

IIS は主にエディタ UI と C++ サービスを公開します。エージェント向けおよび統合パスは C++/JSON に基づいています。
