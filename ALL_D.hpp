#pragma once
#include "Strategy.hpp"

class ALL_D : public Strategy{
public:
    CD play(Player p) override {return D;}; 
};
