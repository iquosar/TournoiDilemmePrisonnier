#pragma once
#include "Strategy.hpp"

class ALL_C : public Strategy{
public:
    CD play(Strategy&) override {return C;}; 
    std::string name(){return "ALL_C";};
};
