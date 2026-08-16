<!-- doc-provenance: AKDB:plugins/VisualFidelityDirector/architecture.md; docs/architecture/plugins/VisualFidelityDirector/product-facts.yml; reconciled 2026-07-12 -->
# Dépannage

## J'ai activé le plugin et rien ne s'est passé

Cause : VFD s'ouvre à partir d'une entrée de menu ; il n'affiche pas de fenêtre au démarrage.

Solution :

1. Redémarrez Unreal Editor après avoir activé le plugin.
2. Ouvrez **Tiny Tools > Visual Fidelity Director**.
3. Si le menu est toujours manquant, confirmez que le plugin est activé dans **Édition > Plugins**.

## Métriques en direct indisponibles

Cause : les métriques en direct nécessitent un contexte de mesure de fenêtres d'affichage de l'éditeur disponible. Certaines plates-formes, sessions sans interface ou premiers ticks d'éditeur peuvent ne pas exposer les données de passe GPU.

Solution :

1. Cliquez sur **Refresh** une fois la fenêtre d'affichage visible.
2. Attendez que la fenêtre d'échantillonnage multi-images se termine (plusieurs ticks d'éditeur).
3. Traitez `-1` ou les chaînes indisponibles explicites comme une dégradation honnête — VFD n'invente pas de chiffres.

## Aucun profil n'apparaît dans la barre de profils

Cause : aucun profil de fidélité n'existe encore sous `Saved/VisualFidelityDirector/profiles/`.

Solution :

1. Importez ou dupliquez un profil via le workflow de votre projet, ou migrez à partir d'une recette intégrée à l'aide des Expert Tools et de l'outillage de projet.
2. Cliquez sur **Refresh** sur la page Cockpit.

## L'application gouvernée a tout ignoré

Cause : aucune destination n'a été cochée, la différence compilée correspond déjà, ou la destination est bloquée.

Solution :

1. Cliquez d'abord sur **Build Destinations**.
2. Examinez chaque résumé et cochez l'approbation uniquement pour les destinations prévues.
3. Confirmez que le profil actif se compile avec les modifications (`Compile Preview`).

## La comparaison de profils n'affiche aucune différence

Cause : les deux profils se compilent dans le même état souhaité pour tous les axes, ou un profil a échoué à la validation.

Solution :

1. Validez que les deux profils se compilent sans erreur.
2. Modifiez une variante ou un niveau d'intention sur un profil et rafraîchissez.

## Le panneau de commande / Expert Tools s'ouvre mais aucun rapport n'est écrit

Cause : le dossier `Saved` du projet est peut-être en lecture seule ou indisponible.

Solution :

1. Basculez sur **Expert Tools** et cliquez sur **Open Output Folder**.
2. Confirmez que le projet peut écrire dans `Saved/VisualFidelityDirector/`.
3. Réessayez **Export Snapshot** et lisez la ligne **Status**.

## L'aperçu d'application a tout ignoré

Cause : la recette sélectionnée contient peut-être des recommandations d'exportation uniquement, la valeur recommandée correspond déjà à la valeur actuelle, ou la CVar est indisponible dans ce contexte d'engine.

Solution :

1. Exportez d'abord une évaluation à blanc de la recette.
2. Ouvrez `settings_diff.md`.
3. Vérifiez les colonnes **Mode**, **Supported** et **Risk**.

## Une CVar indique Indisponible

Cause : certaines CVars dépendent de la version de l'engine, du rendu, de la plate-forme ou du contexte.

Solution : traitez la recommandation comme un examen manuel. VFD enregistre les valeurs indisponibles au lieu de faire échouer l'ensemble du workflow.

## Les recommandations MRQ n'ont pas modifié mon préréglage

Cause : la mutation des préréglages MRQ n'est intentionnellement pas prise en charge.

Solution : ouvrez `mrq_recommendation.md` et appliquez manuellement tous les paramètres cinématographiques après examen.

## La recommandation Lumen n'a pas modifié de maillage ou de matériau

Cause : les paramètres des cartes de maillage Lumen, les graphes de matériaux et les drapeaux de partage de cartes de matériaux sont intentionnellement réservés à un examen manuel uniquement.

Solution : exportez **Lumen Deep Scan** ou une évaluation à blanc de recette Lumen, puis inspectez les rapports et appliquez manuellement les modifications de maillage ou de matériau uniquement après validation visuelle.

## Les diagnostics expérimentaux semblent trop grossiers

Cause : le rapport de diagnostic est une carte thermique d'acheminement des révisions basée sur des métadonnées. Il ne s'agit pas d'une carte thermique de différence d'images basée sur les pixels et il ne capture pas les vecteurs de mouvement.

Solution : utilisez les rapports de snapshot et de scanner pour un examen structuré ; capturez les preuves visuelles manuellement lorsque cela est nécessaire.

## L'application de la bibliothèque Blueprint n'a rien écrit

Cause : `ApplyPersistentConfiguration` requiert `Request.bUserApproved` et des résumés de destinations approuvés.

Solution : appelez d'abord `PreviewPersistentDestinations`, marquez uniquement les destinations prévues comme approuvées dans la requête, puis appelez l'application avec `bUserApproved=true`.
