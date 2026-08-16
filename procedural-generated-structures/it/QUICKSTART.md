<!-- doc-provenance: AKDB:plugins/ProceduralGeneratedStructures/architecture.md; docs/architecture/plugins/ProceduralGeneratedStructures/product-facts.yml; reconciled 2026-06-21 -->
# Guida rapida

Questa guida accompagna dall'installazione a un **risultato visibile**: un `AAsyncProceduralGeneratedActor` che rigenera strutture di mesh istanziate da un asset di dati. Il plugin funziona in modo autonomo — non è richiesto alcun altro plugin.

## Cosa si otterrà dopo questa guida

Un actor nel livello le cui istanze di mesh statica istanziata vengono catturate in un asset di dati e rigenerate da esso, rendendo la struttura riutilizzabile e rigenerabile.

## Requisiti

- Editor Unreal Engine 5 e un livello aperto.
- Una `UStaticMesh` del progetto da istanziare (ad es. la mesh di un muro o di un pilastro).
- Nessun software di terze parti, account o runtime. Vedere [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## 1. Installare e abilitare

1. Aggiungere **ProceduralGeneratedStructures** dalla libreria Fab al progetto (o installarlo nell'engine).
2. Aprire **Edit → Plugins**, abilitare **ProceduralGeneratedStructures** e riavviare quando richiesto.

## 2. Posizionare l'actor (Primo risultato)

1. Nel pannello **Place Actors**, cercare **Async Procedural Generated Actor** e trascinarlo nel livello (oppure aggiungere `AAsyncProceduralGeneratedActor` dall'elenco delle classi).
2. Aggiungere uno o più componenti figli **Instanced Static Mesh Component** all'actor e assegnare a ciascuno un **nome di componente stabile** (ad es. `Walls`). Assegnare la propria mesh statica e posizionare alcune istanze.

## 3. Un esempio pratico: catturare e rigenerare

1. Creare un **Procedural Structure Data Asset** (`UProceduralStructureDataAsset`) nel Content Browser e assegnarlo alla proprietà **ProceduralStructure** dell'actor.
2. In **ReadInComponentConfiguration**, aggiungere una voce il cui **Name** corrisponda al componente (`Walls`) e scegliere uno **StructureType** (ad es. `Structure`).
3. Impostare **bReadInMeshComponentData** per catturare le istanze attuali del componente nell'asset di dati.
4. In **ComponentConfiguration**, aggiungere una voce che mappi lo stesso **Name** (`Walls`) alla voce dell'asset di dati.
5. Visualizzare un'anteprima con **GetBuildPlan** da Blueprint/C++ o dal percorso di anteprima automatizzato. Un piano pulito non presenta problemi bloccanti e riporta il totale esatto di istanze che verranno rigenerate.
6. Rigenerare — abilitare **bAutoBuildOnConstruction** (rigenera durante la costruzione) oppure spostare/modificare l'actor per attivare una build.

**Risultato atteso:** le mesh istanziate vengono rigenerate dall'asset di dati. Le trasformazioni esplicite catturate vengono riprodotte esattamente (mai ricentrate). Per iterare, impostare **bClearProceduralStructureInformation** per cancellare i dati memorizzati e catturare di nuovo.

## 4. Prestazioni / Asincrono

- **bUseAsyncBuild**: distribuisce la build su più frame anziché in un singolo passaggio bloccante.
- **InstancesPerFrame**: quante istanze vengono aggiunte per tick quando la build asincrona è abilitata.
- **GetBuildProgress** / **GetAddedBuildInstanceCount**: traccia il progresso della build asincrona per gli strumenti.
- **bCenterGeneratedTransforms**: centra le trasformazioni delle *righe generate* attorno all'origine XY locale (le istanze esplicite catturate non vengono mai ricentrate).

## 5. Generare strutture basate su righe (Opzionale)

Oltre a riprodurre le istanze catturate, una voce dell'asset di dati può definire **InstancedMeshRows** per generare griglie/righe in modo procedurale (conteggi di righe per dimensione con trasformazioni di movimento per dimensione). Vedere [SettingsReference.md](SettingsReference.md) per ogni campo.

## 6. Passaggi successivi

- Flusso di lavoro completo e note di build: [UserManual.md](UserManual.md).
- Ogni proprietà dell'actor e campo dell'asset di dati: [SettingsReference.md](SettingsReference.md).
- Problemi e soluzioni: [TROUBLESHOOTING.md](TROUBLESHOOTING.md) e [FAQ.md](FAQ.md).
