//
// Created by 2karo on 27. 12. 2023.
//

#ifndef CLOVECEPOSEM_HRAC_H
#define CLOVECEPOSEM_HRAC_H

#include <vector>
#include <string>
#include "Figurka.h"
#include "Kocka.h"

class Hrac {
private:
    std::string meno;
    std::string farbaFiguriek;
    std::vector<Figurka> figurky;
    bool jeSkonceny;

public:
    Hrac(std::string paMeno, std::string paFarba){
        meno=paMeno;
        farbaFiguriek=paFarba;
    }

    void hodKockou(Kocka kocka);                                //hrac hadze kockou
    void spravPosun(Figurka zvolenaFigurka, int pocetPoli);     //hrac sa rozhoduje, ktoru svoju figurku posunie
    void vypisInfo();                                           //vypis informacie o hracovi
};


#endif //CLOVECEPOSEM_HRAC_H

