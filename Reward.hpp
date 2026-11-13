#pragma once
#include <utility>

using score = std::pair<int,int>;

class Reward{
public:
    const score GAINS[2][2];

    Reward(score cc, score cd, score dc, score dd)
        : GAINS{{cc, cd}, 
                {dc, dd}} {}

    Reward() : Reward({3,3}, {0,5}, 
                      {5,0}, {2,2}) {}
};