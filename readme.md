# Labo Multithread Sudoku

## Introduction

Ce projet se compose de 4 parties principales qui feront l'objet d'une implémentation en C : `stat.c`, `sudoku_checker.c`, `producer_consumer.c`, `search.c`. L'intérêt de ce laboratoire est l'utilisation du multithreading.

## stat.c

Ce premier programme consiste à utiliser plusieurs threads pour effectuer 3 tâches distinctes: un calcul de moyenne, une recherche d'un élément le plus petit et d'un élément le plus grand. 

### Structure 

Notre programme est constitué d'un `main` et de 3 fonctions : `mean`, `minimum`, `maximum`. Nous implémentons 3 threads, 1 par fonction :
```c
pthread_create(&thread1, NULL, mean, NULL);
pthread_create(&thread2, NULL, minimum, NULL);
pthread_create(&thread3, NULL, maximum, NULL);
```

### Utilisation

Pour compiler `stat.c`, utilisez la commande suivante :

```sh
gcc stat.c -pthread -o stat
```

Puis pour compiler :

```sh
./stat <[argument 1] [argument2] ...>
```
où chaque argument est un nombre. 

## sudoku_checker.C

La deuxième tâche consista à implémenter un programme qui vérifie si une grille de sudoku est valide ou non. 

### Structure

Notre programme est consituté de 3 fonctions qui implémentent les règles du sudoku, à savoir `check_row` qui regarde si chaque ligne contient les chiffres de 1 à 9 compris, `check_column` qui fonctionne de manière analogue mais pour les colonnes et finalement `check_square` qui vérifie si les 9 zones de 3x3 contiennent tous les chiffres.
Dans notre main, nous créons 27 threads répartis en 3 groupes de 9. Chaque groupe sera utilisé avec chaque fonctions citées précédemment. Chaque thread retournera 1 si le test effectué est concluant et stockera cette valeur dans un tableau appelé `valid_thread` de longueur 27. Finalement, si l'intégralité des valerus de cette liste `valid_thread` est 1, le sudoku est concluant.
Notre code est adapté à une tableau à 2 dimensions de 9x9, voici un exemple :
```c
int sudoku[9][9] = {
    {5, 3, 4, 6, 8, 7, 9, 1, 2},
    {6, 7, 2, 1, 9, 5, 3, 4, 8},
    {1, 9, 8, 3, 4, 2, 5, 6, 7},
    {8, 5, 9, 7, 6, 1, 4, 2, 3},
    {4, 2, 6, 8, 5, 3, 7, 9, 1},
    {7, 1, 3, 9, 2, 4, 8, 5, 6},
    {9, 6, 1, 5, 3, 7, 2, 8, 4},
    {2, 8, 7, 4, 1, 9, 6, 3, 5},
    {3, 4, 5, 2, 8, 6, 1, 7, 9}
};
``` 

### Utilisation

Pour compiler `sudoku_checker.c`, utilisez la commande suivante :

```sh
gcc sudoku_checker.c -pthread -o sudoku
```

Puis pour compiler :

```sh
./sudoku
```

## producer_consumer.c

### Structure

### Utilisation


## search.c

### Structure

### Utilisation