---
lang: it
title: EditorExtensionBase Troubleshooting
audience: [end_user]
owner_ref: plugin:EditorExtensionBase
applies_to:
  component: EditorExtensionBase
symptom: Editor utility BindWidget slots are null or selection helpers warn in the log.
recovery:
  steps:
    - Confirm the plugin is enabled under Edit > Plugins and restart the editor
    - Re-read the matching troubleshooting entry and apply the documented fix
    - Re-run the quick start smoke check
version:
  since: "1.0"
---
# Risoluzione dei problemi

Formato: Sintomo → Causa → Soluzione.

## 0. L'ho abilitato ma non è successo nulla

**Sintomo:** Dopo aver abilitato **EditorExtensionBase** e riavviato, non appare alcun nuovo menu Tiny Tools e non ci sono cambiamenti evidenti nell'interfaccia utente.  
**Causa:** Questo plugin è uno strato di base condiviso; non registra un menu del prodotto di propria iniziativa.  
**Soluzione:** Verificare che il plugin sia abilitato in **Modifica → Plugin**, quindi chiamare `UEditorManagerUtilityLibrary::GetSelectedAssetsForAction` da un Editor Utility Widget o da uno strumento dell'editor in C++ (vedere [QUICKSTART.md](QUICKSTART.md)). L'assenza di un nuovo menu è prevista.

## 1. Il plugin si abilita ma le Blueprint helper non riescono a trovare la libreria

**Sintomo:** I nodi Blueprint per `Editor Manager Utility Library` mancano dopo l'abilitazione.  
**Causa:** Il modulo Editor non è stato caricato, oppure l'asset Editor Utility è stato compilato prima che il plugin fosse abilitato.  
**Soluzione:** Confermare che **EditorExtensionBase** sia abilitato in **Modifica → Plugin**, riavviare l'editor, quindi aggiornare/ricompilare la Blueprint Editor Utility.

## 2. `EditorUtilityButtonWidget: Button is null`

**Sintomo:** Il log `LogEditorExtensionBase` segnala un avviso che il pulsante è null.  
**Causa:** La sottoclasse Blueprint del Widget Utility non ha associato lo slot del pulsante BindWidget richiesto.  
**Soluzione:** Aprire la Blueprint del widget, associare lo slot del pulsante dichiarato su `UEditorUtilityButtonWidget`, compilare e riaprire lo strumento.

## 3. `EditorUtilityButtonWidget: Text block is null`

**Sintomo:** Avviso che il BindWidget del blocco di testo è null.  
**Causa:** Il blocco di testo dell'etichetta non è associato nella Blueprint.  
**Soluzione:** Associare lo slot del blocco di testo sulla base C++, impostare il testo di visualizzazione, compilare.

## 4. `EditorUtilityTabButtonWidget: SelectedIcon is null` / `UnselectedIcon is null`

**Sintomo:** Il pulsante della scheda segnala un avviso per icone mancanti.  
**Causa:** Gli slot per le icone selezionate o non selezionate non sono associati o gli asset mancano.  
**Soluzione:** Assegnare e associare entrambi gli slot delle icone; verificare che i riferimenti soft/object si risolvano correttamente.

## 5. `EditorUtilityTask_PrepareUndo: No assets selected`

**Sintomo:** I log di preparazione del rollback segnalano che nessun asset è stato selezionato.  
**Causa:** La selezione del Content Browser è vuota quando viene eseguita l'attività.  
**Soluzione:** Selezionare prima gli asset transazionali, quindi eseguire l'utilità prepare-undo.

## 6. Asset ignorati perché non transazionali

**Sintomo:** Avvisi che un asset non è transazionale / non è un `UObject` / non è valido.  
**Causa:** L'attività prepare-undo accetta solo asset `UObject` transazionali validi.  
**Soluzione:** Limitare la selezione agli asset che supportano le transazioni dell'editor; ignorare gli oggetti non-asset o transitori.

## 7. Helper begin-transaction deprecato ancora in uso

**Sintomo:** Avvisi di deprecazione che fanno riferimento a `BeginTransactionAndGetSelectedAssets`.  
**Causa:** I punti di chiamata utilizzano ancora l'helper deprecato in UE 5.4.  
**Soluzione:** Sostituire con `GetSelectedAssetsForAction` più un `FScopedTransaction` di proprietà del chiamante, e utilizzare `CheckoutAndSaveAssets` per la persistenza.

## 8. Checkout riuscito con avvisi

**Sintomo:** Codice di risultato `SucceededWithCheckoutWarning` o parametro out del checkout false mentre alcuni file sono stati salvati.  
**Causa:** Il controllo versione ha restituito avvisi durante il checkout.  
**Soluzione:** Ispezionare lo stato del controllo versione per gli asset, risolvere blocchi/conflitti, riprovare `CheckoutAndSaveAssets`.

## Documenti correlati

- [QUICKSTART.md](QUICKSTART.md)
- [UserManual.md](UserManual.md)
- [SettingsReference.md](SettingsReference.md)
- [FAQ.md](FAQ.md)
