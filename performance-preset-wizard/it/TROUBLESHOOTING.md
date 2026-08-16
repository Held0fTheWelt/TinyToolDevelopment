<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/PerformancePresetWizard/architecture.md -->
# Risoluzione dei problemi

## Il plugin non appare nel menu Tools

Verifica che il plugin sia abilitato in **Edit > Plugins** e riavvia l'editor.

## Nessun preset presente nell'elenco

Usa **Refresh** nella procedura guidata. Verifica che gli asset siano effettivamente DataAsset `UPerformancePresetAsset`.

## Impossibile applicare un preset

Assicurati che un preset sia selezionato. Se l'asset è stato eliminato o spostato, aggiorna l'elenco.

## Alcune CVar vengono segnalate come mancanti

Il nome della CVar non è stato risolto nel gestore della console di Unreal (errore di battitura, plugin disabilitato o versione diversa del motore). Le CVar mancanti non impediscono l'applicazione del resto del preset.

## Le CVar vengono conteggiate come non valide

Le voci non valide hanno un nome o un valore vuoto. Correggi la riga nell'editor in blocco.

## "Restore Previous" non è disponibile

Il ripristino è disponibile solo dopo aver applicato un preset nella sessione corrente dell'editor.

## Il preset all'avvio non viene applicato

Verifica che **Apply Preset On Editor Startup** sia abilitato e che **Startup Preset** punti a un asset valido.
