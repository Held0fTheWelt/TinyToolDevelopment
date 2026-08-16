<!-- doc-provenance: product-facts.yml reconciled 2026-07-01; source AKDB:plugins/AssetLoaderStudio/architecture.md -->
# Manuale utente di Asset Loader Studio

Aprire lo spazio di lavoro da **Tiny Tools -> Asset Loader Studio -> Asset Loader Studio**.

Asset Loader Studio è strutturato attorno a un unico ciclo di revisione: ispezionare, convalidare, anteprima, applicare, verificare. È possibile interrompere l'operazione in fase di ispezione o continuare con le modifiche governate, se il profilo di autorizzazione attivo lo consente.

Lo spazio di lavoro contiene sette visualizzazioni:

- **Graph** mostra i nodi di asset, riga, campo, riferimento e diagnostica.
- **Table** mostra le righe di DataAsset/DataTable consapevoli dello schema e i campi modificabili.
- **Validation** spiega i riferimenti mancanti, i percorsi non validi, gli ID duplicati e i blocchi di autorizzazione.
- **Jobs** mostra lo stato dell'ultima richiesta di caricamento in fase di runtime.
- **Inspector** mostra la modalità attiva, il profilo di autorizzazione, l'ultima anteprima e l'ultimo rapporto di applicazione.
- **History** conserva le azioni recenti dello spazio di lavoro.
- **Governance** mostra il profilo attivo, le sovrascrizioni del percorso, lo stato di verifica e le azioni del profilo.

Le modalità controllano l'autorità di modifica:

- **Simple** utilizza il profilo di sola lettura.
- **Guided** consente modifiche in fasi sicure con approvazione.
- **Expert** consente anteprime più ampie di operazioni bulk/persist e richiede comunque l'approvazione prima dell'applicazione.

Utilizzare **Inspect** dopo aver inserito un percorso completo dell'oggetto, ad esempio `/Game/Data/DT_Items.DT_Items`. Utilizzare gli input Row, Field e New Value per anteprimare un aggiornamento strutturato del campo. **Apply** esegue solo l'ultima anteprima approvata e contrassegna i pacchetti modificati come "sporchi" per un salvataggio esplicito.

## Ciclo di revisione

1. Ispezionare l'asset di origine.
2. Verificare lo stato della graph/table e le diagnostica.
3. Selezionare un profilo che corrisponda al livello di autorità necessario.
4. Anteprimere l'operazione e verificare i target, l'hash del piano, i conteggi degli elementi interessati, il rischio e le indicazioni di recupero.
5. Applicare solo l'anteprima appena revisionata.
6. Ispezionare il rapporto di applicazione e la cronologia di verifica.
7. Salvare manualmente i pacchetti sporchi dopo la revisione.
