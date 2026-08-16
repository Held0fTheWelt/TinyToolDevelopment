<!-- doc-provenance: product-facts.yml reconciled 2026-07-19; source AKDB:plugins/BestPracticesJournal/architecture.md; release 1.1.2 -->
# Logiciels tiers

Best Practices Journal ne blesse aucun runtime tiers, fournisseur de modèles, serveur de base de données ou exécutable externe.

Les flux de travail optionnels SQLite ou Postgres sont des profils de stockage et des choix d'environnement externe. Ils ne sont pas livrés sous forme de logiciels tiers embarqués dans le package du plugin.

Si un projet utilise SQLite, Postgres, IIS, UCM, UCI, PRS ou tout autre composant optionnel de l'écosystème, ce composant reste un choix externe du projet ou du studio. Le package livré de BPJ doit toujours pouvoir ouvrir, valider, importer, exporter et réviser les artefacts JSON sans ces composants.

Les fournisseurs et consommateurs optionnels sont des surfaces d'intégration, non des logiciels embarqués. Leur absence doit se traduire par un statut ou des diagnostics, et non par un échec de démarrage ou d'utilisation initiale de BPJ.
