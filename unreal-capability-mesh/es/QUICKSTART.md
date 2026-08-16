<!-- doc-provenance: AKDB:plugins/UnrealCapabilityMesh/architecture.md; docs/architecture/plugins/UnrealCapabilityMesh/product-facts.yml; reconciled 2026-07-19 -->
# Guía de inicio rápido

Esta guía le acompaña desde una instalación limpia hasta un **resultado funcional y visible**: un inventario de capacidades detectadas y una ruta ejecutada por usted mismo que devuelve una respuesta JSON. No se requiere programación ni redacción de manifiestos — el plugin incluye un perfil predeterminado listo para usar.

## Lo que obtendrá tras esta guía

El panel de control abierto, el **Default Capability Mesh Profile** incluido cargado, capacidades detectadas y una ruta (`sample.echo.route.v1`) ejecutada con una respuesta JSON y un informe guardado que puede abrir.

## Requisitos

- Unreal Engine 5.4 o posterior.
- Plataforma: Windows (Win64), Linux o Mac.
- Un **proyecto** de Unreal en el que habilitar el plugin. UCM es un plugin de editor en C++: en un proyecto C++ se compila al iniciar el editor por primera vez; en un proyecto solo de Blueprint, instálelo para una versión coincidente del motor (a través de su biblioteca de Fab) para que el editor pueda cargar sus módulos de editor precompilados.
- No se requiere software de terceros, cuenta, modelo de IA ni tiempo de ejecución externo. Consulte [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## 1. Instalar y habilitar

1. Adquiera **Unreal Capability Mesh** desde su biblioteca de Fab y añádelo a su proyecto (aparece en la carpeta `Plugins/` del proyecto) o instálelo en el motor.
2. Abra su proyecto. En el editor, vaya a **Edit → Plugins**, busque `Unreal Capability Mesh` y marque **Enabled**.
3. Reinicie el editor cuando se le solicite. (En un proyecto C++, deje que se compile en este primer inicio.)

UCM puede funcionar sin una carpeta de configuración local en el proyecto. Carga el perfil predeterminado incluido y los perfiles locales de los plugins proveedores habilitados. Utilice `Config/UnrealCapabilityMesh/` solo cuando el proyecto necesite intencionadamente anulaciones o rutas compuestas propiedad del proyecto.

## 2. Obtener el primer resultado

1. Abra el panel de control: **Tools → Unreal Capability Mesh**.
2. En la página **Overview** debería ver el perfil activo **"Default Capability Mesh Profile"**.
3. Haga clic en **Reload Setup**. UCM carga el perfil, valida la configuración JSON, registra las definiciones y ejecuta la detección.
4. Abra la página **Capabilities** — ahora verá las capacidades detectadas (por ejemplo `mesh.sample.echo`) con su disponibilidad y efectos secundarios.
5. Abra la página **Diagnostics** — muestra los mensajes de validación y detección resultantes de la recarga. Una recarga limpia indica que el plugin funciona correctamente.

Acaba de hacer funcionar el producto utilizando únicamente lo incluido en el paquete.

## 3. Un ejemplo práctico real: Ejecutar una ruta

UCM incluye una ruta de ejemplo segura y de solo lectura, `sample.echo.route.v1`, que llama a un punto de entrada de eco. Utilícela para ejecutar su primera ruta de extremo a extremo.

1. Abra la página **Routes**.
2. En el campo de ID de ruta, introduzca:

   ```text
   sample.echo.route.v1
   ```

3. Haga clic en **Dry Run**. UCM planifica la ruta y confirma que la capacidad `mesh.sample.echo` está disponible con efectos secundarios `read_only` y **sin aprobación requerida**. El informe de simulación (dry-run) está limpio.
4. En el campo de entrada de la ruta, introduzca este JSON (estos son los parámetros esperados — un sobre de entrada de ruta cuyo campo `request_json` contiene su carga útil):

   ```json
   {
     "request_json": "{\"message\":\"hello\"}"
   }
   ```

5. Haga clic en **Execute**.

**Resultado esperado:** la ruta devuelve una respuesta de eco JSON con la forma `{"echo": { ... }}` y genera un informe de ejecución de ruta. El punto de entrada es la función incluida `UCapabilityMeshTestInvoker::EchoJson`, que envuelve la carga útil de la solicitud como `{"echo":<request>}`.

La página Routes también contiene la columna de aprobación **Route Catalog** para la autoaprobación automática **EXPERIMENTACIÓN**. Deje **Approve all at own risk** y todos los conmutadores individuales desactivados para este inicio rápido. Solo sirven para probar rutas con aprobación bajo su propia responsabilidad.

## 4. Dónde se guardan los resultados

Todos los archivos generados se escriben en la carpeta `Saved/` de su proyecto:

```text
Saved/UnrealCapabilityMesh/
  setup_validation_report.json     ← validación tras recargar
  capability_registry.json         ← capacidades registradas
  discovery_report.md              ← resumen de detección en formato legible
  compatibility_matrix.json        ← compatibilidad entre capacidades y puntos de entrada
  route_reports/                   ← planes de simulación (dry-run)
  route_execution_reports/         ← entradas y salidas de rutas ejecutadas (su resultado de eco)
```

Abra `route_execution_reports/` para ver la respuesta de la ruta que acaba de ejecutar.

## 5. Próximos pasos

- Manejo del panel y de cada función con sus parámetros: [UserManual.md](UserManual.md).
- Cada campo de perfil, directiva y ruta de salida: [SettingsReference.md](SettingsReference.md).
- Personalice la configuración solo cuando sea necesario: cree `<SuProyecto>/Config/UnrealCapabilityMesh/project_profile.json` o copie los manifiestos específicos que el proyecto vaya a anular, y vuelva a hacer clic en **Reload Setup**. Deje los manifiestos de los proveedores en sus respectivos plugins.
- Conectar otro plugin: [INTEGRATION.md](INTEGRATION.md).
- ¿Algo no funciona? Consulte [TROUBLESHOOTING.md](TROUBLESHOOTING.md) y [FAQ.md](FAQ.md).

Cuando Tiny Tool Execution Integration Bridge está habilitado, vuelve a cargar UCM antes de que TTER detecte las rutas proyectadas durante el inicio del editor. El botón manual **Reload Setup** sigue siendo la acción habitual tras editar un perfil o habilitar un proveedor.

---

> **Para mantenedores / compilación desde el código fuente (no requerido para usar el plugin):** las herramientas de validación del repositorio fuente son exclusivas para mantenedores y **no** forman parte del paquete Fab. No necesita Python ni puertas de código fuente para instalar o usar UCM.
