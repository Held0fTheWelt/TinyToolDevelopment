<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/LogLevelEditor/architecture.md -->
# FAQ (Foire aux questions)

## LogLevelEditor modifie-t-il mes déclarations de catégories C++ ?

Non. Il ne réécrit pas le code source. Il découvre les catégories et utilise le système de commandes de console d'Unreal pour modifier la verbosité active.

## Les modifications sont-elles permanentes ?

Seules les surcharges volontaires enregistrées dans le `ULogLevelDataAsset` configuré sont persistantes. Les modifications de la console en cours d'exécution sans mise à jour du DataAsset sont temporaires.

## Pourquoi une catégorie a-t-elle disparu de la liste ?

Elle peut être masquée par la liste permanente, la liste temporaire, filtrée par le texte de recherche ou exclue du périmètre de l'analyse actuelle.

## Pourquoi manque-t-il un niveau par défaut ?

Le scanner reconnaît les macros Unreal courantes. Si un projet utilise des macros enveloppes personnalisées ou un formatage inhabituel, la catégorie peut être trouvée sans que le niveau par défaut puisse être déduit.

## Puis-je inclure les catégories de journalisation du moteur ?

Oui. Activez l'analyse des plugins et/ou des sources du moteur dans les paramètres.

## Cela fonctionne-t-il dans les jeux packagés ?

Non. LogLevelEditor est un plugin d'éditeur destiné aux flux de travail de développement.

## Puis-je partager une configuration de journalisation avec mon équipe ?

Oui. Enregistrez les surcharges dans le DataAsset et soumettez-le au contrôle de version de votre projet.

## Pourquoi le plugin retente-t-il d'appliquer les niveaux sauvegardés au démarrage ?

Les modules de l'éditeur Unreal peuvent démarrer avant que le moteur soit prêt à traiter les commandes de console. La logique de réessai évite de perdre les surcharges au lancement.

## Que se passe-t-il si une commande de console échoue ?

L'interface et le DataAsset ne sont pas mis à jour comme si la commande avait réussi. L'échec est consigné dans le journal.

## Puis-je rendre une catégorie totalement silencieuse ?

Utilisez `NoLogging`, mais gardez à l'esprit que les règles de verbosité à la compilation et à l'exécution d'Unreal s'appliquent toujours.

## Prend-il en charge des noms de verbosité personnalisés ?

Non. Il prend en charge les noms de verbosité standard d'Unreal.

## Le DataAsset est-il obligatoire ?

L'interface peut inspecter et appliquer des changements à l'exécution, mais la réapplication au démarrage nécessite un DataAsset configuré.

## Le plugin peut-il détecter les catégories issues de plugins ?

Oui. Les plugins du projet font partie du parcours d'analyse normal. Les plugins du moteur sont optionnels.

## Est-il adapté au contrôle de code source ?

Oui, lorsqu'il est utilisé à bon escient. L'élément partagé principal est le DataAsset contenant les surcharges persistantes.
