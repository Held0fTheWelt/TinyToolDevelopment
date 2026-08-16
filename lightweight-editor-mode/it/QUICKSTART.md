<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/LightweightEditorMode/architecture.md -->
# Guida rapida

Questa guida ti accompagna dall'installazione a un **risultato visibile**: una viewport dell'editor più veloce e reattiva che puoi ripristinare completamente con un solo clic. Lightweight Editor Mode funziona in modo autonomo — non è richiesto alcun altro plugin.

## Cosa otterrai dopo questa guida

Un profilo di modifica "leggero" e reversibile abilitato (viewport più veloce), e le conoscenze per cambiare profilo e ripristinare lo stato originale dell'editor su richiesta.

## Requisiti

- Editor di Unreal Engine 5 (il plugin influisce solo sulla viewport dell'editor, mai sul gioco pacchettizzato a runtime).
- Nessun software di terze parti, account o runtime aggiuntivo richiesto. Vedi [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## 1. Installazione e abilitazione

1. Aggiungi **Lightweight Editor Mode** dalla tua libreria Fab al progetto (o installalo nel motore).
2. Apri **Edit → Plugins**, abilita **Lightweight Editor Mode** e riavvia quando richiesto.

## 2. Aprire lo strumento (Primo risultato)

1. Apri **Tools → Performance → Lightweight Editor Mode**. Si aprirà una scheda ancorabile con un menu a discesa dei profili, un pulsante di attivazione e una casella di controllo *Enable on Editor startup*.
2. Seleziona il profilo **Balanced** (l'impostazione predefinita consigliata).
3. Fai clic su **Enable Lightweight Mode**.

**Risultato atteso:** la viewport si aggiorna immediatamente — Balanced riduce la percentuale di schermo e la scalabilità, disabilita l'illuminazione dispendiosa e forza la modalità Unlit / non in tempo reale. L'editor diventa subito più reattivo.

## 3. Un esempio pratico: Cambiare profilo e ripristinare

1. Con la modalità abilitata, cambia il profilo nel menu a discesa su **Aggressive**. La viewport si aggiorna con le impostazioni più aggressive (percentuale di schermo più bassa, bassa scalabilità, nessuna ombra/nebbia dispendiosa). Lo stato originale precedente all'attivazione viene comunque preservato.
2. Fai clic su **Disable Lightweight Mode**.

**Risultato atteso:** l'editor ripristina i livelli di scalabilità salvati, le sovrascritture delle variabili di console, le modalità di visualizzazione della viewport e lo stato in tempo reale — torni esattamente dove avevi iniziato.

> I profili sono ottimizzati per la reattività e non per la fedeltà visiva, quindi aspettati viewport a risoluzione inferiore, non illuminate (Unlit) e con meno ombre mentre il profilo è attivo. **Disabilita la modalità prima di revisionare l'illuminazione o scattare screenshot.**

## 4. Personalizzare i profili

Apri **Project Settings → Plugins → Lightweight Editor Mode** per modificare i valori dei profili Mild / Balanced / Aggressive / Extreme. Il profilo selezionato viene copiato nei valori attivi prima dell'applicazione della modalità. Vedi [PerformanceTuningReference.md](PerformanceTuningReference.md).

## 5. Opzionale: Abilitare all'avvio dell'editor

Spunta **Enable on Editor startup** per fare in modo che la modalità si attivi automaticamente non appena le viewport dell'editor sono disponibili al successivo avvio.

## 6. Passaggi successivi

- Comportamento completo per ciascun profilo e flussi di lavoro consigliati: [UserManual.md](UserManual.md).
- Riferimento di tutte le impostazioni: [SettingsReference.md](SettingsReference.md).
- Problemi (es. stato non aggiornato dopo il riavvio → *Restore Lightweight State*):
  [TROUBLESHOOTING.md](TROUBLESHOOTING.md) e [FAQ.md](FAQ.md).
