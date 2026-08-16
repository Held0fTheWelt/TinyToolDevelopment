<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/LogLevelEditor/architecture.md -->
# Fehlerbehebung

## Das Tool zeigt meine Kategorie nicht an

Prüfen Sie:

- Die Kategorie ist in einem gescannten Quellpfad deklariert oder definiert.
- Die Dateiendung ist `.h`, `.hpp`, `.cpp` oder `.inl`.
- Die Kategorie ist nicht durch permanente oder temporäre Ausblend-Einstellungen verborgen.
- Der Scan ist abgeschlossen oder wird noch verarbeitet.
- Das Makro ist eines der unterstützten Unreal-Log-Makros.

## Der Standard-Verbosity-Wert fehlt oder ist falsch

Der Scanner kann Standardwerte nur aus erkennbaren Makro-Argumenten ableiten. Einige Kategorien werden möglicherweise mit einem leeren oder Fallback-Standardwert aufgeführt.

Lösungen:

- Verwenden Sie nach Möglichkeit Standard-Unreal-Makroformatierung.
- Fügen Sie eine dauerhafte Überschreibung hinzu, wenn Sie einen bekannten Wert benötigen.

## Das Ändern einer Ausführlichkeit bewirkt nichts

Mögliche Ursachen:

- Die Kategorie ist noch nicht durch ein geladenes Modul registriert.
- Unreal hat den Konsolenbefehl abgelehnt.
- Runtime-Code hat die Kategorie nach dem Editor-Befehl erneut geändert.

Prüfen Sie das Output Log auf `LogLogLevelEditor`-Meldungen.

## Gespeicherte Ausführlichkeit wird beim Start nicht angewendet

Prüfen Sie:

- `LogLevelDataAsset` zeigt auf ein gültiges Asset.
- Das DataAsset enthält Überschreibungseinträge.
- Die Kategorie existiert zu dem Zeitpunkt, an dem die Start-Wiederholung läuft.

## Mein DataAsset enthält zu viele Einträge

Das DataAsset sollte nur beabsichtigte Überschreibungen enthalten. Setzen Sie Zeilen auf erkannte Standardwerte zurück, um unnötige Einträge zu entfernen.

## Temporäre Ausblendwerte sind wieder aufgetaucht

Temporäre Ausblendwerte sind flüchtig und überstehen keine Sitzungen. Nutzen Sie `LogChannelsToHide` für dauerhaftes Ausblenden.

## Das Scannen dauert zu lange

Deaktivieren Sie das Scannen von Engine-Plugins und Engine-Quellcode, außer es wird benötigt.

Empfohlene Standardkonfiguration:

```text
bAlsoListEnginePluginChannels = false
bAlsoListEngineSourceChannels = false
```

## Das Output Log ist weiterhin zu laut

Einige Systeme können über mehrere Kategorien hinweg loggen. Suchen Sie nach verwandten Kategorie-Präfixen und passen Sie jeden relevanten Kanal an.

## Das Plugin öffnet sich, zeigt aber keine DataAsset-Überschreibungen

Der Scanner und das DataAsset sind getrennt:

- Scanner: entdeckt verfügbare Kategorien.
- DataAsset: speichert dauerhafte Überschreibungen.

Ein leeres DataAsset ist normal, wenn keine dauerhaften Überschreibungen konfiguriert sind.

## Die Quellcodeverwaltung zeigt ständig Änderungen am DataAsset an

Sie haben wahrscheinlich dauerhafte Überschreibungen geändert. Behalten Sie die Änderungen als Team-Richtlinie bei oder setzen Sie Zeilen vor dem Commit auf Standardwerte zurück.

## Zu sammelnde Support-Informationen

Bei der Meldung eines Problems angeben:

- Unreal Engine-Version.
- Plugin-Version.
- Ob Engine-Quellcode-/Plugin-Scannen aktiviert ist.
- Beispiel für die Deklaration einer Log-Kategorie.
- Relevante `LogLogLevelEditor`-Ausgabe.
