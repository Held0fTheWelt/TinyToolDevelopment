<!-- doc-provenance: product-facts.yml reconciled 2026-07-04; source AKDB:plugins/NamingConventionUtility/architecture.md -->
# Riferimento delle impostazioni

Naming Convention Utility memorizza le sue impostazioni a livello di progetto in `UNamingConventionUtility_Settings`.

## Oggetto delle impostazioni

File sorgente:

```text
Source/NamingConventionUtility/Public/NamingConventionUtility_Settings.h
```

Posizione nell'editor:

```text
Edit > Project Settings > Plugins > Naming Convention Utility
```

## NamingConventionDataAssetPath

Tipo:

```text
FSoftObjectPath
```

Predefinito:

```text
/NamingConventionUtility/Editor/Data/DA_NamingConvention.DA_NamingConvention
```

Scopo:

- Punta al DataAsset contenente le regole di rinominazione.
- Usato dal flusso di lavoro di rinominazione delle cartelle.
- Utilizzato come destinazione per la conversione di DataTable.

## bConfirmBeforeApplyingConventions

Predefinito:

```text
true
```

Scopo:

- Mostra un'anteprima e richiede conferma prima di applicare le rinominazioni in blocco.

## bFixRedirectorsAfterRename

Predefinito:

```text
true
```

Scopo:

- Tenta di correggere automaticamente i redirector nelle cartelle selezionate dopo la rinominazione.

## DataAsset: NamingConventions

Ogni voce definisce la regola per un `EFileTypeIdentifier`.

Campi:

- `FileTypeIdentifier`: tipo di asset di destinazione.
- `NamingsToRemove`: frammenti vecchi da rimuovere.
- `PreFix`: prefisso da aggiungere.
- `PostFix`: suffisso da aggiungere.

## Profili del Workbench

Il Workbench offre tre opzioni:

- `epic_recommended`: regole in sola lettura conformi alle linee guida Epic.
- `tiny_legacy`: regole in sola lettura compatibili con la versione 1.0.x.
- `project_custom`: il file specificato in `NamingConventionDataAssetPath`.

## Report

Generati sotto:

```text
Saved/NamingConventionUtility/Reports/
```
