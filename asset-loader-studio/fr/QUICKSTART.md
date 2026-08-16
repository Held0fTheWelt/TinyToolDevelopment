<!-- doc-provenance: product-facts.yml reconciled 2026-07-01; source AKDB:plugins/AssetLoaderStudio/architecture.md -->
# Démarrage rapide

## Objectif

Ouvrir Asset Loader Studio, soumettre une demande de chargement au moment de l'exécution, inspecter un instantané de table, prévisualiser une opération gouvernée et l'appliquer uniquement après que la prévisualisation a été autorisée.

## Première exécution

1. Activez **Asset Loader Studio** et redémarrez l'éditeur Unreal si demandé.
2. Ouvrez **Outils > Tiny Tools > Asset Loader Studio**.
3. Choisissez le mode **Guided** pour la première exécution normale. Utilisez **Simple** lorsque vous souhaitez uniquement une inspection.
4. Saisissez un chemin d'objet complet connu tel que `/Game/Data/DT_Items.DT_Items` ou un chemin DataAsset que vous contrôlez, puis cliquez sur **Inspect**.
5. Examinez l'état du job renvoyé, les chemins chargés, les échecs partiels, le graphe de dépendances et les diagnostics.
6. Capturez un instantané de table à partir d'un DataAsset ou d'une DataTable que vous contrôlez.
7. Ouvrez **Validation** et résolvez les actifs manquants, les lignes en double, les références invalides ou les refus de permission avant de tenter une mutation.
8. Utilisez **Preview Operation** pour toute action de création, duplication, renommage, retargeting, réparation, sauvegarde, annulation ou suppression.
9. Utilisez **Apply Operation** uniquement lorsque la prévisualisation signale une décision de profil autorisée, un niveau de risque acceptable et des cibles correspondant aux actifs que vous souhaitez modifier.
10. Examinez le rapport d'application et sauvegardez les packages modifiés via votre flux de travail Unreal/contrôle de source habituel.

## Points d'entrée Blueprint et Runtime

- `SubmitLoadRequest` démarre une demande de chargement au moment de l'exécution et renvoie un état de job.
- `CaptureTableSnapshot` lit les données de table structurées pour la validation et le travail sur le graphe.
- `PreviewOperation` évalue une mutation planifiée par rapport à un profil de permission avant l'application.

Gardez les intégrations UCM et MCP en option ; l'espace de travail et le sous-système runtime constituent le chemin d'utilisation initiale autonome.
