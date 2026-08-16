<!-- doc-provenance: product-facts.yml reconciled 2026-07-19; source AKDB:plugins/BestPracticesJournal/architecture.md; release 1.1.2 -->
# Référence des paramètres

Les paramètres de BPJ définissent l'emplacement des artefacts de pratiques locaux au projet et le comportement des projections de stockage optionnelles.

| Paramètre | Type | Valeur par défaut | Effet |
| --- | --- | --- | --- |
| `StorageBackend` | enum | `JsonArtifacts` | Sélectionne les artefacts JSON, le mode SQLite local ou un profil studio basé sur Postgres. |
| `StorageScope` | enum | `ProjectSaved` | Choisissez le périmètre de stockage projet, utilisateur, espace de travail ou personnalisé. |
| `StorageRootOverride` | path | vide | Surcharge la racine des artefacts locaux lorsqu'un emplacement personnalisé est requis. |
| `WorkspaceStorageRoot` | path | vide | Pointe BPJ vers une racine d'artefacts d'espace de travail partagée. |
| `SQLiteDatabasePathOverride` | path | vide | Surcharge le chemin du fichier de base de données SQLite pour le mode professionnel local. |
| `SQLiteDatabaseFileName` | string | `bpj.sqlite` | Nomme le fichier de base de données SQLite local par défaut. |
| `PostgresConnectionProfileName` | string | défini par le profil | Nomme le profil de bridge externe utilisé par une configuration Postgres studio. |
| `PostgresDsnEnvironmentVariable` | string | `BPJ_POSTGRES_DSN` | Nomme la variable d'environnement utilisée par l'outillage de bridge externe. |
| `bEnableJsonCompatibilityExport` | boolean | true | Maintient les exportations JSON portables disponibles même lorsqu'un autre mode de stockage est sélectionné. |
| `bEnableMarkdownProjection` | boolean | true | Écrit des projections Markdown lisibles pour la révision et la transmission. |
| `bEnableIisDerivedIndex` | boolean | true | Autorise les exportations de recherche dérivées IIS lorsqu'un flux d'indexation optionnel est présent. |
| `JournalSourceFolders` | path array | vide | Sélectionne les répertoires locaux contenant des journaux de projet ou de fichiers uniques que BPJ reconnaît et affiche sur place. |

Conservez les secrets en dehors des fichiers de plugins distribuables. BPJ ne livre pas de serveur de base de données et ne conserve pas les identifiants de fournisseurs.

## Sécurité du stockage

Le back-end par défaut `JsonArtifacts` garantit que BPJ reste simple et révisable en écrivant des fichiers portables sous la racine de stockage sélectionnée. Les profils SQLite et Postgres sont des choix de stockage optionnels pour des flux professionnels locaux ou en studio ; ils ne font pas d'un serveur de base de données une partie du package du plugin.

Conservez `bEnableJsonCompatibilityExport` activé lorsque les outils en aval, les réviseurs ou l'intégration continue ont besoin d'artefacts JSON stables. Conservez `bEnableMarkdownProjection` activé lorsque des utilisateurs humains ont besoin de fichiers de révision et de transmission lisibles.

## Valeurs par défaut recommandées

- Utilisez `JsonArtifacts` et `ProjectSaved` pour la première utilisation et la validation de packages sécurisés pour Fab.
- Définissez `StorageRootOverride` uniquement lorsque le projet dispose d'une politique d'artefacts locaux révisée.
- Conservez la projection Markdown activée pour la révision des dossiers et des résultats.
- Conservez l'exportation de compatibilité JSON activée lorsque SQLite ou Postgres est sélectionné.
- Traitez les index dérivés d'IIS comme des sorties dérivées optionnelles, et non comme le magasin canonique de BPJ.

## Traitement des données

La racine de stockage sélectionnée peut contenir des chemins de projet, des notes de révision, des descriptions de preuves, des détails de résultats d'implémentation, des chemins de rapports de validation et des métadonnées de provenance. Révisez les exportations avant de les envoyer en dehors du projet.
