<!-- doc-provenance: product-facts.yml reconciled 2026-07-01; source AKDB:plugins/AssetLoaderStudio/architecture.md -->
# Einstellungsreferenz

Die Einstellungen von Asset Loader Studio konzentrieren sich auf Governance-Profile, zugelassene Pfade/Klassen, Audit-Richtlinien und Routen-Overrides.

## Governance-Einstellungen

| Einstellung | Typ | Standard | Wirkung |
| --- | --- | --- | --- |
| `DefaultProfileId` | string | `guided_safe` | Wählt das Standard-Berechtigungsprofil aus, wenn kein Routen- oder Anforderungsprofil angegeben ist. |
| `ProfileDirectories` | array | `Config/AssetLoaderStudio/Governance/Profiles` | Listet Ordner auf, die nach Berechtigungsprofil-JSON durchsucht werden. |
| `AllowedRoots` | array | `/Game`, `/Engine` | Beschränkt Mutationsziele auf genehmigte Unreal-Pfade. |
| `AllowedClasses` | array | Paket-Standard | Schränkt Mutationsziele auf genehmigte Pfadklassen ein, falls konfiguriert. |
| `AuditRetentionDays` | integer | `30` | Steuert, wie lange Audit-Protokolle aufbewahrt werden, bevor sie bereinigt werden. |
| `AuditLogDirectory` | string | `Saved/AssetLoaderStudio/Audit` | Speichert persistierte Audit-Einträge für Vorschau- und Anwendungsoperationen. |
| `bAuditPreviewOperations` | boolean | `true` | Schreibt Audit-Einträge für Operationsvorschauen. |
| `bAuditApplyOperations` | boolean | `true` | Schreibt Audit-Einträge für Anwendungsoperationen. |

## Berechtigungsprofil-Felder

Berechtigungsprofile definieren `profile_id`, zulässige Aktionen, maximale Anzahl betroffener Assets/Zeilen, zulässige Pfade/Klassen, Schreibschutzmodus, Dry-Run-Modus, Anwendungsbestätigung, destruktive Genehmigung und Audit-Aufbewahrung. Verwenden Sie `read_only` zur Inspektion, `guided_safe` für normale überprüfte Bearbeitungen und `expert` nur für vertrauenswürdige Massenarbeiten.

## Routen-Overrides

Optionale Routen-Overrides können eine UCM-Route auf ein strengeres oder lockereres Profil abbilden. Routen-Overrides ersetzen keine lokalen Vorschau-/Anwendungsprüfungen; sie wählen lediglich das Profil aus, das von diesen Prüfungen verwendet wird.

## Praktische Standardwerte

- Beginnen Sie mit `guided_safe` für überprüfte Editor-Arbeiten.
- Behalten Sie `read_only` bei für Ermittlung, Validierung, Tabellenexport und automatisierte Prüfungen, die keine Assets verändern dürfen.
- Verwenden Sie `expert` nur für vertrauenswürdige Massenarbeiten und halten Sie die destruktive Genehmigung explizit.
- Halten Sie die Audit-Aufbewahrung hoch genug, um Ihr normales Release-Überprüfungsfenster abzudecken.
