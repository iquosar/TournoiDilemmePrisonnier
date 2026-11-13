#pragma once
#include "Player.hpp"

enum CD { C = 0 , D = 1};

class Strategy{
public:
    virtual CD play(Player p) = 0;
};