---
lang: it
title: EditorExtensionBase Settings Reference
audience: [end_user]
owner_ref: plugin:EditorExtensionBase
applies_to:
  component: EditorExtensionBase
contract_ref: plugin:EditorExtensionBase/widget-properties
version:
  since: "1.0"
---
# Riferimento alle impostazioni

Editor Extension Base **non** include una classe `UDeveloperSettings` né un oggetto delle impostazioni di progetto `.ini`. I valori configurabili sono presenti nelle sottoclassi condivise di Editor Utility Widget e negli oggetti utility come campi `UPROPERTY`.

## UEditorToolHeaderWidget

| Nome | Tipo | Valore predefinito | Effetto |
| --- | --- | --- | --- |
| `TitleText` | `FText` | valore predefinito del widget | Titolo visualizzato nell'intestazione. |
| `SubtitleText` | `FText` | valore predefinito del widget | Riga secondaria sotto il titolo. |
| Blocchi titolo/sottotitolo (BindWidget) | riferimenti al widget | devono essere associati | Slot Slate/UMG obbligatori; le associazioni mancanti generano un avviso in fase di esecuzione. |

## UEditorUtilityButtonWidget

| Nome | Tipo | Valore predefinito | Effetto |
| --- | --- | --- | --- |
| Proprietà dello stile del pulsante | campi di stile del widget | impostati dal designer | Stile visivo per il pulsante condiviso. |
| Pulsante/blocco testo (BindWidget) | riferimenti al widget | devono essere associati | Target del clic e etichetta; un pulsante o un testo null generano un avviso. |

## UEditorUtilityTabButtonWidget

| Nome | Tipo | Valore predefinito | Effetto |
| --- | --- | --- | --- |
| Presentazione selezionata/non selezionata | campi di stato + icona | impostati dal designer | Controlla l'aspetto della scheda quando è selezionata. |
| Slot pulsante/icona (BindWidget) | riferimenti al widget | devono essere associati | Le icone selezionate/non selezionate mancanti generano avvisi. |

## UUndoableAssetActionUtility

| Nome | Tipo | Valore predefinito | Effetto |
| --- | --- | --- | --- |
| Descrizione dell'azione/campi dell'asset | campi utility editanywhere | impostati dal chiamante | Descrive l'azione sull'asset annullabile eseguita dall'utility. |
| Codice di risultato | enum | runtime | Include `SucceededWithCheckoutWarning` quando avvisi di checkout accompagnano il successo. |

## UEditorUtilityTask_PrepareUndo

| Nome | Tipo | Valore predefinito | Effetto |
| --- | --- | --- | --- |
| Input asset selezionati | campi utility editanywhere | impostati dal chiamante | Asset considerati per la preparazione all'annullamento; gli asset null/non validi/non transazionali vengono saltati con avvisi. |

## Cosa non è presente

| Superficie attesa | Stato |
| --- | --- |
| `UEditorExtensionBaseSettings` DeveloperSettings | non ancora disponibile nel codice sorgente |
| `Config/DefaultEditorExtensionBase.ini` | non incluso |
| Pannello Preferenze di progetto | non ancora disponibile |

## Documenti correlati

- [UserManual.md](UserManual.md) — catalogo comportamentale.
- [QUICKSTART.md](QUICKSTART.md) — prima chiamata helper di selezione.
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md) — avvisi di BindWidget e selezione.
