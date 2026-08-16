<!-- doc-provenance: SAD architecture.md sections 2,7,8; facts product-facts.yml; reconciled 2026-07-16 -->
# Logiciels tiers

Internal Index Service fournit le code source tiers suivant. Marquez la soumission du plugin comme contenant des logiciels tiers et incluez cette entrée dans le formulaire de déclaration de logiciels tiers d'Epic.

| Logiciel | Version | Licence | Source | Chemin dans le plugin | Utilisation |
| --- | --- | --- | --- | --- | --- |
| hnswlib | 0.9.0 | Apache License 2.0 | https://github.com/nmslib/hnswlib | `Source/ThirdParty/hnswlib` | Back-end d'indexation vectorielle locale C++ en en-tête uniquement (header-only) pour la recherche des plus proches voisins approximatifs. |

Le plugin paqueté inclut les fichiers originaux `LICENSE` et `NOTICE.md` sous `Source/ThirdParty/hnswlib`.
