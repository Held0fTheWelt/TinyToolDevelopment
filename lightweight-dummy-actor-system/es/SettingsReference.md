---
lang: es
title: LightweightDummyActorSystem Settings Reference
audience: [end_user]
owner_ref: plugin:LightweightDummyActorSystem
applies_to:
  component: LightweightDummyActorSystem
contract_ref: plugin:LightweightDummyActorSystem/profile-properties
version:
  since: "1.0"
---
# Referencia de configuración

LightweightDummyActorSystem **no** incluye un objeto `UDeveloperSettings` / Preferencias del proyecto. Los valores configurables se encuentran en Data Assets, componentes y estructuras, como se detalla a continuación (basados en encabezados públicos).

## ULDASRepresentationProfile (`UDataAsset`)

| Nombre | Tipo | Predeterminado | Efecto |
| --- | --- | --- | --- |
| `Descriptor` | `FLDASRepresentationDescriptor` | vacío | Descriptor de representación base aplicado al registro del sujeto. |
| `PromoteDistance` | `float` | `0.0` | Entrada de distancia utilizada por la política de promoción. |
| `DemoteDistance` | `float` | `0.0` | Entrada de distancia utilizada por la política de degradación. |
| `PromotionCooldownSeconds` | `float` | `1.0` | Tiempo de enfriamiento entre promociones. |
| `bAllowRuntimePromotion` | `bool` | `true` | Cuando es false, las solicitudes de promoción en tiempo de ejecución no están permitidas por el perfil. |
| `bFailClosedOnPromotionFailure` | `bool` | `false` | Cuando es true, el fallo de promoción falla de forma cerrada. |
| `RequiredReadinessProviders` | `TArray<FName>` | vacío | Proveedores de disponibilidad nombrados que deben cumplirse. |

## ULDASDummyActorComponent

| Nombre | Tipo | Predeterminado | Efecto |
| --- | --- | --- | --- |
| Campos de enlace de perfil/sujeto | propiedades del componente editanywhere | establecidos por el llamador | Vincula el componente a la representación del sujeto LDAS. |
| Instantánea replicada | propiedad replicada | tiempo de ejecución | Transporta el estado de la instantánea con la notificación `OnRep`. |

## ALDASLightweightDummyActor

| Nombre | Tipo | Predeterminado | Efecto |
| --- | --- | --- | --- |
| Componentes visibles | referencias de componentes | construidos | Componentes de representación de escena/depuración. |
| Campo de enlace LDAS | editanywhere | establecidos por el llamador | Enlaza el actor a los datos del sujeto LDAS. |

## FLDASTransitionRecord / estructuras de instantánea

Las estructuras de transición e instantánea exponen campos editanywhere para el id. del sujeto, el tipo de representación, las marcas de tiempo y las listas de problemas de disponibilidad. Trátalas como contratos de datos en lugar de configuraciones globales; los valores predeterminados son los predeterminados de la estructura en los encabezados bajo `Public/Structs/`.

## Lo que no está presente

| Superficie | Estado |
| --- | --- |
| `ULDASDeveloperSettings` | aún no disponible |
| Objeto de configuración `Config/DefaultLightweightDummyActorSystem.ini` | no se envía como panel de configuración del comprador |
| Configuraciones de WarCollection / Lightning / puente UCM | adaptadores opcionales solo para el objetivo |

## Documentos relacionados

- [UserManual.md](UserManual.md)
- [QUICKSTART.md](QUICKSTART.md)
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md)
