<!-- doc-provenance: AKDB:plugins/ProceduralGeneratedStructures/architecture.md; docs/architecture/plugins/ProceduralGeneratedStructures/product-facts.yml; reconciled 2026-06-21 -->
# Troubleshooting

## I enabled the plugin but nothing happens

The plugin adds the `AAsyncProceduralGeneratedActor` class and the `UProceduralStructureDataAsset`.
Place the actor in a level (Place Actors → *Async Procedural Generated Actor*); there is no menu —
the workflow lives on the actor's Details panel.

## Build produces no instances

- Confirm the actor has at least one `UInstancedStaticMeshComponent` child with a **stable name**.
- Confirm **ComponentConfiguration** has an entry whose **Name** matches that component.
- Confirm the data asset entry has a valid **Mesh** assigned.
- If using read-in, make sure you captured first (**bReadInMeshComponentData**) with a matching
  **ReadInComponentConfiguration** entry.
- Inspect **GetBuildPlan**. It reports precise issue codes such as `component_not_found:<Name>`,
  `data_asset_element_not_found:<Name>`, and `data_asset_element_missing_mesh:<Name>`.

## Preview reports a very high instance count

The build plan reports both potential generated instances before pruning and the exact generated
count after pruning. If both are too high, reduce row counts, add pruning, or enable **bUseAsyncBuild**
and lower **InstancesPerFrame**.

## Captured instances moved/recentered unexpectedly

Explicit captured instances are replayed exactly and are never recentered. Only **generated row**
transforms are affected by **bCenterGeneratedTransforms**.

## Build hitches the editor / game on large structures

Enable **bUseAsyncBuild** and lower **InstancesPerFrame** so instances are added across multiple
ticks instead of in one blocking pass.

## Read-in captured the wrong component

`ReadInComponentConfiguration` matches by component **Name**. Ensure component names are stable and
unique, and that the configuration entry's `Name` matches exactly.

## Generated grid has gaps

Check the `Pruned*` arrays on the row information — pruned indices/instances are intentionally
skipped. Clear them to generate a full grid.
