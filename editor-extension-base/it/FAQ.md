# FAQ

## A cosa serve Editor Extension Base?

È una base condivisa per i plugin dell'interfaccia utente dell'editor di Tiny Tool Development: widget di utilità dell'editor riutilizzabili, helper per selezione / checkout / salvataggio, utility di preparazione per l'annullamento e un modulo di macro runtime leggero.

## È uno strumento per l'utente finale?

No. Non registra un menu del prodotto Tiny Tools autonomo. I plugin delle funzionalità lo consumano come dipendenza.

## Quali moduli di Unreal carica?

`EditorExtensionBase` (Editor) e `EditorExtensionRuntimeBase` (Runtime), come dichiarato in `EditorExtensionBase.uplugin`.

## Richiede altri plugin Tiny Tool?

No. Richiede il plugin **Editor Scripting Utilities** di Unreal (abilitato nel descrittore). I plugin di scena, AI o altri plugin Tiny Tool sono consumatori opzionali, non requisiti di configurazione.

## Come leggo la selezione corrente del Content Browser?

Chiama `UEditorManagerUtilityLibrary::GetSelectedAssetsForAction` da Blueprint o C++ dopo aver abilitato il plugin. Vedi [QUICKSTART.md](QUICKSTART.md).

## Come dovrei aprire una transazione di annullamento?

Possiedi un `FScopedTransaction` nel chiamante. `BeginTransactionAndGetSelectedAssets` è deprecato a partire da Unreal Engine 5.4.

## Perché i miei widget Blueprint generano avvisi a runtime?

Gli slot BindWidget come pulsanti, blocchi di testo o icone sono null. Assicurati che il Blueprint del Widget di utilità associ ogni slot richiesto dichiarato nella classe base C++.

## CheckoutAndSaveAssets ha sempre successo?

No. Segnala gli esiti del checkout e del salvataggio tramite parametri out booleani. I fallimenti del controllo versione o del salvataggio emergono lì e nei codici di risultato correlati come `SucceededWithCheckoutWarning`.

## Esistono DeveloperSettings a livello di progetto?

No. I campi configurabili risiedono sui widget e sulle utility condivisi. Vedi [SettingsReference.md](SettingsReference.md).

## Il pacchetto include software di terze parti?

No. Vedi [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## Quali versioni del motore sono supportate?

Il descrittore impacchettato mira a Unreal Engine 5.4.0 su Win64, Linux e Mac per l'allow list del modulo editor.

## Dove posso ottenere supporto?

Usa `mailto:support@tiny-tool-development.com` (descrittore `SupportURL`) o il link di supporto nella pagina del prodotto Fab.

## Posso usare solo le macro runtime senza il modulo editor?

Sì. `EditorExtensionRuntimeBase` è un modulo runtime separato progettato per rimanere leggero nelle dipendenze per i consumatori non-editor.

## PrepareUndo modifica immediatamente gli asset?

Prepara le opzioni di annullamento per gli asset transazionali selezionati e salta le selezioni non valide con avvisi. La persistenza avviene comunque attraverso gli helper di checkout/salvataggio quando si scrive intenzionalmente.

## Le macro runtime possono richiamare moduli solo per l'editor?

No. Mantieni `EditorExtensionRuntimeBase` leggero nelle dipendenze. I widget dell'editor e gli helper di selezione rimangono nel modulo Editor.
