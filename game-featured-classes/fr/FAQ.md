# FAQ

## GameFeaturedClasses inclut-il des classes de gameplay ?

Non. La version 1.0.1 est un shell de plugin d'exécution léger avec descripteur, limite de module, métadonnées d'emballage, icône et journal des modifications. Le comportement premium de GameFeature Workbench est spécifié par la cible, mais n'est pas encore implémenté dans ce package.

## Un autre plugin Tiny Tool est-il requis ?

Non. Le shell de module actuel se charge de lui-même. Les futures intégrations avec LightweightDummyActorSystem, Unreal Capability Mesh ou Project Intelligence Orchestrator sont une architecture cible optionnelle, et non une exigence d'exécution pour ce package.

## Quelles versions du moteur sont prises en charge ?

La matrice de version emballée cible Unreal Engine 5.4 à 5.8 (descripteur `EngineVersion` 5.4.0 sur cette branche).

## Inclut-il des logiciels tiers ou des services externes ?

Non. Le package n'inclut pas de logiciels tiers et ne nécessite pas de compte, de fournisseur d'IA ou d'exécution externe. Consultez [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## Où puis-je obtenir de l'aide ?

Utilisez `mailto:support@tiny-tool-development.com` (descripteur `SupportURL`) ou le lien de support sur la page produit Fab.

## Pourquoi n'y a-t-il pas de panneau de paramètres ?

La version 1.0.1 n'expose aucun DeveloperSettings ni descripteur de classe mise en avant. Consultez [SettingsReference.md](SettingsReference.md).

## Puis-je placer les classes mises en avant de mon projet dans ce dossier de plugin ?

Non pour la distribution en tant que contenu GFC dans la version 1.0.1. Conservez les classes de gameplay de votre projet dans vos propres modules jusqu'à ce qu'un package ultérieur distribue explicitement les assets de classe mise en avant.

## Comment vérifier que le shell a été chargé ?

Activez le plugin, redémarrez l'éditeur et confirmez que le module d'exécution `GameFeaturedClasses` est présent. Consultez l'exemple détaillé dans [QUICKSTART.md](QUICKSTART.md).

## Où se trouve la documentation en ligne ?

https://docs.tiny-tool-development.com/game-featured-classes/
