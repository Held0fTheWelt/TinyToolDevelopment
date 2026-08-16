<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/LogLevelEditor/architecture.md -->
# Manuel de l'utilisateur

Ce manuel explique le flux de travail quotidien dans l'éditeur pour LogLevelEditor.

## Installation

1. Ajoutez le plugin au dossier `Plugins` de votre projet ou installez-le via Fab.
2. Activez **LogLevelEditor** dans **Edit > Plugins**.
3. Redémarrez l'éditeur si Unreal vous y invite.
4. Confirmez que le contenu du plugin est visible si vous souhaitez inspecter le DataAsset par défaut.

## Ouverture de l'outil

Ouvrez LogLevelEditor depuis **Tools → Log Tools → Log Level Editor** ou via le raccourci optionnel de la barre d'outils. Le plugin s'ouvre sous la forme d'un onglet ancrable afin de rester intégré à l'espace de travail.

## Premier scan

Au lancement, l'outil analyse les emplacements configurés à la recherche de catégories de journaux.

Par défaut, il se concentre sur :

- Les fichiers sources du projet.
- Les fichiers sources des plugins du projet.

Des paramètres optionnels permettent d'inclure :

- Les fichiers sources des plugins du moteur.
- Les fichiers sources du moteur.

Les analyses du moteur peuvent être coûteuses. Ne les activez que si vous avez réellement besoin des catégories du moteur dans votre tableau de bord.

## Lecture de la liste

Chaque ligne représente une catégorie de journal.

Champs importants :

- Nom de catégorie : le nom de la catégorie de journal Unreal, par exemple `LogTemp`.
- Niveau par défaut détecté : la verbosité par défaut déduite de la macro de déclaration/définition lorsque c'est possible.
- Niveau actuel : le niveau actuellement rapporté par Unreal pour la catégorie enregistrée. Si Unreal ne peut pas encore le rapporter, la ligne affiche `Unavailable`. Après le scan initial, cette valeur est rafraîchie régulièrement.
- Chemin source : l'emplacement où le scanner a trouvé la catégorie, si disponible.

## Modification de la verbosité

1. Trouvez la catégorie en utilisant la recherche ou le filtrage.
2. Choisissez un niveau de verbosité via les boutons de la ligne.
3. Le plugin exécute la commande de console Unreal.
4. La ligne et le DataAsset sont mis à jour uniquement après le succès de la commande.

Choix courants :

- `Warning` : réduire le bruit tout en conservant les problèmes importants.
- `Log` : niveau standard habituel pour les sorties normales.
- `Verbose` : utile pour le diagnostic.
- `VeryVerbose` : sortie très détaillée et généralement temporaire.
- `NoLogging` : rendre une catégorie aussi silencieuse que le permet Unreal.

## Restauration des valeurs par défaut

Lorsque la verbosité sélectionnée correspond au niveau par défaut détecté, le plugin supprime la surcharge persistante pour cette catégorie. Cela permet de garder le DataAsset concentré sur les modifications réelles.

Si aucun niveau par défaut n'a été détecté, considérez la ligne comme informative et réinitialisez-la manuellement vers la valeur attendue par votre projet.

## Surcharges persistantes

Les valeurs persistantes sont stockées dans le `ULogLevelDataAsset` configuré.

Flux de travail recommandé :

1. Conservez les surcharges volontaires à l'échelle du projet dans le DataAsset par défaut.
2. Ne soumettez cet asset au contrôle de version que si ces surcharges constituent la politique de l'équipe.
3. Évitez d'enregistrer du bruit de débogage temporaire dans le contrôle de code source partagé.
4. Utilisez les paramètres de masquage temporaire pour votre concentration personnelle sur l'interface.

## Application au démarrage

Les surcharges enregistrées sont réappliquées lors du démarrage de l'éditeur. Le module attend que le moteur soit prêt à accepter des commandes de console et réessaie plusieurs fois lors d'un démarrage précoce.

## Masquage des catégories

Liste de masquage permanent :

- Stockée dans la configuration.
- Utile pour les catégories qui doivent rarement apparaître dans l'outil.

Liste de masquage temporaire :

- Stockée de façon éphémère.
- Utile pour se concentrer localement pendant une session.
- Non écrite dans la configuration.

## Settings

Ouvrez les paramètres du plugin sous les paramètres de l'éditeur / du projet.

Paramètres clés :

- `LogLevelDataAsset` : DataAsset utilisé pour stocker les surcharges persistantes.
- `bAutoSaveLogLevelDataAsset` : enregistre automatiquement l'asset après des modifications intentionnelles.
- `bShowToolbarButton` : affiche ou masque le raccourci dans la barre d'outils.
- `bAlsoListEnginePluginChannels` : inclut les catégories des plugins du moteur dans les scans.
- `bAlsoListEngineSourceChannels` : inclut les catégories des sources du moteur dans les scans.
- `LogChannelsToHide` : catégories masquées en permanence.
- `LogChannelsToHideTemporary` : catégories masquées uniquement pour la session.

## Flux de travail d'équipe recommandé

Pour une utilisation en équipe :

1. Conservez le DataAsset par défaut dans le contrôle de code source.
2. N'enregistrez que les surcharges stables répondant aux règles du projet.
3. Ne soumettez pas les masquages temporaires locaux.
4. Documentez les profils de débogage et de support dans le wiki de votre projet.

## Suppression du plugin

Avant de supprimer le plugin :

1. Réinitialisez les modifications temporaires de verbosité.
2. Supprimez ou ignorez le DataAsset du plugin s'il n'est plus utilisé.
3. Désactivez le plugin et redémarrez l'éditeur.

Le plugin ne modifie pas les déclarations de catégories de journaux dans le code source, sa suppression ne nécessite donc aucun nettoyage en C++.
