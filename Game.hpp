#pragma once
#include "Strategy.hpp"
#include "Reward.hpp"
#include <vector>

#define PROBA_ARRET_PARTIE 1

class Game {
public:
    std::vector<Strategy*> players;
    int tour;
    Reward reward;

    Game(std::vector<Strategy*> p_players, int p_tour = 200, Reward p_rew = Reward())
        : players(p_players), tour(p_tour), reward(p_rew) {}

    score partie(Strategy& a, Strategy& b);
    score partieRandomArret(Strategy& a, Strategy& b);
    void start(bool randomStop = false);
};

inline score Game::partie(Strategy& a, Strategy& b) {
    a.listCD.clear();
    b.listCD.clear();
    //score A et score B
    int sa = 0, sb = 0;
    for (int t = 0; t < tour; t++) {
        CD ca = a.aleaCoupInverse(a.play(b));   // Implémentation de la modification "bruit"
        CD cb = b.aleaCoupInverse(b.play(a));   // Implémentation de la modification "bruit"
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

// Partie avec arrêt aléatoire (probabilité de PROBA_ARRET_PARTIE de s'arrêter à chaque tour)
inline score Game::partieRandomArret(Strategy& a, Strategy& b) {
    a.listCD.clear();
    b.listCD.clear();
    //score A et score B
    int sa = 0, sb = 0, nb_tours = 0;
    while (std::rand() % 100 >= PROBA_ARRET_PARTIE) {
        CD ca = a.aleaCoupInverse(a.play(b));   // Implémentation de la modification "bruit"
        CD cb = b.aleaCoupInverse(b.play(a));   // Implémentation de la modification "bruit"
        a.listCD.push_back(ca);
        b.listCD.push_back(cb);
        score gains = reward.GAINS[ca][cb];   // la case (coup de a, coup de b)
        //le couple
        int ga = gains.first;                 // gain de a
        int gb = gains.second;                // gain de b
        sa += ga;
        sb += gb;
        nb_tours++;
    }
    //std::cout << "Partie arrêtée après " << nb_tours << " tours." << std::endl;
    return {sa, sb};
}

inline void Game::start(bool randomStop) {
    size_t n = players.size();
    for (size_t i = 0; i < n; i++) {
        for (size_t j = i + 1; j < n; j++) {
            //modif: c'est bien 5 parties par duo
            for (int k = 0; k < 5; k++) { 
                score s = (randomStop) ? partieRandomArret(*players[i], *players[j]) : partie(*players[i], *players[j]);
                players[i]->point += s.first;
                players[j]->point += s.second;
            }
        }
    }
}    