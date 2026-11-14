#pragma once
#include "Strategy.hpp"

// joue le coup inverse de l'adversaire (et C au premier tour)
class Inverse : public Strategy{
public:
    CD play(Strategy& p) override {
        return p.listCD.empty()? C : inverseCD(p.listCD.back());
    };
    
    std::string name(){return "Inverse";};
};
