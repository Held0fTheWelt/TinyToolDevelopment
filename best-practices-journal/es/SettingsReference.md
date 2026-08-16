<!-- doc-provenance: product-facts.yml reconciled 2026-07-19; source AKDB:plugins/BestPracticesJournal/architecture.md; release 1.1.2 -->
# Referencia de configuración

La configuración de BPJ determina dónde se almacenan los artefactos de prácticas locales del proyecto y cómo se comportan las proyecciones de almacenamiento opcionales.

| Configuración | Tipo | Predeterminado | Efecto |
| --- | --- | --- | --- |
| `StorageBackend` | enum | `JsonArtifacts` | Selecciona artefactos JSON, modo SQLite local o un perfil de estudio respaldado por Postgres. |
| `StorageScope` | enum | `ProjectSaved` | Selecciona el alcance de almacenamiento por proyecto, usuario, espacio de trabajo o personalizado. |
| `StorageRootOverride` | path | vacío | Anula la raíz de artefactos locales cuando se requiere una ubicación personalizada. |
| `WorkspaceStorageRoot` | path | vacío | Apunta BPJ a una raíz de artefactos compartida del espacio de trabajo. |
| `SQLiteDatabasePathOverride` | path | vacío | Anula la ruta del archivo de base de datos SQLite para el modo profesional local. |
| `SQLiteDatabaseFileName` | string | `bpj.sqlite` | Nombra el archivo de base de datos SQLite local predeterminado. |
| `PostgresConnectionProfileName` | string | definido por el perfil | Nombra el perfil de puente externo utilizado por una configuración de estudio con Postgres. |
| `PostgresDsnEnvironmentVariable` | string | `BPJ_POSTGRES_DSN` | Nombra la variable de entorno utilizada por la herramienta de puente externo. |
| `bEnableJsonCompatibilityExport` | boolean | true | Mantiene disponibles las exportaciones JSON portables aunque se seleccione otro modo de almacenamiento. |
| `bEnableMarkdownProjection` | boolean | true | Genera proyecciones Markdown legibles para revisión y entrega. |
| `bEnableIisDerivedIndex` | boolean | true | Permite exportaciones de búsqueda derivadas de IIS cuando existe un flujo de trabajo de indexación opcional. |
| `JournalSourceFolders` | path array | vacío | Selecciona directorios locales con diarios de proyectos o de archivo único que BPJ reconoce y muestra en el lugar. |

Mantenga las credenciales fuera de los archivos del plugin distribuibles. BPJ no incluye un servidor de base de datos ni guarda credenciales de proveedores.

## Seguridad del almacenamiento

El motor predeterminado `JsonArtifacts` mantiene BPJ accesible y revisable al guardar archivos portables bajo la raíz de almacenamiento seleccionada. Los perfiles SQLite y Postgres son opciones de almacenamiento adicionales para flujos profesionales locales o de estudio; no convierten a un servidor de base de datos en parte del paquete del plugin.

Mantenga habilitado `bEnableJsonCompatibilityExport` cuando las herramientas posteriores, revisores o la CI necesiten artefactos JSON estables. Mantenga habilitado `bEnableMarkdownProjection` cuando los usuarios requieran archivos de revisión y entrega legibles.

## Valores predeterminados recomendados

- Utilice `JsonArtifacts` y `ProjectSaved` para el primer uso y la validación de paquetes seguros para Fab.
- Configure `StorageRootOverride` solo si el proyecto cuenta con una directiva revisada de artefactos locales.
- Mantenga la proyección Markdown habilitada para la revisión de informes y resultados.
- Mantenga habilitada la exportación de compatibilidad JSON cuando seleccione SQLite o Postgres.
- Trate los índices derivados de IIS como salidas derivadas opcionales, no como el almacén canónico de BPJ.

## Tratamiento de datos

La raíz de almacenamiento seleccionada puede contener rutas del proyecto, notas de revisión, descripciones de evidencia, detalles de resultados de implementación, rutas de informes de validación y metadatos de procedencia. Revise las exportaciones antes de enviarlas fuera del proyecto.
