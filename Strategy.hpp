#pragma once
#include <vector>
#include <string>

enum CD { C = 0 , D = 1};

class Strategy{
public:
    int point;
    std::vector<CD> listCD;
    virtual CD play(Strategy& p) = 0;
    virtual std::string name() = 0;

    Strategy(): point(0) , listCD({}) {}
};