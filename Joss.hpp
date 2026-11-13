#pragma once
#include "Strategy.hpp"
#include <cstdlib>

class JOSS : public Strategy{
public:

    CD alea(){
        return (std::rand() % 10 == 7)? D : C;
    }

    CD choix(CD prevu){
        return (prevu == D)? prevu : alea();
    }    

    CD play(Strategy& p) override {
        return p.listCD.empty()? C : choix(p.listCD.back());
    }; 
};