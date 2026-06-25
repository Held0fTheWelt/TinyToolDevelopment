# Tiny Tool Matrix Experience Spec

Status: Draft v0.1
Owner: Tiny Tool Development
Created: 2026-06-22
Scope: New static WebGL experience, separate from the existing Atlas.

## 1. Purpose

The Tiny Tool Matrix Experience is a new visual product section. It presents Tiny Tool
plugins as functional Matrix nodes in a 3D workspace. The experience must make plugins
understandable before it makes them spectacular.

Core promise:

- Every plugin has a purpose.
- Every plugin has visible input and output.
- Every plugin has a readable influence radius.
- Risky operations are small in form but large in effect.
- The Matrix aesthetic supports comprehension, not the other way around.

## 2. Product Position

This is not a replacement for the existing Tiny Tool Atlas. It is a new part of the
product website and can link to or from the Atlas later.

Target surface:

- Static web page.
- WebGL scene using Three.js or Babylon.js.
- No backend requirement.
- Deployable through the existing static site pipeline.
- Usable as a guided 3D/360-style experience.

Proposed future public route:

```text
/matrix-experience.html
```

## 3. Non-Goals

- Do not build a generic cyberpunk city.
- Do not build a fantasy wonderland.
- Do not copy Shadowrun names, factions, trademarks, or protected text into public copy.
- Do not make plugins invisible behind atmosphere.
- Do not implement this as a modification of the existing Atlas unless explicitly decided later.
- Do not depend on Unreal Engine for runtime or authoring.

## 4. Experience Model

The scene is a dark Matrix workspace divided into zones. The user can inspect plugins,
follow data routes, and switch between modes that reveal different operational layers.

Required modes:

1. Survey
   - Shows the whole Matrix lobby and the plugin zones.

2. Influence
   - Shows each plugin's effect radius on the grid and nearby systems.

3. Flow
   - Shows input and output streams between plugins.

4. Risk
   - Highlights publish, sync, migration, delete, deploy, and release operations.

## 5. Plugin Zones

### 5.1 Index and Store Routing

Role: discovery, catalog, routing, bridge, distribution.

Initial plugins:

- InternalIndexService
- LLMStore
- IIS-LLM-Store-Bridge
- Store
- UnifiedMcpServer

Visual grammar:

- InternalIndexService: scan/index tower.
- LLMStore: catalog depot or host archive.
- IIS-LLM-Store-Bridge: bridge gate between index and store zones.
- Store: distribution terminal.
- UnifiedMcpServer: protocol gate or guarded public surface.

### 5.2 Unreal Production Tools

Role: shaping the Unreal working environment.

Initial plugins:

- UnrealCapabilityMesh
- AsyncSplineBuilder
- LightweightEditorMode
- PerformancePresetWizard
- LogLevelEditor

Visual grammar:

- UnrealCapabilityMesh: central capability graph/spine.
- AsyncSplineBuilder: geometry rail or spline constructor.
- LightweightEditorMode: lean viewport/control node.
- PerformancePresetWizard: tuning console.
- LogLevelEditor: signal/noise valve.

### 5.3 Quality and Hygiene Tools

Role: clean, rename, trim, validate, legally mark.

Initial plugins:

- SmartContentDiet
- NamingConventionUtility
- CodeCopyrightEditor
- LogLevelEditor

Visual grammar:

- SmartContentDiet: trimming/filtering station.
- NamingConventionUtility: rename/lint grid.
- CodeCopyrightEditor: header/rights seal station.
- LogLevelEditor: signal/noise filter.

### 5.4 Release and Risk Operations

Role: small operation with large Matrix impact.

Initial plugins:

- UnifiedMcpServer
- InternalIndexService
- IIS-LLM-Store-Bridge
- LLMStore
- Store

Visual grammar:

- Release Gate: small central node.
- Red outer radius: exposed or dangerous effect scope.
- Amber middle radius: publish/sync staging.
- Cyan/green routes: validated input and output.
- Rollback lane: visible escape route.

## 6. Object Grammar

Each plugin node must expose the same information model.

```text
PluginNode
  id
  name
  zone
  purpose
  input
  action
  output
  influenceRadius
  riskLevel
  linkedPlugins
  visualMetaphor
```

Required visual states:

- Idle: dim but readable.
- Hover/focus: plugin name, radius, and links brighten.
- Selected: inspector opens and camera frames the node.
- Influence mode: radius and affected terrain become primary.
- Flow mode: input and output lines animate.
- Risk mode: warning rings and rollback routes become primary.

## 7. Interaction Contract

Desktop:

- Drag: orbit or pan around the scene.
- Wheel: zoom.
- Click plugin: open inspector.
- Click zone hotspot: fly to zone.
- Keyboard Tab: focus nodes.
- Escape: close inspector.

Mobile:

- One finger drag: orbit/pan.
- Pinch: zoom.
- Tap plugin: open inspector.
- Tap zone chip: move to zone.

Accessibility:

- DOM fallback list of plugins below or beside canvas.
- Keyboard reachable inspector.
- Reduced motion mode disables constant particle motion.
- High contrast labels remain readable without relying only on color.

## 8. Visual Direction

Base:

- Glossy black grid.
- Deep void background.
- Dense but controlled data paths.
- Small host nodes with clear shapes.
- Functional colors, not decorative rainbow.

Color semantics:

- Cyan: scan, index, analysis.
- Green: validation, repair, safe output.
- Amber: build, store, staging, release prep.
- Red: risk, exposed surface, destructive change.
- Violet/blue: bridge, protocol, cross-system link.

Key rule:

The plugin name and operational purpose must remain legible at all times.

## 9. Static Delivery Contract

The implementation should be static and self-contained.

Proposed future files:

```text
Website/src/static/matrix-experience.css
Website/src/static/matrix-experience.js
Website/src/static/matrix-experience-data.js
Website/dist/matrix-experience.html
Website/dist/matrix-experience.css
Website/dist/matrix-experience.js
Website/dist/matrix-experience-data.js
```

Data may be embedded as JS instead of JSON to avoid local file/fetch problems in static
preview contexts.

## 10. Acceptance Criteria

MVP is successful when:

- At least 12 real Tiny Tool plugins are visible.
- Plugin names are readable in the default view.
- Four zones are visually distinct.
- Clicking each plugin opens an inspector.
- Every selected plugin shows purpose, input, output, influence radius, and risk.
- Flow mode animates plugin connections.
- Influence mode shows local effect radii.
- Risk mode shows release/sync/deploy danger clearly.
- It runs from a static local server.
- It works on desktop and mobile viewport sizes.
- A non-WebGL fallback list exists.

## 11. Resource Anchors

These anchors define the source material used to create the experience. Future prompts,
implementation tasks, and design reviews should reference these IDs instead of inventing
new source sets.

### 11.1 Local Concept Artifacts

| ID | Resource | Purpose |
| --- | --- | --- |
| R-CONCEPT-01 | `D:\TinyToolDevelopment\matrix-actual-plugin-concepts.png` | Current readable concept sheet using actual plugin names. |
| R-CONCEPT-02 | `D:\TinyToolDevelopment\matrix-actual-plugin-concepts.svg` | Editable source for the actual plugin concept sheet. |
| R-CONCEPT-03 | `D:\TinyToolDevelopment\matrix-plugin-concepts.png` | Earlier abstract plugin concept sheet; useful for layout comparison. |
| R-CONCEPT-04 | `D:\TinyToolDevelopment\matrix-plugin-concepts.svg` | Editable source for the earlier abstract concept sheet. |

### 11.2 Plugin Source Anchors

| ID | Resource | Purpose |
| --- | --- | --- |
| R-PLUGIN-ROOT | `D:\TinyToolDevelopment\PluginImages` | Real plugin list and visual product source folders. |
| R-PLUGIN-DOCS | `D:\TinyToolDevelopment\Documentation` | Product documentation grouped by plugin category. |
| R-PLUGIN-AI | `D:\TinyToolDevelopment\Documentation\ai-plugins` | AI plugin documentation. |
| R-PLUGIN-BRIDGE | `D:\TinyToolDevelopment\Documentation\bridge-plugins` | Bridge plugin documentation. |
| R-PLUGIN-EDITOR | `D:\TinyToolDevelopment\Documentation\editor-tools` | Editor tool documentation. |
| R-PLUGIN-ENGINE | `D:\TinyToolDevelopment\Documentation\engine-plugins` | Engine plugin documentation. |
| R-PLUGIN-FOUNDATION | `D:\TinyToolDevelopment\Documentation\foundation-plugins` | Foundation plugin documentation. |

Initial concrete plugin names from `R-PLUGIN-ROOT`:

- AsyncSplineBuilder
- CodeCopyrightEditor
- IIS-LLM-Store-Bridge
- InternalIndexService
- LightweightEditorMode
- LLMStore
- LogLevelEditor
- NamingConventionUtility
- PerformancePresetWizard
- SmartContentDiet
- Store
- UnifiedMcpServer
- UnrealCapabilityMesh

### 11.3 Technical Anchors

| ID | Resource | Purpose |
| --- | --- | --- |
| R-TECH-01 | `D:\TinyToolDevelopment\Website\README.md` | Static site preview and deployment conventions. |
| R-TECH-02 | `D:\TinyToolDevelopment\Website\build.py` | Existing static build pipeline. |
| R-TECH-03 | `D:\TinyToolDevelopment\Website\src\static\vendor\three.module.min.js` | Existing vendored Three.js module. |
| R-TECH-04 | `D:\TinyToolDevelopment\Website\src\static\atlas3d.js` | Reference only: existing Three.js interaction pattern. Not the implementation target. |
| R-TECH-05 | `D:\TinyToolDevelopment\Website\content.py` | Existing product catalog and site data source. |

### 11.4 Matrix Inspiration Anchors

Use these only as inspiration and design research. Do not copy protected prose into the
public experience.

| ID | Resource | Pages | Design value |
| --- | --- | --- | --- |
| R-SR-2XS | `D:\Shadowrun\Novels\5210 - 2XS.pdf` | PDF pages 29-33 | First Matrix entry, black space, colored beams, iconic hosts. |
| R-SR-SEATTLE | `D:\Shadowrun\Novels\7601 - Into the Shadows.pdf` | PDF pages 105-106 | Seattle as beautiful dangerous Matrix city. |
| R-SR-AZRAEL | `D:\Shadowrun\Novels\5365 - Fade to Black.pdf` | PDF pages 51-52 | Dangerous corporate icon, hostile electronic forest, forbidden small hut/decker node. |
| R-SR-WOLF-RAVEN | `D:\Shadowrun\Novels\5712 - Wolf and Raven.pdf` | PDF pages 14-16 | Seattle RTG and reality-filter/metaphor override by a legendary decker. |
| R-SR-PSYCHOTROPE | `D:\Shadowrun\Novels\5713 - Psychotrope.pdf` | PDF pages 17, 20, 35-37, 41, 48, 72 | UV hosts, Matrix as physical place, psychotropic/danger imagery. |
| R-SR-2050 | `D:\Shadowrun\Sourcebooks\26230 - Shadowrun 2050.pdf` | PDF page 152 | Canonical RTG/LTG structure and grid/host framing. |
| R-SR-MATRIX | `D:\Shadowrun\Rulebooks\7909 - Matrix.pdf` | PDF page 49 | Hosts floating above LTG grid, stylized corporate host icons. |
| R-SR-UNWIRED | `D:\Shadowrun\Rulebooks\26004 - Unwired.pdf` | PDF page 173 | UV nodes as hyper-real, high-risk Matrix spaces. |
| R-SR-VR | `D:\Shadowrun\Rulebooks\7107 - Virtual Realities.pdf` | Printed pages 50-52 | Matrix as inhabited sensory metaphor, sculpted systems, reality filters. |
| R-SR-TARGET-MATRIX | `D:\Shadowrun\Sourcebooks\7219 - Target Matrix.pdf` | Printed pages 30, 77, 109-110 | Mirror Maze, Schwarzschild Radiance, bait/trap hosts. |

Rendered scan references already produced locally:

| ID | Resource | Purpose |
| --- | --- | --- |
| R-SCAN-MAZE | `D:\TinyToolDevelopment\tmp\pdfs\matrix_inspiration\target_datahavens-031.png` | Target Matrix: The Maze / mirror-room data haven inspiration. |
| R-SCAN-RADIANCE | `D:\TinyToolDevelopment\tmp\pdfs\matrix_inspiration\target_clubs_games-078.png` | Target Matrix: Schwarzschild Radiance and Event Horizon host. |
| R-SCAN-BAIT | `D:\TinyToolDevelopment\tmp\pdfs\matrix_inspiration\target_anomalies-110.png` | Target Matrix: bait host / dangerous invitation pattern. |
| R-SCAN-VR-REALITIES | `D:\TinyToolDevelopment\tmp\pdfs\matrix_search\virtual_realities_realities-051.png` | Virtual Realities: metaphor and sculpted systems page. |
| R-SCAN-VR-FILTERS | `D:\TinyToolDevelopment\tmp\pdfs\matrix_search\virtual_realities_realities-052.png` | Virtual Realities: reality filters and sensory cut-outs. |

## 12. Source Usage Rules

- Use source material as design grammar, not as public text.
- Public wording must describe Tiny Tool Development and its plugins.
- Avoid direct Shadowrun terminology in public product labels unless legally cleared.
- Keep the final experience brand-owned: Tiny Tool Matrix, Tiny Tool Experience, or a
  project-specific name still to be chosen.
- When in doubt, cite internal source IDs in design notes but omit them from public UI.

## 13. Open Decisions

- Final runtime: Three.js or Babylon.js.
- Navigation style: orbit camera, first-person walk, or guided 360 hotspots.
- Whether labels are always visible or only visible in focus mode.
- Whether the existing Atlas data model should feed the experience later.
- Whether the experience should live under the current website build or as a separate
  static package that is copied into the site.

## 14. Next Spec Tasks

1. Define the exact plugin data schema.
2. Map every initial plugin to a visual metaphor.
3. Define the first camera path and zone order.
4. Define the inspector content model.
5. Decide Three.js versus Babylon.js.
6. Create a build/deploy integration spec.

