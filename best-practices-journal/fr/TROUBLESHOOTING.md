<!-- doc-provenance: product-facts.yml reconciled 2026-07-19; source AKDB:plugins/BestPracticesJournal/architecture.md; release 1.1.2 -->
# Dépannage

## Échec de la validation de la pratique

**Cause :** L'enregistrement ne dispose pas du contexte requis, de l'applicabilité, des preuves, des compromis, des modes de défaillance, de la provenance, de l'état de révision ou des notes de droits.

**Solution :** Ouvrez la pratique, complétez les champs manquants et validez à nouveau avant de l'accepter ou de l'exporter.

## La pratique semble trop générique

**Cause :** L'enregistrement est rédigé comme un slogan ou une préférence de style au lieu d'une pratique réutilisable accompagnée de son contexte et de ses preuves.

**Solution :** Ajoutez le problème, le contexte cible, les raisons de son fonctionnement, les limites d'application, les compromis, les préconditions, les modes de défaillance, les références de preuves et les exigences de validation. Conservez-la comme candidate jusqu'à ce que ces champs soient clairs.

## Garde-fou du dossier rejeté

**Cause :** Le dossier d'application ressemble à un plan d'exécution, manque d'une pratique source révisée, contient du code d'implémentation copié ou tente d'accorder une autorité de mutation.

**Solution :** Réécrivez le dossier sous forme d'intention uniquement. Incluez le contexte cible, l'adaptation recommandée, les contraintes, la validation requise et l'état d'approbation, puis laissez l'exécuteur en aval créer son propre plan.

## L'importation du résultat a réduit la confiance

**Cause :** Le résultat importé a signalé un échec, une régression, un rejet, un succès partiel ou des leçons contredisant la pratique d'origine.

**Solution :** Conservez le résultat. Mettez à jour les notes de révision, ajoutez une spécialisation ou une pratique de remplacement si nécessaire, et évitez de supprimer des preuves négatives dans le seul but de conserver la recommandation d'origine intacte.

## Fournisseur manquant

**Cause :** Des fournisseurs optionnels de candidats, de preuves, de résultats d'implémentation ou de transmission sont absents ou désactivés.

**Solution :** Poursuivez avec des enregistrements manuels/locaux ou activez le fournisseur optionnel. L'absence de fournisseur n'est pas fatale pour le flux de travail autonome du journal.

## Le rapport du fournisseur semble caviardé

**Cause :** BPJ caviarde les diagnostics du fournisseur avant de rédiger les rapports d'intégration afin que les invites (prompts), jetons, chemins et champs de type secret ne fuient pas dans les artefacts partagés.

**Solution :** Utilisez le rapport caviardé pour le partage. Inspectez l'outillage local du fournisseur uniquement si vous êtes autorisé à manipuler les diagnostics bruts.

## Back-end de stockage indisponible

**Cause :** Le back-end de stockage sélectionné ne peut pas ouvrir le chemin configuré ou le profil externe.

**Solution :** Revenez à `JsonArtifacts`, vérifiez les chemins locaux ou corrigez le profil de base de données externe en dehors du package de plugin livré.

## La sortie du commandlet est difficile à trouver

**Cause :** Le journal du commandlet ne fait que résumer l'opération ; le rapport sauvegardé constitue le résultat durable.

**Solution :** Inspectez `Saved/BestPracticesJournal/reports/` pour consulter les rapports de validation et d'importation. Filtrez les journaux Unreal par `LogBestPracticesJournal` lorsque vous avez besoin des diagnostics environnants.
