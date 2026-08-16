<!-- doc-provenance: product-facts.yml reconciled 2026-07-04; source AKDB:plugins/NamingConventionUtility/architecture.md -->
# Documentazione di Naming Convention Utility

Naming Convention Utility è un plugin per l'editor di Unreal Engine progettato per applicare prefissi e suffissi coerenti agli asset nelle cartelle selezionate del Content Browser. Individua i tipi di asset, crea un piano di rinominazione, valida i nomi di destinazione, mostra in anteprima le modifiche pianificate in un banco di lavoro (workbench) ancorabile e applica le rinominazioni degli asset selezionati tramite gli strumenti asset dell'editor.

Questa cartella contiene la documentazione completa fornita con il plugin.

## Inizia qui

- [BUYER_GUIDE.md](BUYER_GUIDE.md): panoramica per gli acquirenti, casi d'uso e idoneità.
- [QUICKSTART.md](QUICKSTART.md): breve guida dall'installazione al risultato.
- [UserManual.md](UserManual.md): flusso di lavoro completo per configurazione, scansione, modifica, reportistica e applicazione delle convenzioni.
- [FAQ.md](FAQ.md): domande e risposte pronte per Fab.

## Riferimento

- [SettingsReference.md](SettingsReference.md): impostazioni, campi dei DataAsset e configurazioni consigliate.
- [TechnicalOverview.md](TechnicalOverview.md): architettura e modello di sicurezza per i manutentori.
- [CodeDocumentation.md](CodeDocumentation.md): struttura del codice, contratti e punti di estensione.
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md): problemi comuni e soluzioni.
- [ReleaseChecklist.md](ReleaseChecklist.md): checklist di validazione prima della pubblicazione.

## Asset inclusi

- `../Readme.pdf`: file lisez-moi tradizionale.
- `../Content/Editor/Data/DA_NamingConvention.uasset`: DataAsset di convenzioni predefinito.
- `../Content/Editor/Data/DT_NamingConvention.uasset`: esempio/sorgente di DataTable.
- `../Resources/NamingConvention.csv`: riferimento per l'importazione CSV.
- `../Resources/NamingConvention.json`: riferimento per l'importazione JSON.
- `../Resources/NamingConvention_EpicRecommended.csv`: riferimento per l'importazione del profilo raccomandato da Epic.
- `../Resources/NamingConvention_TinyLegacy.csv`: riferimento per l'importazione del profilo di compatibilità 1.0.x.
- `../Resources/FileTypeValues.txt`: riferimento dell'enumerazione dei tipi di file.
- `../Resources/ToolTypeValues.txt`: riferimento dei tipi di strumenti della DataTable.

## Flusso di lavoro rapido

1. Abilita il plugin e riavvia l'editor se richiesto.
2. Apri le Project Settings e verifica il DataAsset delle convenzioni configurato.
3. Apri il Naming Workbench dal menu del plugin o da un'azione contestuale su una cartella.
4. Scegli **Epic Recommended**, **Tiny Legacy** o **Project Custom**.
5. Esegui la scansione della cartella, ispeziona la conformità, i motivi di esclusione e i percorsi di destinazione.
6. Seleziona le righe accettate che desideri applicare, quindi esporta un report o applica le modifiche dopo la revisione.
7. Salva gli asset/pacchetti interessati dopo che Unreal ha completato l'operazione di rinominazione.

## Modello di sicurezza

Il plugin tratta le operazioni di rinominazione come azioni ad alto impatto. Prima di chiamare gli strumenti di rinominazione di Unreal, costruisce un piano ed esclude le voci a rischio.

Il piano verifica:

- Tipi di asset non supportati.
- Regole di convenzione mancanti.
- Nomi generati vuoti o non validi.
- Percorsi di destinazione degli oggetti non validi.
- Asset di destinazione già esistenti.
- Pacchetti di destinazione già esistenti su disco.
- Destinazioni duplicate all'interno dello stesso lotto.
- Asset sorgente duplicati selezionati attraverso cartelle sovrapposte.

Il Workbench mostra un'anteprima prima di applicare il piano, protegge l'applicazione con l'hash del piano verificato e scrive report JSON/Markdown in `Saved/NamingConventionUtility/Reports/`.

## Cosa modifica lo strumento

Il plugin rinomina gli asset di Unreal tramite `IAssetTools::RenameAssets`.

Non esegue:

- Rinominazione di file grezzi all'esterno del sistema degli asset.
- Modifica di file sorgente importati.
- Modifica dei nomi delle classi in C++.
- Modifica dei nomi delle classi Blueprint all'interno del codice generato.
- Decisioni sulla politica di denominazione del tuo studio al posto tuo.

## Famiglie di denominazione predefinite

Il DataAsset predefinito include prefissi Unreal comuni come:

- `T_`, `T_N_`, `T_D_` per le texture.
- `M_`, `MI_`, `MF_` per i materiali.
- `SM_`, `SK_`, `SKEL_` per mesh e scheletri.
- `BP_`, `BPI_`, `BPF_`, `WB_` per Blueprint e widget.
- `NS_`, `NE_`, `PS_` per gli effetti.
- `DT_`, `CT_`, `CF_`, `CV_`, `CLC_` per dati e curve.

Il Workbench include inoltre:

- `epic_recommended`: prefissi allineati a Epic con mappature delle collisioni documentate.
- `tiny_legacy`: lo stile predefinito retrocompatibile della versione 1.0.x.
- `project_custom`: le tue regole personalizzate memorizzate nel DataAsset.

Puoi modificare o sostituire il DataAsset in base ai tuoi standard. Il Workbench può anche copiare un profilo integrato nel DataAsset del progetto.

## Limitazioni importanti

- Il rilevamento dei sottotipi delle texture combina impostazioni di compressione e token nel nome.
- I tipi di asset non riconosciuti dal plugin vengono ignorati.
- Unreal potrebbe mostrare finestre di dialogo o non completare la rinominazione a causa di riferimenti, controllo codice sorgente o pacchetti bloccati.
- La rinominazione di cartelle di grandi dimensioni deve essere revisionata attentamente.

## Nota legale

Naming Convention Utility è uno strumento di produttività. Aiuta ad applicare gli standard di denominazione ma non garantisce che uno standard sia corretto per ogni studio o pipeline.
