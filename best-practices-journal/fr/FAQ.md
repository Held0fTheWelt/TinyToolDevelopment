<!-- doc-provenance: product-facts.yml reconciled 2026-07-19; source AKDB:plugins/BestPracticesJournal/architecture.md; release 1.1.2 -->
# FAQ

## BPJ est-il un outil de prise de notes générique ?

Non. BPJ est destiné aux pratiques d'ingénierie appuyées par des preuves, avec applicabilité, compromis, modes de défaillance, provenance, état de révision et historique des résultats.

## Quand une élément doit-il rester un candidat ?

Conservez-le comme candidat lorsque les preuves, l'applicabilité, les compromis, les modes de défaillance, la provenance ou l'état de révision sont incomplets. Les candidats peuvent être utiles, mais ne doivent pas être traités comme des directives acceptées.

## BPJ modifie-t-il les fichiers du projet ?

Non. BPJ peut créer des dossiers d'application et importer des résultats, mais la mutation de projet appartient à des outils en aval approuvés ou à des flux de travail humains.

## Que doit contenir un dossier d'application ?

Utilisez un dossier pour le contexte cible, l'adaptation recommandée, les contraintes, les références de preuves, la validation requise et le statut d'approbation. Ne l'utilisez pas comme un plan de correctif ou une commande de mutation.

## BPJ nécessite-t-il IIS, SDA, UCI, PRS, UCM ou LLM Store ?

Non. BPJ est autonome. Des plugins Tiny Tool optionnels peuvent fournir des preuves, de l'indexation, de la documentation, de l'implémentation ou des flux de routes, mais ne sont pas requis pour l'utilisation de base.

## BPJ peut-il appeler l'IA ou décider des étapes d'implémentation ?

Non. BPJ peut stocker des preuves ou des intentions créées par un autre flux de travail révisé, mais il ne possède pas l'exécution de l'IA, la recherche, la planification de correctifs, l'application, l'annulation ou la validation finale.

## Où les données sont-elles stockées ?

Le profil par défaut utilise des artefacts JSON locaux au projet sous la racine de stockage de BPJ. Des profils SQLite optionnels ou des profils studio externes peuvent être configurés pour des flux de travail plus importants.

## Quelles données peuvent être sensibles ?

Les enregistrements de pratiques, preuves, dossiers, résultats et rapports peuvent contenir des chemins locaux, des noms de projets, des notes de révision, des sorties de validation, des notes de droits ou des diagnostics de fournisseurs. Révisez et caviardez les exportations avant de les partager.

## Où trouver les journaux et les rapports ?

Les rapports sont enregistrés sous `Saved/BestPracticesJournal/reports/`. Les diagnostics du runtime, de l'éditeur et des commandlets utilisent `LogBestPracticesJournal` dans le journal Unreal. Les artefacts sauvegardés restent la preuve durable.

## Puis-je partager des pratiques avec une équipe ?

Oui, après révision. Traitez les exportations comme locales au projet jusqu'à ce qu'elles aient été assainies pour retirer les chemins privés, les notes confidentielles et les preuves sensibles relatives aux droits.

## Des fournisseurs optionnels manquants peuvent-ils casser le journal ?

Non. Les fournisseurs manquants doivent apparaître uniquement sous forme de statut ou de diagnostic. Les enregistrements manuels, les preuves locales, la validation, l'exportation et l'importation de résultats doivent rester disponibles.

## Faut-il importer les résultats échoués ?

Oui. Les résultats échoués, rejetés, partiels et sans effet (no-op) sont importants car ils peuvent affaiblir, contredire, spécialiser ou remplacer la pratique. Les masquer rend le journal moins digne de confiance.
