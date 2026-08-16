<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/CodeCopyrightEditor/architecture.md -->
# Démarrage rapide

Ce guide vous accompagne de l'installation jusqu'à un **résultat réel** : une notice de droit d'auteur cohérente appliquée aux fichiers sources sélectionnés, accompagnée d'un rapport d'analyse consultable. Code Copyright Editor fonctionne de manière totalement autonome — aucun autre plugin n'est requis.

## Ce que vous obtiendrez après ce guide

Votre identité/licence configurée, la base de code analysée avec un statut par fichier, et une réécriture contrôlée appliquée aux fichiers que vous avez sélectionnés — plus un rapport d'analyse JSON sous `Saved/CodeCopyrightEditor/`.

## Exigences

- Éditeur Unreal Engine 5 (le plugin s'exécute dans l'éditeur, pas dans les jeux paquetés).
- Un projet C++ ou Blueprint avec des dossiers source/plugin à analyser.
- Aucun logiciel tiers, compte ou environnement d'exécution externe requis. Voir [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## 1. Installer et activer

1. Ajoutez **Code Copyright Editor** depuis votre bibliothèque Fab au projet (ou installez-le dans le moteur).
2. Dans l'éditeur, ouvrez **Edit → Plugins**, activez **Code Copyright Editor** et redémarrez lorsque demandé.

## 2. Ouvrir l'outil (Premier résultat)

1. Ouvrez **Tools → Code Tools → Code Copyright Editor**.
2. Dans l'onglet **Configure**, définissez votre identité et votre licence (propriétaire, identifiant de licence, modèle, portée d'analyse). Cliquez sur **Save**.
3. Passez à l'onglet **Scan & Review** et cliquez sur **Scan Files**.

Vous voyez maintenant chaque fichier éligible avec un badge de statut (`OK`, `MISSING`, `REPLACE`, `PROTECTED`, …). L'analyse n'écrit jamais dans les fichiers — il s'agit d'un aperçu sécurisé.

## 3. Un exemple concret : Appliquer les notices aux fichiers sélectionnés

1. Dans **Scan & Review**, cliquez sur **Select Changeable** — cela coche uniquement les lignes qui peuvent être réécrites en toute sécurité (`MISSING`, `REPLACE`). Les fichiers `PROTECTED` et `CONFLICT` restent inchangés.
2. Sélectionnez d'abord une seule ligne et comparez la notice **existante** et **proposée** dans l'aperçu.
3. (Recommandé) Dans l'onglet **Configure**, activez **Create Backup Before Write** et validez votre travail dans le contrôle de source au préalable.
4. Cliquez sur **Apply Selected** et confirmez. L'outil réécrit uniquement les fichiers cochés et modifiables, puis relance une analyse.

**Résultat attendu :** Les fichiers appliqués passent au statut `UPDATED` ; le résultat de l'application et une nouvelle analyse sont affichés. Dans **Apply & Reports**, cliquez sur **Export JSON**.

## 4. Où se trouvent les résultats

```text
Saved/CodeCopyrightEditor/LastCopyrightScan.json
```

Vous pouvez également mettre à jour la notice au niveau du projet (sans réécriture des sources) avec **Update Project Notice**, qui écrit dans *Project Settings → Project → Description → Legal → Copyright Notice*.

## 5. Étapes suivantes

- Flux de travail complet et chaque onglet/action : [UserManual.md](UserManual.md).
- Tous les jetons de modèle (`{CopyrightText}`, `{LicenseIdentifier}`, `{FileMetadataBlock}`, …) : [SettingsReference.md](SettingsReference.md).
- Paramètres : [SettingsReference.md](SettingsReference.md).
- Problèmes : [TROUBLESHOOTING.md](TROUBLESHOOTING.md) et [FAQ.md](FAQ.md).
