---
lang: de
title: EditorExtensionBase Quick Start
audience: [end_user]
owner_ref: plugin:EditorExtensionBase
applies_to:
  component: EditorExtensionBase
preconditions:
  - Unreal Engine project open with the plugin package available
  - Edit > Plugins can enable EditorExtensionBase
expected_result:
  text: GetSelectedAssetsForAction returns the current Content Browser selection after the plugin is enabled.
version:
  since: "1.0"
---
# Schnellstart

Dieser Leitfaden führt Sie von der Installation bis zur **ersten echten Anwendung**: Aktivieren von EditorExtensionBase und Aufrufen eines gemeinsam genutzten Editor-Hilfsprogramms aus einem Blueprint-Utility oder einem C++-Editor-Tool. EditorExtensionBase ist eine Unterstützungsschicht für andere Editor-Plugins – es ist kein eigenständiges Produkt im Sinne eines Tiny-Tools-Menüs.

## Was Sie nach diesem Leitfaden haben werden

Das Plugin ist aktiviert, und ein erfolgreicher Aufruf von `UEditorManagerUtilityLibrary::GetSelectedAssetsForAction` (oder der äquivalenten, für Blueprints aufrufbaren Variante) gibt die aktuelle Auswahl im Content Browser zurück.

## Voraussetzungen

- Unreal Engine 5.4 oder höher (Deskriptor `EngineVersion` 5.4.0).
- Editor Scripting Utilities aktiviert (deklarierte Abhängigkeit in `EditorExtensionBase.uplugin`).
- Keine Drittanbieter-Software, kein Konto und keine externe Laufzeit. Siehe [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## 1. Installation und Aktivierung

1. Fügen Sie **EditorExtensionBase** aus Ihrer Fab-Bibliothek zum Projekt hinzu (oder installieren Sie es im Plugins-Verzeichnis der Engine).
2. Öffnen Sie **Bearbeiten → Plugins**, aktivieren Sie **EditorExtensionBase** und starten Sie das Programm neu, wenn Sie dazu aufgefordert werden.
3. Stellen Sie sicher, dass **Editor Scripting Utilities** weiterhin aktiviert ist.

## 2. Überprüfen, ob die Module geladen wurden

Nach dem Neustart stellt das Paket zwei Module bereit:

| Modul | Typ | Rolle |
| --- | --- | --- |
| `EditorExtensionBase` | Editor | Widgets, Auswahlhilfen, Undo-Hilfsprogramme. |
| `EditorExtensionRuntimeBase` | Laufzeit | Leichtgewichtige Makros, die für Nicht-Editor-Konsumenten sicher sind. |

## 3. Durchgeführtes Beispiel: Lesen der aktuellen Auswahl

1. Wählen Sie ein oder mehrere Assets im Content Browser aus.
2. Rufen Sie aus einem Editor Utility Widget oder einem Editor-C++-Tool, das von diesem Plugin abhängt, Folgendes auf:

```cpp
TArray<UObject*> Selected = UEditorManagerUtilityLibrary::GetSelectedAssetsForAction(nullptr);
```

3. Speichern Sie die zurückgegebenen Objekte oder führen Sie Aktionen damit durch, indem Sie `CheckoutAndSaveAssets` aufrufen, wenn Sie explizit schreiben:

```cpp
bool bCheckoutOk = false;
bool bSaveOk = false;
const bool bOk = UEditorManagerUtilityLibrary::CheckoutAndSaveAssets(
	Selected, bCheckoutOk, bSaveOk);
```

## Erwartetes Ergebnis

- `Selected` enthält die Auswahl des Content Browser (oder ist leer, wenn nichts ausgewählt ist).
- Beim Aufruf von `CheckoutAndSaveAssets` melden die booleschen Ausgabeparameter die Ergebnisse des Checkouts und des Speicherns, ohne eine Transaktion für Sie zu erstellen – der Aufrufer ist für den `FScopedTransaction`-Bereich verantwortlich.

## Nächste Schritte

- Lesen Sie [UserManual.md](UserManual.md) für das Widget- und Utility-Katalog.
- Lesen Sie [SettingsReference.md](SettingsReference.md) für bearbeitbare Eigenschaften der gemeinsam genutzten Widgets.
- Verwenden Sie [TROUBLESHOOTING.md](TROUBLESHOOTING.md), wenn BindWidget-Slots oder Auswahlhilfen Warnungen im Protokoll ausgeben.
