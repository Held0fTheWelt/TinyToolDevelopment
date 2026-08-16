<!-- doc-provenance: AKDB:plugins/ProceduralGeneratedStructures/architecture.md; docs/architecture/plugins/ProceduralGeneratedStructures/product-facts.yml; reconciled 2026-06-21 -->
# ProceduralGeneratedStructures Dokumenation

ProceduralGeneratedStructures baut wiederverwendbare instanziierte Static-Mesh-Strukturen aus einem Data Asset. Der Laufzeit-Actor kann vorhandene `UInstancedStaticMeshComponent`-Instanzen in ein `UProceduralStructureDataAsset` einlesen und dann diese expliziten Instanzen neu bauen oder zusätzliche zeilenbasierte Strukturen generieren. Er macht auch Bauplan- und Statistikdaten verfügbar, sodass Sie Zielkomponenten, blockierende Probleme, Mutationsabsichten, den asynchronen Fortschritt und die exakten Instanzzahlen nach dem Beschneiden (Pruning) überprüfen können, bevor Sie einen Rebuild anwenden.

## Dokumentation

- [QUICKSTART.md](QUICKSTART.md): Installieren → Actor platzieren → Erfassen und Neu bauen, mit erwarteten Ergebnissen.
- [UserManual.md](UserManual.md): vollständiger Workflow, Kernobjekte und Bauhinweise.
- [SettingsReference.md](SettingsReference.md): jede Actor-Eigenschaft und jedes Data-Asset-Feld.
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md) · [FAQ.md](FAQ.md)
- [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md): Erklärung zu Drittanbietersoftware (keine gebündelt).

## Kern-Assets

- `AAsyncProceduralGeneratedActor` besitzt den Build-Workflow und kann Komponenten synchron oder über Editor-/Spiel-Ticks hinweg neu bauen.
- `UProceduralStructureDataAsset` speichert benannte Mesh-Einträge mit expliziten Transformationen und optionalen Zeilengenerierungsregeln.
- `FInstancedComponentConfiguration` ordnet eine benannte instanziierte Mesh-Komponente am Actor einem gespeicherten Data-Asset-Eintrag zu.
- `FProceduralStructureBuildPlan` und `FProceduralStructureElementStats` stellen exakte Vorschaudaten für Tools, Blueprints und UCM-Routen bereit.

## Bauhinweise

- Explizite Transformationen, die aus Szenenkomponenten gelesen werden, werden exakt wiedergegeben und beim Rebuild nicht neuzentriert.
- Generierte Zeilentransformationen können mit `bCenterGeneratedTransforms` um den lokalen XY-Ursprung zentriert werden.
- `InstancesPerFrame` begrenzt, wie viele Instanzen pro Tick hinzugefügt werden, wenn der asynchrone Build aktiviert ist.
- Zeilenzahlen werden vor der Generierung auf nicht-negative Werte begrenzt.
- Baupläne melden die generierte Zeilenkapazität vor dem Beschneiden und die exakte generierte Anzahl nach dem Beschneiden.

## Empfohlener Workflow

1. Fügen Sie einen `AAsyncProceduralGeneratedActor` zu einem Level oder Blueprint hinzu.
2. Fügen Sie ein oder mehrere `UInstancedStaticMeshComponent`-Unterelemente mit stabilen Komponentennamen hinzu.
3. Weisen Sie ein `UProceduralStructureDataAsset` zu.
4. Konfigurieren Sie `ReadInComponentConfiguration`, um vorhandene Komponenteninstanzen zu erfassen.
5. Konfigurieren Sie `ComponentConfiguration`, um diese Einträge neu zu bauen.
6. Überprüfen Sie `GetBuildPlan` oder die Vorschauroute und verwenden Sie die im Editor aufrufbaren Aktionen zum Lesen, Löschen und Bauen, um die Struktur zu iterieren.
