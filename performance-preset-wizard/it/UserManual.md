<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/PerformancePresetWizard/architecture.md -->
# Manuale utente

Questo manuale descrive il normale flusso di lavoro nell'editor per Performance Preset Wizard.

## Aprire la procedura guidata

1. Abilita **Performance Preset Wizard** in **Edit > Plugins**.
2. Riavvia Unreal Editor se richiesto.
3. Apri **Tools > Performance > Performance Preset Wizard**.

La procedura guidata analizza il registro degli asset alla ricerca di asset `UPerformancePresetAsset` ed elenca i preset rilevati.

## Pannello principale

La procedura guidata comprende due aree principali:

- Elenco dei preset: tutti gli asset dei preset di prestazioni rilevati.
- Pannello dei dettagli: nome del preset selezionato, descrizione, livelli di scalabilità, sovrascritture CVar, testo di stato e pulsanti di azione.

Usa **Refresh** quando sono stati creati, rinominati, spostati o importati nuovi preset.

## Selezionare un preset

Fai clic su un preset nell'elenco per caricarne il riepilogo.

## Applicare un preset

1. Seleziona un preset.
2. Rivedi il riepilogo.
3. Fai clic su **Apply Preset**.

L'ordine delle operazioni è il seguente:

1. Acquisizione di un punto di ripristino.
2. Limitazione dei valori di scalabilità all'intervallo `0..4` di Unreal.
3. Applicazione della scalabilità tramite `Scalability::SetQualityLevels`.
4. Iterazione delle sovrascritture CVar.
5. Ignorare le voci non valide o non corrette.
6. Ignorare le voci `editor-only` al di fuori del contesto dell'editor.
7. Report nell'area di stato e notifiche.

## Ripristinare le impostazioni precedenti

Fai clic su **Restore Previous** per tornare alle impostazioni acquisite immediatamente prima dell'ultima applicazione riuscita.

Il ripristino include:

- La struttura completa della scalabilità prima dell'applicazione.
- I valori precedenti per le CVar specifiche sovrascritte dal preset.

L'applicazione di un altro preset sostituisce il punto di ripristino precedente.

## Preset all'avvio dell'editor

Apri **Edit > Project Settings > Plugins > Performance Preset Wizard**.

Impostazioni disponibili:

- **Apply Preset On Editor Startup**: abilita o disabilita l'applicazione all'avvio.
- **Startup Preset**: riferimento morbido (soft reference) all'asset del preset da applicare dopo l'inizializzazione dell'editor.

## Preset in runtime

I preset in runtime utilizzano gli stessi asset `UPerformancePresetAsset`. I giochi pacchettizzati li applicano manualmente tramite `UPerformancePresetRuntimeSubsystem`.

Flusso Blueprint tipico:

1. Ottieni la `GameInstance` corrente.
2. Ottieni il `Performance Preset Runtime Subsystem`.
3. Passa un asset di preset ad `ApplyRuntimePreset`.
4. Chiama `RestoreLatestBackup` in caso di annullamento.

## Widget di selezione runtime

`UPerformancePresetRuntimeSelectorWidget` è incluso come punto di partenza UMG. Può elencare i preset configurati, applicare il preset selezionato e ripristinare l'ultimo backup.

I preset visualizzati dal widget predefinito possono essere configurati sotto **Project Settings > Plugins > Performance Preset Wizard Runtime**.

## Editor di CVar in blocco

Utilizza l'editor di testo CVar per copiare sovrascritture da note o sessioni della console.

Sintassi supportata:

```text
# Le righe di commento sono consentite
r.ScreenPercentage=85
r.Nanite=1
r.Shadow.Virtual.Enable=1,editor
```

Usa **Export** per scrivere l'array corrente nell'editor e **Apply** per analizzare nuovamente il testo nell'asset.

## Nomi consigliati

Utilizza nomi espliciti:

- `Laptop Dev`
- `Desktop Mid Range 60 FPS`
- `Console Like Review`
- `VR Mobile Stable`
- `Cinematic Capture 4k`

## Spostamento o rimozione dei preset

Se il preset all'avvio smette di essere applicato, seleziona nuovamente l'asset in Project Settings e salva le impostazioni.
