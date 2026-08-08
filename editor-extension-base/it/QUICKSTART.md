---
lang: it
title: EditorExtensionBase Quick Start
audience: [end_user]
owner_ref: plugin:EditorExtensionBase
applies_to:
  component: EditorExtensionBase
preconditions:
  - Unreal Engine project open with the plugin package available
  - Edit > Plugins can enable EditorExtensionBase
expected_result:
  text: GetSelectedAssetsForAction returns the current Content Browser selection after the plugin is enabled.
version:
  since: "1.0"
---
# Avvio rapido

Questa guida ti accompagna dall'installazione al **primo utilizzo effettivo**: abilitazione di Editor Extension Base e chiamata di un helper dell'editor condiviso da un Blueprint Utility o da uno strumento C++ per l'editor. Editor Extension Base è un livello di supporto per altri plugin dell'editor; non è un prodotto del menu Tiny Tools autonomo.

## Cosa avrai dopo questa guida

Il plugin abilitato e una chiamata riuscita a `UEditorManagerUtilityLibrary::GetSelectedAssetsForAction` (o all'equivalente richiamabile da Blueprint) che restituisce la selezione corrente del Content Browser.

## Requisiti

- Unreal Engine 5.4 o successivo (descrittore `EngineVersion` 5.4.0).
- Editor Scripting Utilities abilitati (dipendenza dichiarata in `EditorExtensionBase.uplugin`).
- Nessun software di terze parti, account o runtime esterno. Vedi [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## 1. Installazione e abilitazione

1. Aggiungi **EditorExtensionBase** dalla tua libreria Fab al progetto (o installalo nella directory Plugins dell'engine).
2. Apri **Edit → Plugins**, abilita **EditorExtensionBase** e riavvia quando richiesto.
3. Conferma che **Editor Scripting Utilities** rimanga abilitato.

## 2. Verifica che i moduli siano caricati

Dopo il riavvio, il pacchetto espone due moduli:

| Modulo | Tipo | Ruolo |
| --- | --- | --- |
| `EditorExtensionBase` | Editor | Widget, helper di selezione, utility di annullamento. |
| `EditorExtensionRuntimeBase` | Runtime | Macro leggere sicure per consumatori non-editor. |

## 3. Esempio pratico: lettura della selezione corrente

1. Seleziona uno o più asset nel Content Browser.
2. Da un Editor Utility Widget o da uno strumento C++ per l'editor che dipende da questo plugin, chiama:

```cpp
TArray<UObject*> Selected = UEditorManagerUtilityLibrary::GetSelectedAssetsForAction(nullptr);
```

3. Salva o agisci sugli oggetti restituiti con `CheckoutAndSaveAssets` quando scrivi intenzionalmente:

```cpp
bool bCheckoutOk = false;
bool bSaveOk = false;
const bool bOk = UEditorManagerUtilityLibrary::CheckoutAndSaveAssets(
	Selected, bCheckoutOk, bSaveOk);
```

## Risultato atteso

- `Selected` contiene la selezione del Content Browser (o è vuoto quando nulla è selezionato).
- Quando chiami `CheckoutAndSaveAssets`, i parametri out booleani riportano gli esiti di checkout e salvataggio senza inventare una transazione per te: il chiamante è responsabile dell'ambito `FScopedTransaction`.

## Prossimi passi

- Leggi [UserManual.md](UserManual.md) per il catalogo di widget e utility.
- Leggi [SettingsReference.md](SettingsReference.md) per le proprietà modificabili sui widget condivisi.
- Usa [TROUBLESHOOTING.md](TROUBLESHOOTING.md) quando gli slot BindWidget o gli helper di selezione generano avvisi nel log.
