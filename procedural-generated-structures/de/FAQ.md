<!-- doc-provenance: AKDB:plugins/ProceduralGeneratedStructures/architecture.md; docs/architecture/plugins/ProceduralGeneratedStructures/product-facts.yml; reconciled 2026-06-21 -->
# FAQ

**Benötigt dieses Plugin ein anderes Plugin?**
Nein. Es funktioniert völlig eigenständig.

**Enthält es Meshes?**
Nein. Sie stellen Ihre eigenen `UStaticMesh`-Assets bereit; das Plugin instanziiert sie.

**Welche Engine-Versionen werden unterstützt?**
Unreal Engine 5.4+ (Win64, Linux, Mac). Das Modul ist Runtime, sodass der Actor im Editor und in paketierten Spielen funktioniert.

**Bündelt es Drittanbietersoftware, Python oder AI-Modelle?**
Nein. Siehe [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

**Was ist der Unterschied zwischen expliziten Instanzen und Zeilengenerierung?**
Explizite Instanzen sind exakte Transformationen (oft aus bestehenden Komponenten erfasst) und werden wie besehen wiedergegeben. Die Zeilengenerierung erzeugt prozedural Instanzen aus Zeilenzahlen und Transformationsbewegungen pro Dimension, die im Data Asset definiert sind.

**Kann ich zur Laufzeit bauen, nicht nur im Editor?**
Ja. Der Actor ist laufzeitfähig und kann synchron oder über Ticks hinweg bauen (`bUseAsyncBuild`).

**Wie vermeide ich Ruckler bei großen Strukturen?**
Aktivieren Sie `bUseAsyncBuild` und passen Sie `InstancesPerFrame` an.

**Kann ich vor der Mutation von Komponenten eine Vorschau anzeigen lassen?**
Ja. Verwenden Sie `GetBuildPlan` oder die Rebuild-Vorschauroute. Der Plan meldet Zielkomponenten, blockierende Probleme, Mutationsabsichten und exakte Instanzzahlen nach dem Beschneiden.

**Können Tools den asynchronen Build-Fortschritt anzeigen?**
Ja. `GetEstimatedBuildInstanceCount`, `GetAddedBuildInstanceCount` und `GetBuildProgress` stellen den Fortschritt für Editor-Tools, Blueprints und Automatisierungsrouten bereit.

**Wo melde ich Probleme oder erhalte Support?**
Verwenden Sie den Support-Link auf der Fab-Produktseite.
