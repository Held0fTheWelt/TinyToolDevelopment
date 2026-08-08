# Preguntas frecuentes

## ¿Qué hace LightweightDummyActorSystem?

Proporciona un servicio de representación en tiempo de ejecución para flujos de trabajo de actores ficticios, que incluye el registro de sujetos, la representación de actores ficticios, transiciones de promoción y degradación, diagnósticos, un inspector del editor y un commandlet de validación.

## ¿Se puede usar sin otros plugins de Tiny Tool?

Sí. Los módulos Runtime, Editor y DeveloperTool se implementan como el paquete principal. Las integraciones opcionales especificadas para el destino, como WarCollection, LightningCore, UCM, PIO y los adaptadores BPJ, no son necesarias para el comportamiento principal entregado.

## ¿Qué versiones del motor son compatibles?

La matriz de versiones empaquetadas está dirigida a Unreal Engine 5.4 hasta 5.8 en Win64, Linux y Mac, donde las listas permitidas del módulo permiten esas plataformas.

## ¿Modifica los activos del proyecto por sí mismo?

No. El servicio principal gestiona el estado de representación y transición. Cualquier mutación específica del proyecto o comportamiento del adaptador debe revisarse en el flujo de trabajo del proyecto propietario.

## ¿Dónde puedo obtener soporte?

Utilice el enlace de soporte en la página del producto de Fab.
