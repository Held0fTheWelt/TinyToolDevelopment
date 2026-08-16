<!-- doc-provenance: product-facts.yml reconciled 2026-07-15; source AKDB:plugins/AsyncSplineBuilder/architecture.md -->
# Documentation d'Async Spline Builder

Async Spline Builder génère des maillages de spline pour routes, circuits de course, tuyaux, rails, murs et objets secondaires sans provoquer de calages majeurs de l'éditeur. Il prend en charge la génération synchrone, le traitement par lots asynchrone dans l'éditeur, le traitement par lots asynchrone au runtime, les plans de maillage par segment, les murs de tènement optionnels, les interruptions de saut, les murs de dénivelé, les assets de points de spline et la déformation de hauteur de paysage réservée à l'éditeur avec peinture de couche additive.

Ce dossier contient la documentation livrée avec le plugin.

## Commencer ici

- [BUYER_GUIDE.md](BUYER_GUIDE.md) : vue d'ensemble du produit, flux de travail, forces et limitations.
- [UserManual.md](UserManual.md) : flux de travail complet dans l'éditeur depuis le premier placement d'actor jusqu'aux régénérations.
- [FAQ.md](FAQ.md) : questions et réponses prêtes pour Fab.

## Référence

- [SettingsReference.md](SettingsReference.md) : chaque paramètre important d'actor et configuration de base recommandée.
- [LandscapeAndWalls.md](LandscapeAndWalls.md) : alignement, déformation de hauteur, murs de tènement, interruptions et murs de dénivelé.
- [TechnicalOverview.md](TechnicalOverview.md) : architecture de niveau mainteneur et flux de génération.
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md) : problèmes courants de configuration, génération, tracé et géométrie.

Les audits réservés aux mainteneurs, notes de finalisation, commandes d'automatisation, notes héritées et listes de contrôle de publication peuvent exister dans le dépôt source, mais sont exclus du package acheteur.

## Flux de travail rapide

1. Activez le plugin et redémarrez l'éditeur si nécessaire.
2. Ouvrez **Tools > Track Tools > Async Spline Builder**.
3. Placez ou sélectionnez un `ASplineGeneratingActor` depuis le panneau de flux de travail.
4. Assignez `MainMesh` dans la section de configuration du panneau.
5. Modifiez les points de la `TrackSpline` dans le viewport.
6. Utilisez **Build Now** pour une génération immédiate ou **Rebuild** pour un traitement par lots asynchrone.
7. Utilisez les assistants de segment pour créer des lignes par segment avant les modifications avancées par segment.
8. Optionnel : activez les murs de tènement et configurez les types d'objets de tracé dans le panneau Details.
9. Optionnel : assignez un paysage, exécutez **Deform Height**, puis **Paint Layer** (nécessite `PaintLayer` sur l'actor) pour la peinture de poids additive.

## Fonctionnalités principales

- Génération de maillage de route ou de piste le long d'une spline.
- Track Shape Editor pour la création native de points de tracé/agencement avec contrôles concepteur pour agencements, ancres et segments.
- Validate Layout Connectors pour vérifier les métadonnées passives de connecteur (`PitEntry`, `PitExit`, `Link`, `ServiceAccess` ou personnalisées) avant de se fier aux relations de parcours.
- Apply Layout Connector pour ajouter ou mettre à jour des enregistrements passifs de relation d'agencement sans créer de branches de maillage cachées.
- Régénérations asynchrones dans l'éditeur avec `SegmentsPerTick`.
- Régénérations asynchrones au runtime via une pompe à minuterie au tick suivant.
- Sélection de maillage par segment et planification de longueur de maillage.
- Maillages supplémentaires de début, milieu et fin pour glissières, barrières, clôtures, tuyaux ou maillages de détail.
- Interruptions de saut qui neutralisent les maillages de route et latéraux.
- Zones de dénivelé et murs de dénivelé procéduraux entre paliers de hauteur.
- Murs de tènement procéduraux qui tracent vers le bas jusqu'au terrain ou autres types d'objets configurés.
- Nettoyage des composants générés basé sur les tags, résistant aux tableaux obsolètes et aux régénérations de construction.
- Sauvegarde/chargement des points de spline via `USplinePointListAsset`.
- Déformation de hauteur de paysage réservée à l'éditeur plus peinture de couche globale additive.
- Tests d'automatisation pour les comportements à haut risque.

## Position runtime prise en charge

Le module runtime contient l'actor, la génération de maillage de spline, la génération de murs de tènement, la génération de murs de dénivelé, l'accès aux assets de données et la pompe asynchrone au runtime.

Le module éditeur contient le panneau de flux de travail, la déformation de paysage et peinture de couche réservées à l'éditeur, ainsi que les assistants de sélection de l'éditeur. Les jeux empaquetés peuvent générer les maillages de spline et les murs procéduraux, mais les modifications de hauteur/poids de paysage et le panneau de flux de travail sont réservés à l'éditeur.

## Panneau de flux de travail de l'éditeur

La surface principale de l'éditeur est **Tools > Track Tools > Async Spline Builder**. Elle regroupe le flux de travail courant dans les onglets **Build**, **Segments** et **Terrain** pour garder les tâches quotidiennes compactes sans masquer l'état de validation.

Utilisez le Track Shape Editor lorsqu'un tracé nécessite la création native de points/agencements, et utilisez les contrôles de connecteurs d'agencement lorsque les voies des stands, accès de service ou itinéraires alternatifs nécessitent des métadonnées de relation explicites.

Utilisez le panneau pour le travail quotidien. Utilisez le panneau Details d'Unreal pour les champs bruts avancés tels que les tableaux de maillages supplémentaires par segment, les paramètres détaillés UV de mur, les tableaux d'objets de tracé, les paramètres de collision personnalisés et les champs expérimentaux.

## Limitations importantes

- Paysage : déformation de hauteur plus peinture de poids de couche **globale additive** lorsque `PaintLayer` est défini (`PaintLandscapeLayerNow` ou panneau **Paint Layer**). Le mode de peinture de remplacement/effacement n'est pas implémenté.
- La déformation de paysage est une opération ponctuelle dans l'éditeur, et non une étape automatique de chaque régénération de piste.
- Les paysages de production complexes nécessitent toujours un contrôle qualité manuel, en particulier dans les virages serrés, les terrains très escarpés et les configurations de murs mixtes par segment.
- L'automatisation asynchrone au runtime est couverte par un crochet de test déterministe ; une passe d'intégration complète dans un monde PIE avec minuterie reste recommandée pour les cartes finales.

## Validation

Pour une passe de validation de package locale, compilez la cible éditeur de votre projet et exécutez le groupe d'automatisation AsyncSplineBuilder depuis les outils d'automatisation d'Unreal. Conservez les chemins de commandes spécifiques aux mainteneurs dans les notes de version locales plutôt que dans le package acheteur livré.

## Première passe de production recommandée

Utilisez d'abord une courte spline de test ouverte, puis une boucle fermée, puis la piste réelle. Conservez `bUseAsyncBuild` activé, commencez avec `SegmentsPerTick = 2` et ne l'augmentez qu'après avoir confirmé la réactivité de l'éditeur. Configurez les types d'objets de tracé avant d'activer l'alignement ou les murs de tènement, car la validation bloque intentionnellement les générations qui détruiraient l'ancienne géométrie sans produire de remplacement valide.

## Note légale

Async Spline Builder est fourni selon les termes de licence inclus avec la distribution du produit. Le plugin ne concède aucun droit sur les maillages, matériaux, paysages ou contenus tiers utilisés avec les pistes générées.
