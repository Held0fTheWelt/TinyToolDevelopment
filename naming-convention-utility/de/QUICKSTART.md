<!-- doc-provenance: product-facts.yml reconciled 2026-07-04; source AKDB:plugins/NamingConventionUtility/architecture.md -->
# Schnellanleitung

Diese Anleitung führt Sie von der Installation bis zu einem konkreten Ergebnis: Assets in einem Ordner werden nach einer Vorschau- und Bestätigungsphase gemäß Ihrer Namenskonvention umbenannt. Naming Convention Utility funktioniert eigenständig. Es ist kein anderes Plugin erforderlich.

## Was Sie nach dieser Anleitung haben

Die Namensregeln wurden überprüft, ein Ordner in der Naming Workbench gescannt und ausgewählte Assets wurden über das Asset-System von Unreal umbenannt (z. B. `OldWall` -> `SM_OldWall`).

## Anforderungen

- Unreal Engine 5 Editor mit einem Projekt, das umzubenennende Content-Assets enthält.
- Keine Software von Drittanbietern, Konten oder Zusatz-Runtimes erforderlich. Siehe [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## 1. Installieren und Aktivieren

1. Fügen Sie **Naming Convention Utility** aus Ihrer Fab-Bibliothek zum Projekt hinzu oder installieren Sie es in der Engine.
2. Öffnen Sie **Edit > Plugins**, aktivieren Sie **Naming Convention Utility** und starten Sie neu, wenn Sie dazu aufgefordert werden.

## 2. Regeln überprüfen

1. Öffnen Sie **Edit > Project Settings > Plugins > Naming Convention Utility**.
2. Die zentrale Einstellung ist **NamingConventionDataAssetPath**, die standardmäßig auf das mitgelieferte `/NamingConventionUtility/Editor/Data/DA_NamingConvention` verweist.
3. Öffnen Sie dieses DataAsset, um die benutzerdefinierten Projektregeln zu sehen. Jede Regel besitzt ein `FileTypeIdentifier`, `NamingsToRemove`, `PreFix` und `PostFix`.

Beispiel:

```text
FileTypeIdentifier = FTC_STATICMESH
NamingsToRemove    = ["StaticMesh_", "Mesh_"]
PreFix             = "SM_"
PostFix            = ""
```

Empfohlen: Duplizieren Sie das Standard-DataAsset in Ihren Projektinhalt und lassen Sie `NamingConventionDataAssetPath` auf die Kopie verweisen. Sie können auch ein integriertes Workbench-Profil in das konfigurierte Projekt-DataAsset kopieren.

## 3. Scannen in der Naming Workbench

1. Öffnen Sie die **Naming Workbench** über das Plugin-Menü oder klicken Sie mit der rechten Maustaste auf einen Content Browser-Ordner, um die Workbench für diesen Bereich zu öffnen.
2. Wählen Sie ein Profil:
   - **Epic Recommended** für einen Epic-konformen Grundstandard.
   - **Tiny Legacy** für den 1.0.x-Standardstil.
   - **Project Custom** für Ihr konfiguriertes DataAsset.
3. Klicken Sie auf **Scan**. Die Workbench zeigt akzeptierte Umbenennungen, bereits konforme Assets, übersprungene Assets, den Konformitätsprozentsatz und die häufigsten Abweichungen an.

## 4. Eine echte Umbenennung anwenden

1. Suchen Sie ein Static Mesh namens `OldWall` in den akzeptierten Zeilen.
2. Bestätigen Sie, dass der Zielpfad auf `SM_OldWall.SM_OldWall` endet.
3. Lassen Sie die Zeile für die Anwendung ausgewählt.
4. Optional: Klicken Sie auf **Export**, um einen Vorschau-Bericht zu schreiben.
5. Klicken Sie auf **Apply** und bestätigen Sie.

Erwartetes Ergebnis: `OldWall` wird zu `SM_OldWall`; Unreal schließt die Umbenennung ab. Speichern Sie betroffene Pakete anschließend. Apply schreibt einen JSON/Markdown-Audit-Bericht unter `Saved/NamingConventionUtility/Reports/`.

## 5. Häufige Überspringungsgründe

Eine geplante Umbenennung wird übersprungen, wenn der Asset-Typ nicht unterstützt wird, keine Regel zum erkannten Typ passt, der Name bereits der Konvention entspricht, der generierte Name ungültig ist, das Ziel bereits existiert oder zwei Assets zum selben Zielnamen führen würden.

## 6. Nächste Schritte

- Vollständiger Workflow, Regelfelder, DataTable-Konvertierung, Textur-Untertyperkennung: [UserManual.md](UserManual.md).
- Einstellungen: [SettingsReference.md](SettingsReference.md).
- Probleme: [TROUBLESHOOTING.md](TROUBLESHOOTING.md) und [FAQ.md](FAQ.md).

Asset-Umbenennungen betreffen Pakete und Referenzen. Testen Sie zuerst in einem kleinen Ordner, halten Sie die Quellcodeverwaltung vor großen Umbenennungen sauber und überprüfen Sie generierte Redirectoren.
