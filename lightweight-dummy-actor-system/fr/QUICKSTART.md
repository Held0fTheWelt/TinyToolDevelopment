---
lang: fr
title: LightweightDummyActorSystem Quick Start
audience: [end_user]
owner_ref: plugin:LightweightDummyActorSystem
applies_to:
  component: LightweightDummyActorSystem
preconditions:
  - Unreal Engine project open with the plugin package available
  - Edit > Plugins can enable LightweightDummyActorSystem
expected_result:
  text: Subject registers through ULDASWorldSubsystem and QueryReadiness returns a readiness report.
version:
  since: "1.0"
---
# Démarrage rapide

Ce guide installe **LightweightDummyActorSystem (LDAS)** et explique comment enregistrer un premier sujet fonctionnel à l'aide de l'API d'exécution fournie. Les MVP 1+2+3 sont implémentés : noyau d'exécution, noyau de transition, inspecteur de l'éditeur et commandlet de validation.

## Ce que vous aurez après ce guide

Le plugin activé et un sujet enregistré via `ULDASWorldSubsystem::RegisterSubject` / `RegisterSubjectFromProfile` avec une requête de disponibilité que vous pouvez inspecter.

## Prérequis

- Unreal Engine 5.4–5.8 (matrice packagée ; Win64/Linux/Mac là où les listes autorisées des modules le permettent).
- Aucun autre plugin Tiny Tool n'est requis pour le package principal.
- Aucun logiciel tiers, compte ou runtime externe n'est nécessaire. Consultez [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## 1. Installation et activation

1. Obtenez **LightweightDummyActorSystem** depuis Fab et ajoutez-le au projet.
2. Ouvrez **Édition → Plugins**, activez **LightweightDummyActorSystem**, puis redémarrez lorsque cela est demandé.
3. Confirmez que les modules Runtime, Editor et DeveloperTool se chargent (`LightweightDummyActorSystem`, `LightweightDummyActorSystemEditor`, `LightweightDummyActorSystemDeveloper`).

## 2. Création d'un profil de représentation

1. Dans le Content Browser, créez un Data Asset de classe `ULDASRepresentationProfile`.
2. Définissez les champs du profil ancré, par exemple :

| Champ | Valeur exemple | Signification |
| --- | --- | --- |
| `PromoteDistance` | `2500.0` | Seuil de distance utilisé par les entrées de la politique de promotion. |
| `DemoteDistance` | `3000.0` | Seuil de distance utilisé par les entrées de la politique de rétrogradation. |
| `PromotionCooldownSeconds` | `1.0` | Nombre minimum de secondes entre les promotions. |
| `bAllowRuntimePromotion` | `true` | Autorise les demandes de promotion à l'exécution. |
| `bFailClosedOnPromotionFailure` | `false` | Si true, l'échec de la promotion entraîne un échement fermé. |
| `RequiredReadinessProviders` | (vide ou fournisseurs nommés) | Fournisseurs de disponibilité supplémentaires requis avant la promotion. |

## 3. Exemple complet : Enregistrement et interrogation

Depuis du code gameplay ou un utilitaire d'éditeur capable d'accéder au sous-système du monde :

```cpp
UWorld* World = /* monde actuel */;
ULDASWorldSubsystem* LDAS = World->GetSubsystem<ULDASWorldSubsystem>();

FLDASSubjectId SubjectId;
// Remplissez les champs de SubjectId requis par la liaison de votre projet.

FLDASRepresentationDescriptor Descriptor;
// Remplissez les champs du descripteur ou utilisez RegisterSubjectFromProfile avec le Data Asset.

const bool bRegistered = LDAS->RegisterSubjectFromProfile(SubjectId, ProfileAsset);
const FLDASReadinessReport Report = LDAS->QueryReadiness(
	SubjectId, ELDASRepresentationKind::Heavy /* ou Dummy selon votre intention */);
```

## Résultat attendu

- `bRegistered` est true lorsque l'ID du sujet est accepté.
- `QueryReadiness` retourne un `FLDASReadinessReport` dont le statut est `Ready`, `Warning` ou un statut bloquant avec des entrées d'erreur — jamais un succès silencieux.

## 4. Validation des contrats (optionnel)

Exécutez le commandlet de validation packagé `ULDASValidateContractsCommandlet` depuis un hôte d'éditeur/commandlet pour vérifier la cohérence des contrats du projet.

## Prochaines étapes

- [UserManual.md](UserManual.md) — sous-systèmes, Actor, composant, transitions.
- [SettingsReference.md](SettingsReference.md) — propriétés des profils et des composants.
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md) — échecs de disponibilité et de promotion.
