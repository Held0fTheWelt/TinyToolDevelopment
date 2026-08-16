<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/LogLevelEditor/architecture.md -->
# Référence des paramètres

LogLevelEditor stocke sa configuration dans `ULogLevelEditor_Settings`.

## Objet de paramètres

Fichier source :

```text
Source/LogLevelEditor/Public/LogLevelEditor_Settings.h
```

Portée de la configuration :

```text
EditorPerProjectUserSettings
```

Cela signifie que de nombreux paramètres sont propres à l'utilisateur ou à l'éditeur plutôt qu'à l'exécution du jeu.

## LogLevelDataAsset

Type :

```text
TSoftObjectPtr<ULogLevelDataAsset>
```

Par défaut :

```text
/LogLevelEditor/DA_LogLevelVerbosity.DA_LogLevelVerbosity
```

Objectif :

- Stocke les surcharges de verbosité persistantes par catégorie.
- Est chargé par le module au démarrage.
- Est mis à jour par le widget après l'exécution réussie d'une commande.

Recommandation :

- Utilisez l'asset par défaut fourni pour les petits projets.
- Créez une copie spécifique au projet si vous souhaitez un contrôle strict dans le contrôle de code source.

## bAutoSaveLogLevelDataAsset

Par défaut :

```text
true
```

Objectif :

- Enregistre automatiquement le DataAsset après toute modification de surcharge persistante.
- Réduit le risque d'oublier d'enregistrer l'asset après un changement de politique de journalisation.

## bShowToolbarButton

Par défaut :

```text
true
```

Objectif :

- Affiche le raccourci vers Log Level Editor dans la barre d'outils du Level Editor.
- L'entrée du menu **Tools → Log Tools → Log Level Editor** reste disponible lorsque ce raccourci est masqué.

## bAlsoListEnginePluginChannels

Par défaut :

```text
false
```

Objectif :

- Inclut les répertoires sources des plugins du moteur dans le scanner.

Compromis :

- Résultats plus complets.
- Temps d'analyse plus long et plus de catégories dans l'interface.

## bAlsoListEngineSourceChannels

Par défaut :

```text
false
```

Objectif :

- Inclut les répertoires sources du moteur dans le scanner.

Compromis :

- Visibilité très large.
- Analyses potentiellement beaucoup plus lourdes.

## bTemporaryHideLogLevels

Par défaut :

```text
false
```

Objectif :

- Active la liste de masquage réservée à la session.

Stockage :

- Éphémère (Transient).
- Non sauvegardé dans la configuration.

## LogChannelsToHideTemporary

Objectif :

- Noms des catégories masquées uniquement pour la session en cours d'éditeur.

Exemple :

```text
LogTemp
LogSlate
LogDerivedDataCache
```

## LogChannelsToHide

Objectif :

- Noms des catégories masquées au fil des sessions.

Recommandation :

- Utiliser avec parcimonie. Le masquage permanent peut rendre plus difficile la découverte de journaux utiles ultérieurement.

## Configuration de base pratique

Pour la plupart des projets :

```text
bAutoSaveLogLevelDataAsset = true
bAlsoListEnginePluginChannels = false
bAlsoListEngineSourceChannels = false
bTemporaryHideLogLevels = false
```
