# Manual del usuario

`GameFeaturedClasses` proporciona actualmente una cáscara de complemento de tiempo de ejecución ligera para clases de jugabilidad destacada específicas del proyecto.

## Comportamiento actual del paquete

| Área | Estado en 1.0.1 |
| --- | --- |
| Módulo de tiempo de ejecución (`GameFeaturedClasses`) | Enviado — solo inicio/apagado. |
| Descriptor / empaquetado / icono / registro de cambios | Enviado. |
| Clases de jugabilidad destacada | aún no disponibles |
| Acciones de Game Feature / activos de conjunto de características | aún no disponibles |
| Registro de tiempo de ejecución / límite de interfaz | aún no disponibles |
| Banco de trabajo del editor / reparación / informes de prueba | aún no disponibles |
| Rutas de automatización de Tiny Tools | aún no disponibles |

<!-- image slot: gfc-module-shell -->

## Mapa de origen

- `Source/GameFeaturedClasses/GameFeaturedClasses.Build.cs` — dependencias del módulo.
- `Source/GameFeaturedClasses/Public/GameFeaturedClasses.h` — interfaz `FGameFeaturedClassesModule`.
- `Source/GameFeaturedClasses/Private/GameFeaturedClasses.cpp` — inicio y apagado.

## Cómo usar la cáscara hoy

1. Habilite el complemento (consulte [QUICKSTART.md](QUICKSTART.md)).
2. Mantenga las clases destacadas específicas del proyecto en sus propios módulos hasta que este paquete las envíe.
3. No documente ni dependa de los menús del banco de trabajo que no están presentes en esta compilación.

## Arquitectura objetivo (informativa, no enviada)

La arquitectura interna del producto describe un futuro GameFeature Workbench premium donde los autores declaran clases destacadas y conjuntos de características, las acciones con alcance de mundo las registran, los consumidores las resuelven a través de un límite de registro/interfaz, y los mantenedores escanean un grafo de características, anticipan reparaciones gobernadas y exportan informes de prueba. Ese comportamiento es **solo especificado para el objetivo** y no debe tratarse como funcionalidad disponible para el comprador en 1.0.1.

## Autarquía

La cáscara del módulo se carga por sí misma. Las futuras integraciones opcionales con `LightweightDummyActorSystem`, Unreal Capability Mesh o Project Intelligence Orchestrator no son requisitos de configuración para este paquete.

## Documentos relacionados

- [QUICKSTART.md](QUICKSTART.md)
- [SettingsReference.md](SettingsReference.md)
- [FAQ.md](FAQ.md)
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md)
- [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md)
