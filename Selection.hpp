#pragma once
#include "Game.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>


// Un joueur n'affronte jamais lui-même, seulement les autres entrées.
// Si on met deux TFT dans le vecteur, ce sont juste deux joueurs différents qui se rencontrent normalement
// (chacun a son historique et sa part, rien de spécial à gérer ici).
class Selection {
public:
    std::vector<Strategy*> joueurs;
    Game game;   // juste pour réutiliser partie()

    std::vector<std::vector<double>> gains;   // gains[i][j] = score moyen de i contre j sur une partie
    // proportion de chaque joueur dans la population (somme = 1), ça évite d'avoir 400 instances d'une strat
    std::vector<double> parts;                

    // parts[i] est la proportion de joueurs[i]


    Selection(std::vector<Strategy*> p_joueurs, Reward rew = Reward())
        : joueurs(p_joueurs), game(p_joueurs, 200, rew) {}

    // on fait jouer chaque paire une fois pour toutes (pas besoin de rejouer à chaque génération)
    void calculerGains() {
        size_t n = joueurs.size();
        // on crée la matrice des gains : n lignes, chacune étant un vecteur de n cases à 0.0
        // std::vector<double>(n, 0.0) construit UNE ligne de n zéros, et assign en met n copies(donc matrice n x n)
        // faut l'initialiser à 0
        gains.assign(n, std::vector<double>(n, 0.0));

        for (size_t i = 0; i < n; i++) {
            for (size_t j = i + 1; j < n; j++) {   // i + 1 : jamais contre soi-même
                for (int k = 0; k < 5; k++) {      // 5 parties, format d'Axelrod
                    score s = game.partie(*joueurs[i], *joueurs[j]);
                    // on divise par 5 car on fait 5 parties (une moyenne)
                    gains[i][j] += s.first / 5.0;
                    gains[j][i] += s.second / 5.0;
                }
            }
        }
    }

    // une génération : chaque part est multipliée par (score / score moyen)
    void generation() {
        size_t n = joueurs.size();

        // le score moyen d'UN individu de chaque stratégie, rempli juste après
        std::vector<double> scoreJoueur(n, 0.0);
        double moyenne = 0.0;

        for (size_t i = 0; i < n; i++) {
            for (size_t j = 0; j < n; j++)
                if (j != i) scoreJoueur[i] += parts[j] * gains[i][j];

            // Les TFT sont 40 % de la salle, donc leur score compte pour 40 % de la moyenne
            moyenne += parts[i] * scoreJoueur[i];
        }

        // Les stratégies qui ont marqué plus que la moyenne "font plus d'enfants" à la génération suivante.
        // Ex : TFT marque 1,2 fois la moyenne -> sa part est multipliée par 1,2
        //      ALL_C marque 0,6 fois la moyenne -> sa part est multipliée par 0,6
        for (size_t i = 0; i < n; i++)
            parts[i] = parts[i] * scoreJoueur[i] / moyenne;
    }
// Une génération : on fait évoluer la part de chaque stratégie dans la population.
//
// Exemple concret avec 3 stratégies à 1/3 chacune (gains moyens sur une partie de 200 tours) :
//    TFT   contre ALL_D = 398   TFT   contre ALL_C = 600
//    ALL_D contre TFT   = 403   ALL_D contre ALL_C = 1000
//    ALL_C contre TFT   = 600   ALL_C contre ALL_D = 0
//
//    score TFT   = 1/3 * 398 + 1/3 * 600  = 332.7
//    score ALL_D = 1/3 * 403 + 1/3 * 1000 = 467.7
//    score ALL_C = 1/3 * 600 + 1/3 * 0    = 200.0
//    moyenne     = 1/3 * (332.7 + 467.7 + 200) = 333.4
//
//    nouvelle part  X    = part gen d'avant * score / moyenne 
//    nouvelle part TFT   = 33.3% * 332.7 / 333.4 = 33.26%  (stable)
//    nouvelle part ALL_D = 33.3% * 467.7 / 333.4 = 46.75%  (grossit, il exploite ALL_C, et un peu TFT)
//    nouvelle part ALL_C = 33.3% * 200.0 / 333.4 = 19.99%  (rétrécit, il se fait exploiter)
//    total = 1
//
// Et au fil des générations, plus ALL_C disparaît, moins ALL_D a de victimes à exploiter


    void afficherEntete() {
        //setw(6) pour faire des espaces
        std::cout << std::setw(6) << "gen";
        for (Strategy* s : joueurs) std::cout << std::setw(10) << s->name();
        std::cout << std::endl;
    }

    void afficherParts(int g) {
        std::cout << std::setw(6) << g;
        for (double p : parts)
            std::cout << std::setw(10) << std::fixed << std::setprecision(2) << p * 100;   // en %
        std::cout << std::endl;
    }

    // nbGen générations, une ligne affichée toutes les "pas" générations
    void start(int nbGen, int pas) {
        calculerGains();
        parts.assign(joueurs.size(), 1.0 / joueurs.size());   // au début tout le monde à égalité

        afficherEntete();
        afficherParts(0);
        for (int g = 1; g <= nbGen; g++) {
            generation();
            if (g % pas == 0) afficherParts(g);
        }
    }
};