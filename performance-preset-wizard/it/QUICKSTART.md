<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/PerformancePresetWizard/architecture.md -->
# Guida rapida

Questa guida ti accompagna dall'installazione a un **risultato concreto**: un preset di prestazioni applicato al tuo editor (scalabilità + variabili di console), che puoi ripristinare completamente con un solo clic. Performance Preset Wizard funziona in modo autonomo.

## Cosa otterrai dopo questa guida

La procedura guidata aperta con i preset rilevati, un preset applicato (livelli di scalabilità + sovrascritture CVar) e la possibilità di ripristinare le impostazioni precedenti.

## Requisiti

- Editor di Unreal Engine 5. L'applicazione in fase di esecuzione in un gioco pacchettizzato è opzionale.
- Nessun software di terze parti, account o runtime aggiuntivo richiesto. Vedi [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## 1. Installazione e abilitazione

1. Aggiungi **Performance Preset Wizard** dalla tua libreria Fab al progetto (o installalo nel motore).
2. Apri **Edit → Plugins**, abilita **Performance Preset Wizard** e riavvia quando richiesto.

## 2. Aprire la procedura guidata

1. Apri **Tools → Performance → Performance Preset Wizard**.
2. La procedura guidata analizza il registro degli asset alla ricerca di asset `UPerformancePresetAsset` e li elenca per nome visualizzato, piattaforma di destinazione e percorso.
3. Fai clic su un preset per caricare il relativo pannello dei dettagli.

## 3. Un esempio pratico: applicare e ripristinare

1. Seleziona un preset di esempio incluso.
2. Fai clic su **Apply Preset**.

**Risultato atteso:** La procedura guidata acquisisce un punto di ripristino, limita la scalabilità all'intervallo `0..4` di Unreal e la applica, quindi applica ciascuna sovrascrittura CVar.

3. Fai clic su **Restore Previous**.

**Risultato atteso:** La struttura di scalabilità e le CVar specifiche modificate dal preset tornano ai valori acquisiti immediatamente prima dell'applicazione.

## 4. Creare un proprio preset

Apri un qualsiasi `PerformancePresetAsset` nel Content Browser. Il pannello Details offre menu a discesa per categoria e un **editor di CVar in blocco**:

```text
# Le righe di commento sono consentite
r.ScreenPercentage=85
r.Nanite=1
r.Shadow.Virtual.Enable=1,editor
```

`,editor` contrassegna una sovrascrittura come riservata all'editor. Usa **Export** per scrivere l'array nell'editor di testo e **Apply** per analizzarlo di nuovo nell'asset. Vedi [PresetAuthoringGuide.md](PresetAuthoringGuide.md).

## 5. Opzionale: Utilizzo all'avvio e in runtime

- **Avvio dell'editor:** *Project Settings → Plugins → Performance Preset Wizard* → **Apply Preset On Editor Startup** + **Startup Preset**.
- **Gioco pacchettizzato:** Applica i preset tramite `UPerformancePresetRuntimeSubsystem.ApplyRuntimePreset` e `RestoreLatestBackup`, oppure usa il widget `UPerformancePresetRuntimeSelectorWidget`. Vedi [RuntimeUsage.md](RuntimeUsage.md).

## 6. Passaggi successivi

- Flusso di lavoro completo e cronologia dei backup: [UserManual.md](UserManual.md).
- Preset inclusi: [SamplePresetsReference.md](SamplePresetsReference.md).
- Impostazioni: [SettingsReference.md](SettingsReference.md). Problemi: [TROUBLESHOOTING.md](TROUBLESHOOTING.md), [FAQ.md](FAQ.md).
