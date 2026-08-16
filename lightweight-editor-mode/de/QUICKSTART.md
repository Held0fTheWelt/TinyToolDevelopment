<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/LightweightEditorMode/architecture.md -->
# Schnellanleitung

Diese Anleitung führt Sie von der Installation bis zu einem **sichtbaren Ergebnis**: einem schnelleren, reaktionsschnelleren Editor-Viewport, den Sie mit einem Klick vollständig wiederherstellen können. Lightweight Editor Mode funktioniert eigenständig – es ist kein anderes Plugin erforderlich.

## Was Sie nach dieser Anleitung haben

Ein aktivierte, umkehrbare "Lightweight"-Bearbeitungsprofil (schnellerer Viewport) sowie das Wissen, wie Sie Profile wechseln und Ihren ursprünglichen Editor-Zustand bei Bedarf wiederherstellen.

## Anforderungen

- Unreal Engine 5 Editor (das Plugin betrifft nur den Editor-Viewport, niemals das paketierte Spiel zur Laufzeit).
- Keine Software von Drittanbietern, Konten oder Zusatz-Runtimes erforderlich. Siehe [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## 1. Installieren und Aktivieren

1. Fügen Sie **Lightweight Editor Mode** aus Ihrer Fab-Bibliothek zum Projekt hinzu (oder installieren Sie es in der Engine).
2. Öffnen Sie **Edit → Plugins**, aktivieren Sie **Lightweight Editor Mode** und starten Sie den Editor neu, wenn Sie dazu aufgefordert werden.

## 2. Tool öffnen (Erstes Ergebnis)

1. Öffnen Sie **Tools → Performance → Lightweight Editor Mode**. Ein andockbarer Tab öffnet sich mit einem Profil-Dropdown, einer Umschalt-Schaltfläche und dem Kontrollkästchen *Enable on Editor startup*.
2. Wählen Sie das Profil **Balanced** (die empfohlene Standardeinstellung).
3. Klicken Sie auf **Enable Lightweight Mode**.

**Erwartetes Ergebnis:** Der Viewport wird sofort aktualisiert — Balanced verringert den Bildschirmprozentsatz und die Skalierbarkeit, deaktiviert aufwendige Beleuchtung und erzwingt Unlit / Nicht-Echtzeit. Der Editor fühlt sich sofort reaktionsschneller an.

## 3. Ein konkretes Beispiel: Profil wechseln, dann wiederherstellen

1. Während der Modus aktiviert ist, ändern Sie das Profil-Dropdown auf **Aggressive**. Der Viewport wird mit den aggressiveren Einstellungen aktualisiert (niedrigerer Bildschirmprozentsatz, niedrige Skalierbarkeit, keine aufwendigen Schatten/Nebel). Ihr ursprünglicher Zustand vor der Aktivierung bleibt weiterhin erhalten.
2. Klicken Sie auf **Disable Lightweight Mode**.

**Erwartetes Ergebnis:** Der Editor stellt Ihre gesicherten Skalierbarkeitsstufen, Konsolevariablen-Overrides, Viewport-Ansichtsmodi und den Echtzeit-Zustand wieder her — Sie befinden sich wieder genau da, wo Sie begonnen haben.

> Profile sind auf Reaktionsfähigkeit und nicht auf visuelle Treue ausgelegt. Erwarten Sie daher bei aktiviertem Modus eine geringere Auflösung, unbeleuchtete (Unlit) und weniger schattierte Viewports. **Deaktivieren Sie den Modus vor Beleuchtungsprüfungen oder Screenshots.**

## 4. Profile anpassen

Öffnen Sie **Project Settings → Plugins → Lightweight Editor Mode**, um die Profilwerte für Mild / Balanced / Aggressive / Extreme zu bearbeiten. Das ausgewählte Profil wird in die aktiven Werte kopiert, bevor der Modus angewendet wird. Siehe [PerformanceTuningReference.md](PerformanceTuningReference.md).

## 5. Optional: Bei Editor-Start aktivieren

Aktivieren Sie **Enable on Editor startup**, damit sich der Modus beim nächsten Start automatisch einschaltet, sobald Editor-Viewports vorhanden sind.

## 6. Nächste Schritte

- Vollständiges Verhalten pro Profil und empfohlene Workflows: [UserManual.md](UserManual.md).
- Alle Einstellungen: [SettingsReference.md](SettingsReference.md).
- Probleme (z. B. veralteter Zustand nach Neustart → *Restore Lightweight State*):
  [TROUBLESHOOTING.md](TROUBLESHOOTING.md) und [FAQ.md](FAQ.md).
