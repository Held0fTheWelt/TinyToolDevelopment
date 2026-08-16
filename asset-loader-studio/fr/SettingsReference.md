<!-- doc-provenance: product-facts.yml reconciled 2026-07-01; source AKDB:plugins/AssetLoaderStudio/architecture.md -->
# Référence des paramètres

Les paramètres d'Asset Loader Studio sont centrés sur les profils de gouvernance, les racines/classes autorisées, la politique d'audit et les remplacements de routes.

## Paramètres de gouvernance

| Paramètre | Type | Valeur par défaut | Effet |
| --- | --- | --- | --- |
| `DefaultProfileId` | string | `guided_safe` | Sélectionne le profil de permission par défaut lorsqu'aucun profil de route ou de demande n'est fourni. |
| `ProfileDirectories` | array | `Config/AssetLoaderStudio/Governance/Profiles` | Liste les dossiers analysés pour trouver les fichiers JSON de profils de permission. |
| `AllowedRoots` | array | `/Game`, `/Engine` | Limite les cibles de mutation aux racines Unreal approuvées. |
| `AllowedClasses` | array | Valeur par défaut du package | Restreint les cibles de mutation aux chemins de classes approuvés lorsqu'ils sont configurés. |
| `AuditRetentionDays` | integer | `30` | Contrôle la durée de conservation des journaux d'audit avant purge. |
| `AuditLogDirectory` | string | `Saved/AssetLoaderStudio/Audit` | Stocke les entrées d'audit persistantes pour les opérations de prévisualisation et d'application. |
| `bAuditPreviewOperations` | boolean | `true` | Écrit les entrées d'audit pour les prévisualisations d'opérations. |
| `bAuditApplyOperations` | boolean | `true` | Écrit les entrées d'audit pour les opérations d'application. |

## Champs du profil de permission

Les profils de permission définissent l'identifiant `profile_id`, les actions autorisées, le nombre maximal d'actifs/lignes affectés, les racines/classes autorisées, le mode lecture seule, le mode simulation (dry-run), la confirmation d'application, l'approbation destructive et la conservation de l'audit. Utilisez `read_only` pour l'inspection, `guided_safe` pour les modifications révisées normales, et `expert` uniquement pour les travaux en masse de confiance.

## Remplacements de routes

Les remplacements de routes optionnels peuvent associer une route UCM à un profil plus strict ou plus souple. Ces remplacements ne remplacent pas les vérifications locales de prévisualisation/application ; ils sélectionnent uniquement le profil utilisé par ces vérifications.

## Valeurs par défaut pratiques

- Commencez avec `guided_safe` pour les travaux d'éditeur révisés.
- Conservez `read_only` pour la découverte, la validation, l'exportation de tables et les vérifications automatisées qui ne doivent pas modifier les actifs.
- Utilisez `expert` uniquement pour les travaux en masse de confiance et maintenez une approbation destructive explicite.
- Conservez une durée de rétention de l'audit suffisamment longue pour couvrir votre fenêtre habituelle de révision de version.
