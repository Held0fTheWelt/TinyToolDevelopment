---
lang: fr
title: GameFeaturedClasses Troubleshooting
audience: [end_user]
owner_ref: plugin:GameFeaturedClasses
applies_to:
  component: GameFeaturedClasses
symptom: Buyer expects a GameFeature workbench or featured classes that are not shipped in 1.0.1.
recovery:
  steps:
    - Confirm the plugin is enabled under Edit > Plugins and restart the editor
    - Re-read the matching troubleshooting entry and apply the documented fix
    - Re-run the quick start smoke check
version:
  since: "1.0"
---
# Dépannage

Format : Symptôme → Cause → Solution.

## 0. Je l'ai activé et rien ne s'est passé

**Symptôme :** Après avoir activé `GameFeaturedClasses` et redémarré, il n'y a pas de menu Tiny Tools, aucun nouvel actif du Content Browser, ni d'interface utilisateur de l'atelier de travail (workbench).  
**Cause :** La version `1.0.1` ne fournit que l'armature du module d'exécution. Les classes mises en avant et les interfaces éditeur ne sont pas encore disponibles.  
**Solution :** Confirmez que le plugin est activé sous **Édition → Plugins**, puis vérifiez que le module `GameFeaturedClasses` se charge (voir [QUICKSTART.md](QUICKSTART.md)). Attendez-vous à l'absence de menu produit jusqu'à ce qu'un package ultérieur le fournisse.

## 1. Recherche d'un menu GameFeature Workbench manquant

**Symptôme :** Aucune entrée Tiny Tools / workbench n'apparaît après l'activation du plugin.  
**Cause :** La version 1.0.1 ne fournit que l'armature du module d'exécution ; les interfaces workbench de l'éditeur ne sont pas encore disponibles.  
**Solution :** Utilisez le plugin uniquement comme limite de module. Ne vous attendez pas à une interface workbench tant qu'un package ultérieur ne le fournit pas explicitement.

## 2. Aucune classe mise en avant dans le Content Browser

**Symptôme :** L'activation du plugin n'ajoute pas d'actifs de classes de gameplay.  
**Cause :** Le package n'inclut pas de contenu de classe mise en avant ou d'ensemble de fonctionnalités.  
**Solution :** Conservez les classes de votre projet dans vos propres modules ; considérez la livraison des classes mises en avant comme un travail pour un package futur.

## 3. Le plugin n'apparaît pas sous Édition → Plugins

**Symptôme :** La recherche de `GameFeaturedClasses` ne retourne rien.  
**Cause :** Le plugin n'a pas été copié dans le dossier Plugins du projet ou du moteur, ou le descripteur a été filtré.  
**Solution :** Confirmez que `GameFeaturedClasses.uplugin` existe sous l'arborescence `Plugins` du projet (ou dans les Plugins du moteur), puis redémarrez l'éditeur.

## 4. Échec du chargement du module sur un moteur non pris en charge

**Symptôme :** L'activation réussit dans l'interface utilisateur, mais le module d'exécution échoue lors de la compilation/chargement.  
**Cause :** Version du moteur hors de la matrice 5.4–5.8 emballée ou incompatibilité binaire.  
**Solution :** Utilisez une branche de moteur prise en charge correspondant à la build Fab, ou reconstruisez à partir des sources sur ce moteur.

## 5. Attente de `LightweightDummyActorSystem` ou PIO comme dépendance obligatoire

**Symptôme :** Les guides d'installation d'autres produits suggèrent que GFC nécessite LDAS/UCM/PIO.  
**Cause :** Ces intégrations sont une architecture cible optionnelle, et non des exigences d'exécution pour l'armature.  
**Solution :** Activez uniquement `GameFeaturedClasses` pour la vérification rapide de l'armature. Ajoutez les modules pairs ultérieurement uniquement lorsqu'une intégration fournie est disponible.

## 6. Où se trouve la documentation en ligne ?

**Symptôme :** Le DocsURL du descripteur Fab devrait rediriger vers une page de navigateur.  
**Cause :** Les pages d'accueil en ligne se trouvent en dehors du package Fab.  
**Solution :** Ouvrez `https://docs.tiny-tool-development.com/game-featured-classes/` (DocsURL du descripteur) ou utilisez l'ensemble `Documentation/` inclus dans le package fourni avec ce plugin.

## Documents connexes

- [QUICKSTART.md](QUICKSTART.md)
- [UserManual.md](UserManual.md)
- [FAQ.md](FAQ.md)
- [SettingsReference.md](SettingsReference.md)
