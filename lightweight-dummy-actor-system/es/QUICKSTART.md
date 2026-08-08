---
lang: es
title: LightweightDummyActorSystem Quick Start
audience: [end_user]
owner_ref: plugin:LightweightDummyActorSystem
applies_to:
  component: LightweightDummyActorSystem
preconditions:
  - Unreal Engine project open with the plugin package available
  - Edit > Plugins can enable LightweightDummyActorSystem
expected_result:
  text: Subject registers through ULDASWorldSubsystem and QueryReadiness returns a readiness report.
version:
  since: "1.0"
---
# Inicio rápido

Esta guía instala **LightweightDummyActorSystem (LDAS)** y muestra el registro del primer sujeto funcional utilizando la API de tiempo de ejecución proporcionada. Se implementa MVP 1+2+3: núcleo de tiempo de ejecución, núcleo de transición, inspector del editor y commandlet de validación.

## Qué tendrás después de seguir esta guía

El plugin habilitado y un sujeto registrado a través de `ULDASWorldSubsystem::RegisterSubject` / `RegisterSubjectFromProfile` con una consulta de disponibilidad que puedes inspeccionar.

## Requisitos

- Unreal Engine 5.4–5.8 (paquete matricial; Win64/Linux/Mac donde las listas permitidas del módulo lo permitan).
- No se requiere ningún otro plugin de Tiny Tool para el paquete principal.
- No se necesita software de terceros, cuenta ni tiempo de ejecución externo. Consulta [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## 1. Instalar y habilitar

1. Obtén **LightweightDummyActorSystem** de Fab y añádelo al proyecto.
2. Abre **Editar → Plugins**, habilita **LightweightDummyActorSystem** y reinicia cuando se te solicite.
3. Confirma que se cargan los módulos Runtime, Editor y DeveloperTool (`LightweightDummyActorSystem`, `LightweightDummyActorSystemEditor`, `LightweightDummyActorSystemDeveloper`).

## 2. Crear un perfil de representación

1. En el Content Browser, crea un Data Asset de la clase `ULDASRepresentationProfile`.
2. Establece los campos del perfil base, por ejemplo:

| Campo | Valor de ejemplo | Significado |
| --- | --- | --- |
| `PromoteDistance` | `2500.0` | Umbral de distancia utilizado por las entradas de la política de promoción. |
| `DemoteDistance` | `3000.0` | Umbral de distancia utilizado por las entradas de la política de degradación. |
| `PromotionCooldownSeconds` | `1.0` | Mínimo de segundos entre promociones. |
| `bAllowRuntimePromotion` | `true` | Permite solicitudes de promoción en tiempo de ejecución. |
| `bFailClosedOnPromotionFailure` | `false` | Cuando es true, el fallo de promoción provoca un fallo cerrado. |
| `RequiredReadinessProviders` | (vacío o proveedores con nombre) | Proveedores de disponibilidad adicionales requeridos antes de la promoción. |

## 3. Ejemplo práctico: Registrar y consultar

Desde código de juego o una utilidad de editor que pueda acceder al subsystem del mundo:

```cpp
UWorld* World = /* mundo actual */;
ULDASWorldSubsystem* LDAS = World->GetSubsystem<ULDASWorldSubsystem>();

FLDASSubjectId SubjectId;
// Rellena los campos de SubjectId requeridos por la vinculación de tu proyecto.

FLDASRepresentationDescriptor Descriptor;
// Rellena los campos del descriptor o utiliza RegisterSubjectFromProfile con el Data Asset.

const bool bRegistered = LDAS->RegisterSubjectFromProfile(SubjectId, ProfileAsset);
const FLDASReadinessReport Report = LDAS->QueryReadiness(
	SubjectId, ELDASRepresentationKind::Heavy /* o Dummy según tu intención */);
```

## Resultado esperado

- `bRegistered` es true cuando se acepta el id del sujeto.
- `QueryReadiness` devuelve un `FLDASReadinessReport` cuyo estado es `Ready`, `Warning` o un estado bloqueante con entradas de problemas — nunca un éxito silencioso.

## 4. Validar contratos (opcional)

Ejecuta el commandlet de validación empaquetado `ULDASValidateContractsCommandlet` desde un host de editor/commandlet para comprobar la consistencia de los contratos del proyecto.

## Próximos pasos

- [UserManual.md](UserManual.md) — subsystems, actor, component, transitions.
- [SettingsReference.md](SettingsReference.md) — profile and component properties.
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md) — readiness and promotion failures.
