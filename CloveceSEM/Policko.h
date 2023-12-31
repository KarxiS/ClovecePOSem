//
// Created by 2karo on 31. 12. 2023.
//

#ifndef CLOVECEPOSEM_POLICKO_H
#define CLOVECEPOSEM_POLICKO_H


#include "Hrac.h"

class Policko {
private:
    char znakovaReprezentacia='*';
    int cislo = -1;
    bool jeDomcekEnd=false;
    bool jeDomcekSpawn=false;
    int hracDomcekVystup=0;

public:
    Policko(int cislo=-1, char znak='*');
    char getZnak();
    Policko setZnak(char znak);
    int getCislo();
    Policko setCislo(int cislo);
    Policko setSpawn(Hrac hrac);
};


#endif //CLOVECEPOSEM_POLICKO_H
