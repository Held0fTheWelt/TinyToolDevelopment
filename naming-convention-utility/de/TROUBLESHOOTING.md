<!-- doc-provenance: product-facts.yml reconciled 2026-07-04; source AKDB:plugins/NamingConventionUtility/architecture.md -->
# Fehlerbehebung

## Das Kontextmenü erscheint nicht

Prüfen Sie:

- Das Plugin ist aktiviert.
- Der Editor wurde nach dem Aktivieren neu gestartet.
- Sie klicken mit der rechten Maustaste auf einen Content Browser-Ordner für die Ordneraktion.
- Sie wählen eine kompatible DataTable für die Konvertierungsaktion aus.

## Das Tool meldet, dass keine Assets umbenannt werden

Mögliche Gründe:

- Alle Assets entsprechen bereits den konfigurierten Konventionen.
- Asset-Typen werden nicht unterstützt.
- Das konfigurierte DataAsset ist leer.
- Der ausgewählte Ordner enthält keine Assets rekursiv.
- Alle generierten Namen wären ungültig oder kollidieren.

Prüfen Sie Überspringe-Beispiele im Vorschau-Dialog oder den Übersprungen-Filter der Workbench.

## Die Workbench blockiert das Anwenden als veraltet (Stale)

Der Workbench-Anwendungspfad vergleicht den überprüften Plan-Hash mit dem aktuellen Ordner-/Profil-/Regelplan.

Mögliche Gründe:

- Sie haben den Ordnerbereich nach dem Scannen geändert.
- Sie haben das Profil nach dem Scannen gewechselt.
- Sie haben eine Project Custom-Regel nach dem Scannen bearbeitet.
- Assets wurden nach dem Scannen geändert, verschoben oder umbenannt.

Klicken Sie erneut auf **Scan**, überprüfen Sie die aktualisierten Zielpfade und wenden Sie ausgewählte Zeilen an.

## Ich kann ein integriertes Profil nicht bearbeiten

`epic_recommended` und `tiny_legacy` sind schreibgeschützte Baselines.

Nutzen Sie **Copy to Project**, um das konfigurierte Project Custom DataAsset durch dieses Profil zu ersetzen, und bearbeiten Sie dann die Project Custom-Regeln.

## Eine Textur erhielt das generische `T_`-Präfix

Die Textur-Untertyperkennung ist heuristisch. Wenn der Texturname und die Komprimierungseinstellungen keinen spezifischen Zweck anzeigen, nutzt das Plugin die generische Texturregel.

Lösungen:

- Benennen Sie die Quelltextur vor dem Ausführen des Utilities mit klareren Tokens um.
- Passen Sie Ihre Regeln an, um das generische `T_` für alle Texturen zu nutzen.

## Eine Umbenennung schlug nach Bestätigung fehl

Unreal-Asset-Umbenennungen können fehlschlagen aufgrund von:

- Bestehenden Referenzen.
- Quellcodeverwaltungs-Checkout-Problemen.
- Gesperrten Paketen.
- Existierenden Assets, die während der Planung nicht sichtbar waren.

Prüfen Sie das Output Log. Wenn Sie die Workbench genutzt haben, prüfen Sie auch den JSON/Markdown-Bericht unter `Saved/NamingConventionUtility/Reports/`.

## Redirectoren bleiben bestehen

Das Plugin versucht eine Redirector-Korrektur nur nach tatsächlichen Umbenennungen und nur, wenn aktiviert.

Wenn Redirectoren bestehen bleiben:

- Führen Sie **Fix Up Redirectors in Folder** manuell aus.
- Prüfen Sie den Checkout-Status der Quellcodeverwaltung.
- Speichern Sie betroffene Pakete.

## DataTable-Konvertierung hat mein Ziel-Asset gelöscht

Die Konvertierung bittet vor dem Ersetzen von Einträgen um Bestätigung und nutzt eine Transaktion. Nutzen Sie sofort das Rückgängigmachen (Undo) in Unreal.

## Zu sammelnde Support-Informationen

Bei der Meldung eines Problems angeben:

- Unreal Engine-Version.
- Plugin-Version.
- Ausgewählter Ordnerpfad.
- Konfigurierter DataAsset-Pfad.
- Beispiel für alten und erwarteten neuen Namen.
