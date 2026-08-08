# Manual del usuario

LightweightDummyActorSystem (LDAS) es un servicio de representación de tiempo de ejecución autónomo para flujos de trabajo de dummy-actor. MVP 1+2+3 incluye los módulos Runtime, Editor y DeveloperTool.

## Capacidades implementadas

| Capacidad | Tipos principales |
| --- | --- |
| Registro de sujeto | `ULDASWorldSubsystem::RegisterSubject`, `RegisterSubjectFromProfile`, `UnregisterSubject` |
| Consulta de disponibilidad | `QueryReadiness` → `FLDASReadinessReport` |
| Promoción / degradación | `RequestPromotion`, `RequestDemotion` con `ELDASTransitionReason` |
| Representación dummy | `ALDASLightweightDummyActor`, `ULDASDummyActorComponent` |
| Activo de perfil | `ULDASRepresentationProfile` |
| Diagnósticos | `ULDASDiagnosticsSubsystem` |
| Inspector del editor | `SLDASRepresentationInspector` |
| Validación | `FLDASEditorValidationService`, `ULDASValidateContractsCommandlet` |

<!-- image slot: ldas-inspector -->

## Flujo de tiempo de ejecución

1. Obtenga `ULDASWorldSubsystem` del mundo.
2. Registre un sujeto con un descriptor o un `ULDASRepresentationProfile`.
3. Consulte la disponibilidad para el tipo de representación deseado.
4. Solicite promoción o degradación cuando la política y la disponibilidad lo permitan.
5. Inspeccione los diagnósticos / inspector del editor al investigar fallos.

La promoción y la degradación están controladas por políticas. Los proveedores integrados (`ULDASBuiltInReadinessProvider`, `ULDASBuiltInPromotionPolicy`, `ULDASBuiltInHeavyActorAdapter`) proporcionan el comportamiento predeterminado; los proyectos pueden registrar proveedores adicionales en compilaciones compatibles.

## Interfaces del editor

- Inspector de representación para sujetos registrados.
- Servicio de validación del editor para comprobaciones de contrato.
- Commandlet del desarrollador para ejecuciones de validación fuera de línea.

## Autarquía e integraciones opcionales

Los módulos Core Runtime / Editor / DeveloperTool funcionan sin plugins de Tiny Tool pares. Los siguientes permanecen como **solo para objetivos** y deben degradarse elegantemente cuando estén ausentes:

- Adaptador piloto de solo lectura de WarCollection
- Prueba piloto de multijugador
- Puente de entidades de LightningCore
- Puentes de automatización UCM / PIO / BPJ

No trate estos adaptadores como requisitos de configuración para el núcleo entregado.

## Documentos relacionados

- [QUICKSTART.md](QUICKSTART.md)
- [SettingsReference.md](SettingsReference.md)
- [FAQ.md](FAQ.md)
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md)
- [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md)
