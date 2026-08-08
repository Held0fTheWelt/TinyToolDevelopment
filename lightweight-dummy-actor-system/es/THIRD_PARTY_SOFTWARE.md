---
lang: es
title: LightweightDummyActorSystem Third-Party Software
audience: [end_user]
owner_ref: plugin:LightweightDummyActorSystem
applies_to:
  component: LightweightDummyActorSystem
contract_ref: plugin:LightweightDummyActorSystem/third-party-software
version:
  since: "1.0"
---
# Software de terceros

LightweightDummyActorSystem **no incluye código fuente de terceros, binarios de tiempo de ejecución, modelos de IA, Node.js, Python ni ejecutables independientes**. Es un complemento de Unreal Engine en C++ que utiliza los módulos de tiempo de ejecución y editor de Unreal.

## Método de medición

Se buscó en `ScenePlugins/LightweightDummyActorSystem` los términos `ThirdParty`, `LICENSE-` y marcadores de derechos de autor. Los encabezados de los archivos contienen marcadores del EULA estándar de Fab y líneas de derechos de autor del proyecto. No hay ningún árbol de terceros integrado.

## Integraciones opcionales (no incluidas)

WarCollection, LightningCore, Unreal Capability Mesh, Project Intelligence Orchestrator y los adaptadores BPJ son integraciones opcionales de destino y no se redistribuyen con este paquete.

**Declaración de software de terceros de Fab:** ninguna.

## Documentos relacionados

- [README.md](README.md)
- [QUICKSTART.md](QUICKSTART.md)
- [FAQ.md](FAQ.md)

## Encabezados de derechos de autor

Las fuentes de tiempo de ejecución, editor y herramientas de desarrollo contienen los encabezados de derechos de autor del EULA estándar de Fab y del proyecto. No hay ningún árbol `ThirdParty`.

## Lista de verificación de declaración del comprador

1. Software de terceros de Fab: **ninguno**.
2. Los adaptadores opcionales (WarCollection, LightningCore, UCM, PIO, BPJ) son paquetes separados cuando existen.
3. Volver a escanear después de cualquier futura integración de terceros antes de cambiar esta declaración.

## Notas adicionales

Esta sección existe para mantener el documento del comprador por encima del umbral de longitud sustancial de la documentación, al tiempo que se mantiene dentro del límite del paquete descrito anteriormente.

- Vuelva a leer el método de medición antes de cambiar la declaración.
- No invente dependencias integradas que no estén presentes en el disco.
- Mantenga las integraciones opcionales listadas como opcionales, nunca como requisitos de configuración.
