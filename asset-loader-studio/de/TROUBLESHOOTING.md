<!-- doc-provenance: product-facts.yml reconciled 2026-07-01; source AKDB:plugins/AssetLoaderStudio/architecture.md -->
# Fehlerbehebung

## Fehlende Assets

Verwenden Sie vollständige Objektpfade mit dem Objekt-Suffix, beispielsweise `/Game/Data/DA_Item.DA_Item`. Wenn die Validierung `ALS.Table.MissingReferencedAsset` meldet, leiten Sie das Feld auf ein vorhandenes Asset um oder leeren Sie es.

## Falsche Pfade

`ALS.InvalidSoftObjectPath` und `ALS.Table.InvalidReferencePath` bedeuten, dass der Pfad nicht als Unreal-Objektpfad geparst werden kann. Kopieren Sie die Referenz erneut aus dem Content Browser.

## Fehlgeschlagene Anwendungsaktionen (Applies)

Anwendungen erfordern eine zulässige Vorschau und ein Genehmigungs-Token. Im Editor-Workspace genehmigt die Schaltfläche "Apply" die letzte Vorschau. Setzen Sie bei der Automatisierung `approval_token` auf die Vorschau-ID oder auf `approved`.

## Berechtigungsablehnungen

Verwenden Sie `asset_loader_studio.state.read.v1`, um aktive Profile zu inspizieren. Häufige Ablehnungen betreffen den Schreibschutzmodus, den reinen Dry-Run-Modus, Grenzen für betroffene Zeilen/Assets, Pfade außerhalb von `allowed_roots` oder eine fehlende destruktive Berechtigung.

## Fehlgeschlagenes Speichern

Generisches Anwenden markiert Pakete als geändert ("dirty") und liefert Hinweise zur Wiederherstellung. Speichern Sie nach Überprüfung der geänderten Assets über den Speicher-Dialog des Unreal Editors oder Ihren Quellcode-Verwaltungs-Workflow.

## Leere oder doppelte Zeilen

DataTables mit leeren oder doppelten Zeilen-IDs können nicht sicher auf stabile Zeilenoperationen abgebildet werden. Benennen Sie die Zeilen in der besitzenden Tabelle um oder reparieren Sie sie, und erfassen Sie dann einen neuen Snapshot.

## Blockierte destruktive Aktionen

Löschungen und andere destruktive Operationen benötigen ein Profil, das sie zulässt, sowie ein explizites destruktives Genehmigungs-Token. Es wird empfohlen, den Plan vorher vorzuschauen, Backups oder den Quellcode-Verwaltungsstatus zu sichern und nur die überprüfte Vorschau anzuwenden.
