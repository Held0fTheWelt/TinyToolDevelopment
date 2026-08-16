<!-- doc-provenance: product-facts.yml reconciled 2026-07-01; source AKDB:plugins/AssetLoaderStudio/architecture.md -->
# Referencia de configuración

La configuración de Asset Loader Studio se centra en los perfiles de gobernanza, las raíces/clases permitidas, la directiva de auditoría y las anulaciones de ruta.

## Configuración de gobernanza

| Configuración | Tipo | Predeterminado | Efecto |
| --- | --- | --- | --- |
| `DefaultProfileId` | string | `guided_safe` | Selecciona el perfil de permisos predeterminado cuando no se proporciona un perfil de ruta o solicitud. |
| `ProfileDirectories` | array | `Config/AssetLoaderStudio/Governance/Profiles` | Enumera las carpetas analizadas en busca de archivos JSON de perfiles de permisos. |
| `AllowedRoots` | array | `/Game`, `/Engine` | Limita los objetivos de modificación a raíces de Unreal aprobadas. |
| `AllowedClasses` | array | Predeterminado del paquete | Restringe los objetivos de modificación a rutas de clase aprobadas si están configuradas. |
| `AuditRetentionDays` | integer | `30` | Controla cuánto tiempo se conservan los registros de auditoría antes de ser depurados. |
| `AuditLogDirectory` | string | `Saved/AssetLoaderStudio/Audit` | Almacena entradas de auditoría persistentes para operaciones de vista previa y aplicación. |
| `bAuditPreviewOperations` | boolean | `true` | Escribe entradas de auditoría para las vistas previas de operaciones. |
| `bAuditApplyOperations` | boolean | `true` | Escribe entradas de auditoría para las operaciones de aplicación. |

## Campos del perfil de permisos

Los perfiles de permisos definen `profile_id`, acciones permitidas, número máximo de activos/filas afectados, raíces/clases permitidas, modo de solo lectura, modo de simulación (dry-run), confirmación de aplicación, aprobación destructiva y retención de auditoría. Utilice `read_only` para inspección, `guided_safe` para ediciones revisadas normales y `expert` únicamente para trabajos masivos de confianza.

## Anulaciones de ruta

Las anulaciones de ruta opcionales pueden mapear una ruta UCM a un perfil más estricto o más flexible. Las anulaciones de ruta no reemplazan las comprobaciones locales de vista previa/aplicación; solo seleccionan el perfil utilizado por dichas comprobaciones.

## Valores predeterminados prácticos

- Comience con `guided_safe` para trabajos de editor revisados.
- Mantenga `read_only` para detección, validación, exportación de tablas y comprobaciones automatizadas que no deban modificar activos.
- Utilice `expert` solo para trabajos masivos de confianza y mantenga la aprobación destructiva explícita.
- Mantenga la retención de auditoría lo suficientemente alta como para cubrir su período habitual de revisión de lanzamientos.
