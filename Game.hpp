#pragma once
#include "Player.hpp"
#include "Reward.hpp"
#include <vector>

//le "tournoi"
class Game{
public:
    std::vector<Player> players;
    int tour = 200;
    Reward reward;
};