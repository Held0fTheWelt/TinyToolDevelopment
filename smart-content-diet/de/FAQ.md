<!-- doc-provenance: AKDB:plugins/SmartContentDiet/architecture.md; docs/architecture/plugins/SmartContentDiet/product-facts.yml; reconciled 2026-07-16 -->
# FAQ

**Benötigt Smart Content Diet KI, ein Konto oder ein anderes Plugin?**
Nein. Der Kernzyklus (Scannen → Prüfen → Sichere Fixes anwenden → Erneut scannen → Messen) läuft vollständig im Editor ohne KI-Dienst, Konto oder Peer-Plugin. Optionale Ökosystem-Routen über **Unreal Capability Mesh (UCM)** existieren, sind jedoch niemals erforderlich.

**Ist die Ausführung sicher?**
Scannen und Vorschau sind schreibgeschützt. Das Anwenden von Korrekturen/Reduktionen/Verschiebungen/Löschungen **verändert Projekt-Assets** — führen Sie dies nur in einem gesicherten, quellcodeverwalteten und wegwerfbaren Workspace aus. Verändernde Routen sind standardmäßig genehmigungsgeschützt. Die Nutzung erfolgt auf eigenes Risiko.

**Welche Engine-Versionen werden unterstützt?**
Unreal Engine 5.4+. Es ist ein Editor-Plugin.

**Was ist der Unterschied zwischen Quick Safe, Full und Deep Scans?**
Quick Safe nutzt nur Registry/Metadaten (kein Asset-Laden, schnell). Full lädt Assets für handlungsrelevante Mesh-/Textur-/Material-Ergebnisse. Deep fügt tiefe Material-/Static-Mesh-Metriken hinzu und ist am langsamsten.

**Warum kann ich die Tabs Preset oder Governance nicht sehen?**
Das sind erweiterte Tabs (Ingenieur / Producer). Wechseln Sie die Rolle in den Einstellungen oder im Header.

**Kann ich es in CI / headless ausführen?**
Ja. Ein Commandlet unterstützt `-QuickSafe` / `-FullScan` / `-DeepScan`, `-OptimizationQueueReport` und `-ApplySafeQueue` (Anwendung nur auf gesicherten Projekten).

**Bündelt es Drittanbieter-Software?**
Nein. Siehe [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

**Wo erhalte ich Support?**
Nutzen Sie den Support-Link auf der Fab-Produktseite.
