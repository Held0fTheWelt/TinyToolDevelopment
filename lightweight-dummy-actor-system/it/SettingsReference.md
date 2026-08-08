---
lang: it
title: LightweightDummyActorSystem Settings Reference
audience: [end_user]
owner_ref: plugin:LightweightDummyActorSystem
applies_to:
  component: LightweightDummyActorSystem
contract_ref: plugin:LightweightDummyActorSystem/profile-properties
version:
  since: "1.0"
---
# Riferimento alle impostazioni

LightweightDummyActorSystem **non** include un oggetto `UDeveloperSettings` / Preferenze del progetto. I valori configurabili sono presenti su Data Assets, componenti e struct come elencato di seguito (basati su header pubblici).

## ULDASRepresentationProfile (`UDataAsset`)

| Nome | Tipo | Default | Effetto |
| --- | --- | --- | --- |
| `Descriptor` | `FLDASRepresentationDescriptor` | vuoto | Descrittore di rappresentazione base applicato al record del soggetto. |
| `PromoteDistance` | `float` | `0.0` | Distanza di input utilizzata dalla politica di promozione. |
| `DemoteDistance` | `float` | `0.0` | Distanza di input utilizzata dalla politica di demozione. |
| `PromotionCooldownSeconds` | `float` | `1.0` | Tempo di attesa tra le promozioni. |
| `bAllowRuntimePromotion` | `bool` | `true` | Se falso, le richieste di promozione a runtime sono disconsentite dal profilo. |
| `bFailClosedOnPromotionFailure` | `bool` | `false` | Se vero, il fallimento della promozione causa un fallimento chiuso. |
| `RequiredReadinessProviders` | `TArray<FName>` | vuoto | Provider di prontezza nominati che devono essere soddisfatti. |

## ULDASDummyActorComponent

| Nome | Tipo | Default | Effetto |
| --- | --- | --- | --- |
| Campi di associazione profilo/soggetto | proprietà del componente editanywhere | impostato dal chiamante | Associa il componente alla rappresentazione del soggetto LDAS. |
| Snapshot replicato | proprietà replicata | runtime | Trasporta lo stato dello snapshot con notifica `OnRep`. |

## ALDASLightweightDummyActor

| Nome | Tipo | Default | Effetto |
| --- | --- | --- | --- |
| Componenti visibili | riferimenti ai componenti | costruiti | Componenti di rappresentazione di scena/debug. |
| Campo di binding LDAS | editanywhere | impostato dal chiamante | Collega l'attore ai dati del soggetto LDAS. |

## FLDASTransitionRecord / struct di snapshot

Le struct di transizione e snapshot espongono campi editanywhere per l'ID del soggetto, il tipo di rappresentazione, i timestamp e le liste degli errori di prontezza. Trattale come contratti dati piuttosto che come impostazioni globali; i default sono i default delle struct negli header sotto `Public/Structs/`.

## Cosa non è presente

| Superficie | Stato |
| --- | --- |
| `ULDASDeveloperSettings` | non ancora disponibile |
| Oggetto impostazioni `Config/DefaultLightweightDummyActorSystem.ini` | non distribuito come pannello delle impostazioni per acquirenti |
| Impostazioni di WarCollection / Lightning / bridge UCM | adattatori opzionali solo per il target |

## Documenti correlati

- [UserManual.md](UserManual.md)
- [QUICKSTART.md](QUICKSTART.md)
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md)
