<!-- doc-provenance: AKDB:plugins/VisualFidelityDirector/architecture.md; docs/architecture/plugins/VisualFidelityDirector/product-facts.yml; reconciled 2026-07-12 -->
# Guía de inicio rápido

Esta guía lo lleva desde la instalación hasta un resultado real: el cockpit de Visual Fidelity Director abierto con una vista de perfil actualizada y una comparación de perfiles lado a lado.

## Lo que tendrá después de esta guía

El cockpit VFD abierto en Unreal Editor, el muestreo de métricas en vivo iniciado, un eje de composición revisado con detalles de variante y procedencia, y una comparación con un segundo perfil.

## Requisitos

- Editor de Unreal Engine 5.4 en Win64, Linux o Mac.
- Un proyecto que pueda cargar complementos de editor.
- Sin software de terceros, cuenta, servicio de IA u otro complemento de Tiny Tool.

## 1. Instalar y habilitar

1. Agregue **VisualFidelityDirector** desde su biblioteca de Fab al proyecto, o instálelo en el motor.
2. Abra **Editar > Complementos**.
3. Busque **Visual Fidelity Director**.
4. Habilite el complemento y reinicie Unreal Editor cuando se le solicite.

Si instala un paquete de complemento solo de código fuente en un proyecto C++, deje que Unreal compile los módulos del proyecto en el próximo inicio del editor.

## 2. Abrir el Cockpit

1. Abra **Tiny Tools > Visual Fidelity Director**.
2. Confirme que la página **Cockpit** esté activa (predeterminada).
3. Revise el banner de estado, el selector de perfiles y la barra de métricas.

Resultado esperado:

- El título de la pestaña acoplable es **Visual Fidelity Director**.
- La barra de perfiles enumera los perfiles conocidos de `Saved/VisualFidelityDirector/profiles/` más el contexto integrado/proyecto.
- La barra de métricas se llena durante varios tics del editor (muestreo multicuadro) o muestra un estado no disponible explícito.

## 3. Ejemplo práctico: Revisar un eje

1. Haga clic en **Refresh** en la tarjeta de acción del Cockpit.
2. Seleccione cualquier franja de eje de composición (por ejemplo **Anti-Aliasing** o **Upscaling**).
3. En el cajón de detalles del eje, revise:
   - la **ruta de herencia** desde el perfil raíz hasta el perfil activo;
   - filas de **procedencia** para configuraciones compiladas;
   - **hallazgos locales al control** para ese eje.
4. Cambie el cuadro combinado **Variant** cuando haya varias variantes de canalización disponibles. Las variantes no disponibles permanecen visibles pero deshabilitadas con evidencia de compatibilidad.

Resultado esperado:

- Las actualizaciones de los deslizadores de intención reflejan la variante seleccionada.
- La procedencia y los hallazgos se actualizan para el eje seleccionado.
- Ningún archivo de proyecto cambia hasta que use la aplicación gobernada o la vista previa de aplicación de Expert Tools.

## 4. Ejemplo práctico: Comparar dos perfiles

1. Desplácese hasta la tarjeta **Profile Comparison** en la página Cockpit.
2. Elija un perfil en **Compare against** del menú desplegable.
3. Lea el resumen de diferencias por eje.

Resultado esperado:

- Los ejes con diferencias se enumeran con detalles a nivel de configuración.
- Los ejes que coinciden no muestran filas de diferencias.
- La comparación utiliza el mismo comparador en tiempo de ejecución que `UVFDCockpitBlueprintLibrary::CompareFidelityProfiles`.

## 5. Opcional: Captura de Expert Tools

1. Cambie a la página **Expert Tools**.
2. Haga clic en **Export Snapshot**.

Resultado esperado:

- Existe `Saved/VisualFidelityDirector/reports/<timestamp>/quality_snapshot.json`.
- Las copias más recientes aparecen en `Saved/VisualFidelityDirector/reports/`.

Esta ruta conserva el flujo de trabajo de captura y receta de 1.x para los usuarios que prefieren la revisión basada en informes.

## 6. Opcional: Aplicación permanente gobernada

Solo continúe si tiene la intención de escribir archivos de configuración del proyecto.

1. En la página Cockpit, haga clic en **Build Destinations** en el cajón de aplicación.
2. Revise cada resumen de destino (Scalability, ini de renderizador, Device Profiles).
3. Marque la aprobación solo para los destinos que acepte.
4. Haga clic en **Apply Approved**.

Resultado esperado:

- Copias de seguridad con marca de tiempo y un manifiesto de reversión en la raíz de copia de seguridad de configuración de VFD.
- Informe de aplicación con resultados de verificación.
- **Rollback** restaura los archivos respaldados si falla alguna verificación.

## 7. Dónde se ubican las salidas

```text
Saved/VisualFidelityDirector/profiles/
Saved/VisualFidelityDirector/reports/<timestamp>/
Saved/VisualFidelityDirector/recipes/
```

## 8. Próximos pasos

- Lista completa de operaciones: [UserManual.md](UserManual.md)
- Controles y funciones Blueprint: [SettingsReference.md](SettingsReference.md)
- Problemas y soluciones: [TROUBLESHOOTING.md](TROUBLESHOOTING.md)
- Respuestas de compatibilidad y seguridad: [FAQ.md](FAQ.md)
