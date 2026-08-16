<!-- doc-provenance: AKDB:plugins/VisualFidelityDirector/architecture.md; docs/architecture/plugins/VisualFidelityDirector/product-facts.yml; reconciled 2026-07-12 -->
# FAQ

## Ersetzt VFD den Renderer oder das Anti-Aliasing von Unreal?

Nein. Es ist eine Diagnose-, Profil-, Evidenz-, Vergleichs-, Rezept-, Trockenlauf-, Scanner- und Empfehlungsschicht über den bestehenden Rendering-Systemen von Unreal.

## Was hat sich in 2.0.0 geändert?

Version `2.0.0` fügt das profilzentrierte Cockpit (Variantenselektor, Vererbungspfad, Provenienz, Befunde, Profilvergleich, verwaltetes permanentes Anwenden, Multi-Frame-Laufzeitmetriken), `UVFDCockpitBlueprintLibrary` und verpackte Blueprint-Showcase-Assets hinzu. Die integrierte Expert Tools-Seite behält den 1.x Snapshot- und Rezept-Workflow bei.

## Erfordert es KI oder Cloud-Dienste?

Nein. VFD erfordert keine externe KI, Cloud, Python, Node.js oder Konten.

## Benötigt es andere Tiny Tool-Plugins?

Nein. Der Kern-Workflow ist eigenständig.

## Welche Unreal-Version wird unterstützt?

Visual Fidelity Director unterstützt Unreal Engine 5.4 bis 5.8 über den passenden Engine-Branch-Deskriptor und unterstützt Win64, Linux und Mac.

## Kann es mein Projekt verändern?

Standardmäßig nein. Verwaltetes permanentes Anwenden kann nur drei Konfigurationsziele beschreiben, wenn Sie diese explizit genehmigen: Scalability-Gruppen in `DefaultGameUserSettings.ini`, Renderer-Einstellungen in `DefaultEngine.ini` und Device Profiles in `DefaultDeviceProfiles.ini`. Expert Tools **Preview Apply + Rollback** kann unterstützte Editor-Sitzungs-CVars vorübergehend festlegen und anschließend wiederherstellen. Assets, Materialien, Post Process Volumes und MRQ-Presets werden nicht verändert.

## Ändert Lumen Deep Scan Meshes oder Materialien?

Nein. Der Lumen Deep Scan schreibt Überprüfungsbefunde aus Snapshot- und Asset-Registry-Metadaten. Er ändert keine Static Mesh Card-Einstellungen, Materialgraphen, Material Card-Sharing-Flags, Projektkonfigurationen oder MRQ-Presets.

## Erfasst es Screenshots?

Der Expert Tools A/B-Workflow schreibt reine Metadaten-Vergleichsberichte, außer ein zukünftiger Workflow liefert Screenshot-Pfade. Verwenden Sie Berichte, um Entscheidungen zu verknüpfen und visuelle Evidenzen bei Bedarf manuell zu erfassen.

## Warum haben einige Befunde "mittleres Vertrauen"?

Viele visuelle Artefakte sind inhalts- und bewegungsabhängig. VFD trennt Fakten von Heuristiken, sodass Sie manuelle Überprüfungen steuern können, ohne Metadaten als Beweis zu behandeln.

## Wo landen Profile und Berichte?

```text
Saved/VisualFidelityDirector/profiles/
Saved/VisualFidelityDirector/reports/
Saved/VisualFidelityDirector/recipes/
```

## Kann ich VFD über Blueprints verwenden?

Ja. `UVFDCockpitBlueprintLibrary` macht Profil-, Evidenz-, Funktions- und verwaltete Anwendungsfunktionen verfügbar. Siehe `Content/Blueprints/BPF_VFD_API` für verdrahtete Beispiele.

## An wen wende ich mich für Support?

Nutzen Sie die im Plugin-Deskriptor angegebene Support-E-Mail:
`support@tiny-tool-development.com`.

Discord: `#support` (siehe Produktliste bei Veröffentlichung).
