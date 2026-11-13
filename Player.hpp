#pragma once
#include "Strategy.hpp"
#include <vector>
#include <memory>

class Player{
public:
    int point;
    std::shared_ptr<Strategy> strat;
    //la liste DU JOUEUR et pas celle de son adversaire
    std::vector <CD> listCD;

    Player(std::shared_ptr<Strategy> p_strat);
};

Player::Player(std::shared_ptr<Strategy> p_strat){
    strat = p_strat;
    point = 0;
    listCD = {};
}