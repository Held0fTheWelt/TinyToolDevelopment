<!-- doc-provenance: AKDB:plugins/SmartContentDiet/architecture.md; docs/architecture/plugins/SmartContentDiet/product-facts.yml; reconciled 2026-07-16 -->
# Drittanbieter-Software

Smart Content Diet **bündelt keinen Quellcode von Drittanbietern, keine Laufzeit-Binärdateien, KI-Modelle, Node.js, Python oder eigenständige ausführbare Dateien**. Es ist ein C++ Unreal Engine Editor-Plugin, das nur Unreal Engine-Module und Standard-Unreal-APIs nutzt (Asset Registry, Asset-Analyse, Editor-UI, Commandlet).

Der Kernzyklus (Scannen → Prüfen → Sichere Korrektur) läuft vollständig im Editor **ohne KI-Dienst und ohne externes Werkzeug**. Optionale pluginübergreifende Ökosystem-Routen (über **Unreal Capability Mesh (UCM)**) sind JSON-deklariert und fügen diesem Paket keine Drittanbieter-Software hinzu.

Keine externe Software, kein Konto und keine Laufzeitumgebung ist erforderlich, um das Plugin zu installieren oder zu nutzen.

**Fab-Drittanbieter-Software-Erklärung:** Keine gebündelte Drittanbieter-Software.
