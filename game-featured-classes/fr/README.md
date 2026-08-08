# Documentation de GameFeaturedClasses

GameFeaturedClasses est un shell de plugin d'exécution léger pour les classes de gameplay mises en avant spécifiques au projet. La version `1.0.1` inclut le descripteur, les métadonnées d'emballage, l'icône, le journal des modifications et une limite de module d'exécution (`StartupModule` / `ShutdownModule`).

Public cible : équipes ayant besoin de la limite de package GFC dans un projet dès aujourd'hui, alors que les classes mises en avant et le GameFeature Workbench premium restent l'architecture cible (pas encore disponibles dans ce package).

## Package actuel

- Le module d'exécution `GameFeaturedClasses` se charge après activation + redémarrage.
- Aucun asset de classe de gameplay mise en avant, aucune action Game Feature, registre ou workbench d'éditeur n'est fourni pour le moment.
- Aucun autre plugin Tiny Tool n'est requis pour le shell.

## Prise en main

1. Activez le plugin — consultez l'exemple pratique [QUICKSTART.md](QUICKSTART.md) (vérification de fumée du module).
2. Lisez [UserManual.md](UserManual.md) pour la limite actuelle vs cible.
3. Utilisez [TROUBLESHOOTING.md](TROUBLESHOOTING.md) lorsqu'un menu workbench est attendu mais manquant.

## Fichiers associés

- [../README.md](../README.md) — aperçu du produit.
- [../CHANGELOG.md](../CHANGELOG.md) — historique des versions.
- [SettingsReference.md](SettingsReference.md) · [FAQ.md](FAQ.md) · [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md)
