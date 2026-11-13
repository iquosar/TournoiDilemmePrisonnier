#pragma once
#include "Strategy.hpp"


//D au premier tour. Si l'adversaire riposte, joue TIT-FOR-TAT ; sinon répète C, C, D
class Tester : public Strategy{
public:
    bool trahis = false;
    CD play(Strategy& p) override {
        size_t size = p.listCD.size();
        
        if(size == 0){ 
            trahis = false; //faut remettre à 0 entre chaque partie
            return D ;
        }
        
        //joue D ? Si oui tft
        if((p.listCD.back() == D) || (trahis)){
            trahis = true;
            return p.listCD.back();
        } 

        return (size % 3 == 0) ? D : C;            // C C D C C D
    }
}; 
