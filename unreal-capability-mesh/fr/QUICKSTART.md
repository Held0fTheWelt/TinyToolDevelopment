<!-- doc-provenance: AKDB:plugins/UnrealCapabilityMesh/architecture.md; docs/architecture/plugins/UnrealCapabilityMesh/product-facts.yml; reconciled 2026-07-19 -->
# Démarrage rapide

Ce guide vous accompagne d'une nouvelle installation vers un **résultat fonctionnel et visible** : un inventaire de capacités découvertes et une route que vous exécutez vous-même et qui renvoie une réponse JSON. Aucun codage ni rédaction de manifeste n'est requis — le plugin est livré avec un profil par défaut prêt à l'emploi.

## Ce que vous obtiendrez après ce guide

Le panneau de configuration ouvert, le profil intégré **Default Capability Mesh Profile** chargé, les capacités découvertes et une route (`sample.echo.route.v1`) exécutée avec une réponse JSON et un rapport sauvegardé que vous pouvez ouvrir.

## Prérequis

- Unreal Engine 5.4 ou ultérieur.
- Plate-forme : Windows (Win64), Linux ou Mac.
- Un **projet** Unreal dans lequel activer le plugin. UCM est un plugin d'éditeur C++ : dans un projet C++, il se compile au premier démarrage de l'éditeur ; dans un projet Blueprint uniquement, installez-le pour une version de moteur correspondante (via votre bibliothèque Fab) afin que l'éditeur puisse charger ses modules d'éditeur précompilés.
- Aucun logiciel tiers, compte, modèle d'IA ou runtime externe n'est requis. Consultez [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## 1. Installer et activer

1. Obtenez **Unreal Capability Mesh** depuis votre bibliothèque Fab et ajoutez-le à votre projet (il apparaît sous le dossier `Plugins/` du projet) ou installez-le dans le moteur.
2. Ouvrez votre projet. Dans l'éditeur, allez dans **Edit → Plugins**, recherchez `Unreal Capability Mesh` et cochez **Enabled**.
3. Redémarrez l'éditeur lorsque vous y êtes invité. (Pour un projet C++, laissez-le compiler lors de ce premier démarrage.)

UCM peut fonctionner sans dossier de configuration local au projet. Il charge le profil par défaut intégré et les profils locaux des plugins fournisseurs activés. Utilisez `Config/UnrealCapabilityMesh/` uniquement lorsque le projet a intentionnellement besoin de surcharges ou de routes composées propres au projet.

## 2. Obtenir un premier résultat

1. Ouvrez le panneau de configuration : **Tools → Unreal Capability Mesh**.
2. Sur la page **Overview**, vous devriez voir le profil actif **"Default Capability Mesh Profile"**.
3. Cliquez sur **Reload Setup**. UCM charge le profil, valide la configuration JSON, enregistre les définitions et exécute la découverte.
4. Ouvrez la page **Capabilities** — vous voyez maintenant les capacités découvertes (par exemple `mesh.sample.echo`) avec leur disponibilité et leurs effets secondaires.
5. Ouvrez la page **Diagnostics** — elle affiche les messages de validation de la configuration et de découverte issus du rechargement. Un rechargement propre signifie que le plugin fonctionne.

Vous venez de faire fonctionner le produit en utilisant uniquement ce qui est livré dans le package.

## 3. Un exemple concret : Exécuter une route

UCM fournit une route d'exemple sécurisée et en lecture seule, `sample.echo.route.v1`, qui appelle un point d'entrée d'écho. Utilisez-la pour exécuter votre première route de bout en bout.

1. Ouvrez la page **Routes**.
2. Dans le champ de l'identifiant de route, saisissez :

   ```text
   sample.echo.route.v1
   ```

3. Cliquez sur **Dry Run**. UCM planifie la route et confirme que la capacité `mesh.sample.echo` est disponible avec des effets secondaires `read_only` et **sans approbation requise**. Le rapport d'essai (dry-run) est propre.
4. Dans le champ d'entrée de la route, saisissez ce JSON (ce sont les paramètres attendus — une enveloppe d'entrée de route dont le champ `request_json` contient votre charge utile) :

   ```json
   {
     "request_json": "{\"message\":\"hello\"}"
   }
   ```

5. Cliquez sur **Execute**.

**Résultat attendu :** la route renvoie une réponse d'écho JSON sous la forme `{"echo": { ... }}` et rédige un rapport d'exécution de route. Le point d'entrée est la fonction fournie `UCapabilityMeshTestInvoker::EchoJson`, qui enveloppe la charge utile de la requête sous la forme `{"echo":<request>}`.

La page Routes contient également la colonne d'approbation **Route Catalog** pour l'auto-approbation automatique **EXPÉRIMENTALE**. Laissez **Approve all at own risk** et tous les commutateurs par route désactivés pour ce démarrage rapide. Ils ne servent qu'à tester les routes nécessitant une approbation sous votre propre responsabilité.

## 4. Emplacement des résultats

Tous les fichiers générés sont écrits sous le dossier `Saved/` de votre projet :

```text
Saved/UnrealCapabilityMesh/
  setup_validation_report.json     ← validation du rechargement
  capability_registry.json         ← capacités enregistrées
  discovery_report.md              ← résumé de découverte lisible par l'utilisateur
  compatibility_matrix.json        ← compatibilité capacité/point d'entrée
  route_reports/                   ← plans d'essai (dry-run)
  route_execution_reports/         ← entrées et sorties de routes exécutées (votre résultat d'écho)
```

Ouvrez `route_execution_reports/` pour voir la réponse de la route que vous venez d'exécuter.

## 5. Étapes suivantes

- Utiliser le panneau et chaque fonction avec ses paramètres : [UserManual.md](UserManual.md).
- Tous les champs de profil, politiques et chemins de sortie : [SettingsReference.md](SettingsReference.md).
- Personnaliser la configuration uniquement en cas de besoin : créez `<VotreProjet>/Config/UnrealCapabilityMesh/project_profile.json` ou copiez les manifestes spécifiques que le projet souhaite surcharger, puis cliquez à nouveau sur **Reload Setup**. Laissez les manifestes appartenant aux fournisseurs dans leurs plugins.
- Connecter un autre plugin : [INTEGRATION.md](INTEGRATION.md).
- Un problème ? Consultez [TROUBLESHOOTING.md](TROUBLESHOOTING.md) et [FAQ.md](FAQ.md).

Lorsque Tiny Tool Execution Integration Bridge est activé, il recharge UCM avant que TTER ne découvre les routes projetées lors du démarrage de l'éditeur. Le **Reload Setup** manuel reste l'action normale après l'édition d'un profil ou l'activation d'un fournisseur.

---

> **Pour les mainteneurs / génération à partir des sources (non requis pour utiliser le plugin) :** les outils de validation du dépôt source sont réservés aux mainteneurs et ne font **pas** partie du package Fab. Vous n'avez pas besoin de Python ni de portes de contrôle de code source pour installer ou utiliser UCM.
