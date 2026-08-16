<!-- doc-provenance: product-facts.yml reconciled 2026-07-15; source AKDB:plugins/AsyncSplineBuilder/architecture.md -->
# Guida rapida

Questa guida accompagna dall'installazione a un **risultato visibile**: una mesh di strada/pista generata lungo una spline controllata dall'utente. Async Spline Builder funziona in modo autonomo — non è richiesto alcun altro plugin.

## Cosa si otterrà dopo questa guida

Un `Spline Generating Actor` nel livello con una strada costruita da sezioni di mesh spline che è possibile modellare spostando i punti spline e rigenerare su richiesta.

## Requisiti

- Editor Unreal Engine 5 e un livello aperto.
- Almeno una **mesh stradale** che si ripete lungo il suo asse X locale (vedere il passaggio 3 / Creazione delle mesh nel manuale utente). È possibile utilizzare qualsiasi mesh ripetibile del progetto per iniziare.
- Nessun software di terze parti, account o runtime. Vedere [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## 1. Installare e abilitare

1. Aggiungere **AsyncSplineBuilder** dalla libreria Fab al progetto (o installarlo nell'engine).
2. Aprire **Edit → Plugins**, abilitare **AsyncSplineBuilder** e riavviare quando richiesto.

## 2. Aprire il pannello (Primo risultato)

1. Aprire o creare un livello.
2. Aprire **Tools → Track Tools → Async Spline Builder**. Il pannello contiene le schede **Build**, **Segments** e **Terrain**.

## 3. Un esempio pratico: costruire una pista

1. Nella scheda **Build**, fare clic su **Create Actor** (questo genera un `ASplineGeneratingActor`), oppure selezionarne uno esistente e fare clic su **Use Selection**.
2. In **Setup**, assegnare una mesh ripetibile a `MainMesh` (richiesto). Opzionalmente assegnare `StartMesh` e `EndMesh`.
3. Nel viewport, spostare i punti spline dell'actor per sagomare il percorso.
4. Fare clic su **Validate** (questo verifica che `MainMesh` sia impostato e che la spline sia edificabile).
5. Fare clic su **Build Now**.

**Risultato atteso:** L'actor genera sezioni stradali `USplineMeshComponent` lungo la spline. Spostare un punto spline e fare clic su **Rebuild** per vedere l'aggiornamento della strada.

> Per piste lunghe, abilitare **Use Async Build** e impostare **SegmentsPerTick** in modo che la generazione sia distribuita su più tick e l'editor rimanga reattivo. Utilizzare **Cancel** per interrompere una generazione asincrona in corso.

## 4. Per andare oltre (Opzionale)

- Scheda **Segments**: mesh per segmento, interruzioni di salto (`JumpGapsByPoints`) e dislivelli.
- Scheda **Terrain**: allineamento al paesaggio, deformazione dell'altezza e **muri di contenimento** procedurali (`bGenerateGroundWalls`). Vedere [LandscapeAndWalls.md](LandscapeAndWalls.md).
- **Asset di dati:** salvare/caricare layout con `WriteSplineToDataAsset` / `ReadSplineFromDataAsset`.

## 5. Passaggi successivi

- Flusso di lavoro completo, dati per segmento, interruzioni, dislivelli, muri, deformazione del paesaggio: [UserManual.md](UserManual.md).
- Impostazioni: [SettingsReference.md](SettingsReference.md).
- Problemi e soluzioni: [TROUBLESHOOTING.md](TROUBLESHOOTING.md) e [FAQ.md](FAQ.md).
