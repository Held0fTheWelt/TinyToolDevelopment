<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/CodeCopyrightEditor/architecture.md -->
# Documentazione di Code Copyright Editor

Code Copyright Editor mantiene coerenti le intestazioni del codice sorgente di Unreal Engine in tutto il progetto. Può aggiornare la nota sul copyright nelle impostazioni di progetto (Project Settings), scansionare l'albero dei sorgenti, riscrivere i file selezionati ed essere eseguito come controllo CI headless.

Questa cartella contiene la documentazione completa fornita con il plugin.

## Inizia da qui

- [QUICKSTART.md](QUICKSTART.md): installazione, prima scansione e un passaggio di applicazione reale con i risultati attesi.
- [UserManual.md](UserManual.md): flusso di lavoro completo dell'editor e uso dell'interfaccia utente.
- [SettingsReference.md](SettingsReference.md): ogni impostazione, i valori predefiniti e la configurazione di base raccomandata.
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md): problemi comuni e soluzioni.
- [FAQ.md](FAQ.md): domande e risposte pronte per Fab e gli acquirenti.
- [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md): dichiarazione sui software di terze parti (nessuno incluso).

## Flusso di lavoro rapido nell'editor

1. Apri **Tools > Code Tools > Code Copyright Editor**.
2. Modifica i modelli di nota per i sorgenti e per il progetto.
3. Usa **Scan Files** per classificare il codice sorgente senza scrivere file.
4. Esamina i badge di stato e seleziona solo i file che devono essere riscritti.
5. Aggiungi informazioni e descrizioni opzionali per singolo file per i file selezionati.
6. Usa **Apply Selected** dopo aver controllato l'anteprima.

## Token dei modelli rapidi

Token comuni:

- `{CopyrightText}`
- `{OwnerName}`
- `{ContactEmail}`
- `{ProductName}`
- `{ModuleName}`
- `{FileName}`
- `{RelativeFilePath}`
- `{Year}`
- `{LicenseName}`
- `{LicenseUrl}`
- `{LicenseIdentifier}`
- `{FileInformation}`
- `{FileDescription}`
- `{FileMetadataBlock}`

Per intestazioni conformi a REUSE/SPDX, mantieni questi due tag vicino alla parte superiore del modello:

```text
/* {CopyrightText}
 * SPDX-FileCopyrightText: {CopyrightText}
 * SPDX-License-Identifier: {LicenseIdentifier}
```

## Commandlet

Esegui lo stesso scanner dalla CI o da un terminale locale:

```powershell
UnrealEditor-Cmd.exe "D:\PluginProjectGit\PluginProject.uproject" -run=CodeCopyrightCheck -unattended -nop4 -nosplash -NoShaderCompile -ReportDir="Saved\CodeCopyrightEditor\Reports"
```

Opzioni utili:

- `-Fix`: riscrive i file modificabili prima di produrre il report finale.
- `-ReportDir=<Path>`: scrive i report in una directory relativa al progetto o assoluta.
- `-FailOnProtected`: tratta le note esterne protette come errori di CI.
- `-NoJson`, `-NoSpdx`, `-NoReuse`: salta i singoli formati di report.
- `-NoFail`: scrive i report ma restituisce sempre il codice di uscita `0`.

Per impostazione predefinita, la CI fallisce quando i file verrebbero modificati, esistono conflitti o i file non possono essere letti/scritti. Le note protette di terze parti vengono segnalate ma non fanno fallire la build a meno che non sia impostato `-FailOnProtected`.

## Report rapidi

Il commandlet scrive:

- `CodeCopyrightReport.json`: riepilogo della scansione leggibile dalla macchina.
- `CodeCopyrightReport.spdx`: report in stile Tag/Value SPDX 2.3.
- `REUSE-Report.md`: report di revisione REUSE/SPDX leggibile dall'uomo.

## Nota legale

Code Copyright Editor aiuta ad applicare e rivedere il testo delle note in modo coerente. Non decide la proprietà legale, non valida licenze di terze parti, non concede diritti né sostituisce la consulenza legale.

## Riferimenti

- Specifiche REUSE 3.3: https://reuse.software/spec-3.3/
- Specifiche SPDX 2.3: https://spdx.github.io/spdx-spec/v2.3/
- API UCommandlet Unreal Engine: https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/Engine/Commandlets/UCommandlet
