---
lang: de
title: LightweightDummyActorSystem Settings Reference
audience: [end_user]
owner_ref: plugin:LightweightDummyActorSystem
applies_to:
  component: LightweightDummyActorSystem
contract_ref: plugin:LightweightDummyActorSystem/profile-properties
version:
  since: "1.0"
---
# Einstellungen-Referenz

LightweightDummyActorSystem liefert **kein** `UDeveloperSettings`-/Projekt-Einstellungen-Objekt aus. Konfigurierbare Werte befinden sich in Data Assets, Komponenten und Structs, wie unten aufgeführt (basierend auf öffentlichen Headern).

## ULDASRepresentationProfile (`UDataAsset`)

| Name | Typ | Standardwert | Auswirkung |
| --- | --- | --- | --- |
| `Descriptor` | `FLDASRepresentationDescriptor` | leer | Basis-Darstellungsdeskriptor, der auf den Subjekt-Eintrag angewendet wird. |
| `PromoteDistance` | `float` | `0.0` | Distanzeingabe, die vom Beförderungsrichtlinien verwendet wird. |
| `DemoteDistance` | `float` | `0.0` | Distanzeingabe, die von der Degradierungsrichtlinie verwendet wird. |
| `PromotionCooldownSeconds` | `float` | `1.0` | Abklingzeit zwischen Beförderungen. |
| `bAllowRuntimePromotion` | `bool` | `true` | Wenn falsch, werden Laufzeit-Beförderungsanforderungen von der Profilrichtlinie nicht erlaubt. |
| `bFailClosedOnPromotionFailure` | `bool` | `false` | Wenn wahr, führt ein Beförderungsfehler zu einem geschlossenen Fehlerzustand. |
| `RequiredReadinessProviders` | `TArray<FName>` | leer | Benannte Readiness-Provider, die erfüllt sein müssen. |

## ULDASDummyActorComponent

| Name | Typ | Standardwert | Auswirkung |
| --- | --- | --- | --- |
| Profil-/Subjekt-Bindungs-Felder | editanywhere-Komponenteneigenschaften | vom Aufrufer festgelegt | Bindet die Komponente an die LDAS-Subjekt-Darstellung. |
| Repliziertes Snapshot | repliziertes Eigenschaftsfeld | Laufzeit | Überträgt Snapshot-Zustand mit `OnRep`-Benachrichtigung. |

## ALDASLightweightDummyActor

| Name | Typ | Standardwert | Auswirkung |
| --- | --- | --- | --- |
| Sichtbare Komponenten | Komponentenverweise | konstruiert | Szenen-/Debug-Darstellungskomponenten. |
| LDAS-Bindungsfeld | editanywhere | vom Aufrufer festgelegt | Verknüpft den Actor mit den LDAS-Subjekt-Daten. |

## FLDASTransitionRecord / Snapshot-Structs

Transition- und Snapshot-Structs bieten editanywhere-Felder für Subjekt-ID, Darstellungsart, Zeitstempel und Readiness-Fehlerlisten. Behandeln Sie diese als Datenverträge und nicht als globale Einstellungen; Standardwerte sind Struct-Standardwerte in Headern unter `Public/Structs/`.

## Was ist nicht vorhanden

| Oberfläche | Status |
| --- | --- |
| `ULDASDeveloperSettings` | noch nicht verfügbar |
| `Config/DefaultLightweightDummyActorSystem.ini`-Einstellungsobjekt | nicht als Käufer-Einstellungsseite ausgeliefert |
| WarCollection-/Lightning-/UCM-Bridge-Einstellungen | nur für Zielplattformen optionale Adapter |

## Verwandte Dokumente

- [UserManual.md](UserManual.md)
- [QUICKSTART.md](QUICKSTART.md)
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md)
