#pragma once
#include "Strategy.hpp"

class ALL_D : public Strategy{
public:
    CD play(Strategy& p) override {return D;}; 
    std::string name(){return "ALL_D";};

};
