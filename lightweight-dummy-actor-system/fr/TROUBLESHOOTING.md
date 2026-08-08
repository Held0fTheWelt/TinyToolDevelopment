---
lang: fr
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
# Dépannage

Format : Symptôme → Cause → Correction.

## 0. Je l'ai activé et rien ne s'est passé

**Symptôme :** Après avoir activé `LightweightDummyActorSystem` et redémarré, aucun acteur fictif n'apparaît et aucun flux de travail du produit Tiny Tools ne s'exécute automatiquement.  
**Cause :** LDAS est un package d'API/service. Les sujets s'enregistrent via `ULDASWorldSubsystem` ; rien ne se génère automatiquement sans profil et appel d'enregistrement.  
**Correction :** Créez un Actif de données `ULDASRepresentationProfile` et exécutez l'exemple de travail d'enregistrement + `QueryReadiness` dans [QUICKSTART.md](QUICKSTART.md).

## 1. `RegisterSubject` retourne false

**Symptôme :** L'enregistrement échoue pour un nouvel ID de sujet.  
**Cause :** ID de sujet invalide ou en double, ou descripteur/profil rejeté par le registre du sous-système.  
**Correction :** Vérifiez que les champs `FLDASSubjectId` sont complets et uniques ; confirmez que l'actif de profil est chargé ; réessayez après `UnregisterSubject` si vous remplacez.

## 2. Le statut de disponibilité n'est pas Ready

**Symptôme :** `QueryReadiness` retourne `Warning` ou un statut bloquant avec des problèmes.  
**Cause :** Les fournisseurs de disponibilité requis ont échoué, ou les entrées de politique (distance/refroidissement) ne sont pas satisfaites.  
**Correction :** Inspectez les avertissements/problèmes de `FLDASReadinessReport` ; ajustez les distances, le temps de refroidissement ou `RequiredReadinessProviders` de `ULDASRepresentationProfile` ; résolvez les échecs des fournisseurs avant la promotion.

## 3. La promotion échoue en mode fermé (fail-closed)

**Symptôme :** `RequestPromotion` ne fait pas avancer la représentation lorsque `bFailClosedOnPromotionFailure` est true.  
**Cause :** Le profil demande un comportement d'échec fermé en cas d'échec de la promotion.  
**Correction :** Corrigez d'abord l'échec sous-jacent de disponibilité/politique. Ne désactivez `bFailClosedOnPromotionFailure` que si un échec souple intentionnel est acceptable.

## 4. Promotion d'exécution rejetée

**Symptôme :** Les demandes de promotion sont ignorées tandis que la dégradation fonctionne toujours.  
**Cause :** `bAllowRuntimePromotion` est false sur le profil.  
**Correction :** Activez `bAllowRuntimePromotion` sur `ULDASRepresentationProfile` lorsque la promotion d'exécution est souhaitée.

## 5. L'inspecteur de l'éditeur n'affiche aucun sujet

**Symptôme :** L'interface utilisateur de l'inspecteur est vide après PIE ou le travail dans le monde de l'éditeur.  
**Cause :** Les sujets n'ont jamais été enregistrés sur ce sous-système de monde, ou le contexte de monde inspecté est incorrect.  
**Correction :** Confirmez l'enregistrement par rapport au même `UWorld` que celui observé par l'inspecteur ; réenregistrez après le rechargement de la carte.

## 6. La commande validate rapporte des erreurs de contrat

**Symptôme :** `ULDASValidateContractsCommandlet` se termine avec des résultats.  
**Cause :** Incohérences entre profil/descripteur/contrat dans le contenu du projet.  
**Correction :** Lisez la sortie de la commande, corrigez les actifs nommés, relancez la validation.

## 7. Attente des ponts WarCollection / Lightning / UCM

**Symptôme :** Les API d'adaptateur optionnelles semblent manquantes.  
**Cause :** Ces ponts sont spécifiques à la cible et ne font pas partie de MVP 1+2+3.  
**Correction :** Utilisez uniquement les API principales fournies. Traitez les adaptateurs comme des intégrations futures optionnelles.

## Documents associés

- [QUICKSTART.md](QUICKSTART.md)
- [UserManual.md](UserManual.md)
- [SettingsReference.md](SettingsReference.md)
- [FAQ.md](FAQ.md)
