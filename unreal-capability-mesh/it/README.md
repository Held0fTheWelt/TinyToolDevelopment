<!-- doc-provenance: AKDB:plugins/UnrealCapabilityMesh/architecture.md; docs/architecture/plugins/UnrealCapabilityMesh/product-facts.yml; reconciled 2026-07-19 -->
# Documentazione di Unreal Capability Mesh

Questa cartella documenta il plugin Unreal Capability Mesh per Unreal Engine 5.4+, la configurazione del progetto, l'integrazione e la lettura del codice sorgente.

Pagina prodotto Fab: https://www.fab.com/listings/fd186d26-cdcf-4c4f-93d4-50e437b7673e

## Inizia qui

| Documento | Scopo |
| --- | --- |
| [BUYER_GUIDE.md](BUYER_GUIDE.md) | Ambito del prodotto, moduli inclusi, cosa fa e cosa non fa UCM. |
| [QUICKSTART.md](QUICKSTART.md) | Flusso di configurazione minimo dai manifesti ai report generati. |
| [UserManual.md](UserManual.md) | Flusso di lavoro del pannello di controllo e procedura operativa normale. |
| [TechnicalOverview.md](TechnicalOverview.md) | Architettura, flusso di dati, posizioni di archiviazione e diagnostica. |
| [CodeDocumentation.md](CodeDocumentation.md) | Guida alla lettura del codice sorgente C++ per modulo e classe. |
| [SettingsReference.md](SettingsReference.md) | Struttura cartelle manifesti, campi profilo progetto, campi criteri, percorsi di output. |
| [INTEGRATION.md](INTEGRATION.md) | Come collegare un altro plugin tramite manifesti o adattatori. |
| [TROUBLESHOOTING.md](TROUBLESHOOTING.md) | Problemi comuni di validazione, individuazione, percorsi e invocazione. |
| [FAQ.md](FAQ.md) | Risposte brevi per acquirenti e revisori. |
| [ReleaseChecklist.md](ReleaseChecklist.md) | Checklist di conformità Fab e di pacchettizzazione. |
| [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md) | Dichiarazione sui software di terze parti. |

## Concetto chiave

UCM è un hub neutrale. Non conosce specifici plugin partner nel codice C++. UCM stesso, i plugin provider abilitati e il progetto possono descrivere ciascuno funzionalità (capabilities), endpoint, schemi, regole, percorsi (routes), trasformazioni e adattatori in JSON. Il loader unisce queste radici di configurazione in ordine di priorità, costruisce i registri, valuta le regole di sicurezza e scrive i report.

L'attuale configurazione del progetto utilizza UCM come strato di integrazione primario tra i prodotti Tiny Tool Development. Il comportamento specifico del prodotto rimane nel plugin proprietario sotto forma di endpoint richiamabili tramite JSON o contratti di file; UCM carica solo la configurazione che li connette. I Freebie Bridges sono plugin di riserva/riferimento opzionali per team privi di UCM, non il modello di connessione predefinito.

## Percorsi importanti

```text
<EnabledPlugin>/Config/UnrealCapabilityMesh/  ← manifesti in sola lettura di proprietà del provider
Config/UnrealCapabilityMesh/                   ← override opzionali di proprietà del progetto e percorsi composti
Saved/UnrealCapabilityMesh/                    ← report generati e output dei percorsi
```

Non copiare i manifesti di un provider nel progetto al solo scopo di esporne i percorsi. Abilita il plugin provider e ricarica la configurazione. Crea un override di progetto solo quando il progetto modifica intenzionalmente i campi del profilo o possiede un percorso composto.
