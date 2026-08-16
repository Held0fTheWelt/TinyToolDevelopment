<!-- doc-provenance: product-facts.yml reconciled 2026-07-04; source AKDB:plugins/NamingConventionUtility/architecture.md -->
# FAQ (Domande frequenti)

## Il plugin rinomina effettivamente gli asset o genera solo report?

Rinomina realmente gli asset dopo la tua conferma tramite `IAssetTools::RenameAssets`.

## Rinomina le cartelle?

No. Analizza le cartelle e rinomina gli asset contenuti al loro interno.

## Posso visualizzare in anteprima le modifiche?

Sì. Il Workbench crea un piano di rinominazione dettagliato e consente di esportare un report prima di applicare qualsiasi modifica.

## Cosa succede se due asset ottengono lo stesso nome?

Entrambe le voci in conflitto vengono escluse dal piano per evitare sovrascritture.

## Può rilevare i sottotipi di texture?

Sì, parzialmente tramite la compressione e i token di testo più comuni (`normal`, `roughness`, `metallic`, ecc.).

## Modifica i nomi delle classi Blueprint?

Rinomina l'asset come file/pacchetto, non riscrive il codice interno.

## Posso importare regole da un foglio di calcolo?

Sì, tramite l'importazione di una DataTable compatibile e la funzione di conversione integrata.

## Genera report?

Sì, i report in formato JSON e Markdown vengono salvati sotto `Saved/NamingConventionUtility/Reports/`.

## Corregge i redirector?

Sì, una fase di correzione automatica dei redirector può essere eseguita dopo la rinominazione se abilitata.
