---
lang: es
title: GameFeaturedClasses Third-Party Software
audience: [end_user]
owner_ref: plugin:GameFeaturedClasses
applies_to:
  component: GameFeaturedClasses
contract_ref: plugin:GameFeaturedClasses/third-party-software
version:
  since: "1.0"
---
# Software de terceros

**GameFeaturedClasses** no incluye código fuente de terceros, binarios en tiempo de ejecución, modelos de IA, Node.js, Python ni ejecutables independientes. Es una cáscara de módulo de plugin de Unreal Engine en C++.

## Método de medición

Se buscó en `ScenePlugins/GameFeaturedClasses` los términos `ThirdParty`, `LICENSE-` y marcadores de derechos de autor. Los encabezados del código fuente contienen marcadores de EULA estándar de Fab. No existe ningún árbol de terceros integrado.

## Integraciones opcionales

Los adaptadores futuros (por ejemplo, LightweightDummyActorSystem, Unreal Capability Mesh, Project Intelligence Orchestrator, WarCollection) son solo de arquitectura objetivo y no se redistribuyen con este paquete.

**Declaración de software de terceros de Fab:** ninguna.

## Documentos relacionados

- [README.md](README.md)
- [QUICKSTART.md](QUICKSTART.md)
- [FAQ.md](FAQ.md)

## Encabezados de derechos de autor

Las fuentes del módulo contienen los encabezados de EULA estándar de Fab. No existe ningún directorio `ThirdParty` en el paquete.

## Lista de verificación de declaración del comprador

1. Software de terceros de Fab: **ninguno**.
2. No enumerar los módulos de Unreal Engine como software de terceros integrado en el plugin.
3. Volver a escanear después de cualquier futura integración antes de cambiar esta declaración.

## Notas adicionales

Esta sección existe para mantener el documento del comprador por encima del umbral de longitud sustancial requerido para la documentación, manteniéndose dentro del límite del paquete descrito anteriormente.

- Vuelve a leer el método de medición antes de cambiar la declaración.
- No inventes dependencias integradas que no estén presentes en el disco.
- Mantén las integraciones opcionales listadas como opcionales, nunca como requisitos de configuración.
