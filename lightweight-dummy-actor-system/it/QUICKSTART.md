---
lang: it
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
# Avvio rapido

Questa guida installa **LightweightDummyActorSystem (LDAS)** e illustra la prima registrazione di un soggetto funzionante utilizzando l'API runtime fornita. Sono implementati MVP 1+2+3: core runtime, core di transizione, ispettore dell'editor e commandlet di validazione.

## Cosa avrai dopo questa guida

Il plugin abilitato e un soggetto registrato tramite `ULDASWorldSubsystem::RegisterSubject` / `RegisterSubjectFromProfile` con una query di prontezza ispezionabile.

## Requisiti

- Unreal Engine 5.4–5.8 (matrice pacchettizzata; Win64/Linux/Mac dove le liste bianche dei moduli lo consentono).
- Non è richiesto alcun altro plugin Tiny Tool per il pacchetto core.
- Nessun software di terze parti, account o runtime esterno. Vedi [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## 1. Installa e abilita

1. Ottieni **LightweightDummyActorSystem** da Fab e aggiungilo al progetto.
2. Apri **Modifica → Plugin**, abilita **LightweightDummyActorSystem** e riavvia quando richiesto.
3. Conferma che i moduli Runtime, Editor e DeveloperTool vengano caricati (`LightweightDummyActorSystem`, `LightweightDummyActorSystemEditor`, `LightweightDummyActorSystemDeveloper`).

## 2. Crea un profilo di rappresentazione

1. Nel Content Browser, crea un Data Asset di classe `ULDASRepresentationProfile`.
2. Imposta i campi del profilo radicato, ad esempio:

| Campo | Valore di esempio | Significato |
| --- | --- | --- |
| `PromoteDistance` | `2500.0` | Soglia di distanza utilizzata dagli input della politica di promozione. |
| `DemoteDistance` | `3000.0` | Soglia di distanza utilizzata dagli input della politica di demozione. |
| `PromotionCooldownSeconds` | `1.0` | Minimo di secondi tra le promozioni. |
| `bAllowRuntimePromotion` | `true` | Consente le richieste di promozione a runtime. |
| `bFailClosedOnPromotionFailure` | `false` | Quando true, il fallimento della promozione causa un fallimento chiuso. |
| `RequiredReadinessProviders` | (vuoto o provider nominati) | Provider di prontezza aggiuntivi richiesti prima della promozione. |

## 3. Esempio pratico: registra e interroga

Dal codice di gameplay o da un'utilità dell'editor che può raggiungere il subsystem del mondo:

```cpp
UWorld* World = /* mondo corrente */;
ULDASWorldSubsystem* LDAS = World->GetSubsystem<ULDASWorldSubsystem>();

FLDASSubjectId SubjectId;
// Compila i campi di SubjectId richiesti dal binding del tuo progetto.

FLDASRepresentationDescriptor Descriptor;
// Compila i campi del descriptor o usa RegisterSubjectFromProfile con il Data Asset.

const bool bRegistered = LDAS->RegisterSubjectFromProfile(SubjectId, ProfileAsset);
const FLDASReadinessReport Report = LDAS->QueryReadiness(
	SubjectId, ELDASRepresentationKind::Heavy /* o Dummy in base alla tua intenzione */);
```

## Risultato atteso

- `bRegistered` è true quando l'ID del soggetto viene accettato.
- `QueryReadiness` restituisce un `FLDASReadinessReport` il cui stato è `Ready`, `Warning` o uno stato bloccante con voci di problema — mai un successo silenzioso.

## 4. Convalida i contratti (opzionale)

Esegui il commandlet di validazione pacchettizzato `ULDASValidateContractsCommandlet` da un host dell'editor/commandlet per verificare la coerenza dei contratti per il progetto.

## Prossimi passi

- [UserManual.md](UserManual.md) — subsystems, actor, component, transizioni.
- [SettingsReference.md](SettingsReference.md) — proprietà del profilo e del componente.
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md) — fallimenti di prontezza e promozione.
