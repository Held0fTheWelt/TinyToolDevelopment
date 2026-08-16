<!-- doc-provenance: AKDB:plugins/ProceduralGeneratedStructures/architecture.md; docs/architecture/plugins/ProceduralGeneratedStructures/product-facts.yml; reconciled 2026-06-21 -->
# Fehlerbehebung

## Ich habe das Plugin aktiviert, aber es passiert nichts

Das Plugin fügt die Klasse `AAsyncProceduralGeneratedActor` und das `UProceduralStructureDataAsset` hinzu.
Platzieren Sie den Actor in einem Level (Place Actors → *Async Procedural Generated Actor*); es gibt kein Menü —
der Workflow befindet sich im Details-Panel des Actors.

## Der Build erzeugt keine Instanzen

- Bestätigen Sie, dass der Actor mindestens ein `UInstancedStaticMeshComponent`-Unterelement mit einem **stabilen Namen** hat.
- Bestätigen Sie, dass **ComponentConfiguration** einen Eintrag hat, dessen **Name** mit dieser Komponente übereinstimmt.
- Bestätigen Sie, dass dem Data-Asset-Eintrag ein gültiges **Mesh** zugewiesen ist.
- Wenn Sie das Einlesen verwenden, stellen Sie sicher, dass Sie zuerst erfasst haben (**bReadInMeshComponentData**) mit einem übereinstimmenden **ReadInComponentConfiguration**-Eintrag.
- Überprüfen Sie **GetBuildPlan**. Es meldet präzise Problemcodes wie `component_not_found:<Name>`, `data_asset_element_not_found:<Name>` und `data_asset_element_missing_mesh:<Name>`.

## Die Vorschau meldet eine sehr hohe Instanzzahl

Der Bauplan meldet sowohl potenziell generierte Instanzen vor dem Beschneiden als auch die exakte generierte Anzahl nach dem Beschneiden. Wenn beide zu hoch sind, reduzieren Sie die Zeilenzahlen, fügen Sie Beschneidungen (Pruning) hinzu oder aktivieren Sie **bUseAsyncBuild** und verringern Sie **InstancesPerFrame**.

## Erfasste Instanzen wurden unerwartet verschoben/neuzentriert

Explizit erfasste Instanzen werden exakt wiedergegeben und niemals neuzentriert. Nur Transformationen **generierter Zeilen** werden von **bCenterGeneratedTransforms** beeinflusst.

## Der Build lässt den Editor / das Spiel bei großen Strukturen stocken

Aktivieren Sie **bUseAsyncBuild** und verringern Sie **InstancesPerFrame**, sodass Instanzen über mehrere Ticks hinweg anstelle eines einzelnen blockierenden Durchlaufs hinzugefügt werden.

## Das Einlesen hat die falsche Komponente erfasst

`ReadInComponentConfiguration` gleicht nach dem Komponenten-**Name** ab. Stellen Sie sicher, dass Komponentennamen stabil und eindeutig sind und dass der `Name` des Konfigurationseintrags exakt übereinstimmt.

## Das generierte Raster hat Lücken

Überprüfen Sie die `Pruned*`-Arrays in den Zeileninformationen — beschnittene Indizes/Instanzen werden absichtlich übersprungen. Löschen Sie diese, um ein vollständiges Raster zu generieren.
