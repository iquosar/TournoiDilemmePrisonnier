#pragma once
#include "Strategy.hpp"

class Inverse : public Strategy{
public:
    CD inverseCD(CD cd){
        return (cd == C)? D : C;
    }

    CD play(Strategy& p) override {
        return p.listCD.empty()? C : inverseCD(p.listCD.back());
    };
    
    std::string name(){return "Inverse";};
};
