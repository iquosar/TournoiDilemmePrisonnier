#pragma once
#include "Strategy.hpp"

// ne riposte qu'après deux trahisons consécutives de l'adversaire
class TFT2 : public Strategy {
public:
    CD play(Strategy& p) override {
        size_t n = p.listCD.size();
        if (n >= 2 && p.listCD[n - 1] == D && p.listCD[n - 2] == D)
            return D;
        return C;
    }

    std::string name() override { return "TFT2"; }
};