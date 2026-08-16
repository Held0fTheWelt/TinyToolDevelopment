<!-- doc-provenance: AKDB:plugins/UnrealCapabilityMesh/architecture.md; docs/architecture/plugins/UnrealCapabilityMesh/product-facts.yml; reconciled 2026-07-19 -->
# Documentation Unreal Capability Mesh

Ce dossier documente le plugin Unreal Capability Mesh pour Unreal Engine 5.4+, la configuration du projet, l'intégration et la lecture du code source.

Page produit Fab : https://www.fab.com/listings/fd186d26-cdcf-4c4f-93d4-50e437b7673e

## Commencez ici

| Document | Objectif |
| --- | --- |
| [BUYER_GUIDE.md](BUYER_GUIDE.md) | Portée du produit, modules inclus, ce que fait et ne fait pas UCM. |
| [QUICKSTART.md](QUICKSTART.md) | Flux de configuration minimal des manifestes aux rapports générés. |
| [UserManual.md](UserManual.md) | Flux de travail du panneau de configuration et procédure de fonctionnement normale. |
| [TechnicalOverview.md](TechnicalOverview.md) | Architecture, flux de données, emplacements de stockage et diagnostics. |
| [CodeDocumentation.md](CodeDocumentation.md) | Guide de lecture du code source C++ par module et classe. |
| [SettingsReference.md](SettingsReference.md) | Disposition des dossiers de manifestes, champs de profil de projet, champs de politique, chemins de sortie. |
| [INTEGRATION.md](INTEGRATION.md) | Comment connecter un autre plugin via des manifestes ou des adaptateurs. |
| [TROUBLESHOOTING.md](TROUBLESHOOTING.md) | Problèmes courants de validation, de découverte, de routes et d'invoquations. |
| [FAQ.md](FAQ.md) | Réponses courtes pour les acheteurs et les réviseurs. |
| [ReleaseChecklist.md](ReleaseChecklist.md) | Liste de contrôle de conformité Fab et de packaging. |
| [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md) | Déclaration sur les logiciels tiers. |

## Idée centrale

UCM est un hub neutre. Il ne connaît pas les plugins partenaires spécifiques dans le code C++. UCM lui-même, les plugins fournisseurs activés et le projet peuvent chacun décrire des capacités (capabilities), points d'entrée, schémas, règles, routes, transformations et adaptateurs en JSON. Le chargeur fusionne ces racines de configuration par ordre de priorité, construit des registres, évalue les règles de sécurité et rédige des rapports.

La configuration actuelle du projet utilise UCM comme couche d'intégration principale entre les produits Tiny Tool Development. Le comportement spécifique au produit reste dans le plugin propriétaire sous forme de points d'entrée appelables par JSON ou de contrats de fichiers ; UCM charge uniquement la configuration qui les relie. Les Freebie Bridges sont des plugins de secours/référence optionnels pour les équipes sans UCM, et non le modèle de connexion par défaut.

## Chemins importants

```text
<EnabledPlugin>/Config/UnrealCapabilityMesh/  ← manifestes en lecture seule appartenant au fournisseur
Config/UnrealCapabilityMesh/                   ← surcharges optionnelles du projet et routes composées
Saved/UnrealCapabilityMesh/                    ← rapports générés et sorties de routes
```

Ne copiez pas les manifestes d'un fournisseur dans le projet uniquement pour exposer ses routes. Activez le plugin fournisseur et rechargez la configuration. Créez une surcharge de projet uniquement lorsque le projet modifie intentionnellement les champs de profil ou possède une route composée.
