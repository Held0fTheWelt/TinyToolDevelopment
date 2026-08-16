<!-- doc-provenance: AKDB:plugins/VisualFidelityDirector/architecture.md; docs/architecture/plugins/VisualFidelityDirector/product-facts.yml; reconciled 2026-07-12 -->
# FAQ

## VFD sostituisce il renderer o l'anti-aliasing di Unreal?

No. È uno strato di diagnosi, profilo, elementi di prova, confronto, ricetta, valutazione a secco, scanner e raccomandazione al di sopra dei sistemi di rendering esistenti di Unreal.

## Cosa è cambiato nella versione 2.0.0?

La versione `2.0.0` aggiunge il cockpit incentrato sui profili (selettore di varianti, percorso di ereditarietà, provenienza, risultati, confronto profili, applicazione permanente governata, metriche live multi-frame), `UVFDCockpitBlueprintLibrary` e gli asset showcase Blueprint confezionati. La pagina Expert Tools integrata mantiene il workflow di snapshot e ricette 1.x.

## Richiede IA o servizi cloud?

No. VFD non richiede IA esterna, cloud, Python, Node.js o account.

## Ha bisogno di altri plugin Tiny Tool?

No. Il workflow principale è autonomo.

## Quale versione di Unreal è supportata?

Visual Fidelity Director supporta Unreal Engine da 5.4 a 5.8 tramite il descrittore del ramo dell'engine corrispondente e supporta Win64, Linux e Mac.

## Può modificare il mio progetto?

Per impostazione predefinita, no. L'applicazione permanente governata può scrivere solo su tre destinazioni di configurazione quando le si approva esplicitamente: gruppi Scalability in `DefaultGameUserSettings.ini`, impostazioni del renderer in `DefaultEngine.ini` e Device Profiles in `DefaultDeviceProfiles.ini`. Expert Tools **Preview Apply + Rollback** può impostare temporaneamente le CVar della sessione dell'editor supportate e poi ripristinarle. Asset, materiali, Post Process Volumes e preset MRQ non vengono modificati.

## Lumen Deep Scan modifica mesh o materiali?

No. La scansione approfondita Lumen scrive i risultati della revisione dai metadati di snapshot e Asset Registry. Non modifica le impostazioni delle schede Static Mesh, i grafi dei materiali, le opzioni di condivisione delle schede dei materiali, la configurazione del progetto o i preset MRQ.

## Cattura screenshot?

Il workflow A/B di Expert Tools scrive report di confronto basati sui soli metadati a meno che un workflow futuro non fornisca percorsi di screenshot. Utilizzare i report per collegare le decisioni e catturare manualmente le prove visive quando necessario.

## Perché alcuni risultati hanno "Confidenza media"?

Molti artefatti visivi dipendono dal contenuto e dal movimento. VFD separa i fatti dalle euristiche in modo da poter indirizzare la revisione manuale senza trattare i metadati come prova.

## Dove vanno finire profili e report?

```text
Saved/VisualFidelityDirector/profiles/
Saved/VisualFidelityDirector/reports/
Saved/VisualFidelityDirector/recipes/
```

## Posso usare VFD dai Blueprint?

Sì. `UVFDCockpitBlueprintLibrary` espone funzioni per profili, elementi di prova, funzionalità e applicazione governata. Vedere `Content/Blueprints/BPF_VFD_API` per esempi collegati.

## Chi posso contattare per il supporto?

Utilizzare l'e-mail di supporto elencata nel descrittore del plugin:
`support@tiny-tool-development.com`.

Discord: `#support` (vedere la scheda del prodotto al momento della pubblicazione).
