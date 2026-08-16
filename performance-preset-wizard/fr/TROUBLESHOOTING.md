<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/PerformancePresetWizard/architecture.md -->
# Dépannage

## Le plugin n'apparaît pas dans le menu Tools

Vérifiez que le plugin est activé dans **Edit > Plugins** et redémarrez l'éditeur.

## Aucun préréglage n'est listé

Utilisez **Refresh** dans l'assistant. Vérifiez que les assets sont bien des DataAssets `UPerformancePresetAsset`.

## Un préréglage ne peut pas être appliqué

Assurez-vous qu'un préréglage est sélectionné. Si l'asset a été supprimé ou déplacé, rafraîchissez la liste.

## Certaines CVar sont signalées comme manquantes

Le nom de la CVar n'a pas pu être résolu dans le gestionnaire de console d'Unreal (faute de frappe, plugin désactivé ou autre version du moteur). Les CVar manquantes n'empêchent pas l'application du reste du préréglage.

## Les CVar sont comptées comme invalides

Les entrées invalides ont un nom ou une valeur vide. Corrigez la ligne dans l'éditeur en bloc.

## "Restore Previous" n'est pas disponible

La restauration n'est disponible qu'après avoir appliqué un préréglage au cours de la session actuelle de l'éditeur.

## Le préréglage au démarrage ne s'applique pas

Vérifiez que **Apply Preset On Editor Startup** est activé et que **Startup Preset** pointe vers un asset valide.
