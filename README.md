# Philosopher :spaghetti: :sleeping_bed: :thought_balloon:
## Présentation du projet
**Philosopher** est une simulation classique du problème des philosophes mangeurs, un exercice de synchronisation en informatique. Le projet comprend deux programmes : l'un utilise des threads et l'autre des sémaphores pour gérer la concurrence. L'objectif est de permettre aux philosophes (processus ou threads) de manger, dormir, et penser, tout en évitant les blocages et les conditions de famine.

Le projet explore les techniques de synchronisation pour résoudre les conflits liés à l'accès concurrent aux ressources partagées (les fourchettes). Il met également l'accent sur la rigueur dans la gestion des processus concurrents.

## Objectifs pédagogiques
Le projet Philosopher vise à :

- Comprendre et implémenter les concepts de **synchronisation** avec des **threads** et des **sémaphores**.
- Explorer les mécanismes de gestion de la **concurrence** pour résoudre les conflits liés aux ressources partagées.
- Renforcer la maîtrise des règles strictes de formatage des logs et des contraintes temporelles.

## Fonctionnement des programmes
Paramètres
Les deux programmes prennent les arguments suivants en entrée :
<number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
- number_of_philosophers : Nombre de philosophes (et de fourchettes).
- time_to_die : Temps maximal (en millisecondes) avant qu’un philosophe ne meure s’il ne commence pas à manger.
- time_to_eat : Temps nécessaire pour qu’un philosophe termine de manger.
- time_to_sleep : Temps passé à dormir.
- number_of_times_each_philosopher_must_eat (optionnel) : Nombre minimal de repas que chaque philosophe doit consommer avant que la simulation ne s’arrête. Si omis, la simulation s’arrête lorsqu’un philosophe meurt.

Exemple:
  ./philo 5 800 200 200 5

## Philosophie de la simulation  
1. Chaque philosophe peut être dans un des états suivants : manger, dormir, penser, ou mourir.
2. Un philosophe ne peut manger que s’il tient deux fourchettes.
3. Les messages d’état sont affichés avec un format strict, sans chevauchement, et respectent des contraintes temporelles strictes.
4. La simulation vise à éviter les blocages et à maximiser la survie des philosophes.

## Implémentations
- **Threads** : Chaque philosophe est un thread qui gère son propre cycle de vie. Les fourchettes sont modélisées avec des mutex pour assurer une gestion sécurisée des ressources partagées.
- **Sémaphores** (bonus) : Chaque philosophe est un processus, les sémaphores sont utilisés pour contrôler l'accès aux fourchettes et gérer les synchronisations entre philosophes.
