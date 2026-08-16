<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/LightweightEditorMode/architecture.md -->
# Documentation de Lightweight Editor Mode

Lightweight Editor Mode est un plugin d'éditeur Unreal Engine qui permet aux artistes, level designers, technical artists et programmeurs de réduire temporairement le coût de rendu dans l'éditeur pendant qu'ils travaillent sur des projets lourds. Il est conçu comme un outil de travail réversible : activez-le lorsque la fenêtre d'affichage (viewport) devient trop gourmande, continuez votre édition, puis désactivez-le pour revenir à l'état précédent de l'éditeur.

Cette documentation offre le niveau de détail attendu pour un plugin prêt pour le Marketplace. Elle couvre les attentes des acheteurs, l'utilisation quotidienne, les paramètres, le comportement technique, la validation, le packaging et la maintenance.

## Commencez ici

- [UserManual.md](UserManual.md) explique le flux de travail normal dans l'éditeur.
- [BUYER_GUIDE.md](BUYER_GUIDE.md) explique ce que fait le plugin et à qui il s'adresse.
- [SettingsReference.md](SettingsReference.md) liste chaque paramètre disponible.
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md) aide à diagnostiquer les cas courants dans l'éditeur.
- [TechnicalOverview.md](TechnicalOverview.md) décrit l'architecture à l'exécution.
- [CodeDocumentation.md](CodeDocumentation.md) associe les fichiers sources aux comportements.
- [PerformanceTuningReference.md](PerformanceTuningReference.md) aide à ajuster les profils.
- [ValidationAndQA.md](ValidationAndQA.md) fournit les étapes de test et de validation de publication.
- [CompatibilityAndPackaging.md](CompatibilityAndPackaging.md) couvre les notes sur le moteur et le packaging.
- [FAQ.md](FAQ.md) répond aux questions fréquentes.
- [ReleaseChecklist.md](ReleaseChecklist.md) est la liste de contrôle finale avant publication.

## Ce que le plugin modifie

Lorsqu'il est activé, Lightweight Editor Mode peut appliquer ces optimisations côté éditeur :

- Réduire le pourcentage d'écran (Screen Percentage) du viewport de l'éditeur.
- Réduire la qualité globale de scalabilité (Scalability Quality).
- Désactiver l'éclairage indirect diffus Lumen et les réflexions Lumen.
- Désactiver les cartes d'ombres virtuelles (Virtual Shadow Maps).
- Désactiver le brouillard volumétrique et le brouillard standard.
- Forcer les viewports de l'éditeur en mode d'affichage Unlit (non éclairé).
- Désactiver le rendu en temps réel (Realtime) dans les viewports de l'éditeur.

Le comportement exact dépend du profil sélectionné et des paramètres de profil modifiables dans les Project Settings.

## Promesse de conception fondamentale

Le plugin est intentionnellement réversible :

- Il sauvegarde les paramètres de scalabilité avant de les modifier.
- Il sauvegarde les variables de console (CVars) modifiées avant de définir les valeurs du plugin.
- Il stocke les modes d'affichage et les états en temps réel par viewport pour la session active.
- Il conserve un mode d'affichage de secours persistant pour la récupération après redémarrage.
- Il restaure l'état de l'éditeur lorsque le mode est désactivé ou que le module s'arrête.

Cela rend le plugin idéal pour un soulagement rapide des performances tout en gardant la configuration principale du projet intacte.

## Flux de travail rapide

1. Activez le plugin dans Edit > Plugins.
2. Ouvrez Tools > Performance > Lightweight Editor Mode.
3. Choisissez un profil : Mild, Balanced, Aggressive ou Extreme.
4. Cliquez sur Enable Lightweight Mode.
5. Travaillez dans l'éditeur avec un coût de viewport réduit.
6. Cliquez sur Disable Lightweight Mode avant le travail final sur l'éclairage, les matériaux ou les captures.

## Guides visuels

Le dossier Documentation/Screenshots contient des schémas de flux de travail au format SVG :

- [01-workflow-overview.svg](Screenshots/01-workflow-overview.svg)
- [02-profile-and-settings.svg](Screenshots/02-profile-and-settings.svg)
- [03-restore-flow.svg](Screenshots/03-restore-flow.svg)

Ces schémas sont des éléments de documentation et non des ressources d'interface à l'exécution.

## Portée du moteur

L'implémentation cible les API d'éditeur et les variables de console de rendu au style d'Unreal Engine 5.4. Le détail d'implémentation le plus important est que les viewports de l'éditeur ne suivent pas de manière fiable le même chemin de pourcentage d'écran que le rendu du jeu ou du PIE. Le plugin utilise donc des CVars de pourcentage d'écran spécifiques à l'éditeur.

## Consignes de sécurité

Lightweight Editor Mode est un outil de performance pour l'éditeur, et non un système d'optimisation d'exécution pour les versions finales. Il ne doit pas être utilisé comme unique voie de validation pour l'éclairage final, les ombres, le brouillard, les matériaux ou les rendus cinématographiques.

Avant les captures de version ou les validations visuelles, désactivez le mode et vérifiez la scène avec les paramètres de qualité de production prévus.
