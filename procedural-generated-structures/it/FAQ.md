<!-- doc-provenance: AKDB:plugins/ProceduralGeneratedStructures/architecture.md; docs/architecture/plugins/ProceduralGeneratedStructures/product-facts.yml; reconciled 2026-06-21 -->
# FAQ

**Questo plugin richiede altri plugin?**
No. Funziona in modo del tutto autonomo.

**Include mesh?**
No. L'utente fornisce i propri asset `UStaticMesh`; il plugin si occupa di istanziarli.

**Quali versioni dell'engine sono supportate?**
Unreal Engine 5.4+ (Win64, Linux, Mac). Il modulo è Runtime, quindi l'actor funziona nell'editor e nei giochi pacchettizzati.

**Include software di terze parti, Python o modelli di IA?**
No. Vedere [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

**Qual è la differenza tra istanze esplicite e generazione di righe?**
Le istanze esplicite sono trasformazioni esatte (spesso catturate da componenti esistenti) e vengono riprodotte così come sono. La generazione di righe crea proceduralmente istanze dai conteggi delle righe e dalle trasformazioni di movimento per dimensione definite sull'asset di dati.

**Posso eseguire la build in runtime, non solo nell'editor?**
Sì. L'actor è pronto per il runtime e può eseguire la build in modo sincrono o attraverso i tick (`bUseAsyncBuild`).

**Come posso evitare cali di frame su strutture grandi?**
Abilitare `bUseAsyncBuild` e regolare `InstancesPerFrame`.

**Posso antevedere cosa farà una rigenerazione prima di modificare i componenti?**
Sì. Utilizzare `GetBuildPlan` o il percorso di anteprima di rigenerazione. Il piano riporta i componenti di destinazione, i problemi bloccanti, l'intenzione di mutazione e i conteggi esatti delle istanze dopo la potatura.

**Gli strumenti possono mostrare il progresso della build asincrona?**
Sì. `GetEstimatedBuildInstanceCount`, `GetAddedBuildInstanceCount` e `GetBuildProgress` espongono il progresso per gli strumenti dell'editor, i Blueprint e i percorsi di automazione.

**Dove posso segnalare problemi o ricevere supporto?**
Utilizzare il link di supporto presente sulla pagina del prodotto su Fab.
