# Governierte Automatisierung

Asset Loader Studio ist zunächst eigenständig. Es hängt zur Kompilierzeit nicht vom Unreal Capability Mesh oder Unified MCP Server ab. Optionale UCM-Manifeste werden unter `Config/UnrealCapabilityMesh` bereitgestellt.

Routen:

- `asset_loader_studio.tools.describe.v1`
- `asset_loader_studio.state.read.v1`
- `asset_loader_studio.load.submit.v1`
- `asset_loader_studio.jobs.status.v1`
- `asset_loader_studio.table.snapshot.v1`
- `asset_loader_studio.table.validate.v1`
- `asset_loader_studio.graph.build.v1`
- `asset_loader_studio.governance.snapshot.v1`
- `asset_loader_studio.governance.profile.save.v1`
- `asset_loader_studio.operation.preview.v1`
- `asset_loader_studio.operation.apply.v1`
- `asset_loader_studio.table.export.v1`
- `asset_loader_studio.audit.read.v1`
- `asset_loader_studio.audit.prune.v1`

Berechtigungsprofile:

- `read_only` erlaubt Lesen, Untersuchen, Validieren, Vorschau und Export.
- `guided_safe` erlaubt gestufte Änderungen mit Einschränkungen und Bestätigung.
- `expert` erlaubt Massen- und zerstörerische Capability-Flags, mit strenger Genehmigung für zerstörerische Arbeiten.

Jede Automatisierungsantwort verwendet eine stabile Hülle mit `success`, `operation`, `summary`,
`diagnostics`, `mutation_flags` und routenspezifischen Nutzdaten.

Automatisierung ist optional. Wenn UCM oder MCP nicht installiert ist, verwenden Sie den Editor-Arbeitsbereich, die Blueprint-Bibliothek oder das Laufzeit-Subsystem direkt. Aufrufer von Routen sollten vor der Anwendung eine Vorschau erstellen und die Vorschau-ID oder das Genehmigungs-Token mit ihrem Prüfungsdatensatz speichern.
