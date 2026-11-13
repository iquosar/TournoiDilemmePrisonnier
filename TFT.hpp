#pragma once
#include "Strategy.hpp"

class TFT : public Strategy{
public:
    CD play(Strategy& p) override {
        return p.listCD.empty()? C : p.listCD.back();
    }; 
    std::string name(){return "TFT";};

};