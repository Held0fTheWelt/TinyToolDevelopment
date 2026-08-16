# Automatización gobernada

Asset Loader Studio es independiente por defecto. No depende de Unreal Capability Mesh ni del servidor Unified MCP en tiempo de compilación. Los manifiestos opcionales de UCM se incluyen en `Config/UnrealCapabilityMesh`.

Rutas:

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

Perfiles de permisos:

- `read_only` permite lectura, inspección, validación, vista previa y exportación.
- `guided_safe` permite ediciones por etapas con límites y confirmación.
- `expert` permite banderas de capacidad masivas y destructivas, con aprobación estricta para trabajos destructivos.

Cada respuesta de automatización utiliza un sobre estable con `success`, `operation`, `summary`,
`diagnostics`, `mutation_flags` y cargas útiles específicas de la ruta.

La automatización es opcional. Si UCM o MCP no están instalados, utilice el espacio de trabajo del editor, la biblioteca Blueprint o el subsistema de tiempo de ejecución directamente. Los llamadores de rutas deben realizar una vista previa antes de aplicar y almacenar el ID de vista previa o el token de aprobación con su registro de revisión.
