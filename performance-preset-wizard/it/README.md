<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/PerformancePresetWizard/architecture.md -->
# Documentazione di Performance Preset Wizard

Performance Preset Wizard crea preset di prestazioni di destinazione in fase di esecuzione creati e modificati in Unreal Editor, quindi applicati manualmente tramite la procedura guidata dell'editor, C++, Blueprint o il widget di selezione runtime incluso. Un preset combina i livelli di scalabilità del motore con sovrascritture di variabili di console (CVar) opzionali, consentendo ai team di passare rapidamente tra livelli hardware, budget VR, impostazioni di acquisizione, impostazioni per lo sviluppo su laptop e obiettivi di qualità specifici del progetto.

Questa cartella contiene la documentazione completa fornita con il plugin.

## Inizia qui

- [BUYER_GUIDE.md](BUYER_GUIDE.md): panoramica per gli acquirenti, valore incluso e flussi di lavoro di produzione comuni.
- [UserManual.md](UserManual.md): flusso di lavoro completo nell'editor per aprire la procedura guidata, applicare i preset, ripristinare le impostazioni precedenti e configurare i preset all'avvio.
- [RuntimeUsage.md](RuntimeUsage.md): sottosistema runtime, API Blueprint, cronologia dei backup, provider di archiviazione e widget di selezione.
- [FAQ.md](FAQ.md): risposte pratiche per acquirenti Fab, designer e tecnici grafici.

## Riferimento

- [PresetAuthoringGuide.md](PresetAuthoringGuide.md): come progettare preset affidabili, scegliere i livelli di scalabilità e scrivere sovrascritture CVar.
- [RuntimeUsage.md](RuntimeUsage.md): come i giochi pacchettizzati possono applicare e ripristinare manualmente gli asset dei preset.
- [SettingsReference.md](SettingsReference.md): ogni impostazione del plugin e campo degli asset con valori predefiniti e utilizzo consigliato.
- [SamplePresetsReference.md](SamplePresetsReference.md): preset di esempio `DA_*` inclusi e come adattarli.
- [CodeDocumentation.md](CodeDocumentation.md): struttura del codice sorgente, contratti pubblici, note di implementazione e punti di estensione.
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md): problemi comuni di configurazione, asset, CVar e build con relative soluzioni.

## Asset inclusi

- [Screenshots/](Screenshots): diagrammi di documentazione leggeri che mostrano il flusso di lavoro della procedura guidata, la creazione dei preset e il comportamento di ripristino/avvio.
- `../Content/DA_*.uasset`: asset di dati di esempio che coprono casi d'uso desktop, VR, stile console, prototipi mobili, sviluppo su laptop e cinematografici.
- `../PerformancePresetWizard_Changelog.txt`: note di rilascio fornite con il plugin.

## Flusso di lavoro rapido nell'editor

1. Abilita il plugin e riavvia l'editor se richiesto da Unreal.
2. Apri **Tools > Performance > Performance Preset Wizard**.
3. Seleziona un preset dall'elenco. Usa **Refresh** se sono stati creati o importati di recente nuovi asset di preset.
4. Rivedi il nome visualizzato, la descrizione, la piattaforma di destinazione, il riepilogo della scalabilità e le sovrascritture CVar.
5. Fai clic su **Apply Preset**. La procedura guidata applica prima le impostazioni di scalabilità, quindi le sovrascritture CVar valide.
6. Fai clic su **Restore Previous** se desideri tornare alle impostazioni acquisite immediatamente prima dell'ultima applicazione.
7. Abilita **Apply on Editor Startup** in Project Settings se desideri applicare automaticamente un preset all'apertura dell'editor.

## Flusso di lavoro rapido in runtime

1. Crea e rivedi gli asset dei preset `UPerformancePresetAsset` nell'editor.
2. Aggiungi i preset runtime in **Project Settings > Plugins > Performance Preset Wizard Runtime**, oppure passali direttamente al sottosistema runtime.
3. In C++ o Blueprint, ottieni `UPerformancePresetRuntimeSubsystem` dalla `GameInstance` corrente.
4. Chiama `ApplyRuntimePreset` per un'azione utente o di progetto esplicita.
5. Usa `GetBackupHistory`, `RestoreLatestBackup` o `RestoreBackupById` se il progetto necessita di una funzione di annullamento.
6. Usa `UPerformancePresetRuntimeSelectorWidget` come piccolo widget di selezione UMG sostituibile per menu di test o schermate delle opzioni.

## Formato rapido CVar

L'editor di CVar in blocco accetta una sovrascrittura per riga:

```text
r.ScreenPercentage=85
r.Nanite=1
r.Lumen.Reflections.Allow=0
r.Shadow.Virtual.Enable=1,editor
```

Regole:

- Le righe vuote vengono ignorate.
- Le righe che iniziano con `#` o `//` sono trattate come commenti.
- `Name=Value` crea una sovrascrittura normale.
- `Name=Value,editor` contrassegna la sovrascrittura come solo per l'editor (editor-only).
- Le CVar sconosciute vengono segnalate ma non interrompono l'applicazione del preset.
- I nomi o i valori vuoti vengono ignorati.

## Livelli di scalabilità

Performance Preset Wizard segue la scala di qualità standard di Unreal Engine:

- `0`: Low
- `1`: Medium
- `2`: High
- `3`: Epic
- `4`: Cinematic

Il plugin gestisce le categorie di scalabilità correnti di UE5, tra cui distanza di visualizzazione, anti-aliasing, ombre, illuminazione globale, riflessi, post-processing, texture, effetti, fogliame, shading e paesaggio.

## Note importanti sull'ambito

Performance Preset Wizard non è un framework di benchmarking, un rilevatore hardware, un ottimizzatore automatico o un sostituto dei Device Profiles. I preset devono essere verificati sul progetto e sulla piattaforma di destinazione prima di essere considerati standard di produzione.
