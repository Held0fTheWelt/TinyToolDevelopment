<!-- doc-provenance: AKDB:plugins/SmartContentDiet/architecture.md; docs/architecture/plugins/SmartContentDiet/product-facts.yml; reconciled 2026-07-16 -->
# FAQ

**Smart Content Diet richiede AI, un account o un altro plugin?**
No. Il ciclo principale (scansione → revisione → applicazione di correzioni sicure → nuova scansione → misurazione) viene eseguito interamente nell'editor
senza alcun servizio AI, account o plugin di terze parti. Sono disponibili percorsi opzionali nell'ecosistema tramite **Unreal Capability
Mesh (UCM)**, ma non sono mai obbligatori.

**È sicuro da eseguire?**
La scansione e l'anteprima sono in sola lettura. L'applicazione di correzioni, riduzioni, spostamenti o eliminazioni **modifica le risorse del progetto** — effettuarle solo in uno spazio di lavoro con backup, sotto controllo di versione e eliminabile. I percorsi di modifica sono di default vincolati all'approvazione. Utilizzare a proprio rischio.

**Quali versioni del motore sono supportate?**
Unreal Engine 5.4+. Si tratta di un plugin per l'editor.

**Qual è la differenza tra scansioni Quick Safe, Full e Deep?**
Quick Safe utilizza solo registro/metadata (senza caricamento delle risorse, veloce). Full carica le risorse per trovare mesh, texture e materiali su cui agire. Deep aggiunge metriche approfondite su materiali e mesh statiche ed è la più lenta.

**Perché non riesco a vedere le schede Preset o Governance?**
Sono schede avanzate (Ingegnere / Produttore). Cambiare ruolo nelle Impostazioni o nell'intestazione.

**Posso eseguirlo in CI / headless?**
Sì. Un commandlet supporta `-QuickSafe` / `-FullScan` / `-DeepScan`, `-OptimizationQueueReport` e
`-ApplySafeQueue` (applica solo su progetti con backup).

**Include software di terze parti?**
No. Vedi [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

**Dove posso ottenere supporto?**
Utilizzare il link di supporto nella pagina del prodotto Fab.
