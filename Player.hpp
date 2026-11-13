#pragma once
#include "Strategy.hpp"
#include <vector>

class Player{
public:
    int point;
    Strategy strat;
    //la liste DU JOUEUR et pas celle de son adversaire
    std::vector <CD> listCD;

    Player(Strategy strat);
};