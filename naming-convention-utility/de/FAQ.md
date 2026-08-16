<!-- doc-provenance: product-facts.yml reconciled 2026-07-04; source AKDB:plugins/NamingConventionUtility/architecture.md -->
# FAQ (Häufig gestellte Fragen)

## Benennt das Plugin Assets um oder berichtet es nur Namen?

Es benennt Assets um, nachdem Sie die validierte Vorschau bestätigen. Die Umbenennung erfolgt über Unreals `IAssetTools::RenameAssets`.

## Benennt es Ordner um?

Nein. Es scannt ausgewählte Ordner rekursiv und benennt darin enthaltene Assets um.

## Kann ich Änderungen zuerst in einer Vorschau prüfen?

Ja. Die Naming Workbench erstellt einen Umbenennungsplan, zeigt akzeptierte/konforme/übersprungene Zeilen an und lässt Sie vor dem Anwenden einen Bericht exportieren.

## Was passiert, wenn zwei Assets denselben Namen erhalten würden?

Beide kollidierenden Einträge werden aus dem Umbenennungsplan übersprungen. Die Zusammenfassung enthält entsprechende Überspringe-Gründe.

## Kann es Texturtypen erkennen?

Partiell. Es nutzt Komprimierungseinstellungen und gängige Namenstokens für Normal, Diffuse, Mask, Roughness, Metallic, Opacity und Emissive Texturen.

## Ändert es Blueprint-Klassennamen?

Es benennt das Asset um. Es schreibt keine C++-Symbole oder internen Gameplay-Namenskonventionen um.

## Kann ich meine eigenen Präfixe verwenden?

Ja. Bearbeiten Sie das konfigurierte `UNamingConventionsDataAsset` oder nutzen Sie die Workbench.

## Enthält es einen Standard im Epic-Stil?

Ja. Die Workbench enthält ein schreibgeschütztes `epic_recommended`-Profil sowie ein `tiny_legacy`-Profil.

## Kann ich Konventionen aus einer Tabellenkalkulation importieren?

Ja. Importieren Sie eine kompatible DataTable und nutzen Sie die Konvertierungsfunktion im Kontextmenü.

## Ist der Standard-Namensstandard obligatorisch?

Nein. Er ist ein Start-Preset. Studios sollten Project Custom, Epic Recommended, Tiny Legacy oder ihr eigenes bearbeitetes DataAsset nutzen.

## Erstellt es Berichte?

Ja. Workbench-Export/Anwendung schreibt JSON- und Markdown-Berichte unter `Saved/NamingConventionUtility/Reports/`.

## Korrigiert es Redirectoren?

Der Haupt-Workflow kann nach tatsächlichen Umbenennungen eine Korrektur von Redirectoren versuchen, wenn die Einstellung aktiviert ist.

## Warum wurde ein Asset als nicht unterstützt übersprungen?

Die Asset-Klasse ist von der Typerkennung des Plugins nicht abgedeckt. Sie können den Quellcode erweitern.

## Ist es sicher für große Ordner?

Es ist sicherer als ein blindes Umbenennen, da es einen Plan validiert und als Vorschau anzeigt, aber große Umbenennungen erfordern dennoch Sorgfalt.

## Funktioniert es in paketierten Spielen?

Nein. Es ist ein Editor-Plugin.
