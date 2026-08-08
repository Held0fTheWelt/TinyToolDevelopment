# Domande frequenti

## Cosa fa LightweightDummyActorSystem?

Fornisce un servizio di rappresentazione in runtime per i flussi di lavoro degli attori fittizi, inclusa la registrazione dei soggetti, la rappresentazione degli attori fittizi, le transizioni di promozione e demozione, la diagnostica, un ispettore dell'editor e un commandlet di convalida.

## È utilizzabile senza altri plugin Tiny Tool?

Sì. I moduli Runtime, Editor e DeveloperTool sono implementati come pacchetto core. Gli adattatori WarCollection, LightningCore, UCM, PIO e BPJ sono integrazioni opzionali specifiche per il target e non sono necessarie per il comportamento core fornito.

## Quali versioni del motore sono supportate?

La matrice di rilascio impacchettata mira a Unreal Engine 5.4 attraverso 5.8 su Win64, Linux e Mac, dove le liste consentite dei moduli permettono quelle piattaforme.

## Modifica autonomamente le risorse del progetto?

No. Il servizio core gestisce lo stato di rappresentazione e di transizione. Qualsiasi comportamento di mutazione specifico del progetto o degli adattatori dovrebbe essere esaminato nel flusso di lavoro del progetto proprietario.

## Dove posso ottenere supporto?

Utilizzare il link di supporto nella pagina del prodotto Fab.
