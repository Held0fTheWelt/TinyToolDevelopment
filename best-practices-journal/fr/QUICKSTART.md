<!-- doc-provenance: product-facts.yml reconciled 2026-07-19; source AKDB:plugins/BestPracticesJournal/architecture.md; release 1.1.2 -->
# Démarrage rapide

## Objectif

Créer un journal de pratiques local au projet et autonome, capturer des preuves, réviser une pratique, exporter un dossier d'intention d'implémentation et importer un résultat sans modifier le code source ni les actifs du projet.

## Première exécution

1. Activez **Best Practices Journal** dans le navigateur de plugins d'Unreal Editor.
2. Redémarrez l'éditeur lorsque vous y êtes invité.
3. Ouvrez **Tools > Best Practices Journal**.
4. Créez d'abord un candidat pratique si la directive n'a pas encore été révisée.
5. Renseignez le problème, le contexte, la solution, l'applicabilité, les compromis, les préconditions et les modes de défaillance.
6. Joignez une preuve locale ou une note de preuve manuelle avec la provenance et les notes de droits.
7. Validez l'enregistrement et ajoutez les notes du réviseur avant de le traiter comme une directive acceptée.
8. Utilisez **Search practices** pour retrouver l'enregistrement par sujet, étiquette (tag) ou note de preuve.
9. Créez un dossier d'application pour une cible spécifique et révisez l'exportation JSON/Markdown.
10. Importez un résultat d'implémentation une fois le travail en aval terminé.

BPJ est autonome : des fournisseurs de preuves optionnels, des routes UCM, IIS, SDA, UCI ou PRS peuvent enrichir le flux de travail, mais le cœur du journal, la révision, l'exportation et la boucle de résultats fonctionnent sans aucun autre plugin Tiny Tool.

## Vérifier le résultat

Après la première exécution, révisez les artefacts sauvegardés sous `Saved/BestPracticesJournal/` :

- `practices/` contient les enregistrements de pratiques.
- `application_briefs/` contient les fichiers de transmission d'intention uniquement.
- `implementation_outcomes/` contient les enregistrements de résultats importés.
- `reports/` contient les rapports de validation, d'importation et d'opération.

Ces fichiers constituent la preuve durable pour la révision et la transmission. La sortie du journal Unreal est utile pour les diagnostics, mais elle ne constitue pas la source de référence.

## Contrôle de limite

Un dossier d'application doit décrire l'intention, le contexte cible, les contraintes, la validation requise et l'état d'approbation. Il ne doit pas contenir de code d'implémentation copié, d'instructions de correctif, d'étapes d'annulation ni d'autorisation permettant à BPJ de modifier les fichiers du projet.

## Première bonne pratique

Commencez par une pratique simple disposant de preuves réelles, comme une convention de journalisation spécifique au projet ou une liste de contrôle de révision. Évitez de rédiger une règle trop générale telle que « écrire du meilleur code » à moins de pouvoir fournir le contexte, les modes de défaillance, des exemples de preuves et des exigences de validation.

## Premier bon résultat

Après qu'un flux de travail en aval a essayé le dossier, importez un résultat même si rien n'a changé. Les résultats `rejected`, `failed`, `partial` et `no_op` sont utiles car ils empêchent BPJ de présenter une pratique sur-généralisée comme étant prouvée.
