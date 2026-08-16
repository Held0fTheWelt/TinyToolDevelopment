<!-- doc-provenance: AKDB:plugins/SmartContentDiet/architecture.md; docs/architecture/plugins/SmartContentDiet/product-facts.yml; reconciled 2026-07-16 -->
# Software di terze parti

Smart Content Diet **non include codice sorgente di terze parti, binari runtime, modelli IA, Node.js, Python o eseguibili autonomi**. È un plugin C++ per l'editor Unreal Engine che utilizza solo moduli Unreal Engine e API Unreal standard (registro asset, analisi asset, UI editor, commandlet).

Il ciclo principale scansione → revisione → correzione sicura viene eseguito interamente nell'editor **senza servizi IA e senza strumenti esterni**. Le rotte opzionali dell'ecosistema cross-plugin (tramite **Unreal Capability Mesh (UCM)**) sono dichiarate in JSON e non aggiungono software di terze parti a questo pacchetto.

Nessun software esterno, account o runtime è richiesto per installare o utilizzare il plugin.

**Dichiarazione software di terze parti Fab:** nessun software di terze parti incluso.
