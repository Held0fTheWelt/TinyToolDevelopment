<!-- doc-provenance: product-facts.yml reconciled 2026-07-15; source AKDB:plugins/AsyncSplineBuilder/architecture.md -->
# Schnellstartanleitung

Diese Anleitung führt Sie von der Installation zu einem **sichtbaren Ergebnis**: einem Straßen-/Strecken-Mesh, das entlang einer von Ihnen gesteuerten Spline generiert wird. Async Spline Builder funktioniert eigenständig — es ist kein anderes Plugin erforderlich.

## Was Sie nach dieser Anleitung haben werden

Einen `Spline Generating Actor` in Ihrem Level mit einer Straße, die aus Spline-Mesh-Abschnitten gebaut ist, die Sie durch Verschieben von Spline-Punkten umformen und bei Bedarf neu bauen können.

## Anforderungen

- Unreal Engine 5 Editor und ein geöffnetes Level.
- Mindestens ein **Straßen-Mesh**, das entlang seiner lokalen X-Achse kachelt (siehe Schritt 3 / Mesh Authoring im Benutzerhandbuch). Sie können zu Beginn jedes kachelnde Mesh aus Ihrem Projekt verwenden.
- Keine Software von Drittanbietern, Konten oder Laufzeiten. Siehe [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## 1. Installieren und aktivieren

1. Fügen Sie **AsyncSplineBuilder** aus Ihrer Fab-Bibliothek zum Projekt hinzu (oder installieren Sie es in der Engine).
2. Öffnen Sie **Edit → Plugins**, aktivieren Sie **AsyncSplineBuilder** und starten Sie nach Aufforderung neu.

## 2. Panel öffnen (Erstes Ergebnis)

1. Öffnen oder erstellen Sie ein Level.
2. Öffnen Sie **Tools → Track Tools → Async Spline Builder**. Das Panel verfügt über die Registerkarten **Build**, **Segments** und **Terrain**.

## 3. Ein reales Beispiel: Bauen einer Strecke

1. Klicken Sie auf der Registerkarte **Build** auf **Create Actor** (dies erzeugt einen `ASplineGeneratingActor`) oder wählen Sie einen vorhandenen aus und klicken Sie auf **Use Selection**.
2. Weisen Sie unter **Setup** ein kachelndes Mesh zu `MainMesh` zu (erforderlich). Weisen Sie optional `StartMesh` und `EndMesh` zu.
3. Verschieben Sie im Viewport die Spline-Punkte des Actors, um den Pfad zu geformten.
4. Klicken Sie auf **Validate** (dies prüft, ob `MainMesh` gesetzt ist und die Spline baubar ist).
5. Klicken Sie auf **Build Now**.

**Erwartetes Ergebnis:** Der Actor generiert `USplineMeshComponent`-Straßenabschnitte entlang der Spline. Verschieben Sie einen Spline-Punkt und klicken Sie auf **Rebuild**, um die Aktualisierung der Straße zu sehen.

> Für lange Strecken aktivieren Sie **Use Async Build** und stellen Sie **SegmentsPerTick** ein, damit die Generierung über Ticks hinweg gebatcht wird und der Editor reaktionsfähig bleibt. Verwenden Sie **Cancel**, um einen laufenden asynchronen Build zu stoppen.

## 4. Weitergehen (Optional)

- Registerkarte **Segments**: Meshes pro Segment, Sprunglücken (`JumpGapsByPoints`) und Stunt-Drops.
- Registerkarte **Terrain**: An Landschaft ausrichten, Höhen-Deformation und prozedurale **Bodenwände** (`bGenerateGroundWalls`). Siehe [LandscapeAndWalls.md](LandscapeAndWalls.md).
- **Data Asset:** Speichern/Laden von Layouts mit `WriteSplineToDataAsset` / `ReadSplineFromDataAsset`.

## 5. Nächste Schritte

- Vollständiger Workflow, Daten pro Segment, Lücken, Drops, Wände, Landschaftsdeformation: [UserManual.md](UserManual.md).
- Einstellungen: [SettingsReference.md](SettingsReference.md).
- Probleme: [TROUBLESHOOTING.md](TROUBLESHOOTING.md) und [FAQ.md](FAQ.md).
