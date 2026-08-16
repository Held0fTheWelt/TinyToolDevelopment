<!-- doc-provenance: product-facts.yml reconciled 2026-07-01; source AKDB:plugins/AssetLoaderStudio/architecture.md -->
# Riferimento impostazioni

Le impostazioni di Asset Loader Studio sono incentrate su profili di governance, radici/classi consentite, criteri di audit e override di percorso.

## Impostazioni di governance

| Impostazione | Tipo | Predefinito | Effetto |
| --- | --- | --- | --- |
| `DefaultProfileId` | string | `guided_safe` | Seleziona il profilo di autorizzazione predefinito quando non viene fornito alcun profilo di percorso o richiesta. |
| `ProfileDirectories` | array | `Config/AssetLoaderStudio/Governance/Profiles` | Elenca le cartelle analizzate per i file JSON dei profili di autorizzazione. |
| `AllowedRoots` | array | `/Game`, `/Engine` | Limita i target di modifica alle radici Unreal approvate. |
| `AllowedClasses` | array | Predefinito del pacchetto | Limita i target di modifica a percorsi di classi approvati, se configurati. |
| `AuditRetentionDays` | integer | `30` | Controlla per quanto tempo i log di audit vengono conservati prima dell'eliminazione. |
| `AuditLogDirectory` | string | `Saved/AssetLoaderStudio/Audit` | Memorizza le voci di audit persistenti per le operazioni di anteprima e applicazione. |
| `bAuditPreviewOperations` | boolean | `true` | Scrive le voci di audit per le anteprime delle operazioni. |
| `bAuditApplyOperations` | boolean | `true` | Scrive le voci di audit per le operazioni di applicazione. |

## Campi del profilo di autorizzazione

I profili di autorizzazione definiscono `profile_id`, azioni consentite, numero massimo di asset/righe interessate, radici/classi consentite, modalità sola lettura, modalità dry-run, conferma applicazione, approvazione distruttiva e conservazione audit. Usa `read_only` per l'ispezione, `guided_safe` per modifiche riviste normali ed `expert` solo per operazioni collettive affidabili.

## Override di percorso

Gli override di percorso opzionali possono mappare un percorso UCM a un profilo più rigido o più flessibile. Gli override di percorso non sostituiscono i controlli locali di anteprima/applicazione; selezionano solo il profilo utilizzato da tali controlli.

## Valori predefiniti pratici

- Inizia con `guided_safe` per le attività di editor sottoposte a revisione.
- Mantieni `read_only` per la scoperta, la validazione, l'esportazione di tabelle e le verifiche automatizzate che non devono modificare gli asset.
- Usa `expert` solo per operazioni collettive affidabili e mantieni esplicita l'approvazione distruttiva.
- Mantieni la conservazione dell'audit sufficientemente alta da coprire la normale finestra di revisione dei rilasci.
