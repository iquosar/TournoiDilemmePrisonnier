#pragma once
#include "Player.hpp"
#include "Reward.hpp"
#include <vector>

//le "tournoi"
class Game{
public:
    std::vector<Player> players;
    int tour;
    Reward reward;
    Game(std::vector<Player> p_players, int p_tour = 200, Reward p_rew = Reward())
        : players(p_players), tour(p_tour), reward(p_rew) {}
};
