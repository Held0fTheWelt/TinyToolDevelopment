<!-- doc-provenance: product-facts.yml reconciled 2026-07-04; source AKDB:plugins/NamingConventionUtility/architecture.md -->
# Manuale utente

Questo manuale spiega come configurare e utilizzare Naming Convention Utility nell'editor di Unreal.

## Installazione

1. Aggiungi il plugin alla cartella `Plugins` del tuo progetto o installalo tramite Fab.
2. Abilita **Naming Convention Utility** in **Edit > Plugins**.
3. Riavvia l'editor se richiesto.

## Configurazione del DataAsset

Apri **Edit > Project Settings > Plugins > Naming Convention Utility**.

L'impostazione chiave è:

```text
NamingConventionDataAssetPath
```

Predefinito:

```text
/NamingConventionUtility/Editor/Data/DA_NamingConvention.DA_NamingConvention
```

Puoi:

- Utilizzare l'asset predefinito.
- Duplicarlo nel tuo progetto.
- Modificare prefissi e suffissi.
- Copiare un profilo dal Workbench nel tuo DataAsset.
- Convertire una DataTable compatibile nel DataAsset.

## Campi delle regole

Ogni regola contiene:

- `FileTypeIdentifier`: la categoria dell'asset in Unreal.
- `NamingsToRemove`: stringhe rimosse prima di aggiungere prefisso/suffisso.
- `PreFix`: prefisso aggiunto.
- `PostFix`: suffisso aggiunto.

Esempio:

```text
FileTypeIdentifier = FTC_STATICMESH
NamingsToRemove = ["StaticMesh_", "Mesh_"]
PreFix = "SM_"
PostFix = ""
```

`OldWall` diventa `SM_OldWall`.

## Naming Workbench

Il Naming Workbench è l'interfaccia principale per la revisione, la modifica e l'applicazione delle regole.

Consente di:

- Selezionare una cartella.
- Scegliere `epic_recommended`, `tiny_legacy` o `project_custom`.
- Scansionare gli asset in modo ricorsivo.
- Verificare le righe accettate, conformi o escluse.
- Ispezionare i percorsi di destinazione.
- Esportare report in formato JSON/Markdown.
- Applicare le righe selezionate tramite l'hash del piano.

## Applicazione rapida dal Content Browser

L'azione contestuale sulle cartelle rimane disponibile:

1. Fai clic con il tasto destro su una cartella.
2. Scegli **Apply Naming Conventions**.
3. Rivedi la finestra di anteprima.
4. Conferma per applicare.
5. Salva i pacchetti interessati.

## Anteprima e motivi di esclusione

L'anteprima riassume:

- Numero di asset scansionati.
- Numero di rinominazioni pianificate.
- Numero di asset ignorati.
- Coppie vecchio nome / nuovo nome.
- Motivi di esclusione.

## Report di audit

Le operazioni di esportazione e applicazione generano report sotto:

```text
Saved/NamingConventionUtility/Reports/
```

## Conversione di DataTable

Il plugin può convertire una DataTable compatibile nel DataAsset configurato.

Struttura riga attesa:

```text
FNamingConventionTableInformation
```

Campi:

- `FileType`
- `ToolType`
- `Value`

## Rilevamento dei sottotipi di texture

Utilizza la compressione `TC_Normalmap` e i token del nome (`normal`, `albedo`, `roughness`, `metallic`, ecc.).

## Annullamento e controllo codice sorgente

La rinominazione degli asset influisce sui pacchetti e sui riferimenti. Effettua sempre un test su una piccola cartella, verifica i redirector generati e salva i pacchetti modificati.

## Rimozione del plugin

Prima di rimuovere il plugin:

1. Completa o ripristina le operazioni in sospeso.
2. Salva i pacchetti.
3. Disabilita il plugin e riavvia l'editor.
