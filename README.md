***Gestion Avancée des Processus et des Signaux en C sous Linux***
#
**Contexte**
Ce programme en C illustre la gestion avancée des processus et des signaux sous Linux. Il crée plusieurs processus fils à partir d'un processus père, gère la communication entre ces processus à l'aide de signaux, et met en œuvre des mécanismes de synchronisation pour coordonner les tâches des processus fils.

**Objectifs**
Créer un processus père qui génère quatre processus fils.
Le processus père doit envoyer des signaux aux processus fils pour leur demander d'exécuter des tâches spécifiques.
Les processus fils doivent traiter les signaux reçus, effectuer des tâches complexes, et répondre en envoyant des signaux de confirmation au processus père.
Le processus père doit afficher un message à chaque fois qu'il reçoit une confirmation d'un processus fils.
Implémenter une synchronisation entre les processus fils pour qu'ils ne commencent leurs tâches qu'une fois qu'ils ont tous reçu un signal de départ.
Utiliser un mécanisme de sémaphore pour gérer la synchronisation.
