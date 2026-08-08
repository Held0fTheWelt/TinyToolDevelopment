# Documentazione di LightweightDummyActorSystem

LightweightDummyActorSystem (LDAS) è un servizio di rappresentazione runtime autonomo per flussi di lavoro con dummy-actor. La versione MVP 1+2+3 include i moduli Runtime, Editor e DeveloperTool: registrazione dei soggetti, query di prontezza, criteri di promozione/declassamento, rappresentazione del dummy actor, diagnostica, ispettore dell'editor e un commandlet di validazione.

Destinatari: ingegneri di gameplay e strumenti che necessitano di rappresentazioni leggere dei dummy con criteri di promozione/declassamento, senza richiedere plugin Tiny Tool peer per il pacchetto principale.

## Funzionalità (incluse)

- `RegisterSubject` / `RegisterSubjectFromProfile` / `UnregisterSubject`
- `QueryReadiness` → `FLDASReadinessReport`
- `RequestPromotion` / `RequestDemotion`
- `ULDASRepresentationProfile`, `ALDASLightweightDummyActor`, `ULDASDummyActorComponent`
- Ispettore dell'editor e `ULDASValidateContractsCommandlet`

## Introduzione

1. Abilita il plugin — vedi l'esempio pratico in [QUICKSTART.md](QUICKSTART.md) (registrazione + query di prontezza).
2. Configura un Data Asset `ULDASRepresentationProfile` con valori reali di distanza e cooldown.
3. Leggi [UserManual.md](UserManual.md) e [SettingsReference.md](SettingsReference.md).

## File correlati

- [../README.md](../README.md) — panoramica del prodotto.
- [../CHANGELOG.md](../CHANGELOG.md) — cronologia delle release.
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md) · [FAQ.md](FAQ.md) · [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md)
