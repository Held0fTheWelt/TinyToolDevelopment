# Documentación de LightweightDummyActorSystem

LightweightDummyActorSystem (LDAS) es un servicio de representación de tiempo de ejecución autónomo para flujos de trabajo de dummy-actor. MVP 1+2+3 incluye los módulos Runtime, Editor y DeveloperTool: registro de sujetos, consultas de disponibilidad, puertas de enlace de políticas de promoción/democión, representación de dummy actor, diagnóstico, inspector del editor y un commandlet de validación.

Público objetivo: ingenieros de gameplay y herramientas que necesitan representaciones ligeras de dummy con promoción/democión controlada por políticas, sin requerir plugins de Tiny Tool de pares para el paquete principal.

## Capacidades (incluidas)

- `RegisterSubject` / `RegisterSubjectFromProfile` / `UnregisterSubject`
- `QueryReadiness` → `FLDASReadinessReport`
- `RequestPromotion` / `RequestDemotion`
- `ULDASRepresentationProfile`, `ALDASLightweightDummyActor`, `ULDASDummyActorComponent`
- Inspector del editor y `ULDASValidateContractsCommandlet`

## Primeros pasos

1. Habilita el plugin — consulta el ejemplo práctico en [QUICKSTART.md](QUICKSTART.md) (registro + consulta de disponibilidad).
2. Configura un Data Asset `ULDASRepresentationProfile` con valores reales de distancia y tiempo de enfriamiento.
3. Lee [UserManual.md](UserManual.md) y [SettingsReference.md](SettingsReference.md).

## Archivos relacionados

- [../README.md](../README.md) — descripción general del producto.
- [../CHANGELOG.md](../CHANGELOG.md) — historial de versiones.
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md) · [FAQ.md](FAQ.md) · [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md)
