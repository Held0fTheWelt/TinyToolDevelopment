<!-- doc-provenance: AKDB:plugins/VisualFidelityDirector/architecture.md; docs/architecture/plugins/VisualFidelityDirector/product-facts.yml; reconciled 2026-07-12 -->
# Fehlerbehebung

## Ich habe das Plugin aktiviert und nichts ist passiert

Ursache: VFD wird über einen Menüeintrag geöffnet; es zeigt kein Startfenster an.

Lösung:

1. Starten Sie Unreal Editor nach dem Aktivieren des Plugins neu.
2. Öffnen Sie **Tiny Tools > Visual Fidelity Director**.
3. Wenn das Menü weiterhin fehlt, bestätigen Sie unter **Bearbeiten > Plugins**, dass das Plugin aktiviert ist.

## Live-Metriken nicht verfügbar

Ursache: Live-Metriken erfordern einen verfügbaren Editor-Viewport-Messkontext. Einige Plattformen, headless Sitzungen oder frühe Editor-Ticks machen möglicherweise keine GPU-Pass-Daten verfügbar.

Lösung:

1. Klicken Sie auf **Refresh**, nachdem der Viewport sichtbar ist.
2. Warten Sie, bis das Multi-Frame-Abtastfenster abgeschlossen ist (mehrere Editor-Ticks).
3. Behandeln Sie `-1` oder explizite Nicht-Verfügbar-Zeichenketten als ehrliche Degradierung — VFD erfindet keine Zahlen.

## Keine Profile in der Profilleiste sichtbar

Ursache: Es existieren noch keine Fidelity-Profile unter `Saved/VisualFidelityDirector/profiles/`.

Lösung:

1. Importieren oder duplizieren Sie ein Profil über Ihren Projekt-Workflow oder migrieren Sie mithilfe von Expert Tools und Projektwerkzeugen von einem integrierten Rezept.
2. Klicken Sie auf der Cockpit-Seite auf **Refresh**.

## Verwaltetes Anwenden hat alles übersprungen

Ursache: Es wurden keine Ziele aktiviert, der kompilierte Diff stimmt bereits überein oder das Ziel ist blockiert.

Lösung:

1. Klicken Sie zuerst auf **Build Destinations**.
2. Überprüfen Sie jede Zusammenfassung und aktivieren Sie die Genehmigung nur für beabsichtigte Ziele.
3. Bestätigen Sie, dass das aktive Profil mit Änderungen kompiliert (`Compile Preview`).

## Profilvergleich zeigt keinen Diff

Ursache: Die beiden Profile kompilieren für alle Achsen zum selben Zielzustand, oder ein Profil hat die Validierung nicht bestanden.

Lösung:

1. Validieren Sie, dass beide Profile ohne Fehler kompilieren.
2. Ändern Sie eine Variante oder eine Intent-Stufe auf einem Profil und aktualisieren Sie.

## Das Bedienfeld / Expert Tools öffnet sich, aber es wird kein Bericht geschrieben

Ursache: Der Ordner `Saved` des Projekts ist möglicherweise schreibgeschützt oder nicht verfügbar.

Lösung:

1. Wechseln Sie zu **Expert Tools** und klicken Sie auf **Open Output Folder**.
2. Bestätigen Sie, dass das Projekt in `Saved/VisualFidelityDirector/` schreiben kann.
3. Versuchen Sie **Export Snapshot** erneut und lesen Sie die Zeile **Status**.

## Vorschau-Anwenden hat alles übersprungen

Ursache: Das ausgewählte Rezept enthält möglicherweise nur Export-Empfehlungen, der empfohlene Wert stimmt bereits mit dem aktuellen Wert überein, oder die CVar ist in diesem Engine-Kontext nicht verfügbar.

Lösung:

1. Exportieren Sie zuerst einen Rezept-Trockenlauf.
2. Öffnen Sie `settings_diff.md`.
3. Überprüfen Sie die Spalten **Mode**, **Supported** und **Risk**.

## Eine CVar zeigt "nicht verfügbar" an

Ursache: Einige CVars sind abhängig von Engine-Version, Renderer, Plattform oder Kontext.

Lösung: Behandeln Sie die Empfehlung als manuelle Überprüfung. VFD zeichnet nicht verfügbare Werte auf, anstatt den gesamten Workflow fehlschlagen zu lassen.

## MRQ-Empfehlungen haben mein Preset nicht geändert

Ursache: MRQ-Preset-Mutation wird vorsätzlich nicht unterstützt.

Lösung: Öffnen Sie `mrq_recommendation.md` und wenden Sie alle Cinematic-Einstellungen nach der Überprüfung manuell an.

## Lumen-Empfehlung hat kein Mesh oder Material geändert

Ursache: Lumen Mesh-Card-Einstellungen, Materialgraphen und Material-Card-Sharing-Flags sind vorsätzlich nur für manuelle Überprüfungen vorgesehen.

Lösung: Exportieren Sie **Lumen Deep Scan** oder einen Lumen-Rezept-Trockenlauf, inspizieren Sie dann Berichte und wenden Sie Mesh- oder Materialänderungen erst nach visueller Validierung manuell an.

## Die experimentelle Diagnose sieht zu grob aus

Ursache: Der Diagnosebericht ist eine metadatenbasierte Überprüfungs-Routing-Heatmap. Es handelt sich nicht um eine pixelbasierte Frame-Differenz-Heatmap und erfasst keine Bewegungsvektoren.

Lösung: Verwenden Sie Snapshot- und Scanner-Berichte für eine strukturierte Überprüfung; erfassen Sie visuelle Evidenzen bei Bedarf manuell.

## Blueprint-Bibliothek Anwenden hat nichts geschrieben

Ursache: `ApplyPersistentConfiguration` erfordert `Request.bUserApproved` und genehmigte Ziel-Zusammenfassungen.

Lösung: Rufen Sie zuerst `PreviewPersistentDestinations` auf, markieren Sie nur beabsichtigte Ziele in der Anfrage als genehmigt und rufen Sie dann Anwenden mit `bUserApproved=true` auf.
