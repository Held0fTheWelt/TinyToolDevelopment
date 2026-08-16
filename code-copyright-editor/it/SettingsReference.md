<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/CodeCopyrightEditor/architecture.md -->
# Riferimento impostazioni

Le impostazioni di Code Copyright Editor sono disponibili sotto:

```text
Project Settings > Plugins > Code Copyright Editor
```

La finestra dell'editor espone anche le azioni più importanti per i modelli e il flusso di lavoro.

## Identità

| Impostazione | Predefinito | Usato da |
| --- | --- | --- |
| `OwnerName` | `Your Company or Name` | `{OwnerName}`, `{CopyrightText}`, report |
| `ContactEmail` | Vuoto | `{ContactEmail}` |
| `ProductNameFallback` | `PluginProject` | `{ProductName}` quando non viene trovato alcun nome visualizzato del plugin |
| `CopyrightStartYear` | `2025` | `{Year}`, `{CopyrightText}` |

`{Year}` viene generato come anno di inizio se è uguale all'anno corrente. Se l'anno differisce, viene generato come un intervallo come `2025-2026`.

## Licenza

| Impostazione | Predefinito | Usato da |
| --- | --- | --- |
| `LicenseName` | `Fab Standard End User License Agreement` | `{LicenseName}` |
| `LicenseUrl` | `https://www.fab.com/eula` | `{LicenseUrl}` |
| `LicenseIdentifier` | `LicenseRef-Fab-Standard-EULA` | `{LicenseIdentifier}`, report |

Utilizza identificatori SPDX standard per le licenze standard, ad esempio `MIT` o `Apache-2.0`. Utilizza `LicenseRef-*` per licenze personalizzate o specifiche del marketplace come un EULA di prodotto.

## Modelli

| Impostazione | Scopo |
| --- | --- |
| `SourceNoticeTemplate` | Intestazione generata nei file sorgente. |
| `ProjectSettingsNoticeTemplate` | Nota generata nel campo del copyright a livello di progetto di Unreal. |

## Ambito (Scope)

| Impostazione | Predefinito | Scopo |
| --- | --- | --- |
| `ScanRootPaths` | `Source`, `Plugins` | Cartelle scansionate da `Scan Files`. |
| `SourceFileExtensions` | `.h`, `.hpp`, `.hh`, `.inl`, `.c`, `.cc`, `.cpp`, `.cxx`, `.cs`, `.usf`, `.ush` | Estensioni trattate come file sorgente. |
| `ExcludedPathFragments` | `.git`, `.vs`, `Binaries`, `Content`, `DerivedDataCache`, `External`, `Intermediate`, `Resources`, `Saved`, `ThirdParty` | Frammenti di cartella/percorso saltati durante le scansioni. |
| `ExcludedFilePaths` | Vuoto per impostazione predefinita | File esatti relativi al progetto saltati durante le scansioni. |
| `ExcludedFilePatterns` | `*.generated.h` | Pattern jolly saltati durante le scansioni. |

## Protezione

| Impostazione | Predefinito | Scopo |
| --- | --- | --- |
| `ProtectForeignNotices` | Abilitato | Impedisce che testi di note sconosciuti vengano riscritti automaticamente. |
| `TreatUnrealDefaultNoticesAsReplaceable` | Abilitato | Consente di sostituire le note predefinite/segnaposto di Unreal. |
| `OwnNoticeMarkers` | Nome proprietario, identificatore licenza, testo EULA Fab, testo segnaposto Unreal | Identifica le note che appartengono a questo progetto. |
| `ProtectedNoticeMarkers` | Marcatori del copyright di terze parti e di Epic | Identifica le note che non dovrebbero essere riscritte automaticamente. |

## Configurazione di base raccomandata

Per la maggior parte dei prodotti plugin per Fab:

- Mantieni `ProtectForeignNotices` abilitato.
- Mantieni `TreatUnrealDefaultNoticesAsReplaceable` abilitato.
- Mantieni `ThirdParty`, `External`, `Binaries`, `Intermediate` e `Saved` esclusi.
- Usa `LicenseRef-Fab-Standard-EULA` per prodotti con EULA Fab.
- Mantieni le righe SPDX vicino alla parte superiore del modello per i sorgenti.
- Usa `{FileMetadataBlock}` per un contesto opzionale a livello di file.
