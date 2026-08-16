<!-- doc-provenance: product-facts.yml reconciled 2026-07-04; source AKDB:plugins/NamingConventionUtility/architecture.md -->
# Benutzerhandbuch

Dieses Handbuch erklärt, wie Sie Naming Convention Utility im Unreal Editor konfigurieren und verwenden.

## Installation

1. Fügen Sie das Plugin zum Ordner `Plugins` Ihres Projekts hinzu oder installieren Sie es über Fab.
2. Aktivieren Sie **Naming Convention Utility** unter **Edit > Plugins**.
3. Starten Sie den Editor neu, falls Unreal dazu auffordert.
4. Bestätigen Sie, dass der Plugin-Inhalt sichtbar ist, wenn Sie die mitgelieferten DataAsset- und DataTable-Beispiele untersuchen möchten.

## DataAsset konfigurieren

Öffnen Sie **Edit > Project Settings > Plugins > Naming Convention Utility**.

Die zentrale Einstellung ist:

```text
NamingConventionDataAssetPath
```

Standard:

```text
/NamingConventionUtility/Editor/Data/DA_NamingConvention.DA_NamingConvention
```

Sie können:

- Das bereitgestellte Standard-Asset nutzen.
- Es in Ihren Projektinhalts-Ordner duplizieren.
- Präfixe und Suffixe bearbeiten, um sie an Ihren Standard anzupassen.
- Ein integriertes Workbench-Profil in das konfigurierte Projekt-DataAsset kopieren.
- Eine kompatible DataTable in das Ziel-DataAsset konvertieren.

## Regelfelder

Jede Regel enthält:

- `FileTypeIdentifier`: die Unreal-Asset-Kategorie, auf die die Regel zutrifft.
- `NamingsToRemove`: Teilstrings, die vor dem Hinzufügen von Präfix/Suffix entfernt werden.
- `PreFix`: Präfix, das dem bereinigten Namen vorangestellt wird.
- `PostFix`: Suffix, das dem bereinigten Namen angehängt wird.

Beispiel:

```text
FileTypeIdentifier = FTC_STATICMESH
NamingsToRemove = ["StaticMesh_", "Mesh_"]
PreFix = "SM_"
PostFix = ""
```

`OldWall` wird zu `SM_OldWall`.

## Naming Workbench

Die Naming Workbench ist die primäre Benutzeroberfläche für Überprüfungs-, Bearbeitungs- und Anwendungs-Workflows.

Verwenden Sie sie zum:

- Auswählen eines Ordnerbereichs.
- Wählen von `epic_recommended`, `tiny_legacy` oder `project_custom`.
- Rekursiven Scannen von Assets.
- Überprüfen akzeptierter, konformer, übersprungener oder ausgewählter Zeilen.
- Prüfen von Quell- und Ziel-Objektpfaden.
- Vergleichen des aktiven Profils mit Epic Recommended.
- Kopieren eines integrierten Profils in Project Custom.
- Bearbeiten ausgewählter Project Custom-Regeln.
- Exportieren von JSON/Markdown-Berichten.
- Anwenden ausgewählter akzeptierter Zeilen über einen geschützten Plan-Hash.

Wenn Sie nach dem Scannen ein Profil ändern oder eine Projektregel bearbeiten, scannen Sie erneut vor dem Anwenden. Der geschützte Anwendungspfad blockiert veraltete Pläne.

## Content Browser Schnellanwendung

Die Content Browser-Ordneraktion bleibt für schnelle Workflows verfügbar:

1. Klicken Sie mit der rechten Maustaste auf einen Content Browser-Ordner.
2. Wählen Sie **Apply Naming Conventions**.
3. Überprüfen Sie den Vorschau-Dialog.
4. Bestätigen Sie, wenn die geplanten Namen korrekt sind.
5. Lassen Sie Unreal die Umbenennung abschließen.
6. Speichern Sie betroffene Assets/Pakete.

## Vorschau und Überspringe-Gründe

Die Vorschau fasst zusammen:

- Anzahl gescannter Assets.
- Anzahl geplanter Umbenennungen.
- Anzahl übersprungener Assets.
- Paare aus altem und neuem Namen.
- Überspringe-Gründe.

Häufige Überspringe-Gründe:

- Asset-Typ wird nicht unterstützt.
- Keine Namensregel für den erkannten Typ vorhanden.
- Name entspricht bereits der Konvention.
- Generierter Name ist ungültig.
- Ziel-Asset existiert bereits.
- Mehrere Assets würden zum selben Ziel führen.
- Überprüfter Plan-Hash ist veraltet.

## Audit-Berichte

Workbench-Export und -Anwendung schreiben Berichte unter:

```text
Saved/NamingConventionUtility/Reports/
```

Die Berichte enthalten Profil-Metadaten, Ordnerbereich, Plan-Hash, Anzahl, Konformitätszusammenfassung, akzeptierte Zeilen, übersprungene Zeilen, ausgewählte Zeilen und angewendete Anzahl.

## DataTable-Konvertierung

Das Plugin kann eine kompatible DataTable in das konfigurierte DataAsset konvertieren.

Erwartetes Zeilen-Struct:

```text
FNamingConventionTableInformation
```

Felder:

- `FileType`
- `ToolType`
- `Value`

Unterstützte Tool-Typen:

- `NCTT_TOREMOVE`
- `NCTT_PREFIX`
- `NCTT_POSTFIX`

Workflow:

1. Wählen Sie das kompatible DataTable-Asset aus.
2. Öffnen Sie sein Kontextmenü.
3. Wählen Sie **Convert NamingConvention Table to DataAsset**.
4. Überprüfen Sie die Bestätigungszusammenfassung.
5. Bestätigen Sie, um die Einträge des Ziel-DataAssets zu ersetzen.

Die Konvertierung nutzt eine Editor-Transaktion und kann über die Undo-Funktion von Unreal rückgängig gemacht werden.

## Textur-Untertyperkennung

Die Textur-Untertyperkennung nutzt:

- `TC_Normalmap`-Komprimierung für Normal Maps.
- Namenstokens wie `atlas`, `normal`, `nrm`, `albedo`, `roughness`, `metallic`, `opacity`, `emissive`, `mask`, `orm` und ähnliche gängige Suffixe.

Wenn eine Textur nicht spezifischer klassifiziert werden kann, fällt sie auf `FTC_TEXTURE` zurück.

## Empfohlener Workflow

Für den Produktionseinsatz:

1. Duplizieren Sie das Standard-DataAsset in Ihr Projekt.
2. Öffnen Sie die Workbench und vergleichen Sie Project Custom mit Epic Recommended.
3. Überprüfen Sie jedes Präfix und Suffix.
4. Testen Sie zuerst in einem kleinen Ordner.
5. Exportieren Sie den Vorschau-Bericht zur Überprüfung bei Bedarf.
6. Wenden Sie ausgewählte Zeilen nur an, wenn der Plan aktuell ist.
7. Speichern oder committen Sie Änderungen, nachdem Unreal die Umbenennung abgeschlossen hat.
8. Führen Sie die Bereinigung von Redirectoren aus, falls aktiviert.

## Undo und Quellcodeverwaltung

Asset-Umbenennungen in Unreal können Pakete und Referenzen betreffen. Nutzen Sie normale Quellcodeverwaltungs-Disziplin:

- Testen Sie zuerst in einem kleinen Ordner.
- Halten Sie die Quellcodeverwaltung vor großen Umbenennungen sauber.
- Überprüfen Sie generierte Redirectoren.
- Speichern Sie betroffene Pakete.
- Committen Sie Umbenennungsoperationen getrennt von unbeteiligten Arbeiten.

## Entfernen des Plugins

Vor dem Entfernen des Plugins:

1. Schließen oder machen Sie ausstehende Asset-Umbenennungen rückgängig.
2. Speichern Sie Content-Pakete.
3. Deaktivieren Sie das Plugin.
4. Starten Sie den Editor neu.

Bereits umbenannte Assets bleiben umbenannt, da die Änderungen über das Asset-System von Unreal angewendet wurden.
