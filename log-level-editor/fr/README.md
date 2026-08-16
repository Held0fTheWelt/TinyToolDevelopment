<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/LogLevelEditor/architecture.md -->
# Documentation de LogLevelEditor

LogLevelEditor est un plugin d'éditeur Unreal Engine conçu pour découvrir les catégories de journaux (logs) et modifier leur niveau de détail (verbosity) depuis un tableau de bord dédié dans l'éditeur. Il aide les équipes à réduire les journaux bruyants pendant le travail quotidien, à élever temporairement les canaux de diagnostic lors du débogage et à conserver les surcharges intentionnelles dans un DataAsset.

Les actions principales sont **Scan**, **Set Verbosity** et **Hide Category**.

Ce dossier contient la documentation complète livrée avec le plugin.

## Commencez ici

- [BUYER_GUIDE.md](BUYER_GUIDE.md) : vue d'ensemble pour les acheteurs, adéquation et valeur pratique.
- [UserManual.md](UserManual.md) : flux de travail complet de la configuration à l'application des surcharges.
- [FAQ.md](FAQ.md) : questions et réponses prêtes pour Fab.

## Référence

- [SettingsReference.md](SettingsReference.md) : chaque paramètre, comportement par défaut et configuration recommandée.
- [TechnicalOverview.md](TechnicalOverview.md) : architecture et comportement à l'exécution pour les mainteneurs.
- [CodeDocumentation.md](CodeDocumentation.md) : structure du code, contrats et points d'extension.
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md) : problèmes courants et solutions.
- [ReleaseChecklist.md](ReleaseChecklist.md) : étapes de validation avant la publication d'une mise à jour Fab.

## Ressources incluses

- `../Readme.pdf` : fichier lisez-moi traditionnel.
- `../LogLevelEditor_Changelog.txt` : notes de version.
- `../Content/DA_LogLevelVerbosity.uasset` : DataAsset par défaut utilisé pour les surcharges de verbosité persistantes.
- `../Content/Map_Tutorial_LogLevelEditor.umap` : contenu de tutoriel et de démonstration.

## Flux de travail rapide

1. Activez le plugin et redémarrez l'éditeur lorsque cela vous est demandé.
2. Ouvrez l'onglet Log Level Editor depuis **Tools → Log Tools → Log Level Editor** ou via le raccourci optionnel de la barre d'outils.
3. Laissez le scanner découvrir les catégories de journaux du projet et des plugins.
4. Utilisez les paramètres de recherche et de masquage pour vous concentrer sur les canaux importants.
5. Modifiez le niveau de détail d'une catégorie via les boutons de verbosité de la ligne correspondante.
6. Enregistrez les surcharges dans le `ULogLevelDataAsset` configuré lorsque la modification est intentionnelle.
7. Réinitialisez une catégorie à sa valeur par défaut détectée en sélectionnant à nouveau cette valeur par défaut.

## Ce que l'outil modifie

Le plugin applique des commandes de console Unreal sous la forme :

```text
Log <CategoryName> <VerbosityName>
```

Il ne modifie pas la déclaration source d'une catégorie de journal. Les modifications persistantes sont stockées dans le DataAsset configuré et réappliquées par le module de l'éditeur dès que le moteur est prêt à accepter des commandes de console.

## Noms de verbosité pris en charge

L'assistant de verbosité partagé prend en charge les niveaux de journalisation standard d'Unreal :

- `NoLogging`
- `Fatal`
- `Error`
- `Warning`
- `Display`
- `Log`
- `Verbose`
- `VeryVerbose`

L'éditeur utilise intentionnellement les mêmes noms que ceux affichés par la configuration des journaux Unreal afin d'associer directement les modifications d'interface aux commandes de console.

## Modèle de sécurité

LogLevelEditor évite d'afficher des états erronés :

- Le libellé `Current` est extrait de l'état d'exécution d'Unreal lorsque la catégorie peut être interrogée.
- L'état de l'interface est mis à jour uniquement après le succès d'une commande de console.
- Les surcharges persistantes sont supprimées lorsque la valeur sélectionnée correspond au niveau par défaut détecté.
- Les paramètres de masquage temporaire restent éphémères et ne sont pas écrits dans la configuration.
- Les surcharges enregistrées sont appliquées avec une logique de réessai par catégorie au démarrage, car l'éditeur n'est pas toujours prêt à recevoir des commandes de console au lancement du module.

## Utilisation typique

- Réduire le bruit généré par un plugin bavard tout en le maintenant activé.
- Élever temporairement un sous-système de gameplay, de build, d'asset ou d'éditeur au niveau `Verbose`.
- Restaurer des valeurs par défaut propres après avoir étudié un problème.
- Partager un DataAsset d'équipe contenant des surcharges de verbosité choisies pour l'ensemble du projet.
- Conserver les catégories du moteur et du projet séparées dans les paramètres afin de garder des scans rapides et pertinents.

## Limitations importantes

- Les catégories de journaux doivent exister dans le code source ou être déjà enregistrées par des modules d'exécution/éditeur.
- Le scan du code source ne peut déduire les valeurs par défaut qu'à partir des macros Unreal classiques.
- Le code d'exécution peut toujours modifier la verbosité après l'application des surcharges par l'éditeur.
- Les versions finales (Shipping builds) ne sont pas affectées par ce plugin d'éditeur.

## Note légale

LogLevelEditor est un outil de productivité pour l'éditeur. Il ne modifie pas la sémantique de journalisation d'Unreal Engine, le code source du moteur ou les conditions de licence du projet.
