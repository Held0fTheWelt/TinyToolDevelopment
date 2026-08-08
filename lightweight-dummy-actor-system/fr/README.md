# Documentation de LightweightDummyActorSystem

LightweightDummyActorSystem (LDAS) est un service de représentation d'exécution autonome pour les workflows d'acteurs factices. La version MVP 1+2+3 inclut les modules Runtime, Editor et DeveloperTool : enregistrement des sujets, requêtes de disponibilité, portes de politique de promotion/dégradation, représentation des acteurs factices, diagnostics, inspecteur de l'éditeur et un commandlet de validation.

Public cible : ingénieurs gameplay et outils ayant besoin de représentations factices légères avec promotion/dégradation soumise à des politiques, sans nécessiter de plugins Tiny Tool tiers pour le package principal.

## Fonctionnalités (incluses)

- `RegisterSubject` / `RegisterSubjectFromProfile` / `UnregisterSubject`
- `QueryReadiness` → `FLDASReadinessReport`
- `RequestPromotion` / `RequestDemotion`
- `ULDASRepresentationProfile`, `ALDASLightweightDummyActor`, `ULDASDummyActorComponent`
- Inspecteur de l'éditeur et `ULDASValidateContractsCommandlet`

## Prise en main

1. Activez le plugin — consultez l'exemple pratique dans [QUICKSTART.md](QUICKSTART.md) (enregistrement + requête de disponibilité).
2. Configurez un Data Asset `ULDASRepresentationProfile` avec des valeurs réelles de distance et de temps de recharge.
3. Lisez [UserManual.md](UserManual.md) et [SettingsReference.md](SettingsReference.md).

## Fichiers associés

- [../README.md](../README.md) — aperçu du produit.
- [../CHANGELOG.md](../CHANGELOG.md) — historique des versions.
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md) · [FAQ.md](FAQ.md) · [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md)
