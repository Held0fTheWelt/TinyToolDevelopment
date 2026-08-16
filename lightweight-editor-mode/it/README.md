<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/LightweightEditorMode/architecture.md -->
# Documentazione di Lightweight Editor Mode

Lightweight Editor Mode è un plugin per l'editor di Unreal Engine che consente ad artisti, level designer, technical artist e programmatori di ridurre temporaneamente il costo di rendering dell'editor durante il lavoro su progetti complessi. È progettato come uno strumento di lavoro reversibile: abilitalo quando una viewport diventa troppo pesante, continua a modificare e poi disabilitalo per tornare allo stato precedente dell'editor.

Questa documentazione offre la profondità attesa da un plugin per l'editor pronto per il marketplace. Copre le aspettative degli acquirenti, l'uso quotidiano, le impostazioni, il comportamento tecnico, la validazione, il packaging e la manutenzione.

## Inizia qui

- [UserManual.md](UserManual.md) spiega il normale flusso di lavoro nell'editor.
- [BUYER_GUIDE.md](BUYER_GUIDE.md) spiega cosa fa il plugin e a chi è rivolto.
- [SettingsReference.md](SettingsReference.md) elenca tutte le impostazioni disponibili.
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md) aiuta a diagnosticare i casi comuni nell'editor.
- [TechnicalOverview.md](TechnicalOverview.md) descrive l'architettura a runtime.
- [CodeDocumentation.md](CodeDocumentation.md) associa i file sorgente ai comportamenti.
- [PerformanceTuningReference.md](PerformanceTuningReference.md) aiuta a personalizzare i profili.
- [ValidationAndQA.md](ValidationAndQA.md) fornisce i passaggi di test e validazione per il rilascio.
- [CompatibilityAndPackaging.md](CompatibilityAndPackaging.md) copre le note sul motore e sul packaging.
- [FAQ.md](FAQ.md) risponde alle domande più frequenti.
- [ReleaseChecklist.md](ReleaseChecklist.md) è la checklist finale prima del rilascio.

## Cosa modifica il plugin

Quando abilitato, Lightweight Editor Mode può applicare queste ottimizzazioni lato editor:

- Ridurre la percentuale di schermo (Screen Percentage) della viewport dell'editor.
- Ridurre la qualità di scalabilità globale (Scalability Quality).
- Disabilitare l'illuminazione indiretta diffusa Lumen e le riflessioni Lumen.
- Disabilitare le mappe d'ombra virtuali (Virtual Shadow Maps).
- Disabilitare la nebbia volumetrica e la nebbia standard.
- Forzare le viewport dell'editor in modalità di visualizzazione Unlit (non illuminata).
- Disabilitare il rendering in tempo reale (Realtime) nelle viewport dell'editor.

Il comportamento esatto dipende dal profilo selezionato e dalle impostazioni del profilo modificabili in Project Settings.

## Promessa fondamentale del design

Il plugin è intenzionalmente reversibile:

- Esegue un backup delle impostazioni di scalabilità prima di modificarle.
- Esegue un backup delle variabili di console (CVars) modificate prima di impostare i valori del plugin.
- Memorizza le modalità di visualizzazione e gli stati in tempo reale per ciascuna viewport per la sessione attiva.
- Memorizza una modalità di visualizzazione di fallback permanente per il ripristino dopo il riavvio.
- Ripristina lo stato dell'editor quando la modalità viene disabilitata o il modulo si arresta.

Questo rende il plugin ideale per un rapido alleggerimento delle prestazioni mantenendo intatta la configurazione principale del progetto.

## Flusso di lavoro rapido

1. Abilita il plugin in Edit > Plugins.
2. Apri Tools > Performance > Lightweight Editor Mode.
3. Scegli un profilo: Mild, Balanced, Aggressive o Extreme.
4. Fai clic su Enable Lightweight Mode.
5. Lavora nell'editor con un costo della viewport ridotto.
6. Fai clic su Disable Lightweight Mode prima del lavoro finale su illuminazione, materiali o acquisizioni.

## Guide visive

La cartella Documentation/Screenshots contiene diagrammi del flusso di lavoro in formato SVG:

- [01-workflow-overview.svg](Screenshots/01-workflow-overview.svg)
- [02-profile-and-settings.svg](Screenshots/02-profile-and-settings.svg)
- [03-restore-flow.svg](Screenshots/03-restore-flow.svg)

Questi diagrammi sono risorse di documentazione, non elementi di interfaccia utente a runtime.

## Ambito del motore

L'implementazione si rivolge alle API dell'editor e alle variabili di console di rendering in stile Unreal Engine 5.4. Il dettaglio di implementazione più importante è che le viewport dell'editor non seguono in modo affidabile lo stesso percorso della percentuale di schermo del rendering di gioco o PIE, quindi il plugin utilizza CVar di percentuale di schermo specifiche per l'editor.

## Note sulla sicurezza

Lightweight Editor Mode è uno strumento per le prestazioni dell'editor, non un sistema di ottimizzazione a runtime per le build finali. Non dovrebbe essere utilizzato come unico percorso di validazione per l'illuminazione finale, le ombre, la nebbia, i materiali o l'output cinematografico.

Prima dei rendering finali o delle approvazioni visive, disabilita la modalità e verifica la scena con le impostazioni di qualità di produzione previste.
