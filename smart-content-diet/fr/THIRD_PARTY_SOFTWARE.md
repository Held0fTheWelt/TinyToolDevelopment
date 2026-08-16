<!-- doc-provenance: AKDB:plugins/SmartContentDiet/architecture.md; docs/architecture/plugins/SmartContentDiet/product-facts.yml; reconciled 2026-07-16 -->
# Logiciels tiers

SmartContentDiet **n'intègre aucun code source tiers, binaire d'exécution, modèle d'IA, Node.js, Python ou exécutable autonome**. Il s'agit d'un plugin C++ pour l'éditeur Unreal Engine qui utilise uniquement des modules Unreal Engine et des API Unreal standard (registre d'assets, analyse d'assets, interface éditeur, commandlet).

La boucle principale analyse → examen → correction sûre s'exécute entièrement à l'intérieur de l'éditeur **sans service d'IA ni outil externe**. Les routes optionnelles de l'écosystème inter-plugins (via **Unreal Capability Mesh (UCM)**) sont déclarées en JSON et n'ajoutent aucun logiciel tiers à ce package.

Aucun logiciel externe, compte ou environnement d'exécution n'est requis pour installer ou utiliser le plugin.

**Déclaration de logiciels tiers Fab :** aucun logiciel tiers intégré.
