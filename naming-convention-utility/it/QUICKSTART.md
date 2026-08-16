<!-- doc-provenance: product-facts.yml reconciled 2026-07-04; source AKDB:plugins/NamingConventionUtility/architecture.md -->
# Guida rapida

Questa guida ti accompagna dall'installazione a un risultato concreto: gli asset in una cartella vengono rinominati secondo le tue convenzioni di denominazione dopo una fase di anteprima e conferma. Naming Convention Utility funziona in modo autonomo.

## Cosa otterrai dopo questa guida

Le regole di denominazione verificate, una cartella analizzata nel Naming Workbench e gli asset selezionati rinominati (ad esempio `OldWall` -> `SM_OldWall`) tramite il sistema degli asset di Unreal.

## Requisiti

- Editor di Unreal Engine 5 con un progetto contenente asset da rinominare.
- Nessun software di terze parti, account o runtime aggiuntivo richiesto. Vedi [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## 1. Installazione e abilitazione

1. Aggiungi **Naming Convention Utility** dalla tua libreria Fab al progetto o installalo nel motore.
2. Apri **Edit > Plugins**, abilita **Naming Convention Utility** e riavvia l'editor quando richiesto.

## 2. Verificare le regole

1. Apri **Edit > Project Settings > Plugins > Naming Convention Utility**.
2. L'impostazione principale è **NamingConventionDataAssetPath**, che indica per impostazione predefinita il file fornito `/NamingConventionUtility/Editor/Data/DA_NamingConvention`.
3. Apri quel DataAsset per esaminare le regole personalizzate. Ogni regola ha un `FileTypeIdentifier`, `NamingsToRemove`, `PreFix` e `PostFix`.

Esempio:

```text
FileTypeIdentifier = FTC_STATICMESH
NamingsToRemove    = ["StaticMesh_", "Mesh_"]
PreFix             = "SM_"
PostFix            = ""
```

Consigliato: duplica il DataAsset predefinito nella cartella del contenuto del tuo progetto e fai puntare `NamingConventionDataAssetPath` sulla copia.

## 3. Scansione nel Naming Workbench

1. Apri il **Naming Workbench** dal menu del plugin oppure fai clic con il tasto destro su una cartella del Content Browser per aprire il workbench per quel livello.
2. Scegli un profilo:
   - **Epic Recommended** per una base conforme a Epic.
   - **Tiny Legacy** per lo stile predefinito della versione 1.0.x.
   - **Project Custom** per il DataAsset configurato.
3. Fai clic su **Scan**. Il workbench mostra le rinominazioni accettate, gli asset già conformi, gli asset ignorati e la percentuale di conformità.

## 4. Applicare una vera rinominazione

1. Trova una static mesh chiamata `OldWall` tra le righe accettate.
2. Conferma che il percorso di destinazione termini con `SM_OldWall.SM_OldWall`.
3. Lascia la riga selezionata.
4. Opzionale: fai clic su **Export** per creare un report di anteprima.
5. Fai clic su **Apply** e conferma.

Risultato atteso: `OldWall` diventa `SM_OldWall`; Unreal completa la rinominazione. Salva i pacchetti interessati.

## 5. Motivi di esclusione comuni

Una rinominazione pianificata viene ignorata se il tipo di asset non è supportato, non esiste una regola per il tipo rilevato, il nome è già conforme, il nome generato non è valido o il nome di destinazione esiste già.

## 6. Passaggi successivi

- Flusso di lavoro completo, campi delle regole, conversione di DataTable: [UserManual.md](UserManual.md).
- Impostazioni: [SettingsReference.md](SettingsReference.md).
- Problemi: [TROUBLESHOOTING.md](TROUBLESHOOTING.md) e [FAQ.md](FAQ.md).
