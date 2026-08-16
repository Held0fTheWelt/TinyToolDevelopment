<!-- doc-provenance: product-facts.yml reconciled 2026-07-19; source AKDB:plugins/BestPracticesJournal/architecture.md; release 1.1.2 -->
# Riferimento impostazioni

Le impostazioni di BPJ stabiliscono dove risiedono gli artefatti delle pratiche locali al progetto e come si comportano le proiezioni di archiviazione opzionali.

| Impostazione | Tipo | Predefinito | Effetto |
| --- | --- | --- | --- |
| `StorageBackend` | enum | `JsonArtifacts` | Seleziona artefatti JSON, modalità SQLite locale o un profilo studio basato su Postgres. |
| `StorageScope` | enum | `ProjectSaved` | Sceglie l'ambito di archiviazione progetto, utente, area di lavoro o personalizzato. |
| `StorageRootOverride` | path | vuoto | Sovrascrive la radice degli artefatti locali quando è richiesta una posizione personalizzata. |
| `WorkspaceStorageRoot` | path | vuoto | Punta BPJ a una radice condivisa di artefatti dell'area di lavoro. |
| `SQLiteDatabasePathOverride` | path | vuoto | Sovrascrive il percorso del file di database SQLite per la modalità professionale locale. |
| `SQLiteDatabaseFileName` | string | `bpj.sqlite` | Assegna il nome al file di database SQLite locale predefinito. |
| `PostgresConnectionProfileName` | string | definito dal profilo | Assegna il nome al profilo del bridge esterno utilizzato da una configurazione Postgres da studio. |
| `PostgresDsnEnvironmentVariable` | string | `BPJ_POSTGRES_DSN` | Assegna il nome alla variabile di ambiente utilizzata dagli strumenti del bridge esterno. |
| `bEnableJsonCompatibilityExport` | boolean | true | Mantiene disponibili le esportazioni JSON portabili anche quando è selezionata un'altra modalità di archiviazione. |
| `bEnableMarkdownProjection` | boolean | true | Scrive proiezioni Markdown leggibili per la revisione e la consegna. |
| `bEnableIisDerivedIndex` | boolean | true | Consente esportazioni di recupero derivate da IIS quando è presente un flusso di lavoro di indicizzazione opzionale. |
| `JournalSourceFolders` | path array | vuoto | Seleziona le directory locali contenenti journal di progetto o a singolo file che BPJ riconosce e visualizza sul posto. |

Mantieni i segreti all'esterno dei file di plugin distribuibili. BPJ non include un server di database né memorizza in modo permanente le credenziali dei provider.

## Sicurezza dell'archiviazione

Il backend predefinito `JsonArtifacts` garantisce che BPJ rimanga semplice e verificabile scrivendo file portabili sotto la radice di archiviazione selezionata. I profili SQLite e Postgres sono opzioni di archiviazione opzionali per flussi di lavoro professionali locali o da studio; non rendono un server di database parte del pacchetto del plugin.

Mantieni abilitato `bEnableJsonCompatibilityExport` quando gli strumenti a valle, i revisori o la CI necessitano di artefatti JSON stabili. Mantieni abilitato `bEnableMarkdownProjection` quando gli utenti umani necessitano di file di revisione e consegna leggibili.

## Valori predefiniti raccomandati

- Utilizza `JsonArtifacts` e `ProjectSaved` per il primo utilizzo e per la validazione di pacchetti sicuri per Fab.
- Imposta `StorageRootOverride` solo quando il progetto dispone di una directtiva rivista sugli artefatti locali.
- Mantieni abilitata la proiezione Markdown per la revisione di documenti ed esiti.
- Mantieni abilitata l'esportazione della compatibilità JSON quando è selezionato SQLite o Postgres.
- Tratta gli indici derivati da IIS come output derivati opzionali, non come archivio canonico di BPJ.

## Gestione dei dati

La radice di archiviazione selezionata può contenere percorsi di progetto, note di revisione, descrizioni di evidenze, dettagli sugli esiti di implementazione, percorsi dei report di validazione e metadati di provenienza. Esamina le esportazioni prima di inviarle all'esterno del progetto.
