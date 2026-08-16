<!-- doc-provenance: product-facts.yml reconciled 2026-07-19; source AKDB:plugins/BestPracticesJournal/architecture.md; release 1.1.2 -->
# Manuel de l'utilisateur

Best Practices Journal est un établi d'éditeur pour la gouvernance des pratiques d'ingénierie appuyées par des preuves. Il s'agit d'un outil d'aide à la décision et de mémoire de révision, et non d'un planificateur de correctifs, d'un éditeur de source, d'un exécuteur d'IA ou d'un outil de mutation d'actifs.

## Flux de travail principal

1. Capturez une pratique ou un candidat à partir d'une note manuelle, d'une référence de preuve ou d'un fournisseur optionnel.
2. Ajoutez l'applicabilité, les compromis, les modes de défaillance, la provenance, les notes de droits et les métadonnées de révision.
3. Validez l'enregistrement avant de l'accepter ou de l'exporter.
4. Recherchez des pratiques lors du choix de directives pour une tâche ou une révision.
5. Créez un dossier d'application pour une pratique révisée ou un candidat explicite.
6. Transmettez le dossier à un flux de travail humain, UCI, PRS ou un autre exécuteur approuvé.
7. Importez les rapports de résultats d'implémentation pour enregistrer si la pratique a été validée, affaiblie, contredite, spécialisée ou remplacée.

## Qualité des enregistrements de pratiques

Utilisez BPJ pour des pratiques capables de résister à la révision. Un enregistrement utile comprend :

- Un problème concret et un contexte cible.
- Une solution énoncée sous forme de directive réutilisable, et non de code d'implémentation copié.
- Pourquoi la directive fonctionne, où elle s'applique et où elle échoue.
- Les compromis, préconditions, règles d'adaptation et modes de défaillance.
- Les références de preuves, la provenance, les notes de droits, la confiance et l'état de révision.

Si ces champs sont inconnus, conservez l'élément sous forme de candidat ou de brouillon. Ne le promouvez pas au rang de directive acceptée simplement parce que le résumé semble plausible.

## Opérations publiques

- **Create practice record** stocke une pratique révisée ou un brouillon avec les preuves, le contexte, les compromis et l'état de révision.
- **Create practice candidate** stocke un brouillon ou une proposition dérivée d'un fournisseur jusqu'à sa révision explicite.
- **Attach evidence** lie des preuves locales/manuelles/fournisseurs sans copier de code d'implémentation restreint.
- **Search practices** renvoie les enregistrements de pratiques correspondants depuis le magasin d'artefacts appartenant à BPJ.
- **Create application brief** exporte une transmission d'intention uniquement pour un contexte cible spécifique.
- **Import implementation outcome** boucle la chaîne après l'implémentation ou le rejet.

## Dossiers d'application (Application Briefs)

Un dossier doit aider un autre flux de travail à planifier en toute sécurité. Il peut inclure le projet/module/périmètre cible, l'adaptation recommandée, le raisonnement, les contraintes, les catégories d'actions autorisées et interdites, les exigences de validation, les sorties attendues, les références de preuves, l'état d'approbation et les notes de compatibilité.

Un dossier ne doit pas servir d'autorisation permettant à BPJ de modifier des fichiers. Si l'outil en aval applique des modifications, il doit posséder la résolution du périmètre, la planification d'essai à blanc, l'approbation, les portes de mutation, la validation, l'annulation et son propre rapport de résultat.

## Importations de résultats (Outcome Imports)

Importez chaque résultat significatif, y compris les résultats échoués, rejetés, partiels et sans effet (no-op). Les résultats mettent à jour l'historique de la pratique, la confiance, les notes de révision et les liens d'évolution. Ils ne réécrivent pas la pratique d'origine comme étant universellement correcte.

Utilisez les champs de résultat pour les références aux fichiers modifiés, les chemins de rapports de validation, les leçons apprises, les mises à jour recommandées du journal, les avertissements, les erreurs et les liens vers des plans ou rapports externes.

## Fournisseurs optionnels

Des fournisseurs optionnels de preuves, de candidats, de résultats, de transmission, d'indexation, de routes ou d'implémentation peuvent enrichir BPJ. Ils doivent rester remplaçables. Si un fournisseur est absent, poursuivez avec des enregistrements manuels, des preuves locales, des artefacts JSON/Markdown et la validation BPJ.

## Capability Mesh (MCP)

Les agents sans accès aux fichiers peuvent boucler le cycle de vie du journal axé sur la révision via UMCP :

- `bpj.gather_candidates.v1` — analyse les dossiers de boîte de réception des fournisseurs (y compris `project_intelligence_orchestrator` issu de la transmission PIO).
- `bpj.repository.list.v1` — liste les identifiants de pratiques, candidats, preuves, dossiers et résultats.
- `bpj.practice.read.v1` — lit un enregistrement sérialisé directement.
- `bpj.candidate.promote.v1` — promeut un candidat révisé (nécessite l'approbation de l'utilisateur sur la route).
- `bpj.import_artifacts.v1` — importe les enveloppes de candidats PIO (`schema` / `schema_version` commençant par `bpj.implementation_intent_candidates.`).

Chemin de la boîte de réception des fournisseurs : `Saved/BestPracticesJournal/provider_inbox/candidates/<provider_id>/`.

## Commandlets

Les commandlets sont utiles pour la validation, l'importation d'artefacts et l'exportation d'échantillons, mais ne sont pas des étapes obligatoires lors de la première utilisation. Utilisez les rapports sauvegardés sous `Saved/BestPracticesJournal/reports/` comme preuves durables pour l'automatisation. Les journaux résument ce qui s'est passé ; les artefacts sauvegardés constituent l'enregistrement officiel.

## Limites

BPJ enregistre les connaissances et les intentions. Il ne modifie pas les fichiers sources, les actifs, les fichiers Build.cs, les descripteurs de projet ou le code de plugins externes. Les responsables de l'exécution en aval doivent exécuter leurs propres portes de prévisualisation, d'approbation, de validation et d'annulation.

## Preuves locales et journaux

BPJ stocke les preuves de révision durables sous `Saved/BestPracticesJournal/`. Utilisez les fichiers JSON/Markdown sous `reports`, `application_briefs`, `implementation_outcomes` et `schemas` lors du partage ou de l'audit d'un flux de travail. La catégorie de journal Unreal `LogBestPracticesJournal` est destinée aux diagnostics d'opérateur et aux résumés de commandlets ; elle ne constitue pas le registre officiel des pratiques acceptées.
