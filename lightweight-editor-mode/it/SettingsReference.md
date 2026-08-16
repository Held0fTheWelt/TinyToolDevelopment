<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/LightweightEditorMode/architecture.md -->
# Riferimento delle impostazioni

Lightweight Editor Mode memorizza le impostazioni in EditorPerProjectUserSettings e le espone in Project Settings > Plugins > Lightweight Editor Mode.

## Modello delle impostazioni

L'oggetto impostazioni è composto da tre livelli:

- Opzioni di alto livello come il comportamento all'avvio e l'indice del profilo selezionato.
- Valori attivi a runtime utilizzati dalla modalità quando viene abilitata.
- Quattro strutture di profilo modificabili: Mild, Balanced, Aggressive ed Extreme.

L'interfaccia Slate copia il profilo selezionato nei valori attivi prima di abilitare o aggiornare la modalità.

## Opzioni di alto livello

### bEnableOnStartup

Abilita automaticamente Lightweight Editor Mode all'avvio dell'editor.

Note di implementazione:

- Il modulo non si abilita immediatamente durante StartupModule.
- Avvia un breve temporizzatore.
- Il temporizzatore attende che GEditor disponga dei client delle viewport dell'editor.
- La modalità viene abilitata solo dopo che le viewport sono disponibili.
- Il ripristino di una sessione precedente si esegue prima dell'abilitazione automatica se la sessione precedente dell'editor si è conclusa mentre Lightweight Mode era ancora attivo.

Questo evita di perdere le modifiche alla viewport durante l'avvio iniziale dell'editor.

### AggressivenessLevel

Memorizza l'indice del profilo attualmente selezionato.

| Valore | Profilo |
| --- | --- |
| 0 | Mild |
| 1 | Balanced |
| 2 | Aggressive |
| 3 | Extreme |

Il valore viene limitato all'intervallo valido.

## Valori attivi a runtime

Questi valori vengono applicati da FEditorLightweightMode.

### OverallQuality

Un singolo livello di qualità della scalabilità di Unreal.

| Valore | Significato |
| --- | --- |
| 0 | Low (Basso) |
| 1 | Medium (Medio) |
| 2 | High (Alto) |
| 3 | Epic (Epico) |
| 4 | Cinematic (Cinematografico) |

Il plugin limita questo valore all'intervallo 0..4 prima di applicarlo.

### ScreenPercentage

Percentuale di schermo target per il rendering della viewport dell'editor e per le anteprime PIE/gioco.

| Intervallo | Significato |
| --- | --- |
| 25..59 | Molto aggressivo, bassa fedeltà visiva |
| 60..79 | Modifica orientata alle prestazioni |
| 80..99 | Modifica bilanciata |
| 100 | Risoluzione interna completa |
| 101..200 | Supersampling, raramente utile per la modalità leggera |

Il plugin limita questo valore all'intervallo 25..200.

Dettaglio di implementazione importante: le viewport dell'editor utilizzano CVar della percentuale di schermo specifiche per l'editor. Il plugin imposta:

- r.Editor.Viewport.ScreenPercentage
- r.Editor.Viewport.ScreenPercentageMode.RealTime
- r.Editor.Viewport.ScreenPercentageMode.NonRealTime

Imposta anche r.ScreenPercentage per i percorsi PIE e anteprima di gioco dove quella CVar è ancora rilevante.

### bDisableLumen

Disabilita l'illuminazione indiretta diffusa Lumen e le riflessioni Lumen mentre la modalità è attiva.

CVar:

- r.Lumen.DiffuseIndirect.Allow = 0
- r.Lumen.Reflections.Allow = 0

Quando disabilitato nel profilo, il plugin ripristina tutti i backup esistenti per queste CVar rimuovendo la sua sovrascrittura contrassegnata. Se un'altra sorgente ha modificato la stessa CVar mentre Lightweight Mode era attivo, rimane attivo quel valore più recente.

### bDisableVirtualShadows

Disabilita le mappe d'ombra virtuali (Virtual Shadow Maps).

CVar:

- r.Shadow.Virtual.Enable = 0

Questo può rendere le scene Nanite pesanti e i grandi mondi più reattivi, ma modifica anche in modo significativo l'aspetto delle ombre.

### bDisableVolumetricFog

Disabilita la nebbia volumetrica e la nebbia regolare.

CVar:

- r.VolumetricFog = 0
- r.Fog = 0

Questo è utile nelle scene atmosferiche in cui la nebbia domina il tempo di calcolo dei fotogrammi dell'editor.

### bForceUnlitViewports

Passa le viewport dell'editor in modalità Unlit (non illuminata) mentre la modalità è attiva.

Il plugin memorizza la modalità di visualizzazione originale per viewport prima di cambiarla. Quando la modalità viene disabilitata nella stessa sessione dell'editor, vengono ripristinate le modalità di visualizzazione originali.

### bDisableViewportRealtime

Disattiva il rendering in tempo reale nelle viewport dell'editor mentre la modalità è attiva.

Il plugin utilizza il sistema di sovrascrittura temporanea in tempo reale di Unreal invece di modificare l'impostazione permanente in tempo reale della viewport. Quando disabilitato, rimuove la propria sovrascrittura.

## Valori per profilo

Ogni profilo contiene gli stessi campi:

- OverallQuality
- ScreenPercentage
- bDisableLumen
- bDisableVirtualShadows
- bDisableVolumetricFog
- bForceUnlitViewports
- bDisableViewportRealtime

I profili sono modificabili in Project Settings. La modifica di un profilo non lo applica immediatamente a meno che l'interfaccia utente non copi quel profilo nei valori attivi.

## LastViewModeBeforeLightweight

Questa impostazione nascosta-visibile memorizza l'ultima modalità di visualizzazione rilevata prima di abilitare la modalità. Viene utilizzata come fallback permanente dopo il riavvio dell'editor.

Il ripristino nella stessa sessione utilizza prima i backup per ciascuna viewport. Il ripristino dopo un riavvio non può utilizzare quei backup in memoria, quindi il valore di fallback viene utilizzato solo per riportare le viewport Unlit a una modalità non-Unlit ragionevole.

## bWasLightweightModeActiveLastSession

Questa impostazione diagnostica visibile registra se la modalità Lightweight era attiva prima dell'ultima uscita dall'editor. Viene impostata quando Enable inizia ad applicare le sovrascritture e azzerata da Disable.

Se risulta ancora vera (true) dopo il riavvio, l'interfaccia utente offre Restore Lightweight State e l'abilitazione automatica all'avvio ripristina lo stato precedente della viewport prima di abilitarla nuovamente.

## Scopo dei profili predefiniti

| Profilo | Scopo |
| --- | --- |
| Mild | Lieve alleggerimento mantenendo il contesto visivo |
| Balanced | Impostazione predefinita consigliata per la modifica generale |
| Aggressive | Modifica di scene pesanti in cui la reattività ha la priorità |
| Extreme | Modifiche d'emergenza o su sistemi con risorse molto limitate |

## Personalizzazione consigliata

Per i team dedicati alla grafica, rendi Mild meno distruttivo e lascia attiva la vista Lit. Per i flussi di lavoro su grandi mondi o laptop, rendi Balanced più aggressivo. Per il debugging tecnico, mantieni almeno un profilo che non forzi la modalità Unlit in modo da poter ispezionare rapidamente i problemi di rendering.
