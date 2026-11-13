#pragma once
#include <vector>

enum CD { C = 0 , D = 1};

class Strategy{
public:
    int point;
    std::vector<CD> listCD;
    virtual CD play(Strategy& p) = 0;

    Strategy(): point(0) , listCD({}) {}
};