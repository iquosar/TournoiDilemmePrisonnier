# Tournoi du dilemme du prisonnier itéré

Projet 2 (partie 1) du cours HAI716I : tournoi d'Axelrod, nouvelles stratégies, modifications du tournoi.

## Compiler et lancer

```bash
g++ -std=c++17 -Wall -Wextra main.cpp -o prog
./prog
```

Tous les tournois s'exécutent à la suite, chacun dans une section séparée par des `====`.

## Protocole

- Chaque stratégie affronte chaque autre sur **5 parties de 200 tours** ; le meilleur score total gagne.
- Graine fixe `std::srand(42)`, remise avant chaque tournoi : résultats reproductibles.
- `JUMEAUX` = chaque stratégie présente en deux exemplaires (pour qu'elle puisse affronter une copie d'elle-même).

## Tournois

| Section | Étape | Contenu |
|---|---|---|
| `BASE`, `JUMEAUX` | 1 | les 5 stratégies du cours |
| `ETENDU`, `ETENDU JUMEAUX` | 2 | + Rancune, TF2T, ALL_C, Inverse |
| `ETENDU CERF`, `ETENDU JUMEAUX CERF` | 3 | matrice de la chasse au cerf (4,4 / 0,3 / 3,0 / 1,1) |
| `... TOURS_RANDOM` | 3 | horizon inconnu : 1 % de chance d'arrêter la partie à chaque tour |
| `... SELECTION` | 3 | sélection : la part de chaque stratégie évolue selon son score (1000 générations) |

Bruit : chaque coup peut être inversé avec une probabilité `PROBA_INVERSE` (5 %, dans `Strategy.hpp`).

## Stratégies

`ALL_D`, `RANDOM`, `TFT`, `Tester`, `JOSS` (cours) , `RANCUNE` , `TF2T` (Tit For Two Tats) , `ALL_C` (toujours C) , `Inverse` (joue l'inverse du dernier coup adverse).

## Fichiers

- `main.cpp` : lance tous les tournois
- `Game.hpp` : moteur (partie, tournoi tous contre tous)
- `Selection.hpp` : modification « sélection »
- `Reward.hpp` : matrice de gains
- `Strategy.hpp` : classe de base ; une stratégie par fichier `.hpp`

Journal de bord : `journal.md`.