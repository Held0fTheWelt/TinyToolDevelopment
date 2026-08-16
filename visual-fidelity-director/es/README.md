<!-- doc-provenance: AKDB:plugins/VisualFidelityDirector/architecture.md; docs/architecture/plugins/VisualFidelityDirector/product-facts.yml; reconciled 2026-07-12 -->
# Documentación de Visual Fidelity Director

Esta carpeta contiene la documentación del comprador enviada para Visual Fidelity Director. El flujo de trabajo principal es autónomo: habilite el complemento, abra el cockpit, revise los perfiles de fidelidad y los ejes de composición, inspeccione las evidencias, apruebe opcionalmente las escrituras de configuración gobernadas y use Expert Tools para flujos de trabajo clásicos de captura/receta sin necesitar otro complemento o servicio externo.

La documentación actual del paquete está reconciliada para la versión `2.0.0` y el estado de publicación `In Publishment`.

## Empiece aquí

- [QUICKSTART.md](QUICKSTART.md): instalación, habilitación, primera actualización del cockpit y una tarea de comparación de perfiles.
- [UserManual.md](UserManual.md): cada acción del cockpit, evidencia y Expert Tools.
- [SettingsReference.md](SettingsReference.md): controles, rutas de perfiles, funciones de biblioteca Blueprint, salidas de informes y comportamiento de aplicación.
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md): problemas comunes y soluciones.
- [FAQ.md](FAQ.md): respuestas sobre compatibilidad, seguridad, MRQ, capturas de pantalla y soporte.
- [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md): declaración de dependencias externas.

## Entrada al Cockpit

Abra Visual Fidelity Director desde **Tiny Tools > Visual Fidelity Director** (sección Rendimiento).

La pestaña acoplable ofrece tres páginas:

| Página | Propósito |
| --- | --- |
| **Cockpit** | Barra de perfiles, métricas en vivo multicuadro, nueve ejes de composición, selector de variantes, deslizadores de intención, detalle de eje con ruta de herencia, procedencia, hallazgos, comparación de perfiles y aplicación permanente gobernada. |
| **Evidence** | Once bloques de evidencia de carril fijo asignados a ejes de composición. |
| **Expert Tools** | Panel de control 1.x integrado para capturas, recetas, escáner, vista previa de aplicación e informes heredados. |

## Perfiles e informes

Los perfiles de fidelidad se encuentran en:

```text
Saved/VisualFidelityDirector/profiles/
```

Los informes de Expert Tools y flujos de trabajo de validación se encuentran en:

```text
Saved/VisualFidelityDirector/reports/
```

Las copias de recetas permanecen en:

```text
Saved/VisualFidelityDirector/recipes/
```

## Superficie Blueprint

Los llamadores de Blueprint en tiempo de ejecución utilizan `UVFDCockpitBlueprintLibrary` (mismos servicios C++ que la interfaz del cockpit). Un activo de demostración empaquetado se envía en `Content/Blueprints/BPF_VFD_API`.

## Modelo de seguridad

- La revisión del cockpit, las evidencias y las acciones de comparación son de solo lectura a menos que use el cajón de aplicación gobernada.
- **La aplicación permanente gobernada** escribe solo en los grupos Scalability de `DefaultGameUserSettings.ini`, la configuración del renderizador de `DefaultEngine.ini` y `DefaultDeviceProfiles.ini`, y solo después de una aprobación explícita por destino con soporte de copia de seguridad, verificación y reversión.
- **Expert Tools > Preview Apply + Rollback** sigue siendo la ruta de vista previa de CVar de sesión.
- Los activos, materiales, Post Process Volumes, preajustes MRQ, LevelSequences, Blueprints y configuraciones de accesibilidad permanecen bloqueados.

## Esquemas

Los archivos de esquema en tiempo de ejecución empaquetados se encuentran en `Schemas/` en la raíz del complemento.

## Archivos relacionados

- [../README.md](../README.md): descripción general del producto.
- [../CHANGELOG.md](../CHANGELOG.md): historial de lanzamientos.
