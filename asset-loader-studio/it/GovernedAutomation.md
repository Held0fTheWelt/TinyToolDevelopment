# Automazione governata

Asset Loader Studio è progettato per funzionare in modo autonomo. Non dipende da Unreal Capability Mesh o dal server Unified MCP in fase di compilazione. I manifest UCM opzionali sono distribuiti sotto `Config/UnrealCapabilityMesh`.

Route:

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

Profili di autorizzazione:

- `read_only` consente lettura, ispezione, convalida, anteprima ed esportazione.
- `guided_safe` consente modifiche in fasi con limiti e conferma.
- `expert` consente flag di capacità per operazioni in blocco e distruttive, con approvazione rigorosa per il lavoro distruttivo.

Ogni risposta di automazione utilizza un involucro stabile con `success`, `operation`, `summary`,
`diagnostics`, `mutation_flags` e payload specifici della route.

L'automazione è opzionale. Se UCM o MCP non sono installati, utilizzare direttamente l'area di lavoro dell'editor, la libreria Blueprint
o il sottosistema di runtime. I chiamanti delle route dovrebbero eseguire l'anteprima prima dell'applicazione e memorizzare l'ID dell'anteprima o
il token di approvazione insieme al record di revisione.
