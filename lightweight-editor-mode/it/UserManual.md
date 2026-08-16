<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/LightweightEditorMode/architecture.md -->
# Manuale utente

Questo manuale spiega come utilizzare Lightweight Editor Mode nel lavoro quotidiano all'interno dell'editor di Unreal Engine.

## Scopo

Le scene di grandi dimensioni in Unreal Engine possono rendere le viewport dell'editor molto dispendiose, anche quando le prestazioni finali del gioco sono accettabili. Risoluzione elevata della viewport, Lumen, ombre virtuali, nebbia volumetrica, aggiornamento continuo della viewport in tempo reale e livelli di scalabilità elevati possono consumare tempo di calcolo prezioso durante le modifiche.

Lightweight Editor Mode offre un selettore rapido per attivare un profilo di modifica temporaneo e reversibile. È particolarmente utile quando hai bisogno di reattività per il layout, il blocking, il lavoro con i Blueprint, il foliage, il posizionamento degli asset o la pulizia del progetto.

## Aprire la finestra

1. Apri l'editor di Unreal Engine.
2. Assicurati che il plugin Lightweight Editor Mode sia abilitato.
3. Seleziona Tools > Performance > Lightweight Editor Mode.
4. Il plugin aprirà una scheda ancorabile nell'editor.

La scheda contiene un menu a discesa per i profili, un pulsante di attivazione e una casella di controllo opzionale per l'avvio.

## Scegliere un profilo

Il profilo controlla quanto aggressivamente l'editor riduce il costo di rendering.

### Mild

Mild è destinato a progetti che necessitano solo di un piccolo incremento di prestazioni. Mantiene il comportamento della viewport più vicino alla norma ed è un'ottima prima scelta quando si necessita ancora del contesto visivo.

Comportamento tipico:

- Percentuale di schermo (Screen Percentage) più elevata.
- Scalabilità più alta rispetto ai profili aggressivi.
- Non forza la modalità Unlit per impostazione predefinita.
- Non disabilita la modalità in tempo reale della viewport per impostazione predefinita.

### Balanced

Balanced è l'impostazione predefinita consigliata. Riduce l'illuminazione dispendiosa e i costi della viewport rimanendo al contempo pratico per la modifica generale.

Comportamento tipico:

- Percentuale di schermo media.
- Scalabilità complessiva inferiore.
- Disabilita funzionalità di rendering dispendiose.
- Forza la modalità Unlit e disabilita il tempo reale per impostazione predefinita.

### Aggressive

Aggressive è pensato per scene pesanti in cui la reattività della viewport conta più della fedeltà visiva.

Comportamento tipico:

- Percentuale di schermo più bassa.
- Scalabilità bassa.
- Illuminazione, ombre e nebbia dispendiose disabilitate.
- Viewport forzate in modalità Unlit.
- Aggiornamento della viewport in tempo reale disabilitato.

### Extreme

Extreme è pensato per progetti sovraccarichi, lavoro su laptop, grandi mondi o esigenze di reattività d'emergenza. Usalo quando hai bisogno solo della struttura della scena e della velocità di interazione.

Comportamento tipico:

- Percentuale di schermo molto bassa.
- Scalabilità minima.
- Funzionalità di rendering dispendiose disabilitate.
- Viewport in modalità Unlit e modifiche non in tempo reale.

## Abilitare la modalità

1. Seleziona un profilo.
2. Fai clic su Enable Lightweight Mode.
3. Il plugin applicherà il profilo attivo.
4. Le viewport si aggiorneranno immediatamente.

Quando abilitato, il plugin esegue il backup dello stato originale dell'editor necessario al ripristino:

- Livelli di qualità della scalabilità.
- Valori delle variabili di console modificate.
- Modalità di visualizzazione delle viewport, quando viene forzata la modalità Unlit.
- Sovrascritture temporanee della modalità in tempo reale.

## Modificare il profilo mentre la modalità è attiva

Puoi scegliere un altro profilo mentre la modalità è già attiva. Il plugin aggiorna le impostazioni attive e mantiene i backup originali precedenti all'abilitazione della modalità. Ciò significa che Disable Lightweight Mode ripristinerà comunque lo stato precedente all'attivazione anziché il profilo intermedio.

## Disabilitare la modalità

Fai clic su Disable Lightweight Mode per ripristinare lo stato dell'editor.

Il plugin ripristina:

- Livelli di scalabilità salvati nel backup.
- Le sovrascritture delle variabili di console del plugin. Se un altro sistema ha modificato lo stesso valore mentre la modalità era attiva, verrà mantenuto quel valore più recente.
- Modalità di visualizzazione della viewport salvate nel backup.
- Sovrascritture temporanee del tempo reale.

Se l'editor è stato riavviato prima della disabilitazione della modalità, i backup per sessione non esistono più. In tal caso, il plugin utilizza la modalità di visualizzazione di fallback memorizzata nelle impostazioni ed esegue solo un ripristino conservativo della viewport. Quando viene rilevato questo stato non aggiornato, il pulsante mostra Restore Lightweight State.

## Abilitare all'avvio dell'editor (Enable on Editor startup)

La casella di controllo Enable on Editor startup memorizza un'impostazione utente. Quando abilitata, il plugin attende che le viewport dell'editor esistano e quindi abilita automaticamente Lightweight Editor Mode.

Questo comportamento di avvio ritardato è intenzionale. Durante l'avvio iniziale dei moduli, Unreal potrebbe non aver ancora creato i client delle viewport dell'editor, quindi le modifiche immediate verrebbero perse. Il plugin utilizza un breve temporizzatore ed abilita la modalità non appena l'editor è pronto.

Se l'avvio automatico si esegue dopo che una sessione precedente si è conclusa prima che la modalità venisse disabilitata, il plugin esegue prima il ripristino conservativo della viewport e poi abilita nuovamente il profilo selezionato.

## Flussi di lavoro consigliati

### Level blocking

Utilizza Balanced o Aggressive. Di solito non necessiti dell'illuminazione finale durante la definizione degli spazi, la verifica della navigazione o lo spostamento di grandi gruppi di actor.

### Modifica di foliage o mondi

Utilizza Aggressive. Le scene con molto foliage possono essere dispendiose nella vista Lit con ombre e aggiornamenti in tempo reale.

### Iterazione su Blueprint o Gameplay

Utilizza Mild o Balanced. Mantiene un contesto visivo sufficiente rendendo al contempo la risposta dell'editor più confortevole.

### Revisione dell'illuminazione

Disabilita Lightweight Editor Mode. Il plugin nasconde o riduce intenzionalmente le funzionalità di illuminazione, pertanto non è adatto per l'approvazione visiva finale.

### Acquisizione cinematografica o screenshot

Disabilita Lightweight Editor Mode, ripristina la scalabilità di produzione e rivedi l'inquadratura nella modalità viewport prevista.

## Project Settings

Apri Project Settings > Plugins > Lightweight Editor Mode per modificare i profili e i valori attivi.

Le strutture del profilo costituiscono la fonte di verità per Mild, Balanced, Aggressive ed Extreme. I valori attivi sono ciò che il runtime applica quando la modalità è abilitata. L'interfaccia utente copia il profilo selezionato nei valori attivi prima di applicare la modalità.

## COSA ASPETTARSI VISIVAMENTE

A seconda del profilo, la viewport potrebbe diventare:

- A risoluzione inferiore.
- Non illuminata (Unlit).
- Meno dettagliata.
- Con meno ombre.
- Senza nebbia.
- Non aggiornata in tempo reale finché non si interagisce o si aggiorna manualmente.

Questo è il comportamento previsto. L'obiettivo è la velocità di interazione, non la qualità di rendering finale.

## Cosa non fa il plugin

- Non modifica le impostazioni di esecuzione nei giochi pacchettizzati.
- Non modifica in modo permanente le impostazioni del renderer del progetto.
- Non sovrascrive in modo permanente gli asset delle mappe.
- Non sostituisce il lavoro di scalabilità di Unreal, LOD, HLOD, Nanite o di ottimizzazione dei contenuti.
- Non garantisce risultati identici tra tutte le versioni del motore e fork personalizzati del renderer.

## Abitudine pratica

Utilizza Lightweight Editor Mode come modalità di lavoro temporanea. Disabilitalo prima della revisione finale, prima di segnalare bug di rendering e prima di scattare screenshot di produzione o per il marketplace.
