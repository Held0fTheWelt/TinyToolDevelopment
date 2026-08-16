<!-- doc-provenance: product-facts.yml reconciled 2026-07-19; source AKDB:plugins/BestPracticesJournal/architecture.md; release 1.1.2 -->
# Documentation de Best Practices Journal

Best Practices Journal aide les équipes à gouverner leurs pratiques d'ingénierie réutilisables directement dans Unreal Editor. Il stocke les connaissances sur les pratiques, la provenance, l'état de révision, l'intention d'implémentation et l'historique des résultats sous une racine d'artefacts locale appartenant à BPJ.

La version 1.1.2 prend en charge Unreal Engine 5.4 et les versions ultérieures. Les preuves importées et les sorties des fournisseurs restent des candidats à réviser jusqu'à leur promotion humaine explicite ; aucun producteur externe ne peut accepter une pratique de manière autonome.

BPJ est autonome. Des fournisseurs d'écosystème optionnels peuvent fournir des preuves, des candidats, des résultats ou des destinations de transmission, mais le journal, la validation, la recherche, l'exportation et la boucle de résultats doivent rester utilisables en l'absence de tout fournisseur optionnel.

## Concepts principaux

- Les enregistrements de pratiques (Practice records) décrivent des directives d'ingénierie réutilisables, le contexte, les compromis, l'applicabilité, les modes de défaillance et l'état de révision.
- Les candidats pratiques (Practice candidates) sont des brouillons ou des propositions dérivées de fournisseurs qui nécessitent encore une révision.
- Les enregistrements de preuves (Evidence records) relient les pratiques à des preuves locales au projet, à la provenance, aux notes de droits et au niveau de confiance.
- Les dossiers d'application (Application briefs) décrivent l'intention d'adapter une pratique révisée à une cible spécifique.
- Les importations de résultats (Outcome imports) enregistrent si le travail en aval a validé, affaibli, contredit, spécialisé ou remplacé une pratique.
- Les politiques de caviardage et de garde-fous garantissent que les enregistrements partagés restent intentionnels.
- Les back-ends de stockage permettent à BPJ de fonctionner sous forme d'artefacts JSON, de SQLite local ou d'un profil studio basé sur Postgres.

## Limite du produit

BPJ possède les enregistrements de pratiques, les candidats, les références de preuves, l'état de révision, les dossiers d'application, les importations de résultats d'implémentation, les exportations déterministes, la validation de schéma, le caviardage, les garde-fous et les rapports locaux. Il ne possède pas la planification de correctifs, les essais/applications (dry-run/apply), l'annulation (rollback), la validation finale d'implémentation, l'exécution d'IA ou la mutation de sources/actifs.

Les dossiers d'application sont des artefacts de transmission d'intention uniquement. Les outils en aval ou les flux de travail humains doivent toujours exécuter leurs propres étapes de planification, d'approbation, de mutation, de validation et d'annulation.

## Contrat d'acceptation

Une pratique acceptée ne doit pas être un simple slogan. Avant l'acceptation ou une réutilisation large, enregistrez :

- Le problème, le contexte et la solution.
- Pourquoi cela fonctionne et où cela s'applique.
- Les préconditions, règles d'adaptation, compromis et modes de défaillance.
- Les références de preuves, la provenance, les notes de droits et le niveau de confiance.
- L'état de révision, les notes des réviseurs et l'historique des résultats lorsqu'ils sont disponibles.

Les champs faibles ou manquants doivent être traités comme des constatations de validation, et non comme de simples problèmes de formatage sans importance.

## Contrat de dossier et de résultat

Les dossiers d'application peuvent inclure l'identité de la pratique, le contexte cible, l'adaptation recommandée, les contraintes, les catégories d'actions autorisées et interdites, les exigences de validation, les sorties attendues, les références de preuves, l'état d'approbation et les notes de compatibilité. Ils ne doivent pas inclure de code d'implémentation copié ni accorder d'autorité de mutation.

Les importations de résultats mettent à jour l'historique et la confiance accordée à la pratique. Un résultat échoué ou rejeté est une donnée utile : il doit être importé au lieu d'être masqué, car il peut affaiblir, contredire, spécialiser ou remplacer la pratique d'origine.

## Artefacts locaux et journaux

BPJ écrit les artefacts locaux du projet sous `Saved/BestPracticesJournal/`, notamment `practices`, `candidates`, `evidence`, `application_briefs`, `implementation_outcomes`, `reports`, `schemas`, `logs` et `provider_inbox`. Les diagnostics Unreal utilisent `LogBestPracticesJournal` ; les preuves durables de l'opérateur doivent être tirées des artefacts JSON/Markdown sauvegardés plutôt que des lignes de journal éphémères.

## Documentation acheteur

- [Démarrage rapide](QUICKSTART.md)
- [Manuel de l'utilisateur](UserManual.md)
- [Référence des paramètres](SettingsReference.md)
- [Dépannage](TROUBLESHOOTING.md)
- [FAQ](FAQ.md)
- [Logiciels tiers](THIRD_PARTY_SOFTWARE.md)
- [Storage Backends](StorageBackends.md)

## Surfaces d'opération

- Établi de l'éditeur : créer, réviser, rechercher, préparer des dossiers, importer des résultats et inspecter l'état de l'intégration.
- Artefacts sauvegardés : enregistrements JSON/Markdown sous `Saved/BestPracticesJournal/`.
- Commandlets : validation, importation d'artefacts et exportation d'échantillons pour l'automatisation et les contrôles de mise en ligne.
- Routes/fournisseurs optionnels : surfaces d'intégration remplaçables qui ne doivent pas devenir des prérequis d'utilisation initiale.

## Flux de travail

1. Ouvrez `Tools > Best Practices Journal`.
2. Créez ou importez des enregistrements de pratiques.
3. Joignez les preuves et l'état de révision.
4. Validez et révisez l'enregistrement avant acceptation.
5. Produisez un dossier d'application d'intention uniquement lorsque le contexte d'implémentation est connu.
6. Importez les résultats une fois le travail en aval terminé.

## Fichiers associés

- [../README.md](../README.md) : démarrage rapide.
- [../CHANGELOG.md](../CHANGELOG.md) : historique des versions.
- [StorageBackends.md](StorageBackends.md) : modes de stockage JSON, SQLite et Postgres.
