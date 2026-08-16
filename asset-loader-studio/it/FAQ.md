<!-- doc-provenance: product-facts.yml reconciled 2026-07-01; source AKDB:plugins/AssetLoaderStudio/architecture.md -->
# FAQ

## Asset Loader Studio è autonomo?

Sì. L'area di lavoro dell'editor, il sottosistema runtime, la libreria Blueprint, gli esempi, i profili di governance e la documentazione per l'acquirente funzionano senza UCM, UMCP, MCP o altri plugin Tiny Tool.

## Sostituisce l'Asset Manager di Unreal?

No. Si basa sui percorsi asset di Unreal, sugli ID degli asset primari, su tabelle, pacchetti e sull'Asset Registry. Aggiunge job di caricamento strutturati, diagnostica, snapshot di tabelle, grafi delle dipendenzenze, anteprime e governance.

## Può modificare gli asset del progetto?

Sì, ma le modifiche seguono il principio dell'anteprima prioritaria. Le operazioni di creazione, duplicazione, rinominazione, riorientamento (retarget), riparazione, salvataggio, ripristino (rollback) ed eliminazione devono superare i controlli del profilo di autorizzazione e devono essere verificate prima dell'applicazione.

## Dove vengono memorizzati i registri di audit?

La directory di audit predefinita è `Saved/AssetLoaderStudio/Audit`. Il percorso può essere modificato tramite le impostazioni di governance.

## I percorsi di automazione sono obbligatori?

No. I file UCM/MCP opzionali espongono i medesimi servizi per l'automazione gestita, ma il prodotto principale rimane utilizzabile anche senza di essi.

## Asset Loader Studio è disponibile su Fab?

Lo stato attuale del pacchetto è "In Publishment" (In fase di pubblicazione). Consideralo pronto per la consegna a Fab, ma non ancora disponibile fino alla pubblicazione della scheda sul portale Fab.
