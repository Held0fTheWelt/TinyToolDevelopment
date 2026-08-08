---
lang: de
title: EditorExtensionBase Settings Reference
audience: [end_user]
owner_ref: plugin:EditorExtensionBase
applies_to:
  component: EditorExtensionBase
contract_ref: plugin:EditorExtensionBase/widget-properties
version:
  since: "1.0"
---
# Einstellungen-Referenz

EditorExtensionBase liefert **keine** `UDeveloperSettings`-Klasse oder ein projektbezogenes `.ini`-Einstellungsobjekt mit. Konfigurierbare Werte befinden sich in den gemeinsam genutzten Unterklassen des Editor Utility Widget und in Utility-Objekten als `UPROPERTY`-Felder.

## UEditorToolHeaderWidget

| Name | Typ | Standardwert | Wirkung |
| --- | --- | --- | --- |
| `TitleText` | `FText` | Widget-Standard | Angezeigter Titel im Header. |
| `SubtitleText` | `FText` | Widget-Standard | Sekundäre Zeile unter dem Titel. |
| (BindWidget) Titel-/Untertitelblöcke | Widget-Verweise | müssen gebunden sein | Erforderliche Slate/UMG-Slots; fehlende Bindungen führen zur Laufzeit zu Warnungen. |

## UEditorUtilityButtonWidget

| Name | Typ | Standardwert | Wirkung |
| --- | --- | --- | --- |
| Schaltflächen-Stileigenschaften | Stilfelder im Widget | vom Designer festgelegt | Visueller Stil der gemeinsamen Schaltfläche. |
| (BindWidget) `Button`-/Textblock | Widget-Verweise | müssen gebunden sein | Klickziel und Beschriftung; eine null-Schaltfläche oder ein null-Text führt zu einer Warnung. |

## UEditorUtilityTabButtonWidget

| Name | Typ | Standardwert | Wirkung |
| --- | --- | --- | --- |
| Darstellung ausgewählt/nicht ausgewählt | Icon- und Zustandsfelder | vom Designer festgelegt | Steuert das Erscheinungsbild der ausgewählten Registerkarte. |
| (BindWidget) Schaltflächen-/Icon-Slots | Widget-Verweise | müssen gebunden sein | Fehlende Icons für ausgewählt/nicht ausgewählt führen zu Warnungen. |

## UUndoableAssetActionUtility

| Name | Typ | Standardwert | Wirkung |
| --- | --- | --- | --- |
| Aktionsbeschreibung-/Asset-Felder | Utility-Felder mit `editanywhere` | vom Aufrufer festgelegt | Beschreibt die rückgängig machbare Asset-Aktion, die das Utility ausführt. |
| Ergebniscode | Enum | zur Laufzeit | Enthält `SucceededWithCheckoutWarning`, wenn bei Erfolg Checkout-Warnungen vorliegen. |

## UEditorUtilityTask_PrepareUndo

| Name | Typ | Standardwert | Wirkung |
| --- | --- | --- | --- |
| Ausgewählte Asset-Eingaben | Utility-Felder mit `editanywhere` | vom Aufrufer festgelegt | Assets, die für die Vorbereitung des Rückgängigmachens in Betracht gezogen werden; null/ungültige/nicht-transaktionale Assets werden mit Warnungen übersprungen. |

## Was ist nicht vorhanden

| Erwartete Oberfläche | Status |
| --- | --- |
| `UEditorExtensionBaseSettings` DeveloperSettings | im Quellcode noch nicht verfügbar |
| `Config/DefaultEditorExtensionBase.ini` | nicht ausgeliefert |
| Projekt-Einstellungen-Panel | noch nicht verfügbar |

## Verwandte Dokumente

- [UserManual.md](UserManual.md) — Verhaltenskatalog.
- [QUICKSTART.md](QUICKSTART.md) — erster Aufruf des Selection-Helpers.
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md) — BindWidget- und Selection-Warnungen.
