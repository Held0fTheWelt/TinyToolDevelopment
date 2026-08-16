<!-- doc-provenance: AKDB:plugins/VisualFidelityDirector/architecture.md; docs/architecture/plugins/VisualFidelityDirector/product-facts.yml; reconciled 2026-07-12 -->
# Documentazione di Visual Fidelity Director

Questa cartella contiene la documentazione fornita all'acquirente per Visual Fidelity Director. Il workflow principale è autonomo: abilitare il plugin, aprire il cockpit, esaminare i profili di fedeltà e gli assi di composizione, ispezionare gli elementi di prova, approvare opzionalmente le scritture di configurazione governate e utilizzare Expert Tools per i classici workflow di snapshot/ricette senza necessitare di un altro plugin o servizio esterno.

La documentazione attuale del pacchetto è allineata alla versione `2.0.0` e allo stato di pubblicazione `In Publishment`.

## Inizia qui

- [QUICKSTART.md](QUICKSTART.md): installazione, abilitazione, primo aggiornamento del cockpit e un'attività di confronto dei profili.
- [UserManual.md](UserManual.md): ogni azione del cockpit, delle prove e di Expert Tools.
- [SettingsReference.md](SettingsReference.md): controlli, percorsi dei profili, funzioni della libreria Blueprint, output dei report e comportamento di applicazione.
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md): problemi comuni e soluzioni.
- [FAQ.md](FAQ.md): risposte su compatibilità, sicurezza, MRQ, screenshot e supporto.
- [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md): dichiarazione delle dipendenze esterne.

## Ingresso Cockpit

Aprire Visual Fidelity Director da **Tiny Tools > Visual Fidelity Director** (sezione Performance).

La scheda ancorabile offre tre pagine:

| Pagina | Scopo |
| --- | --- |
| **Cockpit** | Barra dei profili, metriche live multi-frame, nove assi di composizione, selettore di varianti, cursori dell'intento, dettaglio dell'asse con percorso di ereditarietà, provenienza, risultati, confronto dei profili e applicazione permanente governata. |
| **Evidence** | Undici blocchi di prove a corsia fissa mappati sugli assi di composizione. |
| **Expert Tools** | Pannello di controllo 1.x integrato per snapshot, ricette, scanner, anteprima di applicazione e report legacy. |

## Profili e report

I profili di fedeltà si trovano in:

```text
Saved/VisualFidelityDirector/profiles/
```

I report di Expert Tools e dei workflow di validazione si trovano in:

```text
Saved/VisualFidelityDirector/reports/
```

Le copie delle ricette rimangono in:

```text
Saved/VisualFidelityDirector/recipes/
```

## Superficie Blueprint

I chiamanti Blueprint in fase di runtime utilizzano `UVFDCockpitBlueprintLibrary` (stessi servizi C++ dell'interfaccia utente del cockpit). Un asset di dimostrazione confezionato è fornito in `Content/Blueprints/BPF_VFD_API`.

## Modello di sicurezza

- Le azioni di revisione del cockpit, gli elementi di prova e i confronti sono in sola lettura a meno che non si utilizzi il cassetto di applicazione governata.
- **L'applicazione permanente governata** scrive solo nei gruppi Scalability di `DefaultGameUserSettings.ini`, nelle impostazioni del renderer di `DefaultEngine.ini` e in `DefaultDeviceProfiles.ini`, e solo dopo approvazione esplicita per destinazione con supporto per backup, verifica e rollback.
- **Expert Tools > Preview Apply + Rollback** rimane il percorso di anteprima CVar della sessione.
- Asset, materiali, Post Process Volumes, preset MRQ, LevelSequences, Blueprint e impostazioni di accessibilità rimangono bloccati.

## Schemi

I file di schema runtime confezionati si trovano nella cartella `Schemas/` nella radice del plugin.

## File correlati

- [../README.md](../README.md): panoramica del prodotto.
- [../CHANGELOG.md](../CHANGELOG.md): cronologia delle versioni.
