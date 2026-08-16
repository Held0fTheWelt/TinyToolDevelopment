<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/LightweightEditorMode/architecture.md -->
# FAQ (Domande frequenti)

Questa FAQ è scritta sia per gli acquirenti che per il supporto. Risponde alle domande che un utente probabilmente si porrà prima dell'acquisto, durante la prima configurazione e durante la convalida del comportamento di ripristino in un progetto reale.

## Risposte rapide

### Che cos'è Lightweight Editor Mode?

Lightweight Editor Mode è un plugin per l'editor di Unreal Engine che riduce temporaneamente il costo di rendering della viewport dell'editor tramite profili configurabili. È pensato per rendere più comoda la modifica di scene pesanti.

### Si tratta di un plugin di ottimizzazione a runtime?

No. Questo è uno strumento per il flusso di lavoro dell'editor. Non ottimizza il gioco pacchettizzato e non sostituisce il profiling a runtime o l'ottimizzazione dei contenuti.

### Influisce sulle build pacchettizzate?

No. Il plugin è riservato esclusivamente all'editor. Modifica lo stato della sessione dell'editor mentre lavori nell'editor di Unreal e non ha alcun effetto sui giochi pacchettizzati.

### Modifica il mio progetto in modo permanente?

No. La modalità è progettata come una sovrapposizione temporanea. Esegue un backup dei valori modificati e li ripristina quando viene disabilitata. Le impostazioni del profilo vengono salvate come impostazioni utente dell'editor, ma le mappe, gli asset e le impostazioni del renderer del progetto non vengono riscritte.

### A chi è rivolto?

È rivolto agli utenti di Unreal che lavorano in scene dell'editor molto pesanti: grandi mondi, mappe d'ambiente dense, scene ricche di Lumen, livelli ricchi di nebbia, grandi sezioni di foliage o progetti in cui la viewport dell'editor diventa lenta durante il lavoro quotidiano.

## Funzionalità e comportamento

### Cosa può modificare il plugin quando è abilitato?

A seconda del profilo selezionato, può:

- Ridurre la percentuale di schermo della viewport dell'editor.
- Ridurre la qualità di scalabilità globale.
- Disabilitare l'illuminazione indiretta diffusa Lumen.
- Disabilitare le riflessioni Lumen.
- Disabilitare le mappe d'ombra virtuali.
- Disabilitare la nebbia volumetrica e la nebbia regolare.
- Forzare le viewport dell'editor in modalità Unlit.
- Disabilitare il rendering in tempo reale nelle viewport dell'editor.

### Perché la viewport ha un aspetto peggiore quando la modalità è abilitata?

È il comportamento previsto. Il plugin scambia la fedeltà visiva con la reattività dell'editor. Usalo durante la modifica del layout, della struttura, del posizionamento o della logica dei Blueprint. Disabilitalo per l'illuminazione finale, i materiali, gli screenshot, le sequenze cinematografiche o l'approvazione visiva.

### Perché la viewport passa in modalità Unlit?

Alcuni profili forzano la modalità Unlit perché l'illuminazione può essere uno dei costi più elevati del rendering della viewport dell'editor. Puoi modificare qualsiasi profilo e disattivare bForceUnlitViewports se hai ancora bisogno del contesto dell'illuminazione.

### Perché il tempo reale si disattiva?

Alcuni profili disabilitano la modalità in tempo reale della viewport in modo che non continui a ridisegnarsi continuamente. Questo aiuta in scene pesanti o su computer portatili. Puoi disabilitare questo comportamento per ciascun profilo.

### Disabilita Nanite?

No. Il plugin non disabilita direttamente Nanite. Si concentra sulla percentuale di schermo della viewport dell'editor, sulla scalabilità, su Lumen, sulle ombre virtuali, sulla nebbia, sulla modalità di visualizzazione e sul comportamento in tempo reale della viewport.

### Sostituisce le impostazioni di scalabilità di Unreal?

No. Utilizza la scalabilità come parte di un flusso di lavoro dell'editor più ampio. La sola scalabilità di Unreal non copre ogni costo della viewport dell'editor, quindi il plugin controlla anche la percentuale di schermo specifica della viewport dell'editor, le CVar del renderer selezionate, la modalità di visualizzazione e il comportamento in tempo reale.

## Profili

### Quali profili sono inclusi?

Il plugin include quattro profili modificabili:

- Mild
- Balanced
- Aggressive
- Extreme

Balanced è il punto di partenza consigliato.

### Posso personalizzare i profili?

Sì. Apri Project Settings > Plugins > Lightweight Editor Mode. Ogni profilo ha i propri valori di qualità, percentuale di schermo, selettori di funzionalità e comportamenti della viewport.

### Posso cambiare profilo mentre la modalità è abilitata?

Sì. Il plugin aggiorna immediatamente le impostazioni attive e conserva i backup originali di prima dell'abilitazione della modalità. La disabilitazione ripristinerà comunque lo stato precedente all'attivazione anziché un profilo intermedio.

### Quale profilo dovrei usare?

Utilizza Mild quando hai ancora bisogno del contesto visivo. Utilizza Balanced per la modifica generale. Utilizza Aggressive per layout complessi, foliage o modifica di mondi. Utilizza Extreme quando hai bisogno della massima reattività e la fedeltà visiva non ha importanza.

## Ripristino e sicurezza

### Cosa viene ripristinato quando disabilito la modalità?

Durante la stessa sessione dell'editor, il plugin ripristina:

- I livelli di qualità della scalabilità salvati nel backup.
- I valori delle CVar salvati nel backup.
- Le modalità di visualizzazione della viewport modificate dal plugin.
- Gli stati in tempo reale della viewport modificati dal plugin.

### Cosa succede se l'editor si chiude mentre la modalità è abilitata?

La normale chiusura del modulo tenta di disabilitare la modalità. Se l'editor si arresta anomalamete o viene terminato in modo inaspettato, i backup in memoria vanno persi. Il plugin memorizza una modalità di visualizzazione di fallback per evitare di rimanere bloccato in Unlit dopo il riavvio, ma non può ricostruire ogni valore della singola sessione dopo una chiusura imprevista.

### Cosa succede se le viewport rimangono in modalità Unlit dopo un riavvio?

Apri la finestra Lightweight Editor Mode e fai clic su Disable Lightweight Mode. Se un backup della sessione non è disponibile, il plugin utilizza la modalità di visualizzazione di fallback memorizzata e riporta le viewport Unlit a una modalità non-Unlit ragionevole. Se necessario, puoi anche riportare manualmente la viewport in modalità Lit dal menu della viewport.

### Un altro plugin può sovrascrivere le stesse CVar?

Sì. Le CVar di Unreal possono essere modificate dalle configurazioni di progetto, dalla riga di comando, dai profili dispositivo, dalla scalabilità, da altri plugin e dal codice dell'editor. Lightweight Editor Mode utilizza una scrittura di CVar contrassegnata con priorità da plugin e ripristina i propri backup, ma una scrittura successiva da parte di un altro sistema può comunque prevalere.

### Perché le CVar mancanti non vengono trattate come errori?

Le funzionalità del renderer differiscono in base alla versione del motore, alle impostazioni del progetto, alla piattaforma e ai rami personalizzati del motore. Se una CVar non esiste, il plugin la salta e registra la situazione invece di far fallire l'intera modalità.

## Compatibilità

### Quale versione di Unreal Engine è supportata?

L'implementazione si rivolge alle API dell'editor e alle CVar del renderer in stile Unreal Engine 5.4. Convalida ogni versione del motore che intendi elencare come supportata, specialmente le versioni più recenti in cui le CVar del renderer potrebbero cambiare.

### Funziona con rami personalizzati del motore?

Dovrebbe funzionare se esistono le API dell'editor e le CVar richieste. Se un ramo personalizzato rinomina o rimuove CVar del renderer, quelle opzioni specifiche potrebbero essere saltate. Controlla il log di output per i dettagli.

### Funziona su Windows, Linux e Mac?

Il plugin è composto esclusivamente da codice sorgente C++ per l'editor ed evita codice a runtime specifico per piattaforma. Ciascuna piattaforma target dell'editor dovrebbe comunque essere compilata e testata prima di dichiarare il supporto ufficiale.

### Funziona nei commandlet?

Non è previsto alcun flusso di lavoro significativo per i commandlet. Il comportamento principale dipende dai client interattivi delle viewport dell'editor, dall'interfaccia Slate e dallo stato della sessione dell'editor.

## Flusso di lavoro

### Come lo apro?

Utilizza Tools > Performance > Lightweight Editor Mode nell'editor di Unreal.

### Come lo abilito automaticamente?

Spunta Enable on Editor startup nella finestra del plugin. Il plugin attende che esistano le viewport dell'editor, quindi applica il profilo corrente.

### Perché l'abilitazione all'avvio attende prima di applicare?

Durante l'avvio iniziale dei moduli, Unreal potrebbe non aver ancora creato i client delle viewport dell'editor. Il plugin utilizza un breve temporizzatore ed abilita la modalità non appena le viewport dell'editor sono disponibili, in modo da poter acquisire e modificare lo stato in modo affidabile.

### Dovrei lasciarlo abilitato tutto il giorno?

Puoi farlo, ma la migliore abitudine è abilitarlo per la reattività e disabilitarlo prima delle decisioni visive. Non valutare l'illuminazione finale, le ombre, la nebbia, i materiali o gli screenshot mentre la modalità è attiva.

### È utile se il mio collo di bottiglia è la compilazione degli shader o il controllo codice sorgente?

No. Il plugin è mirato al costo di rendering della viewport dell'editor. Non risolverà la compilazione degli shader, il caricamento degli asset, i ritardi del controllo codice sorgente, dischi lenti, scansioni antivirus o strumenti dell'editor personalizzati e complessi.

## Supporto

### Cosa dovrei includere in una richiesta di supporto?

Includi:

- Versione di Unreal Engine.
- Sistema operativo.
- Se il motore è standard o personalizzato.
- Profilo selezionato.
- Se il problema si è verificato all'abilitazione, al cambio di profilo, alla disabilitazione, all'avvio o dopo il riavvio.
- Righe del log di output contenenti "[Lightweight]".
- Qualsiasi altro plugin o script che modifichi le CVar del renderer.

### Dove posso verificare cosa ha fatto il plugin?

Apri il log di output di Unreal e cerca:

- [Lightweight]
- Backup CVar
- Restore CVar
- ApplyActiveSettings
- ApplyViewportSettings
- Lightweight mode ENABLED
- Lightweight mode DISABLED

### Qual è la regola d'uso più importante?

Utilizza Lightweight Editor Mode per la velocità di modifica. Disabilitalo per la verità visiva.
