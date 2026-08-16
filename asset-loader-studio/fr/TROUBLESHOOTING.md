<!-- doc-provenance: product-facts.yml reconciled 2026-07-01; source AKDB:plugins/AssetLoaderStudio/architecture.md -->
# Dépannage

## Actifs manquants

Utilisez des chemins d'objet complets avec le suffixe d'objet, par exemple `/Game/Data/DA_Item.DA_Item`. Si la validation signale `ALS.Table.MissingReferencedAsset`, réorientez le champ vers un actif existant ou effacez-le.

## Mauvais chemins

`ALS.InvalidSoftObjectPath` et `ALS.Table.InvalidReferencePath` signifient que le chemin ne peut pas être analysé comme un chemin d'objet Unreal. Recopiez la référence depuis le Content Browser.

## Échecs d'application

Les applications nécessitent une prévisualisation autorisée et un jeton d'approbation. Dans l'espace de travail de l'éditeur, le bouton Apply approuve la dernière prévisualisation. Via l'automatisation, définissez `approval_token` sur l'ID de prévisualisation ou sur `approved`.

## Refus de permission

Utilisez `asset_loader_studio.state.read.v1` pour inspecter les profils actifs. Les refus courants concernent le mode lecture seule, le mode simulation seule, les limites de lignes/actifs affectés, les racines hors de `allowed_roots` ou l'absence de permission destructive.

## Échecs d'enregistrement

L'application générique marque les packages comme modifiés ("dirty") et fournit des instructions de récupération. Enregistrez via l'invite d'enregistrement de l'éditeur Unreal ou votre flux de contrôle de source après avoir révisé les actifs modifiés.

## Lignes vides ou en double

Les DataTables contenant des identifiants de ligne vides ou en double ne peuvent pas être associées en toute sécurité à des opérations de ligne stables. Renommez ou réparez les lignes dans la table propriétaire, puis capturez un nouvel instantané.

## Actions destructives bloquées

La suppression et d'autres opérations destructives nécessitent un profil qui les autorise ainsi qu'un jeton d'approbation destructive explicite. Privilégiez la prévisualisation du plan, la sauvegarde des copies de sécurité ou de l'état du contrôle de source, puis appliquez uniquement la prévisualisation révisée.
