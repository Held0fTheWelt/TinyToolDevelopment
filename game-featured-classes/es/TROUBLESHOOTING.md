---
lang: es
title: GameFeaturedClasses Troubleshooting
audience: [end_user]
owner_ref: plugin:GameFeaturedClasses
applies_to:
  component: GameFeaturedClasses
symptom: Buyer expects a GameFeature workbench or featured classes that are not shipped in 1.0.1.
recovery:
  steps:
    - Confirm the plugin is enabled under Edit > Plugins and restart the editor
    - Re-read the matching troubleshooting entry and apply the documented fix
    - Re-run the quick start smoke check
version:
  since: "1.0"
---
# Solución de problemas

Formato: Síntoma → Causa → Solución.

## 0. Lo habilité y no pasó nada

**Síntoma:** Tras habilitar `GameFeaturedClasses` y reiniciar, no aparece el menú de Tiny Tools, ni nuevos activos del Content Browser, ni la interfaz de usuario del banco de trabajo.  
**Causa:** La versión `1.0.1` incluye únicamente la estructura del módulo de tiempo de ejecución. Las clases destacadas y las superficies del editor aún no están disponibles.  
**Solución:** Confirma que el plugin está habilitado en **Editar → Plugins**, y verifica que el módulo `GameFeaturedClasses` se carga correctamente (consulta [QUICKSTART.md](QUICKSTART.md)). No esperes ver el menú del producto hasta que se publique un paquete posterior que lo incluya.

## 1. Busco un menú de Workbench de GameFeature que falta

**Síntoma:** No aparece ninguna entrada de Tiny Tools / banco de trabajo tras habilitar el plugin.  
**Causa:** La versión 1.0.1 incluye únicamente la estructura del módulo de tiempo de ejecución; las superficies del banco de trabajo del editor aún no están disponibles.  
**Solución:** Utiliza el plugin únicamente como un límite de módulo. No esperes la interfaz de usuario del banco de trabajo hasta que un paquete posterior lo publique explícitamente.

## 2. No hay clases destacadas en el Content Browser

**Síntoma:** Habilitar el plugin no añade activos de clases de jugabilidad.  
**Causa:** El paquete no incluye contenido de clases destacadas ni de conjuntos de características.  
**Solución:** Mantén las clases de tu proyecto en tus propios módulos; considera el envío de clases destacadas como trabajo futuro de paquetes.

## 3. El plugin no aparece en Editar → Plugins

**Síntoma:** La búsqueda de `GameFeaturedClasses` no devuelve resultados.  
**Causa:** El plugin no se copió en la carpeta de Plugins del proyecto o del motor, o el descriptor fue filtrado.  
**Solución:** Confirma que `GameFeaturedClasses.uplugin` existe dentro del árbol `Plugins` del proyecto (o en Plugins del motor) y, a continuación, reinicia el editor.

## 4. El módulo no se carga en un motor no compatible

**Síntoma:** La habilitación tiene éxito en la interfaz de usuario, pero el módulo de tiempo de ejecución falla durante la compilación o carga.  
**Causa:** La versión del motor está fuera de la matriz 5.4–5.8 empaquetada o hay una incompatibilidad de binarios.  
**Solución:** Utiliza una rama del motor compatible que coincida con la compilación de Fab, o compila desde el código fuente en ese motor.

## 5. Espero que LightweightDummyActorSystem o PIO sean dependencias obligatorias

**Síntoma:** Las guías de configuración de otros productos implican que GFC requiere LDAS/UCM/PIO.  
**Causa:** Esas integraciones son una arquitectura de destino opcional, no requisitos de tiempo de ejecución para la estructura básica.  
**Solución:** Habilita únicamente `GameFeaturedClasses` para la comprobación rápida de la estructura básica. Añade los módulos asociados más adelante únicamente cuando exista una integración publicada.

## 6. ¿Dónde está la documentación en línea?

**Síntoma:** El DocsURL del descriptor de Fab debería redirigir a una página del navegador.  
**Causa:** Las páginas de destino en línea se encuentran fuera del paquete de Fab.  
**Solución:** Abre `https://docs.tiny-tool-development.com/game-featured-classes/` (DocsURL del descriptor) o utiliza el conjunto `Documentation/` incluido en el paquete con este plugin.

## Documentos relacionados

- [QUICKSTART.md](QUICKSTART.md)
- [UserManual.md](UserManual.md)
- [FAQ.md](FAQ.md)
- [SettingsReference.md](SettingsReference.md)
