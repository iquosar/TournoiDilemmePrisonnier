#pragma once
#include "Strategy.hpp"

// C jusqu'à la première trahison de l'adversaire, puis D pour toujours
//https://axelrod.readthedocs.io/en/fix-documentation/reference/overview_of_strategies.html

class RANCUNE : public Strategy {
public:
    bool rancune = false;

    CD play(Strategy& p) override {
        if (p.listCD.empty()) {
            rancune = false;   // nouvelle partie
            return C;
        }
        if (p.listCD.back() == D)
            rancune = true;
        return rancune ? D : C;
    }

    std::string name() override { return "Rancune"; }
};