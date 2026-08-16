<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/CodeCopyrightEditor/architecture.md -->
# Schnellstart

Diese Anleitung führt Sie von der Installation zu einem **echten Ergebnis**: Ein konsistenter Urheberrechtshinweis, der auf ausgewählte Quelldateien angewendet wird, zusammen mit einem Scan-Bericht, den Sie öffnen können. Code Copyright Editor funktioniert vollständig eigenständig — es ist kein weiteres Plugin erforderlich.

## Was Sie nach dieser Anleitung haben

Ihre Eigentümer-/Lizenzdaten sind konfiguriert, die Codebasis ist mit dateibezogenem Status gescannt und eine kontrollierte Erneuerung wurde auf die von Ihnen ausgewählten Dateien angewendet — plus ein JSON-Scan-Bericht unter `Saved/CodeCopyrightEditor/`.

## Anforderungen

- Unreal Engine 5 Editor (das Plugin läuft im Editor, nicht in gepackten Spielen).
- Ein C++- oder Blueprint-Projekt mit Quellcode-/Plugin-Ordnern zum Scannen.
- Keine Drittanbieter-Software, kein Konto und keine externe Laufzeitumgebung erforderlich. Siehe [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## 1. Installieren und aktivieren

1. Füge **Code Copyright Editor** aus deiner Fab-Bibliothek zum Projekt hinzu (oder installiere es in der Engine).
2. Öffne im Editor **Edit → Plugins**, aktiviere **Code Copyright Editor** und starte nach Aufforderung neu.

## 2. Das Werkzeug öffnen (Erstes Ergebnis)

1. Öffne **Tools → Code Tools → Code Copyright Editor**.
2. Lege auf der Registerkarte **Configure** deine Identität und Lizenz fest (Eigentümer, Lizenzkennung, Vorlage, Scanbereich). Klicke auf **Save**.
3. Wechsle zu **Scan & Review** und klicke auf **Scan Files**.

Du siehst nun jede berechtigte Datei mit einem Status-Badge (`OK`, `MISSING`, `REPLACE`, `PROTECTED`, …). Das Scannen schreibt niemals Dateien — dies ist eine sichere Vorschau.

## 3. Ein reales Beispiel: Hinweise auf ausgewählte Dateien anwenden

1. Klicke auf **Scan & Review** auf **Select Changeable** — dies markiert nur die Zeilen, die sicher umgeschrieben werden können (`MISSING`, `REPLACE`). `PROTECTED`- und `CONFLICT`-Dateien bleiben unangetastet.
2. Wähle zuerst eine einzelne Zeile aus und vergleiche den **vorhandenen** mit dem **vorgeschlagenen** Hinweis in der Vorschau.
3. (Empfohlen) Aktiviere auf der Registerkarte **Configure** die Option **Create Backup Before Write** und übertrage deine Arbeit zuerst in die Quellcodeverwaltung.
4. Klicke auf **Apply Selected** und bestätige. Das Tool schreibt nur die markierten, änderbaren Dateien um und führt anschließend einen erneuten Scan durch.

**Erwartetes Ergebnis:** Angewendete Dateien wechseln in den Status `UPDATED`; das Anwendungsergebnis und ein frischer Scan werden angezeigt. Klicke unter **Apply & Reports** auf **Export JSON**.

## 4. Wo Ergebnisse liegen

```text
Saved/CodeCopyrightEditor/LastCopyrightScan.json
```

Du kannst auch den Hinweis auf Projektebene (ohne Quellcode-Umschreibung) mit **Update Project Notice** aktualisieren, was in *Project Settings → Project → Description → Legal → Copyright Notice* schreibt.

## 5. Nächste Schritte

- Vollständiger Workflow und jede Registerkarte/Aktion: [UserManual.md](UserManual.md).
- Alle Vorlagen-Token (`{CopyrightText}`, `{LicenseIdentifier}`, `{FileMetadataBlock}`, …): [SettingsReference.md](SettingsReference.md).
- Einstellungen: [SettingsReference.md](SettingsReference.md).
- Probleme: [TROUBLESHOOTING.md](TROUBLESHOOTING.md) und [FAQ.md](FAQ.md).
