# Manuale Utente

Editor Extension Base pacchettizza i primitivi dell'interfaccia utente dell'editor Unreal e le librerie di utilità condivise, in modo che i plugin di funzionalità possano mantenere un comportamento coerente per la selezione, il checkout, il salvataggio e l'annullamento.

## Pubblico

- Autori di plugin che sviluppano Editor Utility Widget o strumenti per l'editor.
- Team che standardizzano l'UX dell'editor per Tiny Tool Development senza copiare il codice boilerplate dei widget.

Questo plugin **non** è uno strumento per l'utente finale con una propria voce nel menu Tiny Tools.

## Moduli

| Modulo | Caricamento | Contenuti |
| --- | --- | --- |
| `EditorExtensionBase` | Editor / Default | Widget, `UEditorManagerUtilityLibrary`, utilità per l'annullamento / azioni sulle risorse. |
| `EditorExtensionRuntimeBase` | Runtime / Default | Macro condivise (`UsefulMacros.h`) e punto di ingresso del modulo. |

## Widget Condivisi

<!-- image slot: eeb-widget-overview -->

| Classe | Scopo |
| --- | --- |
| `UEditorToolHeaderWidget` | Riga di intestazione con slot BindWidget per titolo/sottotitolo e testo di visualizzazione modificabile. |
| `UEditorUtilityButtonWidget` | Pulsante stilizzato con BindWidgets per blocco di testo e delegato al click. |
| `UEditorUtilityTabButtonWidget` | Pulsante a stile scheda con slot per icone selezionate/non selezionate. |
| `UTwoPaneUserWidget` | Contenitore per layout a due pannelli per schermate di utilità dell'editor. |

Le sottoclassi Blueprint dei widget devono collegare gli slot BindWidget dichiarati; i legami mancanti generano avvisi registrati sotto `LogEditorExtensionBase`.

## Libreria di Utilità del Manager dell'Editor

`UEditorManagerUtilityLibrary` estende `UEditorUtilityLibrary` con helper per la selezione e la persistenza:

| Funzione | Comportamento |
| --- | --- |
| `GetSelectedAssetsForAction` | Restituisce la selezione corrente, eventualmente ancorata a un oggetto primario. |
| `CheckoutAndSaveAssets` | Tentativo di checkout del controllo di versione e salvataggio; segnala il successo tramite parametri out. |
| `GetEditorWorld` | Restituisce il mondo dell'editor corrente quando disponibile. |
| `BeginTransactionAndGetSelectedAssets` | **Deprecato in 5.4** — i chiamanti dovrebbero gestire autonomamente `FScopedTransaction`. |

## Annullamento e Azioni sulle Risorse

| Classe | Comportamento |
| --- | --- |
| `UEditorUtilityTask_PrepareUndo` | Attività di utilità dell'editor che prepara le opzioni di annullamento per le risorse transazionali selezionate; salta gli oggetti null, non validi o non transazionali con avvisi. |
| `UUndoableAssetActionUtility` | Codifica i risultati delle azioni sulle risorse annullabili, incluso `SucceededWithCheckoutWarning` quando avvisi di checkout accompagnano il successo. |

## Regole di Progettazione

1. Mantenere la logica di business specifica della funzionalità nel plugin consumatore.
2. Non trattare questo plugin come un requisito di configurazione per plugin di scene o AI non correlati.
3. Preferire le transazioni gestite dal chiamante rispetto all'helper begin-transaction deprecato.

## Integrazioni Opzionali

I plugin dell'editor Tiny Tool che consumano possono dipendere da Editor Extension Base per la coerenza dell'interfaccia utente. Queste integrazioni sono di proprietà del consumatore; questo pacchetto degrada a "helper non disponibili" solo quando non è abilitato — non sostituisce il comportamento di altri plugin.

## Documenti Correlati

- [QUICKSTART.md](QUICKSTART.md)
- [SettingsReference.md](SettingsReference.md)
- [FAQ.md](FAQ.md)
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md)
