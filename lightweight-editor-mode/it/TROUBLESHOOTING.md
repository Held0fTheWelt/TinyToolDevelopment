<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/LightweightEditorMode/architecture.md -->
# Risoluzione dei problemi

Questa guida copre i problemi comuni e le cause probabili.

## La finestra del plugin non compare

Verifica quanto segue:

- Il plugin è abilitato in Edit > Plugins.
- Il progetto è stato riavviato dopo l'abilitazione del plugin.
- Il modulo è elencato nell'array Plugins nel file .uproject.
- Stai eseguendo l'editor e non un commandlet.

La finestra dovrebbe apparire sotto Tools > Performance > Lightweight Editor Mode.

## La modalità non si abilita all'avvio

L'abilitazione all'avvio attende che esistano i client delle viewport dell'editor. In un progetto complesso questo può richiedere qualche istante dopo l'avvio del modulo.

Verifica:

- Enable on Editor startup sia selezionato.
- Il plugin sia abilitato nel progetto.
- L'editor abbia effettivamente creato le viewport del level editor.
- I log contengano "Scheduling Lightweight Mode auto-enable".
- I log contengano successivamente "Auto-enabling Lightweight Mode after editor viewports became available".

Se l'impostazione viene deselezionata prima che le viewport diventino disponibili, il temporizzatore si annulla automaticamente.

## La percentuale di schermo sembra invariata

Le viewport dell'editor non seguono sempre r.ScreenPercentage. Lightweight Editor Mode utilizza CVar di viewport specifiche per l'editor:

- r.Editor.Viewport.ScreenPercentage
- r.Editor.Viewport.ScreenPercentageMode.RealTime
- r.Editor.Viewport.ScreenPercentageMode.NonRealTime

Se la viewport sembra ancora invariata, verifica:

- Il valore ScreenPercentage del profilo selezionato.
- Se la viewport sta utilizzando un percorso del motore che sovrascrive la percentuale di schermo.
- Se un altro plugin o comando di console modifica le stesse CVar dell'editor dopo l'esecuzione di Lightweight Editor Mode.

## Le viewport rimangono in modalità Unlit dopo la disabilitazione

Il ripristino nella stessa sessione utilizza i backup per ciascuna viewport. Il ripristino al riavvio ha solo il valore salvato LastViewModeBeforeLightweight.

Prova a:

1. Aprire la finestra del plugin.
2. Fare clic su Disable Lightweight Mode.
3. Se necessario, riportare manualmente la viewport in modalità Lit.
4. Riabilitare e disabilitare la modalità nella stessa sessione per confermare il normale ripristino.

Se questo accade spesso, verifica se l'editor viene chiuso mentre la modalità è ancora abilitata.

Dopo un arresto anomalo o una chiusura forzata, il pulsante principale potrebbe mostrare Restore Lightweight State. Fai clic su di esso per eseguire il ripristino conservativo della viewport e cancellare il marcatore di sessione non aggiornato.

## La modalità in tempo reale rimane disabilitata

La disabilitazione del tempo reale utilizza il sistema di sovrascrittura temporanea in tempo reale di Unreal. Nella stessa sessione dell'editor, Disable rimuove la sovrascrittura di Lightweight invece di modificare le preferenze salvate in tempo reale della viewport.

Se il tempo reale risulta ancora disabilitato, verifica se un altro sistema dell'editor ha una propria sovrascrittura in tempo reale attiva. Riabilita manualmente la modalità in tempo reale dal menu della viewport se necessario.

## Lumen risulta ancora abilitato

Verifica se:

- Il profilo selezionato ha bDisableLumen abilitato.
- Il progetto utilizza effettivamente Lumen.
- Un altro plugin o codice di progetto imposta le CVar di Lumen dopo l'abilitazione della modalità.
- Un ramo del motore personalizzato ha rinominato o rimosso le CVar rilevanti.

Il plugin si rivolge a:

- r.Lumen.DiffuseIndirect.Allow
- r.Lumen.Reflections.Allow

Le CVar mancanti vengono ignorate e registrate nel log a livello Verbose.

## Le ombre risultano ancora dispendiose

bDisableVirtualShadows si rivolge alle mappe d'ombra virtuali (Virtual Shadow Maps):

- r.Shadow.Virtual.Enable

Questo non disabilita ogni possibile costo di ombreggiatura in ogni percorso di rendering. Se la tua scena utilizza ombre non virtuali, sistemi di ombre personalizzati, ombre con ray tracing o rendering tramite plugin, potrebbero essere necessarie ulteriori regolazioni specifiche per il progetto.

## La nebbia appare ancora

bDisableVolumetricFog imposta:

- r.VolumetricFog = 0
- r.Fog = 0

Alcuni materiali, volumi di post-processing, sistemi di cielo o effetti atmosferici personalizzati potrebbero comunque creare un aspetto simile alla nebbia.

## L'editor ha un aspetto visivo troppo scadente

Utilizza un profilo meno aggressivo:

- Passa da Extreme ad Aggressive.
- Passa da Aggressive a Balanced.
- Aumenta ScreenPercentage.
- Aumenta OverallQuality.
- Disabilita Force Unlit per un profilo personalizzato.

Dopo aver modificato il profilo mentre la modalità è abilitata, il sistema aggiorna automaticamente le impostazioni attive.

## L'editor è ancora lento

Lightweight Editor Mode è mirato al costo di rendering della viewport dell'editor. Non può risolvere tutti i problemi di prestazioni dell'editor.

Altri possibili colli di bottiglia:

- Compilazione degli asset.
- Compilazione degli shader.
- Operazioni del controllo codice sorgente.
- Construction script nei Blueprint.
- Editor Utility Widget.
- Logica di Tick complessa nei mondi dell'editor.
- Numero elevato di actor.
- Sovraccarico del disco o dell'antivirus.

Utilizza Unreal Insights, i comandi Stat e il normale profiling del progetto per diagnosticare i colli di bottiglia non legati al rendering.

## Disable non ripristina una CVar

Il percorso di ripristino rimuove la sovrascrittura contrassegnata del plugin. Se un altro sistema ha modificato la stessa CVar mentre Lightweight Editor Mode era attivo, rimane attivo quel valore più recente invece di essere sovrascritto dal vecchio backup.

Controlla il log di output per il nome della CVar. Il plugin registra le operazioni di backup e ripristino.

## La pagina Project Settings è nascosta o mancante

La pagina delle impostazioni dovrebbe apparire sotto Project Settings > Plugins > Lightweight Editor Mode.

Se manca:

- Conferma che il modulo sia stato caricato.
- Conferma che il modulo Settings sia disponibile.
- Riavvia l'editor dopo l'abilitazione del plugin.
- Verifica che non vi siano problemi di descrittore del plugin o di build che abbiano impedito il caricamento del modulo.

## La build fallisce dopo l'aggiunta di una nuova CVar

Cause comuni:

- Costante del nome della CVar aggiunta ma non utilizzata in modo coerente.
- Impostazione aggiunta alla struttura del profilo ma non ai campi attivi.
- Istruzione switch dell'interfaccia utente non aggiornata per il nuovo profilo.
- Include mancante per un tipo di Unreal.
- Errore di sintassi all'interno di un blocco di metadati UPROPERTY.

Esegui la build del target dell'editor dopo le modifiche al codice sorgente.

## Log da ispezionare

Cerca nel log di output:

- [Module]
- [Lightweight]
- Backup CVar
- Restore CVar
- ApplyActiveSettings
- ApplyViewportSettings
- Lightweight mode ENABLED
- Lightweight mode DISABLED

I log sono intenzionalmente espliciti in modo che le richieste di supporto possano includere la sequenza rilevante.
