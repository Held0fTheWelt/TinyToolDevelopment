<!-- doc-provenance: AKDB:plugins/ProceduralGeneratedStructures/architecture.md; docs/architecture/plugins/ProceduralGeneratedStructures/product-facts.yml; reconciled 2026-06-21 -->
# Manuale utente

Questo manuale spiega come utilizzare Procedural Generated Structures in Unreal Editor.

## Scopo

Procedural Generated Structures costruisce strutture di mesh statiche istanziate riutilizzabili da un asset di dati.
L'actor runtime può leggere istanze di `UInstancedStaticMeshComponent` esistenti in un `UProceduralStructureDataAsset`, quindi rigenerare tali istanze esplicite o generare strutture aggiuntive basate su righe.

## Oggetti principali

- **`AAsyncProceduralGeneratedActor`** — gestisce il flusso di lavoro di build e può rigenerare componenti in modo sincrono o attraverso i tick dell'editor/gioco.
- **`UProceduralStructureDataAsset`** — memorizza voci di mesh nominate (`FInstancedMeshInformation`) con trasformazioni esplicite e regole opzionali di generazione delle righe.
- **`FInstancedComponentConfiguration`** — mappa un componente mesh istanziato nominato sull'actor a una voce memorizzata nell'asset di dati (`Name` + `StructureType`).
- **`FProceduralStructureBuildPlan`** — riporta cosa farebbe una rigenerazione: componenti di destinazione, problemi bloccanti, intenzione di mutazione, conteggi asincroni e totali esatti di istanze dopo la potatura.
- **`FProceduralStructureElementStats`** — riporta i conteggi di istanze esplicite, generate, potenzialmente generate e totali per voce.
- **`EStructureType`** — `None`, `Structure`, `Railing`, `Tribune`, `Stairs`.

## Flusso di lavoro

1. Aggiungere un `AAsyncProceduralGeneratedActor` a un livello o blueprint.
2. Aggiungere uno o più componenti figli `UInstancedStaticMeshComponent` con **nomi di componenti stabili**.
3. Assegnare un `UProceduralStructureDataAsset` a **ProceduralStructure**.
4. Configurare **ReadInComponentConfiguration** per catturare le istanze dei componenti esistenti nell'asset (attivare con **bReadInMeshComponentData**).
5. Configurare **ComponentConfiguration** per rigenerare tali voci sui componenti.
6. Ispezionare **GetBuildPlan** (Blueprint/C++) o il percorso di anteprima se si utilizza l'automazione. Risolvere eventuali problemi segnalati prima di applicare una rigenerazione.
7. Utilizzare **bClearProceduralStructureInformation** (cancella), **bReadInMeshComponentData** (leggi) e la build (costruzione / asincrona) per iterare sulla struttura.

## Note di build

- Le trasformazioni esplicite lette dai componenti di scena vengono **riprodotte esattamente** e non vengono ricentrate durante la rigenerazione.
- Le trasformazioni delle righe generate possono essere centrate attorno all'origine XY locale con **bCenterGeneratedTransforms**.
- **InstancesPerFrame** limita quante istanze vengono aggiunte per tick quando la build asincrona è abilitata.
- I conteggi delle righe vengono limitati a valori non negativi prima della generazione.
- I piani di build e le statistiche dell'DataAsset riportano sia la capacità delle righe non potate sia il conteggio esatto generato dopo la potatura, consentendo di stimare le rigenerazioni di grandi dimensioni prima della mutazione.
- **bAutoBuildOnConstruction** attiva una build durante `OnConstruction` (simile all'actor spline).
- **bUseAsyncBuild** distribuisce la build su più frame; altrimenti la build avviene in un unico passaggio.
- **GetBuildProgress**, **GetEstimatedBuildInstanceCount** e **GetAddedBuildInstanceCount** riportano il progresso della build asincrona per gli strumenti dell'editor e i Blueprint.

## Piano di build e validazione

`AAsyncProceduralGeneratedActor::GetBuildPlan` è un'anteprima non mutativa. Utilizzarla prima di rigenerare strutture grandi o condivise.

Il piano di build riporta:

- Se esistono un asset di dati, una configurazione di componenti e componenti mesh istanziati di proprietà dell'actor.
- Una voce per componente configurato, inclusi percorso del componente, percorso della mesh, statistiche sugli elementi dell'DataAsset, intenzione di mutazione e codici di problemi bloccanti.
- Totali per istanze esplicite, istanze potenzialmente generate prima della potatura, istanze generate dopo la potatura e conteggio combinato delle istanze.

I codici di problemi bloccanti comuni includono:

- `missing_procedural_structure_data_asset`
- `missing_component_configuration`
- `actor_has_no_instanced_static_mesh_components`
- `component_not_found:<Name>`
- `data_asset_element_not_found:<Name>`
- `data_asset_element_missing_mesh:<Name>`
- `data_asset_element_type_none:<Name>`

## Voci dell'asset di dati

Ogni voce `FInstancedMeshInformation` contiene:

- `Name`, `Type` (`EStructureType`), `Mesh` (`UStaticMesh`).
- `Instances` — trasformazioni esplicite (ad es. catturate dalla scena), riprodotte così come sono.
- `InstancedMeshRows` — regole opzionali di generazione procedurale delle righe (conteggi righe per dimensione, trasformazioni di movimento per dimensione, opzioni di potatura/posizionamento definito). Vedere [SettingsReference.md](SettingsReference.md) per ogni campo.

## Cosa non fa il plugin

- Non crea mesh statiche al posto dell'utente — l'utente fornisce le proprie.
- Non ricentra le istanze catturate esplicitamente.
- Non è un sistema di modellazione procedurale completo; posiziona e rigenera mesh istanziate a partire da dati.
