# FAQ

## Wofür ist EditorExtensionBase?

Es ist eine gemeinsame Grundlage für Editor-UI-Plugins zur Tiny Tool Development: wiederverwendbare Editor Utility Widgets, Hilfsprogramme für Auswahl / Checkout / Speicherung, Undo-Vorbereitungshilfen und ein leichtgewichtiges Runtime-Makromodul.

## Ist es ein Endbenutzer-Tool?

Nein. Es registriert kein eigenes Tiny Tools-Produktmenü. Feature-Plugins konsumieren es als Abhängigkeit.

## Welche Unreal-Module lädt es?

`EditorExtensionBase` (Editor) und `EditorExtensionRuntimeBase` (Runtime), wie in `EditorExtensionBase.uplugin` deklariert.

## Erfordert es andere Tiny Tool-Plugins?

Nein. Es erfordert das Plugin **Editor Scripting Utilities** von Unreal (im Descriptor aktiviert). Scene-, AI- oder andere Tiny Tool-Plugins sind optionale Konsumenten, keine Einrichtungsvoraussetzungen.

## Wie lese ich die aktuelle Content Browser-Auswahl?

Rufen Sie `UEditorManagerUtilityLibrary::GetSelectedAssetsForAction` aus Blueprint oder C++ auf, nachdem das Plugin aktiviert wurde. Siehe [QUICKSTART.md](QUICKSTART.md).

## Wie sollte ich eine Undo-Transaktion öffnen?

Besitzen Sie ein `FScopedTransaction` im Aufrufer. `BeginTransactionAndGetSelectedAssets` ist seit Unreal Engine 5.4 veraltet.

## Warum warnen meine Widget-Blueprints zur Laufzeit?

BindWidget-Slots wie Schaltflächen, Textblöcke oder Symbole sind null. Stellen Sie sicher, dass das Utility Widget Blueprint jeden erforderlichen Slot, der in der C++-Basisklasse deklariert ist, bindet.

## Erfolgt CheckoutAndSaveAssets immer erfolgreich?

Nein. Es meldet Checkout- und Speicherergebnisse über boolesche Ausgabeparameter. Quellcodeverwaltungs- oder Speicherfehler werden dort und in verwandten Ergebnis-Codes wie `SucceededWithCheckoutWarning` sichtbar.

## Gibt es projektweite DeveloperSettings?

Nein. Konfigurierbare Felder befinden sich auf den gemeinsamen Widgets und Hilfsprogrammen. Siehe [SettingsReference.md](SettingsReference.md).

## Enthält das Paket Drittanbieter-Software?

Nein. Siehe [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## Welche Engine-Versionen werden unterstützt?

Der verpackte Descriptor zielt auf Unreal Engine 5.4.0 unter Win64, Linux und Mac für die Allow-Liste des Editor-Moduls ab.

## Wo erhalte ich Unterstützung?

Verwenden Sie `mailto:support@tiny-tool-development.com` (Descriptor `SupportURL`) oder den Support-Link auf der Fab-Produktseite.

## Kann ich nur die Runtime-Makros ohne das Editor-Modul verwenden?

Ja. `EditorExtensionRuntimeBase` ist ein separates Runtime-Modul, das für nicht-Editor-Konsumenten abhängigkeitsleicht bleiben soll.

## Modifiziert PrepareUndo Assets sofort?

Es bereitet Undo-Optionen für ausgewählte transaktionale Assets vor und überspringt ungültige Auswahlen mit Warnungen. Die Persistenz erfolgt weiterhin über Checkout-/Speicher-Hilfsprogramme, wenn Sie absichtlich schreiben.

## Können Runtime-Makros editor-spezifische Module laden?

Nein. Halten Sie die Abhängigkeit von `EditorExtensionRuntimeBase` leichtgewichtig. Editor-Widgets und Auswahlhilfsprogramme verbleiben im Editor-Modul.
