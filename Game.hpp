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
    Game(std::vector<Player> p_players, int p_tour = 200, Reward p_rew = Reward(), int p_parties = 5)
        : players(p_players), tour(p_tour), reward(p_rew) {}
    score partie(Player& a, Player& b); 
    void start();
};

inline score Game::partie(Player& a, Player& b) {
    a.listCD.clear();
    b.listCD.clear();
    int sa = 0, sb = 0;
    for (int t = 0; t < tour; t++) {
        CD ca = a.strat->play(b);   // les deux choisissent AVANT
        CD cb = b.strat->play(a);   // de voir le coup de l'autre
        a.listCD.push_back(ca);
        b.listCD.push_back(cb);
        auto [ga, gb] = reward.GAINS[ca][cb];
        sa += ga;
        sb += gb;
    }
    return {sa, sb};
}

inline void Game::start() {
    for (size_t i = 0; i < players.size(); i++) {
        Player& a = players[i];

        // contre soi-même : on ne garde que le score d'un côté
        Player miroir = a;
        for (int k = 0; k < nbParties; k++)
            a.points += partie(a, miroir).first;

        for (size_t j = i + 1; j < players.size(); j++) {
            Player& b = players[j];
            for (int k = 0; k < nbParties; k++) {
                auto [sa, sb] = partie(a, b);
                a.points += sa;
                b.points += sb;
            }
        }
    }
}