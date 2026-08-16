<!-- doc-provenance: SAD architecture.md sections 6,8,10,11; facts product-facts.yml; reconciled 2026-07-16 -->
# Dépannage

## Échec de compilation sur UE 5.6 avec des erreurs d'en-tête du moteur

S'assurer que les modules IIS compilent avec C++20. Les en-têtes du moteur UE 5.6 utilisent la syntaxe C++20. Les fichiers `.Build.cs` d'IIS doivent utiliser :

```csharp
CppStandard = CppStandardVersion.Cpp20;
```

## La recherche ne renvoie aucun résultat

Vérifier :

- que les chunks préparés ont été importés
- que le catalogue a été reconstruit
- que le texte de la requête n'est pas vide
- que l'état du cycle de vie est actif
- que la racine de l'index pointe vers le dossier de projet attendu

## La recherche vectorielle ne renvoie aucun résultat

Vérifier :

- que les jobs d'embedding ont été construits
- que les jobs d'embedding ont été exécutés avec succès
- que la route/exécuteur LLM Store est enregistré
- que le paramètre du back-end vectoriel correspond aux artefacts persistés

## L'importation échoue

Vérifier que le fichier JSONL de chunks préparés existe et est lisible. Consulter les rapports d'importation sous la racine Saved d'IIS pour vérifier les avertissements de validation et les enregistrements rejetés.

## L'index HNSW ne peut pas se charger ou produit des avertissements du back-end

Si le back-end HNSW ne peut pas se charger ou si des avertissements apparaissent après avoir modifié les paramètres de stockage vectoriel, passez temporairement à `jsonl_bruteforce` pour séparer les problèmes de données vectorielles des problèmes d'indexation spécifiques au back-end. Conserver **Rebuild On Vector Format Mismatch** activé afin que les partitions HNSW persistées incompatibles soient reconstruites à partir des vecteurs sources au lieu d'être chargées avec la mauvaise disposition d'octets.

Confirmer que `Source/ThirdParty/hnswlib` est présent dans le paquet et reconstruire les artefacts vectoriels après avoir modifié **Vector Storage Format**.

## Le réglage runtime ou le verbe d'action de l'index renvoie "Disabled"

Vérifier **Enable Runtime Control Mutations** dans les paramètres du projet. Lorsqu'il est désactivé, les verbes de lecture tels que `iis.control.state` fonctionnent toujours, mais les verbes tune, act, persist et reset renvoient une réponse désactivée par conception.

Réactiver le paramètre pour les verbes de contrôle modificateurs, ou continuer avec les commandes d'état et de diagnostic en lecture seule.

## Les outils d'agent sont absents du client MCP

Vérifier :

- que Unified MCP Server est activé et en cours d'exécution
- que Unreal Capability Mesh est activé
- que la configuration du projet inclut les manifestes de route d'agent IIS (`iis.agent.*.v1`)
- appeler `mesh_list_routes` ou `mesh_reload_setup` et rafraîchir le client MCP
- que IIS peut écrire les contrats d'outils d'agent
- que le client MCP est connecté à l'endpoint UMCP et non à un serveur MCP hérité par plugin

Rafraîchir la configuration Capability Mesh et se reconnecter ou rafraîchir le client MCP après des changements de route.

## L'outil d'agent renvoie des garde-fous de lecture seule

C'est le comportement attendu. Les réponses d'IIS indiquent délibérément que la mutation du projet n'est pas autorisée.

## Le contrôle automatique de performance indique une déviation

Examiner le dernier résultat de performance depuis `iis.perf.last` ou réexécuter `iis.perf.run`. Les déviations signifient généralement que la charge de travail vectorielle actuelle, le back-end ou le réglage dépassent les budgets configurés.

Réduire d'abord l'ampleur de la requête ou la charge vectorielle. Mettre à jour les budgets uniquement après validation représentative sur la machine/profil de projet cible.

## Où trouver les rapports

Par défaut :

```text
Saved/InternalIndexService/reports
Saved/InternalIndexService/imports
Saved/InternalIndexService/agent_contracts
```
