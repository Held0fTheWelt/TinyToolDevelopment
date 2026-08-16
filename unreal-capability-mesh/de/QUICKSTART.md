<!-- doc-provenance: AKDB:plugins/UnrealCapabilityMesh/architecture.md; docs/architecture/plugins/UnrealCapabilityMesh/product-facts.yml; reconciled 2026-07-19 -->
# Schnellstart

Dieser Leitfaden führt Sie von einer Neuinstallation zu einem **funktionalen, sichtbaren Ergebnis**: ein ermitteltes Capability-Inventar und eine selbst ausgeführte Route, die eine JSON-Antwort zurückgibt. Es sind keine Programmierung und kein Verfassen von Manifesten erforderlich – das Plugin wird mit einem einsatzbereiten Standardprofil geliefert.

## Was Sie nach diesem Leitfaden haben

Das Control Panel ist geöffnet, das gebündelte **Default Capability Mesh Profile** ist geladen, Capabilities wurden ermittelt und eine Route (`sample.echo.route.v1`) wurde mit einer JSON-Antwort ausgeführt und ein gespeicherter Bericht erstellt, den Sie öffnen können.

## Anforderungen

- Unreal Engine 5.4 oder neuer.
- Plattform: Windows (Win64), Linux oder Mac.
- Ein Unreal-**Projekt**, in dem das Plugin aktiviert wird. UCM ist ein C++ Editor-Plugin: in einem C++-Projekt kompiliert es beim ersten Editor-Start; in einem reinen Blueprint-Projekt installieren Sie es für eine passende Engine-Version (über Ihre Fab-Bibliothek), damit der Editor seine vorgebauten Editor-Module laden kann.
- Es wird keine Drittanbieter-Software, kein Konto, kein KI-Modell und keine externe Runtime benötigt. Siehe [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## 1. Installieren und Aktivieren

1. Erwerben Sie **Unreal Capability Mesh** aus Ihrer Fab-Bibliothek und fügen Sie es Ihrem Projekt hinzu (es erscheint im Ordner `Plugins/` des Projekts) oder installieren Sie es in der Engine.
2. Öffnen Sie Ihr Projekt. Gehen Sie im Editor zu **Edit → Plugins**, suchen Sie nach `Unreal Capability Mesh` und aktivieren Sie das Kontrollkästchen **Enabled**.
3. Starten Sie den Editor neu, wenn Sie dazu aufgefordert werden. (Lassen Sie es bei einem C++-Projekt beim ersten Start kompilieren.)

UCM kann ohne projekt-lokalen Setup-Ordner arbeiten. Es lädt das gebündelte Standardprofil und plugin-lokale Profile von aktivierten Provider-Plugins. Verwenden Sie `Config/UnrealCapabilityMesh/` nur, wenn das Projekt bewusst Overrides oder projekt-eigene zusammengesetzte Routen benötigt.

## 2. In Betrieb nehmen (Erstes Ergebnis)

1. Öffnen Sie das Control Panel: **Tools → Unreal Capability Mesh**.
2. Auf der Seite **Overview** sollten Sie das aktive Profil **"Default Capability Mesh Profile"** sehen.
3. Klicken Sie auf **Reload Setup**. UCM lädt das Profil, validiert das JSON-Setup, registriert Definitionen und führt die Discovery aus.
4. Öffnen Sie die Seite **Capabilities** – Sie sehen nun die ermittelten Capabilities (zum Beispiel `mesh.sample.echo`) mit ihrer Verfügbarkeit und Seiteneffekten.
5. Öffnen Sie die Seite **Diagnostics** – sie zeigt die Setup-Validierungs- und Discovery-Meldungen des Neuladens. Ein sauberer Reload bedeutet, dass das Plugin funktioniert.

Sie haben das Produkt soeben nur mit den im Paket enthaltenen Mitteln in Betrieb genommen.

## 3. Ein reales Beispiel: Eine Route ausführen

UCM enthält eine sichere, schreibgeschützte Beispiel-Route (`sample.echo.route.v1`), die einen Echo-Endpunkt aufruft. Nutzen Sie diese für Ihre erste End-to-End-Route.

1. Öffnen Sie die Seite **Routes**.
2. Geben Sie im Feld für die Routen-ID ein:

   ```text
   sample.echo.route.v1
   ```

3. Klicken Sie auf **Dry Run**. UCM plant die Route und bestätigt, dass die Capability `mesh.sample.echo` mit `read_only`-Seiteneffekten und **ohne erforderliche Genehmigung** verfügbar ist. Der Dry-Run-Bericht ist sauber.
4. Geben Sie im Routen-Eingabefeld folgendes JSON ein (dies sind die erwarteten Parameter – eine Routen-Eingabe-Hülle, deren Feld `request_json` Ihre Nutzlast trägt):

   ```json
   {
     "request_json": "{\"message\":\"hello\"}"
   }
   ```

5. Klicken Sie auf **Execute**.

**Erwartete Ausgabe:** Die Route gibt eine JSON-Echo-Antwort der Form `{"echo": { ... }}` zurück und schreibt einen Routenausführungs-Bericht. Der Endpunkt ist die mitgelieferte Funktion `UCapabilityMeshTestInvoker::EchoJson`, welche die Anfrage-Nutzlast als `{"echo":<request>}` verpackt.

Die Routes-Seite enthält auch die Spalte **Route Catalog**-Genehmigung für die **EXPERIMENTELLE** automatische Selbstgenehmigung. Lassen Sie **Approve all at own risk** und alle routenspezifischen Schalter für diesen Schnellstart ausgeschaltet. Sie dienen nur dem Testen genehmigungspflichtiger Routen auf eigene Verantwortung.

## 4. Wo Ergebnisse liegen

Alle generierten Dateien werden im Ordner `Saved/` Ihres Projekts abgelegt:

```text
Saved/UnrealCapabilityMesh/
  setup_validation_report.json     ← Reload-Validierung
  capability_registry.json         ← registrierte Capabilities
  discovery_report.md              ← menschenlesbare Discovery-Zusammenfassung
  compatibility_matrix.json        ← Capability/Endpunkt-Kompatibilität
  route_reports/                   ← Dry-Run-Pläne
  route_execution_reports/         ← ausgeführte Routen-Eingaben und -Ausgaben (Ihr Echo-Ergebnis)
```

Öffnen Sie `route_execution_reports/`, um die Antwort der gerade ausgeführten Route einzusehen.

## 5. Nächste Schritte

- Bedienen Sie das Panel und jede Funktion mit ihren Parametern: [UserManual.md](UserManual.md).
- Jedes Profilfeld, jede Richtlinie und jeder Ausgabepfad: [SettingsReference.md](SettingsReference.md).
- Passen Sie das Setup nur bei Bedarf an: Erstellen Sie `<IhrProjekt>/Config/UnrealCapabilityMesh/project_profile.json` oder kopieren Sie spezifische Manifeste, die das Projekt überschreiben möchte, und klicken Sie erneut auf **Reload Setup**. Belassen Sie Provider-Manifeste in deren Plugins.
- Ein anderes Plugin verbinden: [INTEGRATION.md](INTEGRATION.md).
- Wenn etwas nicht funktioniert: [TROUBLESHOOTING.md](TROUBLESHOOTING.md) und [FAQ.md](FAQ.md).

Wenn Tiny Tool Execution Integration Bridge aktiviert ist, lädt es UCM neu, bevor TTER während des Editor-Starts projizierte Routen ermittelt. Ein manuelles **Reload Setup** bleibt die normale Aktion nach dem Bearbeiten eines Profils oder Aktivieren eines Providers.

---

> **Für Maintainer / beim Bauen aus Quellcode (nicht erforderlich zur Nutzung des Plugins):** Quellcode-Repository-Validierungswerkzeuge sind nur für Maintainer gedacht und **nicht** Teil des Fab-Pakets. Sie benötigen weder Python noch Source-Gates, um UCM zu installieren oder zu nutzen.
