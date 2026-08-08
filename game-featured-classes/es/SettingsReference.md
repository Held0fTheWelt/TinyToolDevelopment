---
lang: es
title: GameFeaturedClasses Settings Reference
audience: [end_user]
owner_ref: plugin:GameFeaturedClasses
applies_to:
  component: GameFeaturedClasses
contract_ref: plugin:GameFeaturedClasses/module-shell-settings
version:
  since: "1.0"
---
# Referencia de configuración

GameFeaturedClasses 1.0.1 **no** incluye DeveloperSettings, objetos de configuración `.ini` ni descriptores de clase destacada editables. El módulo en tiempo de ejecución no expone ninguna superficie de configuración `UPROPERTY` más allá de la interfaz de módulo vacía.

## Superficies incluidas

| Nombre | Tipo | Predeterminado | Efecto |
| --- | --- | --- | --- |
| Habilitación del complemento | Interfaz de usuario de complementos del editor | deshabilitado hasta que el comprador lo habilite | Carga el módulo en tiempo de ejecución `GameFeaturedClasses`. |
| `FGameFeaturedClassesModule::StartupModule` | gancho de módulo | invocado por el motor | Inicio del módulo; sin configuración del comprador. |
| `FGameFeaturedClassesModule::ShutdownModule` | gancho de módulo | invocado por el motor | Apagado del módulo; sin configuración del comprador. |

## No disponible aún

| Superficie de configuración esperada | Estado |
| --- | --- |
| Activos de descriptor de clase destacada | no disponible aún |
| Activos de conjunto de características | no disponible aún |
| Configuración de registro / resolución | no disponible aún |
| Preferencias del banco de trabajo del editor | no disponible aún |
| `UGameFeaturedClassesSettings` DeveloperSettings | no disponible aún |
| `Config/DefaultGameFeaturedClasses.ini` | no incluido |

No se inventan filas de configuración aquí. Cuando las versiones posteriores del paquete agreguen campos reales de `UPROPERTY` / DeveloperSettings, esta referencia debe actualizarse desde el código fuente en el mismo cambio.

## Documentos relacionados

- [UserManual.md](UserManual.md) — límite actual frente al objetivo.
- [QUICKSTART.md](QUICKSTART.md) — verificación rápida de habilitación.
- [FAQ.md](FAQ.md)

## Metadatos de empaquetado (no configuraciones en tiempo de ejecución)

El descriptor `.uplugin` contiene `Version` / `VersionName` para el empaquetado. Esos campos son metadatos del complemento, no DeveloperSettings en tiempo de ejecución, y no deben editarse casualmente desde los flujos de trabajo de documentación del comprador.

## Regla de actualización

Cualquier fila de configuración futura en este archivo debe citar la ruta del encabezado y el nombre de la propiedad desde el código fuente en el mismo cambio de documentación.
