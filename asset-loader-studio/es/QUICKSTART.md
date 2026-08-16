<!-- doc-provenance: product-facts.yml reconciled 2026-07-01; source AKDB:plugins/AssetLoaderStudio/architecture.md -->
# Inicio rápido

## Objetivo

Abrir Asset Loader Studio, enviar una solicitud de carga en tiempo de ejecución, inspeccionar una instantánea de tabla, previsualizar una operación gobernada y aplicar solo después de que la previsualización sea permitida.

## Primera ejecución

1. Habilite **Asset Loader Studio** y reinicie Unreal Editor si se le solicita.
2. Abra **Tools > Tiny Tools > Asset Loader Studio**.
3. Elija el modo **Guided** para la primera ejecución normal. Utilice **Simple** cuando solo desee inspeccionar.
4. Introduzca una ruta completa de objeto conocida, como `/Game/Data/DT_Items.DT_Items`, o una ruta de DataAsset que controle, y haga clic en **Inspect**.
5. Revise el estado del trabajo devuelto, las rutas cargadas, las fallas parciales, el grafo de dependencias y los diagnósticos.
6. Capture una instantánea de tabla desde un DataAsset o DataTable que controle.
7. Abra **Validation** y resuelva los activos faltantes, filas duplicadas, referencias no válidas o denegaciones de permisos antes de intentar realizar mutaciones.
8. Utilice **Preview Operation** para cualquier acción de crear, duplicar, renombrar, reorientar, reparar, guardar, revertir o eliminar.
9. Utilice **Apply Operation** solo cuando la previsualización informe una decisión de perfil permitida, un nivel de riesgo aceptable y que los destinos sean los activos que pretendía cambiar.
10. Revise el informe de aplicación y guarde los paquetes modificados a través de su flujo de trabajo normal de Unreal/control de código fuente.

## Puntos de entrada de Blueprint y en tiempo de ejecución

- `SubmitLoadRequest` inicia una solicitud de carga en tiempo de ejecución y devuelve un estado de trabajo.
- `CaptureTableSnapshot` lee datos de tabla estructurados para validación y trabajo de grafo.
- `PreviewOperation` evalúa una mutación planificada frente a un perfil de permisos antes de la aplicación.

Mantenga las integraciones de UCM y MCP como opcionales; el espacio de trabajo y el subsistema en tiempo de ejecución son el camino de primer uso independiente.
