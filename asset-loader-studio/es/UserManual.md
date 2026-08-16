<!-- doc-provenance: product-facts.yml reconciled 2026-07-01; source AKDB:plugins/AssetLoaderStudio/architecture.md -->
# Manual de usuario de Asset Loader Studio

Abra el espacio de trabajo desde **Tiny Tools -> Asset Loader Studio -> Asset Loader Studio**.

Asset Loader Studio se basa en un único ciclo de revisión: inspeccionar, validar, previsualizar, aplicar y auditar. Puede detenerse en la inspección o continuar con ediciones gobernadas cuando el perfil de permisos activo lo permita.

El espacio de trabajo contiene siete vistas:

- **Graph** muestra nodos de activos, filas, campos, referencias y diagnósticos.
- **Table** muestra filas de DataAsset/DataTable conscientes del esquema y campos editables.
- **Validation** explica referencias faltantes, rutas inválidas, identificadores duplicados y bloqueos de permisos.
- **Jobs** muestra el estado de la última solicitud de carga en tiempo de ejecución.
- **Inspector** muestra el modo activo, el perfil de permisos, la última previsualización y el último informe de aplicación.
- **History** conserva las acciones recientes del espacio de trabajo.
- **Governance** muestra el perfil activo, las anulaciones de ruta, el estado de auditoría y las acciones del perfil.

Los modos controlan la autoridad de mutación:

- **Simple** utiliza el perfil de solo lectura.
- **Guided** permite ediciones escalonadas seguras con aprobación.
- **Expert** permite previsualizaciones más amplias de lotes y persistencia, y aún requiere aprobación antes de aplicar.

Utilice **Inspect** después de ingresar una ruta de objeto completa, como `/Game/Data/DT_Items.DT_Items`. Utilice las entradas de Fila, Campo y Nuevo Valor para previsualizar una actualización estructurada de campo. **Apply** solo ejecuta la última previsualización aprobada y marca los paquetes modificados como sucios para su guardado explícito.

## Ciclo de revisión

1. Inspeccione el activo de origen.
2. Verifique el estado del grafo/tabla y los diagnósticos.
3. Seleccione un perfil que coincida con la cantidad de autoridad que necesita.
4. Previsualice la operación y verifique los objetivos, el hash del plan, los conteos afectados, el riesgo y las guías de recuperación.
5. Aplique solo la previsualización que acaba de revisar.
6. Inspeccione el informe de aplicación y el historial de auditoría.
7. Guarde manualmente los paquetes sucios después de la revisión.
