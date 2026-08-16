# Automatisation gouvernée

Asset Loader Studio est conçu pour fonctionner de manière autonome. Il ne dépend ni d'Unreal Capability Mesh ni du serveur Unified MCP au moment de la compilation. Les manifestes UCM optionnels sont livrés sous `Config/UnrealCapabilityMesh`.

Routes :

- `asset_loader_studio.tools.describe.v1`
- `asset_loader_studio.state.read.v1`
- `asset_loader_studio.load.submit.v1`
- `asset_loader_studio.jobs.status.v1`
- `asset_loader_studio.table.snapshot.v1`
- `asset_loader_studio.table.validate.v1`
- `asset_loader_studio.graph.build.v1`
- `asset_loader_studio.governance.snapshot.v1`
- `asset_loader_studio.governance.profile.save.v1`
- `asset_loader_studio.operation.preview.v1`
- `asset_loader_studio.operation.apply.v1`
- `asset_loader_studio.table.export.v1`
- `asset_loader_studio.audit.read.v1`
- `asset_loader_studio.audit.prune.v1`

Profils de permission :

- `read_only` permet la lecture, l'inspection, la validation, l'aperçu et l'exportation.
- `guided_safe` permet des modifications par étapes avec des limites et une confirmation.
- `expert` permet les indicateurs de capacité en masse et destructeurs, avec une approbation forte pour les travaux destructeurs.

Chaque réponse d'automatisation utilise une enveloppe stable contenant `success`, `operation`, `summary`,
`diagnostics`, `mutation_flags` et des charges utiles spécifiques à la route.

L'automatisation est optionnelle. Si UCM ou MCP n'est pas installé, utilisez l'espace de travail de l'éditeur, la bibliothèque Blueprint
ou le sous-système d'exécution directement. Les appelants de route doivent effectuer un aperçu avant l'application et stocker l'identifiant de l'aperçu ou
le jeton d'approbation avec leur enregistrement de révision.
