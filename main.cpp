#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include "Game.hpp"
#include "TFT.hpp"
#include "ALL_D.hpp"
#include "Joss.hpp"
#include "Tester.hpp"
#include "Random.hpp"
#include "RANCUNE.hpp"
#include "TF2T.hpp"



void afficherClassement(std::vector<Strategy*> joueurs) {
    std::sort(joueurs.begin(), joueurs.end(),
              [](Strategy* a, Strategy* b) { return a->point > b->point; });

    for (size_t i = 0; i < joueurs.size(); i++)
        std::cout << i + 1 << ". " << joueurs[i]->name()
                  << " : " << joueurs[i]->point << std::endl;
}

// lance un tournoi et affiche le classement
void lancer(const std::string& titre, std::vector<Strategy*> joueurs, Reward rew = Reward()) {
    std::srand(42);   // graine fixe pour que les résultats soit "fixe" (remise à chaque tournoi)

    Game game(joueurs, 200 , rew);   // 200 tours, 5 parties par duel
    game.start();

    std::cout << "========================================" << std::endl;
    std::cout << titre << std::endl;
    std::cout << "========================================" << std::endl;
    afficherClassement(game.players);
    std::cout << std::endl;
}

int main() {
    // étape 1 : une instance de chaque stratégie du cours
    {
        TFT tft1;
        ALL_D alld1;
        JOSS joss1;
        RANDOM random1;
        Tester tester1;
        lancer("BASE", { &tft1, &alld1, &joss1, &random1, &tester1 });
    }

    // étape 1 bis : les jumeaux (chaque stratégie peut jouer contre une copie d'elle-même)
    {
        TFT tft1, tft2;
        ALL_D alld1, alld2;
        JOSS joss1, joss2;
        RANDOM random1, random2;
        Tester tester1, tester2;
        lancer("JUMEAUX", { &tft1, &alld1, &joss1, &random1, &tester1,
                            &tft2, &alld2, &joss2, &random2, &tester2 });
    }

    // étape 2 : nouvelles stratégies
    {
        TFT tft1;
        ALL_D alld1;
        JOSS joss1;
        RANDOM random1;
        Tester tester1;
        RANCUNE grim;
        TF2T tf2t;
        lancer("ETENDU", { &tft1, &alld1, &joss1, &random1, &tester1,
                           &grim, &tf2t });
    }

    // étape 2 bis : nouvelles stratégies + jumeaux
    {
        TFT tft1, tft2;
        ALL_D alld1, alld2;
        JOSS joss1, joss2;
        RANDOM random1, random2;
        Tester tester1, tester2;
        RANCUNE grim1, grim2;
        TF2T tf2t1, tf2t2;
        lancer("ETENDU JUMEAUX", { &tft1, &alld1, &joss1, &random1, &tester1,
                                   &tft2, &alld2, &joss2, &random2, &tester2,
                                   &grim1, &tf2t1, &grim2, &tf2t2 });
    }

    {
        TFT tft1;
        ALL_D alld1;
        JOSS joss1;
        RANDOM random1;
        Tester tester1;
        RANCUNE grim;
        TF2T tf2t;
        Reward cerf({4,4}, {0,3},
                    {3,0}, {1,1});
        lancer("ETENDU CERF", { &tft1, &alld1, &joss1, &random1, &tester1,
                                &grim, &tf2t }, cerf);
    }

    {
        TFT tft1, tft2;
        ALL_D alld1, alld2;
        JOSS joss1, joss2;
        RANDOM random1, random2;
        Tester tester1, tester2;
        RANCUNE grim1, grim2;
        TF2T tf2t1, tf2t2;
        Reward cerf({4,4}, {0,3},
                    {3,0}, {1,1});
        lancer("ETENDU JUMEAUX CERF", { &tft1, &alld1, &joss1, &random1, &tester1,
                                   &tft2, &alld2, &joss2, &random2, &tester2,
                                   &grim1, &tf2t1, &grim2, &tf2t2 }, cerf);
    }


    return EXIT_SUCCESS;
}