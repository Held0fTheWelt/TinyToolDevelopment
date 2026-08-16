<!-- doc-provenance: AKDB:plugins/UnrealCapabilityMesh/architecture.md; docs/architecture/plugins/UnrealCapabilityMesh/product-facts.yml; reconciled 2026-07-19 -->
# Documentación de Unreal Capability Mesh

Esta carpeta documenta el plugin Unreal Capability Mesh para Unreal Engine 5.4+, la configuración del proyecto, la integración y la lectura del código fuente.

Página del producto en Fab: https://www.fab.com/listings/fd186d26-cdcf-4c4f-93d4-50e437b7673e

## Empiece aquí

| Documento | Propósito |
| --- | --- |
| [BUYER_GUIDE.md](BUYER_GUIDE.md) | Alcance del producto, módulos incluidos, qué hace y qué no hace UCM. |
| [QUICKSTART.md](QUICKSTART.md) | Flujo de configuración mínimo desde manifiestos hasta informes generados. |
| [UserManual.md](UserManual.md) | Flujo de trabajo del panel de control y procedimiento operativo normal. |
| [TechnicalOverview.md](TechnicalOverview.md) | Arquitectura, flujo de datos, ubicaciones de almacenamiento y diagnósticos. |
| [CodeDocumentation.md](CodeDocumentation.md) | Guía de lectura del código fuente C++ por módulo y clase. |
| [SettingsReference.md](SettingsReference.md) | Estructura de carpetas de manifiestos, campos de perfil de proyecto, campos de directivas, rutas de salida. |
| [INTEGRATION.md](INTEGRATION.md) | Cómo conectar otro plugin mediante manifiestos o adaptadores. |
| [TROUBLESHOOTING.md](TROUBLESHOOTING.md) | Problemas habituales de validación, detección, rutas e invocación. |
| [FAQ.md](FAQ.md) | Respuestas breves para compradores y revisores. |
| [ReleaseChecklist.md](ReleaseChecklist.md) | Lista de verificación de empaquetado y cumplimiento para Fab. |
| [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md) | Declaración de software de terceros. |

## Concepto central

UCM es un núcleo neutro. No conoce los plugins asociados específicos en el código C++. UCM, los plugins proveedores habilitados y el propio proyecto pueden describir capacidades (capabilities), puntos de entrada, esquemas, reglas, rutas, transformaciones y adaptadores en JSON. El cargador combina estas raíces de configuración por orden de prioridad, crea registros, evalúa reglas de seguridad y genera informes.

La configuración actual del proyecto utiliza UCM como la capa de integración principal entre productos de Tiny Tool Development. El comportamiento específico de cada producto permanece en el plugin propietario como puntos de entrada invocables por JSON o contratos de archivos; UCM solo carga la configuración que los conecta. Los Freebie Bridges son plugins de referencia/reserva opcionales para equipos sin UCM, no el modelo de conexión predeterminado.

## Rutas importantes

```text
<EnabledPlugin>/Config/UnrealCapabilityMesh/  ← manifiestos de solo lectura propiedad del proveedor
Config/UnrealCapabilityMesh/                   ← anulaciones opcionales propiedad del proyecto y rutas compuestas
Saved/UnrealCapabilityMesh/                    ← informes generados y salidas de rutas
```

No copie los manifiestos de un proveedor en el proyecto únicamente para exponer sus rutas. Habilite el plugin proveedor y vuelva a cargar la configuración. Cree una anulación de proyecto solo cuando el proyecto cambie deliberadamente campos del perfil o sea propietario de una ruta compuesta.
