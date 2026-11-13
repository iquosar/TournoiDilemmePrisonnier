#pragma once
#include "Strategy.hpp"
#include <cstdlib>

class RANDOM : public Strategy{
public:
    CD play(Strategy& p) override {
        return (std::rand() % 2 == 1)? C : D;
    }; 
};