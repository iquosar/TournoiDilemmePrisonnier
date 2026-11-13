#include <iostream>
#include "Game.hpp"
#include "TFT.hpp"
#include "ALL_D.hpp"
#include "Joss.hpp"
#include "Tester.hpp"
#include "Random.hpp"


int main(){
    TFT tft1 , tft2;
    ALL_D all_d; 
    JOSS jo;
    RANDOM rando;
    std::vector<Strategy*> joueurs = { &tft1, &tft2, &all_d, &jo, &rando};

    Game game(joueurs,10);
    game.start();

    for(Strategy* s : game.players){
        int tmp = s->point;
        std::cout<< tmp << std::endl;
    }
    return EXIT_SUCCESS;
}