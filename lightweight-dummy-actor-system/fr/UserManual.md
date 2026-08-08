# Manuel utilisateur

LightweightDummyActorSystem (LDAS) est un service de représentation d'exécution autonome pour les flux de travail de dummy-actor. La version MVP 1+2+3 inclut les modules Runtime, Editor et DeveloperTool.

## Capacités implémentées

| Capacité | Types principaux |
| --- | --- |
| Inscription du sujet | `ULDASWorldSubsystem::RegisterSubject`, `RegisterSubjectFromProfile`, `UnregisterSubject` |
| Interrogation de disponibilité | `QueryReadiness` → `FLDASReadinessReport` |
| Promotion / dégradation | `RequestPromotion`, `RequestDemotion` avec `ELDASTransitionReason` |
| Représentation dummy | `ALDASLightweightDummyActor`, `ULDASDummyActorComponent` |
| Actif de profil | `ULDASRepresentationProfile` |
| Diagnostics | `ULDASDiagnosticsSubsystem` |
| Inspecteur de l'éditeur | `SLDASRepresentationInspector` |
| Validation | `FLDASEditorValidationService`, `ULDASValidateContractsCommandlet` |

<!-- image slot: ldas-inspector -->

## Flux d'exécution

1. Obtenez `ULDASWorldSubsystem` depuis le monde.
2. Inscrivez un sujet avec un descripteur ou un `ULDASRepresentationProfile`.
3. Interrogez la disponibilité pour le type de représentation souhaité.
4. Demandez une promotion ou une dégradation lorsque la politique et la disponibilité le permettent.
5. Inspectez les diagnostics / l'inspecteur de l'éditeur lors de l'investigation des échecs.

La promotion et la dégradation sont soumises à des politiques. Les fournisseurs intégrés (`ULDASBuiltInReadinessProvider`, `ULDASBuiltInPromotionPolicy`, `ULDASBuiltInHeavyActorAdapter`) fournissent un comportement par défaut ; les projets peuvent inscrire des fournisseurs supplémentaires dans les builds pris en charge.

## Interfaces de l'éditeur

- Inspecteur de représentation pour les sujets inscrits.
- Service de validation de l'éditeur pour les vérifications de contrat.
- Commandlet développeur pour les exécutions de validation hors ligne.

## Autonomie et intégrations optionnelles

Les modules Runtime / Editor / DeveloperTool de base fonctionnent sans les plugins Tiny Tool pairs. Les éléments suivants restent **ciblés uniquement** et doivent se dégrader gracefully en leur absence :

- Adaptateur pilote en lecture seule WarCollection
- Preuve de pilote multi-joueur
- Pont d'entité LightningCore
- Ponts d'automatisation UCM / PIO / BPJ

Ne considérez pas ces adaptateurs comme des exigences de configuration pour le noyau livré.

## Documents associés

- [QUICKSTART.md](QUICKSTART.md)
- [SettingsReference.md](SettingsReference.md)
- [FAQ.md](FAQ.md)
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md)
- [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md)
