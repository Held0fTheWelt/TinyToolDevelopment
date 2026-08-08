# Manuale Utente

LightweightDummyActorSystem (LDAS) è un servizio di rappresentazione runtime autonomo per flussi di lavoro di dummy-actor. La versione MVP 1+2+3 include i moduli Runtime, Editor e DeveloperTool.

## Funzionalità Implementate

| Funzionalità | Tipi principali |
| --- | --- |
| Registrazione del soggetto | `ULDASWorldSubsystem::RegisterSubject`, `RegisterSubjectFromProfile`, `UnregisterSubject` |
| Query di prontezza | `QueryReadiness` → `FLDASReadinessReport` |
| Promozione / demozione | `RequestPromotion`, `RequestDemotion` con `ELDASTransitionReason` |
| Rappresentazione dummy | `ALDASLightweightDummyActor`, `ULDASDummyActorComponent` |
| Asset del profilo | `ULDASRepresentationProfile` |
| Diagnostica | `ULDASDiagnosticsSubsystem` |
| Ispezione dell'editor | `SLDASRepresentationInspector` |
| Validazione | `FLDASEditorValidationService`, `ULDASValidateContractsCommandlet` |

<!-- image slot: ldas-inspector -->

## Flusso Runtime

1. Ottenere `ULDASWorldSubsystem` dal mondo.
2. Registrare un soggetto con un descrittore o un `ULDASRepresentationProfile`.
3. Eseguire una query di prontezza per il tipo di rappresentazione desiderato.
4. Richiedere promozione o demozione quando la policy e la prontezza lo consentono.
5. Ispezionare la diagnostica / l'ispettore dell'editor durante l'indagine sui guasti.

Promozione e demozione sono vincolate da policy. I provider integrati (`ULDASBuiltInReadinessProvider`, `ULDASBuiltInPromotionPolicy`, `ULDASBuiltInHeavyActorAdapter`) forniscono il comportamento predefinito; i progetti possono registrare provider aggiuntivi nelle build supportate.

## Interfacce Editor

- Ispettore di rappresentazione per i soggetti registrati.
- Servizio di validazione dell'editor per i controlli dei contratti.
- Commandlet per lo sviluppatore per esecuzioni di validazione offline.

## Autarchia e Integrazioni Opzionali

I moduli Core Runtime / Editor / DeveloperTool funzionano senza plugin Tiny Tool peer. I seguenti rimangono **solo per target** e devono degradare in modo elegante in loro assenza:

- Adattatore pilota in sola lettura WarCollection
- Prova pilota multiplayer
- Bridge entity LightningCore
- Bridge di automazione UCM / PIO / BPJ

Non considerare questi adattatori come requisiti di configurazione per il core distribuito.

## Documenti Correlati

- [QUICKSTART.md](QUICKSTART.md)
- [SettingsReference.md](SettingsReference.md)
- [FAQ.md](FAQ.md)
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md)
- [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md)
