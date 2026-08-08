---
lang: de
title: EditorExtensionBase Troubleshooting
audience: [end_user]
owner_ref: plugin:EditorExtensionBase
applies_to:
  component: EditorExtensionBase
symptom: Editor utility BindWidget slots are null or selection helpers warn in the log.
recovery:
  steps:
    - Confirm the plugin is enabled under Edit > Plugins and restart the editor
    - Re-read the matching troubleshooting entry and apply the documented fix
    - Re-run the quick start smoke check
version:
  since: "1.0"
---
# Fehlerbehebung

Format: Symptom → Ursache → Lösung.

## 0. Ich habe es aktiviert, aber es ist nichts passiert

**Symptom:** Nach dem Aktivieren von **EditorExtensionBase** und dem Neustart gibt es kein neues Tiny-Tools-Menü und keine offensichtliche Änderung der Benutzeroberfläche.  
**Ursache:** Dieses Plugin ist eine gemeinsame Grundlage; es registriert kein eigenes Produktmenü.  
**Lösung:** Überprüfen Sie, ob das Plugin unter **Bearbeiten → Plugins** aktiviert ist, und rufen Sie `UEditorManagerUtilityLibrary::GetSelectedAssetsForAction` aus einem **Editor Utility Widget** oder einem C++-Editor-Tool auf (siehe [QUICKSTART.md](QUICKSTART.md)). Das Fehlen eines neuen Menüs ist erwartungsgemäß.

## 1. Plugin wird aktiviert, aber die Helper-Blueprints können die Bibliothek nicht finden

**Symptom:** Die Blueprint-Knoten für `Editor Manager Utility Library` fehlen nach der Aktivierung.  
**Ursache:** Das Editor-Modul wurde nicht geladen, oder das Editor Utility-Asset wurde kompiliert, bevor das Plugin aktiviert wurde.  
**Lösung:** Bestätigen Sie, dass **EditorExtensionBase** unter **Bearbeiten → Plugins** aktiviert ist, starten Sie den Editor neu und aktualisieren/kompilieren Sie dann das Editor Utility-Blueprint.

## 2. `EditorUtilityButtonWidget: Button is null`

**Symptom:** Das Protokoll `LogEditorExtensionBase` warnt, dass die Schaltfläche null ist.  
**Ursache:** Das Utility Widget Blueprint-Subclass hat den erforderlichen BindWidget-Schaltflächen-Slot nicht gebunden.  
**Lösung:** Öffnen Sie das Widget-Blueprint, binden Sie den auf `UEditorUtilityButtonWidget` deklarierten Schaltflächen-Slot, kompilieren Sie ihn und öffnen Sie das Tool erneut.

## 3. `EditorUtilityButtonWidget: Text block is null`

**Symptom:** Warnung, dass der BindWidget-Textblock null ist.  
**Ursache:** Der Beschriftungs-Textblock ist im Blueprint nicht gebunden.  
**Lösung:** Binden Sie den Textblock-Slot auf der C++-Basis, legen Sie den Anzeigetext fest und kompilieren Sie.

## 4. `EditorUtilityTabButtonWidget: SelectedIcon is null` / `UnselectedIcon is null`

**Symptom:** Der Registerkarten-Schaltflächen-Widget warnt über fehlende Symbole.  
**Ursache:** Die Slots für das ausgewählte oder nicht ausgewählte Symbol sind nicht gebunden oder die Assets fehlen.  
**Lösung:** Weisen Sie und binden Sie beide Symbol-Slots; überprüfen Sie, ob die Soft-/Objekt-Referenzen aufgelöst werden.

## 5. `EditorUtilityTask_PrepareUndo: No assets selected`

**Symptom:** Die Protokolle zur Vorbereitung des Rückgängigmachens melden, dass keine Assets ausgewählt wurden.  
**Ursache:** Die Auswahl im Content Browser ist leer, wenn die Aufgabe ausgeführt wird.  
**Lösung:** Wählen Sie zuerst die transaktionalen Assets aus und führen Sie dann das Prepare-Undo-Utility aus.

## 6. Assets als nicht transaktional übersprungen

**Symptom:** Warnungen, dass ein Asset nicht transaktional ist / kein `UObject` ist / ungültig ist.  
**Ursache:** Die Prepare-Undo-Aufgabe akzeptiert nur gültige transaktionale `UObject`-Assets.  
**Lösung:** Beschränken Sie die Auswahl auf Assets, die Editor-Transaktionen unterstützen; überspringen Sie Nicht-Assets oder flüchtige Objekte.

## 7. Veralteter Begin-Transaction-Helper wird noch verwendet

**Symptom:** Deprecation-Warnungen, die `BeginTransactionAndGetSelectedAssets` referenzieren.  
**Ursache:** Aufrufstellen verwenden noch den in UE 5.4 veralteten Helper.  
**Lösung:** Ersetzen Sie ihn durch `GetSelectedAssetsForAction` plus einem vom Aufrufer verwalteten `FScopedTransaction` und verwenden Sie `CheckoutAndSaveAssets` für die Persistenz.

## 8. Checkout erfolgreich mit Warnungen

**Symptom:** Ergebniscode `SucceededWithCheckoutWarning` oder Checkout-Out-Parameter false, während einige Dateien gespeichert wurden.  
**Ursache:** Die Versionsverwaltung hat während des Checkouts Warnungen zurückgegeben.  
**Lösung:** Überprüfen Sie den Versionsverwaltungsstatus für die Assets, lösen Sie Sperren/Konflikte auf und wiederholen Sie `CheckoutAndSaveAssets`.

## Verwandte Dokumente

- [QUICKSTART.md](QUICKSTART.md)
- [UserManual.md](UserManual.md)
- [SettingsReference.md](SettingsReference.md)
- [FAQ.md](FAQ.md)
