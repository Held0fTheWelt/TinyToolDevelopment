<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/LightweightEditorMode/architecture.md -->
# FAQ (Foire aux questions)

Cette FAQ est rédigée pour les acheteurs et l'assistance. Elle répond aux questions qu'un utilisateur est susceptible de se poser avant l'achat, lors de la première configuration et lors de la validation du comportement de restauration sur un projet réel.

## Réponses rapides

### Qu'est-ce que Lightweight Editor Mode ?

Lightweight Editor Mode est un plugin d'éditeur Unreal Engine qui réduit temporairement le coût de rendu du viewport de l'éditeur grâce à des profils configurables. Il permet de rendre l'édition des scènes lourdes plus fluide.

### S'agit-il d'un plugin d'optimisation pour l'exécution ?

Non. Il s'agit d'un outil de travail pour l'éditeur. Il n'optimise pas votre jeu packagé et ne remplace pas le profilage à l'exécution ni l'optimisation de contenu.

### Affecte-t-il les builds packagés ?

Non. Le plugin est exclusivement réservé à l'éditeur. Il modifie l'état de la session d'éditeur pendant que vous travaillez dans Unreal Editor et n'a aucun effet sur les versions packagées.

### Modifie-t-il mon projet de manière permanente ?

Non. Le mode est conçu comme une surcouche temporaire. Il sauvegarde les valeurs modifiées et les restaure une fois désactivé. Les paramètres de profil sont enregistrés comme paramètres utilisateur de l'éditeur, mais les cartes, les assets et les paramètres de rendu du projet ne sont pas réécrits.

### À qui s'adresse-t-il ?

Il s'adresse aux utilisateurs d'Unreal qui travaillent sur des scènes d'éditeur très lourdes : grands mondes, cartes d'environnement denses, scènes chargées en Lumen, niveaux riches en brouillard, passes massives de feuillage, ou projets où le viewport devient lourd au quotidien.

## Fonctionnalités et comportement

### Que peut modifier le plugin lorsqu'il est activé ?

Selon le profil sélectionné, il peut :

- Réduire le pourcentage d'écran du viewport de l'éditeur.
- Réduire la qualité globale de scalabilité.
- Désactiver l'éclairage indirect diffus Lumen.
- Désactiver les réflexions Lumen.
- Désactiver les cartes d'ombres virtuelles.
- Désactiver le brouillard volumétrique et le brouillard standard.
- Forcer les viewports en mode Unlit.
- Désactiver le rendu en temps réel dans les viewports.

### Pourquoi le viewport semble-t-il visuellement dégradé lorsqu'il est activé ?

C'est tout à fait normal. Le plugin échange la fidélité visuelle contre la réactivité de l'éditeur. Utilisez-le pendant l'édition de la mise en page, de la structure, du placement ou des Blueprints. Désactivez-le pour l'éclairage final, les matériaux, les captures d'écran ou les validations visuelles.

### Pourquoi le viewport passe-t-il en Unlit ?

Certains profils forcent le mode Unlit car l'éclairage peut représenter l'un des coûts les plus élevés du rendu. Vous pouvez modifier n'importe quel profil et désactiver bForceUnlitViewports si vous avez besoin du contexte d'éclairage.

### Pourquoi le rendu en temps réel se désactive-t-il ?

Certains profils désactivent le temps réel pour éviter que les viewports se rafraîchissent en continu. Cela permet d'aider sur les scènes lourdes ou les ordinateurs portables. Vous pouvez désactiver ce comportement par profil.

### Désactive-t-il Nanite ?

Non. Le plugin ne désactive pas directement Nanite. Il se concentre sur le pourcentage d'écran du viewport, la scalabilité, Lumen, les ombres virtuelles, le brouillard, le mode d'affichage et le temps réel.

### Remplace-t-il les paramètres de scalabilité d'Unreal ?

Non. Il intègre la scalabilité dans un flux de travail d'éditeur plus large. La scalabilité seule ne couvre pas tous les coûts du viewport d'éditeur, le plugin contrôle donc aussi le pourcentage d'écran spécifique, certaines CVars de rendu, le mode d'affichage et le temps réel.

## Profils

### Quels profils sont inclus ?

Le plugin comprend quatre profils modifiables :

- Mild
- Balanced
- Aggressive
- Extreme

Balanced est le point de départ recommandé.

### Puis-je personnaliser les profils ?

Oui. Ouvrez Project Settings > Plugins > Lightweight Editor Mode. Chaque profil a sa propre qualité, son pourcentage d'écran et ses options de comportement.

### Puis-je changer de profil pendant que le mode est activé ?

Oui. Le plugin rafraîchit immédiatement les paramètres actifs et conserve les sauvegardes d'origine réalisées avant l'activation initiale. La désactivation restaurera toujours l'état antérieur au mode.

### Quel profil dois-je utiliser ?

Utilisez Mild si vous avez besoin de conserver le contexte visuel. Utilisez Balanced pour l'édition générale. Utilisez Aggressive pour le placement lourd, le feuillage ou l'édition de monde. Utilisez Extreme lorsque vous recherchez une réactivité maximale sans vous soucier de la qualité visuelle.

## Restauration et sécurité

### Que se passe-t-il lorsque je désactive le mode ?

Au cours de la même session, le plugin restaure :

- Les niveaux de qualité de scalabilité sauvegardés.
- Les valeurs de CVars sauvegardées.
- Les modes d'affichage des viewports modifiés par le plugin.
- Les états de temps réel des viewports modifiés par le plugin.

### Que se passe-t-il si l'éditeur se ferme alors que le mode est activé ?

La fermeture normale du module tente de désactiver le mode. En cas de plantage ou de fermeture inopinée, les sauvegardes en mémoire sont perdues. Le plugin enregistre un mode d'affichage de secours pour éviter de rester bloqué en Unlit au redémarrage, mais ne peut pas tout reconstruire après une fermeture imprévue.

### Que faire si les viewports restent en Unlit après redémarrage ?

Ouvrez la fenêtre Lightweight Editor Mode et cliquez sur Disable Lightweight Mode. Si la sauvegarde de session n'est pas disponible, le plugin utilise le mode de secours enregistré pour ramener les viewports vers un mode non-Unlit. Si nécessaire, repassez manuellement en Lit depuis le menu du viewport.

### Un autre plugin peut-il surcharger les mêmes CVars ?

Oui. Les CVars peuvent être modifiées par la configuration du projet, la ligne de commande, les profils de périphériques, la scalabilité, d'autres plugins ou du code d'éditeur. Lightweight Editor Mode utilise une écriture avec étiquette de priorité de plugin, mais une écriture ultérieure par un autre système peut prévaloir.

### Pourquoi les CVars manquantes ne sont-elles pas traitées comme des erreurs ?

Les fonctionnalités de rendu varient selon les versions du moteur, les paramètres de projet, les plateformes et les branches personnalisées. Si une CVar n'existe pas, le plugin la saute et l'indique dans le journal sans faire échouer le mode entier.

## Compatibilité

### Quelle version d'Unreal Engine est prise en charge ?

L'implémentation cible les API d'éditeur et CVars au style d'Unreal Engine 5.4. Validez chaque version du moteur que vous prévoyez de prendre en charge, en particulier les versions récentes où les CVars peuvent évoluer.

### Fonctionne-t-il avec des branches personnalisées du moteur ?

Il devrait fonctionner dès lors que les API d'éditeur et CVars requises existent. Si une branche personnalisée renomme ou supprime des CVars de rendu, ces options spécifiques seront sautées. Consultez le Output Log pour plus de détails.

### Fonctionne-t-il sous Windows, Linux et Mac ?

Le plugin utilise uniquement du code C++ d'éditeur et évite le code d'exécution spécifique à une plateforme. Chaque plateforme cible doit néanmoins être testée avant d'annoncer une prise en charge officielle.

### S'exécute-t-il dans les commandlets ?

Aucun flux de travail significatif n'est fourni pour les commandlets. Le fonctionnement repose sur les clients de viewport interactifs de l'éditeur, l'interface Slate et l'état de session d'éditeur.

## Flux de travail

### Comment l'ouvrir ?

Allez dans Tools > Performance > Lightweight Editor Mode dans Unreal Editor.

### Comment l'activer automatiquement ?

Cochez Enable on Editor startup dans la fenêtre du plugin. Le plugin attend que les viewports de l'éditeur existent puis applique le profil actuel.

### Pourquoi l'activation au démarrage attend-elle avant de s'appliquer ?

Lors du démarrage précoce des modules, Unreal n'a pas forcément encore créé les clients de viewport. Le plugin utilise un temporisateur court pour s'activer dès que les viewports sont disponibles, garantissant une capture fiable de leur état.

### Dois-je le laisser activé toute la journée ?

Vous le pouvez, mais la meilleure habitude est de l'activer pour la vitesse de travail et de le désactiver avant toute décision visuelle. Ne jugez pas l'éclairage, les ombres, le brouillard, les matériaux ou les captures finales lorsque le mode est actif.

### Est-il utile si mon problème vient de la compilation de shaders ou du contrôle de source ?

Non. Le plugin vise uniquement le coût de rendu du viewport d'éditeur. Il ne résoudra pas les délais de compilation de shaders, le chargement d'assets, la lenteur du contrôle de source, les disques lents ou les scans d'antivirus.

## Assistance

### Que dois-je inclure dans une demande d'assistance ?

Incluez :

- La version d'Unreal Engine.
- Le système d'exploitation.
- Si le moteur est standard ou personnalisé.
- Le profil sélectionné.
- Si le problème est survenu à l'activation, au changement de profil, à la désactivation, au démarrage ou après un redémarrage.
- Les lignes du Output Log contenant "[Lightweight]".
- Tout autre plugin ou script modifiant les CVars de rendu.

### Où puis-je vérifier ce que le plugin a fait ?

Ouvrez le Output Log d'Unreal et recherchez :

- [Lightweight]
- Backup CVar
- Restore CVar
- ApplyActiveSettings
- ApplyViewportSettings
- Lightweight mode ENABLED
- Lightweight mode DISABLED

### Quelle est la règle d'utilisation la plus importante ?

Utilisez Lightweight Editor Mode pour la vitesse d'édition. Désactivez-le pour la vérité visuelle.
