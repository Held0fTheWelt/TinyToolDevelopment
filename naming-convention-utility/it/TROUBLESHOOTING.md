<!-- doc-provenance: product-facts.yml reconciled 2026-07-04; source AKDB:plugins/NamingConventionUtility/architecture.md -->
# Risoluzione dei problemi

## Il menu contestuale non appare

Verifica che:

- Il plugin sia abilitato.
- L'editor sia stato riavviato.
- Tu stia facendo clic con il tasto destro su una cartella del Content Browser.

## Lo strumento indica che nessun asset verrà rinominato

Possibili cause:

- Tutti gli asset rispettano già la convenzione.
- I tipi di asset non sono supportati.
- Il DataAsset configurato è vuoto.
- I nomi generati non sarebbero validi.

## Il Workbench segnala il piano come obsoleto (Stale)

Il piano è stato modificato dopo la scansione (cambio di cartella, modifica di regole, ecc.). Fai di nuovo clic su **Scan**.

## Impossibile modificare un profilo integrato

`epic_recommended` e `tiny_legacy` sono in sola lettura. Utilizza **Copy to Project** per duplicare le loro regole nel tuo profilo personalizzato.

## Una texture ha ricevuto il prefisso generico `T_`

Il rilevamento automatico dei sottotipi è euristico. Se i token nel nome non sono espliciti, viene applicata la regola generica.

## Una rinominazione è fallita dopo la conferma

Cause comuni:

- Riferimenti esistenti.
- Problema di blocco nel controllo codice sorgente.
- Pacchetti bloccati.

Controlla il log di output (Output Log).

## Informazioni da fornire al supporto

- Versione di Unreal Engine.
- Versione del plugin.
- Percorso della cartella selezionata.
- Percorso del DataAsset configurato.
