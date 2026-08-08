---
lang: de
title: LightweightDummyActorSystem Quick Start
audience: [end_user]
owner_ref: plugin:LightweightDummyActorSystem
applies_to:
  component: LightweightDummyActorSystem
preconditions:
  - Unreal Engine project open with the plugin package available
  - Edit > Plugins can enable LightweightDummyActorSystem
expected_result:
  text: Subject registers through ULDASWorldSubsystem and QueryReadiness returns a readiness report.
version:
  since: "1.0"
---
# Schnellstart

Dieser Leitfaden installiert **LightweightDummyActorSystem (LDAS)** und führt durch die erste erfolgreiche Registrierung eines Themas unter Verwendung der mitgelieferten Laufzeit-API. MVP 1+2+3 ist implementiert: Laufzeitkern, Übergangskern, Editor-Inspektor und Validierungs-Commandlet.

## Was Sie nach diesem Leitfaden haben

Das Plugin ist aktiviert, und ein Thema wurde über `ULDASWorldSubsystem::RegisterSubject` / `RegisterSubjectFromProfile` registriert, mit einer Bereitschaftsabfrage, die Sie inspizieren können.

## Anforderungen

- Unreal Engine 5.4–5.8 (verpackte Matrix; Win64/Linux/Mac, soweit die Modul-Whitelists dies erlauben).
- Für das Kernpaket ist kein anderes Tiny-Tool-Plugin erforderlich.
- Keine Drittanbieter-Software, kein Konto und keine externe Laufzeit. Siehe [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## 1. Installation und Aktivierung

1. Laden Sie **LightweightDummyActorSystem** von Fab herunter und fügen Sie es dem Projekt hinzu.
2. Öffnen Sie **Bearbeiten → Plugins**, aktivieren Sie **LightweightDummyActorSystem** und starten Sie neu, wenn dazu aufgefordert wird.
3. Bestätigen Sie, dass die Module Runtime, Editor und DeveloperTool geladen werden (`LightweightDummyActorSystem`, `LightweightDummyActorSystemEditor`, `LightweightDummyActorSystemDeveloper`).

## 2. Erstellen eines Repräsentationsprofils

1. Erstellen Sie im Content Browser ein Data Asset der Klasse `ULDASRepresentationProfile`.
2. Legen Sie die Felder des grundlegenden Profils fest, zum Beispiel:

| Feld | Beispielwert | Bedeutung |
| --- | --- | --- |
| `PromoteDistance` | `2500.0` | Distanzschwelle, die von den Eingaben der Beförderungsrichtlinie verwendet wird. |
| `DemoteDistance` | `3000.0` | Distanzschwelle, die von den Eingaben der Degradierungsrichtlinie verwendet wird. |
| `PromotionCooldownSeconds` | `1.0` | Mindestens Sekunden zwischen Beförderungen. |
| `bAllowRuntimePromotion` | `true` | Erlaubt Beförderungsanfragen zur Laufzeit. |
| `bFailClosedOnPromotionFailure` | `false` | Wenn true, schlägt eine fehlgeschlagene Beförderung mit „Closed“-Status fehl. |
| `RequiredReadinessProviders` | (leer oder benannte Anbieter) | Zusätzliche Bereitschaftsanbieter, die vor der Beförderung erforderlich sind. |

## 3. Durchgeführtes Beispiel: Registrieren und Abfragen

Aus Gameplay-Code oder einem Editor-Utility, das auf das World-Subsystem zugreifen kann:

```cpp
UWorld* World = /* aktuelles World */;
ULDASWorldSubsystem* LDAS = World->GetSubsystem<ULDASWorldSubsystem>();

FLDASSubjectId SubjectId;
// Füllen Sie die für Ihre Projektbindung erforderlichen Felder von SubjectId.

FLDASRepresentationDescriptor Descriptor;
// Füllen Sie die Felder des Descriptors oder verwenden Sie RegisterSubjectFromProfile mit dem Data Asset.

const bool bRegistered = LDAS->RegisterSubjectFromProfile(SubjectId, ProfileAsset);
const FLDASReadinessReport Report = LDAS->QueryReadiness(
	SubjectId, ELDASRepresentationKind::Heavy /* oder Dummy entsprechend Ihrer Absicht */);
```

## Erwartetes Ergebnis

- `bRegistered` ist true, wenn die Themen-ID akzeptiert wird.
- `QueryReadiness` gibt einen `FLDASReadinessReport` zurück, dessen Status `Ready`, `Warning` oder ein blockierender Status mit Problem-Einträgen ist — niemals ein stillschweigender Erfolg.

## 4. Verträge validieren (optional)

Führen Sie das verpackte Validierungs-Commandlet `ULDASValidateContractsCommandlet` von einem Editor-/Commandlet-Host aus aus, um die Vertragskonsistenz für das Projekt zu überprüfen.

## Nächste Schritte

- [UserManual.md](UserManual.md) — Subsysteme, Actor, Komponente, Übergänge.
- [SettingsReference.md](SettingsReference.md) — Profil- und Komponenteneigenschaften.
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md) — Bereitschafts- und Beförderungsfehler.
