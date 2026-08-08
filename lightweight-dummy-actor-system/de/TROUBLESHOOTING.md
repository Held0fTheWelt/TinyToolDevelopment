---
lang: de
title: LightweightDummyActorSystem Troubleshooting
audience: [end_user]
owner_ref: plugin:LightweightDummyActorSystem
applies_to:
  component: LightweightDummyActorSystem
symptom: RegisterSubject fails or QueryReadiness returns a non-Ready status with issues.
recovery:
  steps:
    - Confirm the plugin is enabled under Edit > Plugins and restart the editor
    - Re-read the matching troubleshooting entry and apply the documented fix
    - Re-run the quick start smoke check
version:
  since: "1.0"
---
# Fehlerbehebung

Format: Symptom → Ursache → Lösung.

## 0. Ich habe es aktiviert, und es ist nichts passiert

**Symptom:** Nach dem Aktivieren von `LightweightDummyActorSystem` und dem Neustart werden keine Dummy-Aktoren angezeigt, und keine Tiny-Tools-Produktarbeitsabläufe werden automatisch ausgeführt.  
**Ursache:** LDAS ist ein API-/Dienstpaket. Subjekte registrieren sich über `ULDASWorldSubsystem`; ohne Profil und Registrierungsaufruf wird nichts automatisch erstellt.  
**Lösung:** Erstellen Sie ein `ULDASRepresentationProfile`-Datenasset und führen Sie das Registrierungs- und `QueryReadiness`-Beispiel in [QUICKSTART.md](QUICKSTART.md) aus.

## 1. `RegisterSubject` gibt false zurück

**Symptom:** Die Registrierung schlägt für eine neue Subjekt-ID fehl.  
**Ursache:** Ungültige oder doppelte Subjekt-ID oder vom Subsystem-Registry abgelehntes Deskriptor/Profil.  
**Lösung:** Überprüfen Sie, ob die Felder von `FLDASSubjectId` vollständig und eindeutig sind; bestätigen Sie, dass das Profil-Asset geladen ist; versuchen Sie es nach `UnregisterSubject` erneut, wenn Sie ersetzen.

## 2. Der Bereitschaftsstatus ist nicht „Ready“

**Symptom:** `QueryReadiness` gibt `Warning` oder einen blockierenden Status mit Problemen zurück.  
**Ursache:** Erforderliche Bereitschaftsanbieter sind fehlgeschlagen, oder Richtlinieneingaben (Abstand/Cooldown) sind nicht erfüllt.  
**Lösung:** Untersuchen Sie die Warnungen/Probleme in `FLDASReadinessReport`; passen Sie die Abstände, Cooldowns oder `RequiredReadinessProviders` in `ULDASRepresentationProfile` an; beheben Sie Anbieterfehler, bevor Sie befördern.

## 3. Beförderung schlägt im geschlossenen Modus fehl

**Symptom:** `RequestPromotion` führt die Darstellung nicht weiter fort, wenn `bFailClosedOnPromotionFailure` true ist.  
**Ursache:** Das Profil fordert das Verhalten „Fail-Closed“ bei Beförderungsausfall an.  
**Lösung:** Beheben Sie zunächst den zugrunde liegenden Bereitschafts-/Richtlinienfehler. Setzen Sie `bFailClosedOnPromotionFailure` nur dann zurück, wenn ein beabsichtigter weicher Fehler akzeptabel ist.

## 4. Laufzeitbeförderung abgelehnt

**Symptom:** Beförderungsanfragen werden ignoriert, während Degradierungen weiterhin funktionieren.  
**Ursache:** `bAllowRuntimePromotion` ist im Profil auf false gesetzt.  
**Lösung:** Aktivieren Sie `bAllowRuntimePromotion` in `ULDASRepresentationProfile`, wenn eine Laufzeitbeförderung gewünscht ist.

## 5. Der Editor-Inspektor zeigt keine Subjekte an

**Symptom:** Die Inspektor-Benutzeroberfläche ist nach PIE oder Editor-Weltarbeit leer.  
**Ursache:** Subjekte wurden nie in diesem Welt-Subsystem registriert, oder der falsche Weltkontext wird inspiziert.  
**Lösung:** Bestätigen Sie die Registrierung gegenüber demselben `UWorld`, das der Inspektor beobachtet; registrieren Sie nach dem Neuladen der Karte erneut.

## 6. Der Validate-Commandlet meldet Vertragsfehler

**Symptom:** `ULDASValidateContractsCommandlet` endet mit Funden.  
**Ursache:** Profile-/Deskriptor-/Vertragsinkonsistenzen im Projektinhalt.  
**Lösung:** Lesen Sie die Ausgabe des Commandlets, korrigieren Sie die benannten Assets und führen Sie die Validierung erneut aus.

## 7. Erwartung von WarCollection-/Lightning-/UCM-Brücken

**Symptom:** Optionale Adapter-APIs scheinen zu fehlen.  
**Ursache:** Diese Brücken sind zielabhängig und nicht Teil von MVP 1+2+3.  
**Lösung:** Verwenden Sie ausschließlich die mitgelieferten Kern-APIs. Betrachten Sie Adapter als zukünftige optionale Integrationen.

## Verwandte Dokumente

- [QUICKSTART.md](QUICKSTART.md)
- [UserManual.md](UserManual.md)
- [SettingsReference.md](SettingsReference.md)
- [FAQ.md](FAQ.md)
