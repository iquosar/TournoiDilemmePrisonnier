#pragma once
#include "Strategy.hpp"
#include <cstdlib>

class RANDOM : public Strategy{
public:
    CD play(Strategy&) override {
        return (std::rand() % 2 == 1)? C : D;
    }; 
    std::string name(){return "Random";};

};