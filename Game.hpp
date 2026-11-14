#pragma once
#include "Strategy.hpp"
#include "Reward.hpp"
#include <vector>

class Game {
public:
    std::vector<Strategy*> players;
    int tour;
    Reward reward;

    Game(std::vector<Strategy*> p_players, int p_tour = 200, Reward p_rew = Reward())
        : players(p_players), tour(p_tour), reward(p_rew) {}

    score partie(Strategy& a, Strategy& b);
    void start();
};

inline score Game::partie(Strategy& a, Strategy& b) {
    a.listCD.clear();
    b.listCD.clear();
    //score A et score B
    int sa = 0, sb = 0;
    for (int t = 0; t < tour; t++) {
        CD ca = a.play(b);
        CD cb = b.play(a);
        a.listCD.push_back(ca);
        b.listCD.push_back(cb);
        score gains = reward.GAINS[ca][cb];   // la case (coup de a, coup de b)
        //le couple
        int ga = gains.first;                 // gain de a
        int gb = gains.second;                // gain de b
        sa += ga;
        sb += gb;
    }
    return {sa, sb};
}

inline void Game::start() {
    size_t n = players.size();
    for (size_t i = 0; i < n; i++) {
        for (size_t j = i + 1; j < n; j++) {
            //modif: c'est bien 5 parties par duo
            for (int k = 0; k < 5; k++) { 
            score s = partie(*players[i], *players[j]);
            players[i]->point += s.first;
            players[j]->point += s.second;
            }
        }
    }
}    