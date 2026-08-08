# Benutzerhandbuch

Editor Extension Base bündelt gemeinsam genutzte Unreal-Editor-UI-Primitiven und Hilfsbibliotheken, damit Feature-Plugins ein konsistentes Verhalten für Auswahl, Check-out, Speicherung und Rückgängigmachung gewährleisten können.

## Zielgruppe

- Plugin-Autoren, die Editor Utility Widgets oder Editor-Tools entwickeln.
- Teams, die die Tiny Tool Development-Editor-UX standardisieren möchten, ohne Widget-Boilerplate zu kopieren.

Dieses Plugin ist **kein** Endbenutzer-Tool mit einem eigenen Menüeintrag für Tiny Tools.

## Module

| Modul | Laden | Inhalt |
| --- | --- | --- |
| `EditorExtensionBase` | Editor / Standard | Widgets, `UEditorManagerUtilityLibrary`, Hilfsfunktionen für Undo / Asset-Aktionen. |
| `EditorExtensionRuntimeBase` | Runtime / Standard | Gemeinsam genutzte Makros (`UsefulMacros.h`) und Modul-Einstiegspunkt. |

## Gemeinsam genutzte Widgets

<!-- image slot: eeb-widget-overview -->

| Klasse | Zweck |
| --- | --- |
| `UEditorToolHeaderWidget` | Kopfzeile mit Titel-/Untertitel-BindWidget-Slots und bearbarem Anzeigetext. |
| `UEditorUtilityButtonWidget` | Formatierter Button mit Textblock-BindWidgets und Klick-Delegate. |
| `UEditorUtilityTabButtonWidget` | Tab-ähnlicher Button mit Slots für ausgewählte/nicht ausgewählte Symbole. |
| `UTwoPaneUserWidget` | Container für Zwei-Spalten-Layouts in Editor-Utility-Bildschirmen. |

Widget-Blueprint-Subklassen müssen die deklarierten BindWidget-Slots binden; fehlende Bindungen führen zu Warnungen unter `LogEditorExtensionBase`.

## Editor Manager Utility Library

`UEditorManagerUtilityLibrary` erweitert `UEditorUtilityLibrary` um Hilfsfunktionen für Auswahl und Persistenz:

| Funktion | Verhalten |
| --- | --- |
| `GetSelectedAssetsForAction` | Gibt die aktuelle Auswahl zurück, optional verankert durch ein primäres Objekt. |
| `CheckoutAndSaveAssets` | Versucht den Source-Control-Check-out und die Speicherung; meldet den Erfolg über Ausgabeparameter. |
| `GetEditorWorld` | Gibt die aktuelle Editor-Welt zurück, sofern verfügbar. |
| `BeginTransactionAndGetSelectedAssets` | **In 5.4 veraltet** — Aufrufer sollten `FScopedTransaction` selbst verwalten. |

## Undo und Asset-Aktionen

| Klasse | Verhalten |
| --- | --- |
| `UEditorUtilityTask_PrepareUndo` | Editor-Utility-Aufgabe, die Undo-Optionen für ausgewählte transaktionale Assets vorbereitet; überspringt Null-, ungültige oder nicht-transactionale Objekte mit Warnungen. |
| `UUndoableAssetActionUtility` | Kodiert Ergebnisse von undo-fähigen Asset-Aktionen, einschließlich `SucceededWithCheckoutWarning`, wenn Check-out-Warnungen zusammen mit dem Erfolg auftreten. |

## Designregeln

1. Halten Sie funktionspezifische Geschäftslogik im konsumierenden Plugin.
2. Behandeln Sie dieses Plugin nicht als Voraussetzung für die Einrichtung von Szenen- oder AI-Plugins.
3. Bevorzugen Sie aufruferverwaltete Transaktionen gegenüber der veralteten begin-transaction-Hilfsfunktion.

## Optionale Integrationen

Konsumierende Tiny Tool Editor-Plugins können auf Editor Extension Base für UI-Konsistenz zurückgreifen. Diese Integrationen liegen in der Verantwortung des Konsumenten; dieses Paket degradiert nur zu „Hilfsfunktionen nicht verfügbar“, wenn es nicht aktiviert ist — es ersetzt nicht das Verhalten anderer Plugins.

## Verwandte Dokumente

- [QUICKSTART.md](QUICKSTART.md)
- [SettingsReference.md](SettingsReference.md)
- [FAQ.md](FAQ.md)
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md)
