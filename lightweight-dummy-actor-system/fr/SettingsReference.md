---
lang: fr
title: LightweightDummyActorSystem Settings Reference
audience: [end_user]
owner_ref: plugin:LightweightDummyActorSystem
applies_to:
  component: LightweightDummyActorSystem
contract_ref: plugin:LightweightDummyActorSystem/profile-properties
version:
  since: "1.0"
---
# Référence des paramètres

LightweightDummyActorSystem ne fournit **pas** d'objet `UDeveloperSettings` / Préférences du projet. Les valeurs configurables résident dans les Data Assets, les composants et les structs comme indiqué ci-dessous (basées sur les en-têtes publics).

## ULDASRepresentationProfile (`UDataAsset`)

| Nom | Type | Défaut | Effet |
| --- | --- | --- | --- |
| `Descriptor` | `FLDASRepresentationDescriptor` | vide | Descripteur de représentation de base appliqué à l'enregistrement du sujet. |
| `PromoteDistance` | `float` | `0.0` | Entrée de distance utilisée par la politique de promotion. |
| `DemoteDistance` | `float` | `0.0` | Entrée de distance utilisée par la politique de rétrogradation. |
| `PromotionCooldownSeconds` | `float` | `1.0` | Temps de refroidissement entre les promotions. |
| `bAllowRuntimePromotion` | `bool` | `true` | Lorsque faux, les demandes de promotion à l'exécution sont interdites par le profil. |
| `bFailClosedOnPromotionFailure` | `bool` | `false` | Lorsque vrai, l'échec de la promotion entraîne un échement fermé. |
| `RequiredReadinessProviders` | `TArray<FName>` | vide | Fournisseurs de disponibilité nommés qui doivent être satisfaits. |

## ULDASDummyActorComponent

| Nom | Type | Défaut | Effet |
| --- | --- | --- | --- |
| Champs de liaison Profil / sujet | propriétés de composant editanywhere | défini par l'appelant | Lie le composant à la représentation du sujet LDAS. |
| Instantané répliqué | propriété répliquée | runtime | Transporte l'état de l'instantané avec la notification `OnRep`. |

## ALDASLightweightDummyActor

| Nom | Type | Défaut | Effet |
| --- | --- | --- | --- |
| Composants visibles | références de composant | construit | Composants de représentation de scène/débogage. |
| Champ de liaison LDAS | editanywhere | défini par l'appelant | Relie l'acteur aux données du sujet LDAS. |

## FLDASTransitionRecord / structs d'instantané

Les structs de transition et d'instantané exposent des champs editanywhere pour l'ID du sujet, le type de représentation, les horodatages et les listes de problèmes de disponibilité. Traitez-les comme des contrats de données plutôt que comme des paramètres globaux ; les défauts sont les défauts de struct dans les en-têtes sous `Public/Structs/`.

## Ce qui n'est pas présent

| Surface | Statut |
| --- | --- |
| `ULDASDeveloperSettings` | pas encore disponible |
| Objet de paramètres `Config/DefaultLightweightDummyActorSystem.ini` | non livré en tant que panneau de paramètres acheteur |
| Paramètres de pont WarCollection / Lightning / UCM | adaptateurs optionnels ciblés uniquement |

## Documents associés

- [UserManual.md](UserManual.md)
- [QUICKSTART.md](QUICKSTART.md)
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md)
