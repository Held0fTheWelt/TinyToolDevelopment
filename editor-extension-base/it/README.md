# Documentazione di base per l'estensione dell'editor

Editor Extension Base è una base condivisa dell'editor Unreal per i plugin dell'interfaccia utente di Tiny Tool Development. Fornisce widget dell'utilità dell'editor riutilizzabili, helper per la selezione/checkout/salvataggio del Content Browser, utility di preparazione per l'annullamento e un modulo di macro runtime leggero.

Destinatari: autori di plugin e team che necessitano di un'esperienza utente dell'editor coerente senza dover copiare il codice boilerplate per widget e selezione. Questo pacchetto è uno strato di supporto — non registra il proprio menu del prodotto Tiny Tools.

## Funzionalità

- Widget dell'utilità dell'editor condivisi (intestazione, pulsante, pulsante di scheda, layout a due pannelli).
- `UEditorManagerUtilityLibrary` per selezione, checkout/salvataggio e helper del mondo dell'editor.
- Utility di preparazione per l'annullamento e di azione sulle risorse annullabili.
- Modulo runtime (`EditorExtensionRuntimeBase`) con macro condivise per i consumatori non editor.

## Per iniziare

1. Abilita il plugin (e le Utilità di scripting dell'editor) — vedi [QUICKSTART.md](QUICKSTART.md).
2. Chiama `GetSelectedAssetsForAction` da un'utilità dell'editor o da uno strumento dell'editor in C++.
3. Leggi [UserManual.md](UserManual.md) e [SettingsReference.md](SettingsReference.md) per il catalogo completo.

## File correlati

- [../README.md](../README.md) — panoramica del prodotto.
- [../CHANGELOG.md](../CHANGELOG.md) — cronologia delle release.
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md) · [FAQ.md](FAQ.md) · [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md)
