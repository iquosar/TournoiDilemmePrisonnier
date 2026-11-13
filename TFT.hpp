#pragma once
#include "Strategy.hpp"

class TFT : Strategy{
public:
    CD play(Player p) override {
        std::vector<CD> list = p.listCD;
        return list.empty()? C : list[list.length() - 1];
    }; 
};