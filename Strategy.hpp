#pragma once
#include <vector>
#include <string>
#include <cstdlib>

#define PROBA_INVERSE 5

enum CD { C = 0 , D = 1};

class Strategy{
public:
    int point;
    std::vector<CD> listCD;
    virtual CD play(Strategy& p) = 0;
    virtual std::string name() = 0;

    // renvoie le coup inverse
    CD inverseCD(CD cd){
        return (cd == C)? D : C;
    }
    
    // renvoie le coup inverse avec une probabilité de PROBA_INVERSE (define en haut)
    CD aleaCoupInverse(CD cd){
        return (std::rand() % 100 < PROBA_INVERSE)? inverseCD(cd) : cd;
    }

    Strategy(): point(0) , listCD({}) {}
};