<!-- doc-provenance: AKDB:plugins/ProceduralGeneratedStructures/architecture.md; docs/architecture/plugins/ProceduralGeneratedStructures/product-facts.yml; reconciled 2026-06-21 -->
# Documentazione di ProceduralGeneratedStructures

ProceduralGeneratedStructures costruisce strutture di mesh statiche istanziate riutilizzabili da un asset di dati. L'actor runtime può leggere istanze di `UInstancedStaticMeshComponent` esistenti in un `UProceduralStructureDataAsset`, quindi rigenerare tali istanze esplicite o generare strutture aggiuntive basate su righe. Espone anche dati sul piano di build e sulle statistiche in modo da poter ispezionare componenti di destinazione, problemi bloccanti, intenzione di mutazione, progresso asincrono e conteggi esatti delle istanze dopo la potatura (pruning) prima di applicare una rigenerazione.

## Documentazione

- [QUICKSTART.md](QUICKSTART.md): installa → posiziona actor → cattura e rigenera, con i risultati attesi.
- [UserManual.md](UserManual.md): flusso di lavoro completo, oggetti principali e note di build.
- [SettingsReference.md](SettingsReference.md): ogni proprietà dell'actor e campo dell'asset di dati.
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md) · [FAQ.md](FAQ.md)
- [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md): dichiarazione software di terze parti (nessuno incluso).

## Asset principali

- `AAsyncProceduralGeneratedActor` gestisce il flusso di lavoro di build e può rigenerare componenti in modo sincrono o attraverso i tick dell'editor/gioco.
- `UProceduralStructureDataAsset` memorizza voci di mesh nominate con trasformazioni esplicite e regole opzionali di generazione delle righe.
- `FInstancedComponentConfiguration` mappa un componente mesh istanziato nominato sull'actor a una voce memorizzata nell'asset di dati.
- `FProceduralStructureBuildPlan` e `FProceduralStructureElementStats` espongono dati di anteprima esatti per strumenti, Blueprint e percorsi UCM.

## Note di build

- Le trasformazioni esplicite lette dai componenti di scena vengono riprodotte esattamente e non vengono ricentrate durante la rigenerazione.
- Le trasformazioni delle righe generate possono essere centrate attorno all'origine XY locale con `bCenterGeneratedTransforms`.
- `InstancesPerFrame` limita quante istanze vengono aggiunte per tick quando la build asincrona è abilitata.
- I conteggi delle righe vengono limitati a valori non negativi prima della generazione.
- I piani di build riportano la capacità delle righe generate prima della potatura e il conteggio esatto generato dopo la potatura.

## Flusso di lavoro raccomandato

1. Aggiungere un `AAsyncProceduralGeneratedActor` a un livello o blueprint.
2. Aggiungere uno o più componenti figli `UInstancedStaticMeshComponent` con nomi di componenti stabili.
3. Assegnare un `UProceduralStructureDataAsset`.
4. Configurare `ReadInComponentConfiguration` per catturare le istanze dei componenti esistenti.
5. Configurare `ComponentConfiguration` per rigenerare tali voci.
6. Ispezionare `GetBuildPlan` o il percorso di anteprima, quindi utilizzare le azioni di lettura, cancellazione e build richiamabili nell'editor per iterare sulla struttura.
