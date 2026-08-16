<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/PerformancePresetWizard/architecture.md -->
# FAQ (Domande frequenti)

## Performance Preset Wizard è un ottimizzatore automatico?

No. È uno strumento di creazione e applicazione di preset. Non esegue il benchmark dell'hardware.

## Funziona in runtime?

Sì, i giochi pacchettizzati possono applicare manualmente i preset tramite `UPerformancePresetRuntimeSubsystem`, Blueprint, C++ o il widget UMG incluso.

## L'applicazione di un preset salva le impostazioni del progetto?

No. Modifica lo stato corrente del motore/runtime tramite le API di scalabilità e CVar.

## Posso annullare un'applicazione?

Nella procedura guidata dell'editor, usa **Restore Previous**. In runtime, usa `RestoreLatestBackup` o `RestoreBackupById`.

## Cosa succede se una CVar non esiste?

Il plugin la segnala come mancante e continua ad applicare il resto del preset.

## Perché i valori CVar sono memorizzati come stringhe?

Le CVar possono essere interi, float, booleani o testo. Una stringa copre tutti questi casi.

## Cosa significa "Editor Only"?

Una sovrascrittura riservata all'editor si applica solo nel contesto dell'editor e viene ignorata nei giochi pacchettizzati.

## Il plugin sostituisce i Device Profiles?

No. I Device Profiles rimangono la sede idonea per le regole relative alle piattaforme.
