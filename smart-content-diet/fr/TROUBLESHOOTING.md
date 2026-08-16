<!-- doc-provenance: AKDB:plugins/SmartContentDiet/architecture.md; docs/architecture/plugins/SmartContentDiet/product-facts.yml; reconciled 2026-07-16 -->
# Dépannage

## J'ai activé le plugin mais je ne le vois pas

Ouvrez **Tools → Content Tools → Smart Content Diet**. Si l'entrée de menu est manquante, confirmez que le plugin est activé dans *Édition → Plugins* et que vous avez redémarré l'éditeur.

## Un onglet attendu (Préréglage / Gouvernance / Redondance) n'est pas visible

La visibilité des onglets dépend du rôle. **Préréglage** et **Gouvernance** apparaissent pour **Ingénieur / Producteur** (mode avancé) ; **Redondance** n'apparaît que lorsqu'un fournisseur de similarité externe est enregistré. Modifiez votre rôle/niveau d'explication dans les **Paramètres** ou le sélecteur de public de l'en-tête.

## L'analyse ne renvoie rien ou très peu

**Quick Safe** utilise uniquement le chemin registre/métadonnées (aucun chargement d'assets), donc certains résultats nécessitent un passage plus lourd. Basculez la profondeur de l'en-tête sur **Full** (charge les assets) ou **Deep** (métriques approfondies sur matériaux/maillages) et relancez l'analyse.

## « Lancez d'abord une analyse » / résultats ou optimisations vides

Les résultats et les actions d'optimisation nécessitent une analyse terminée. Lancez d'abord une analyse depuis l'en-tête, puis ouvrez **Résultats** ou **Optimiser**.

## L'application est bloquée ou demande une approbation

Les actions modificatives sont soumises à approbation par défaut et doivent s'exécuter dans un espace de travail sauvegardé, sous contrôle de source et jetable. Confirmez votre sauvegarde/contrôle de source, puis approuvez l'action. Les corrections destructives nécessitent en outre un consentement explicite (`allow_destructive: true` sur la route concernée).

## Où se trouvent les rapports d'application ?

```text
Saved/SmartContentDiet/OptimizationQueue/<timestamp>/
```

## Une route inter-plugins affiche « disponible mais plugin non chargé »

C'est attendu et sans danger : SCD ne requiert jamais obligatoirement un plugin pair. Les routes qui référencent un autre plugin (par ex. une collecte de similarité IIS) sont signalées comme *disponibles mais plugin non chargé* lorsque ce pair est absent, tandis que chaque capacité réservée à SCD reste disponible.
