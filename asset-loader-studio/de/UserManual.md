<!-- doc-provenance: product-facts.yml reconciled 2026-07-01; source AKDB:plugins/AssetLoaderStudio/architecture.md -->
# Benutzerhandbuch für Asset Loader Studio

Öffnen Sie den Arbeitsbereich über **Tiny Tools -> Asset Loader Studio -> Asset Loader Studio**.

Asset Loader Studio ist um einen einzigen Überprüfungszyklus aufgebaut: Inspektion, Validierung, Vorschau, Anwendung und Audit. Sie können nach der Inspektion stoppen oder, sofern das aktive Berechtigungsprofil dies zulässt, mit den verwalteten Änderungen fortfahren.

Der Arbeitsbereich enthält sieben Ansichten:

- **Graph** zeigt Knoten für Assets, Zeilen, Felder, Referenzen und Diagnosen.
- **Tabelle** zeigt schema-aware DataAsset/DataTable-Zeilen und bearbeitbare Felder.
- **Validierung** erklärt fehlende Referenzen, ungültige Pfade, doppelte IDs und Berechtigungssperren.
- **Jobs** zeigt den Status der neuesten Laufzeit-Ladeanforderung.
- **Inspektor** zeigt den aktiven Modus, das Berechtigungsprofil, die letzte Vorschau und den letzten Anwendungsbericht.
- **Verlauf** speichert die letzten Arbeitsbereichsaktionen.
- **Governance** zeigt das aktive Profil, Routen-Overrides, Audit-Status und Profilaktionen.

Modi steuern die Mutationsermächtigung:

- **Einfach** verwendet das schreibgeschützte Profil.
- **Geführt** ermöglicht sichere schrittweise Änderungen mit Genehmigung.
- **Experte** ermöglicht breitere Bulk-/Persist-Vorschauen und erfordert dennoch eine Genehmigung vor der Anwendung.

Verwenden Sie **Inspect** (Inspektion), nachdem Sie einen vollständigen Objekt-Pfad wie `/Game/Data/DT_Items.DT_Items` eingegeben haben. Verwenden Sie die Eingabefelder für Zeile, Feld und Neuer Wert, um eine strukturierte Feldaktualisierung in der Vorschau anzuzeigen. **Apply** (Anwenden) führt nur die letzte genehmigte Vorschau aus und markiert geänderte Pakete als „dirty“ für das explizite Speichern.

## Überprüfungszyklus

1. Inspektion des Quellassets.
2. Überprüfung des Graph-/Tabellenstatus und der Diagnosen.
3. Auswahl eines Profils, das der benötigten Ermächtigung entspricht.
4. Vorschau der Operation und Überprüfung von Zielen, Plan-Hash, betroffenen Zählern, Risiko und Wiederherstellungsleitfaden.
5. Nur die gerade überprüfte Vorschau anwenden.
6. Inspektion des Anwendungsberichts und des Audit-Verlaufs.
7. Manuelles Speichern der „dirty“ Pakete nach der Überprüfung.
