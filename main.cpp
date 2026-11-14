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

void afficherClassement(std::vector<Strategy*> joueurs) {
    std::sort(joueurs.begin(), joueurs.end(),
              [](Strategy* a, Strategy* b) { return a->point > b->point; });

    for (size_t i = 0; i < joueurs.size(); i++)
        std::cout << i + 1 << ". " << joueurs[i]->name()
                  << " : " << joueurs[i]->point << std::endl;
}

int main(int argc, char* argv[]) {
    std::srand(42);   // graine fixe pour que les résultats soit "fixe"

    std::string mode = (argc > 1) ? argv[1] : "base";

    // une instance de chaque
    TFT tft1;
    ALL_D alld1;
    JOSS joss1;
    RANDOM random1;
    Tester tester1;
    std::vector<Strategy*> joueurs = { &tft1, &alld1, &joss1, &random1, &tester1 };

    // les jumeaux : chaque stratégie peut jouer contre une copie d'elle-même
    TFT tft2;
    ALL_D alld2;
    JOSS joss2;
    RANDOM random2;
    Tester tester2;

    if (mode == "base") {
        // rien à ajouter
    } else if (mode == "jumeaux") {
        joueurs.insert(joueurs.end(), { &tft2, &alld2, &joss2, &random2, &tester2 });
    } else {
        std::cerr << "Mode inconnu : " << mode << std::endl;
        std::cerr << "Modes : base, jumeaux" << std::endl;
        return EXIT_FAILURE;
    }

    Game game(joueurs);   // 200 tours, 5 parties par duel
    game.start();

    std::cout << "=== Tournoi " << mode << " ===" << std::endl;
    afficherClassement(game.players);

    return EXIT_SUCCESS;
}