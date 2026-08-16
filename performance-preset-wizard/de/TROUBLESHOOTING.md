<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/PerformancePresetWizard/architecture.md -->
# Fehlerbehebung

## Das Plugin erscheint nicht im Tools-Menü

Prüfen Sie, ob das Plugin unter **Edit > Plugins** aktiviert ist, und starten Sie den Editor neu.

## Es werden keine Voreinstellungen aufgelistet

Klicken Sie im Assistenten auf **Refresh**. Stellen Sie sicher, dass es sich bei den Assets um `UPerformancePresetAsset`-Data-Assets handelt.

## Eine Voreinstellung kann nicht angewendet werden

Stellen Sie sicher, dass eine Voreinstellung ausgewählt ist. Wenn das Asset gelöscht oder verschoben wurde, aktualisieren Sie die Liste.

## Einige CVars werden als fehlend gemeldet

Der CVar-Name konnte im Konsolen-Manager von Unreal nicht aufgelöst werden (z. B. Tippfehler, deaktiviertes Plugin oder andere Engine-Version). Fehlende CVars verhindern das Anwenden der restlichen Voreinstellung nicht.

## CVars werden als ungültig gezählt

Ungültige Einträge haben nach dem Trimmen einen leeren Namen oder leeren Wert. Korrigieren Sie die Zeile im Bulk-Editor.

## "Restore Previous" ist nicht verfügbar

Die Wiederherstellung ist nur verfügbar, nachdem in der aktuellen Editor-Sitzung eine Voreinstellung angewendet wurde.

## Die Start-Voreinstellung wird nicht angewendet

Prüfen Sie, ob **Apply Preset On Editor Startup** aktiviert ist und **Startup Preset** auf ein gültiges Asset zeigt.
