//
// Created by andre on 29. 12. 2023.
//

#ifndef CLOVECEPOSEM_FIGURKA_H
#define CLOVECEPOSEM_FIGURKA_H
#include <string>

class Figurka {
private:
    std::string farba;
    int aktualnaPozicia;
    bool vDomceku;  //bud je v domceku alebo v hre
    bool vCieli;    //bud je v cieli alebo v hre

public:
    Figurka(std::string paFarba){
        farba=paFarba;
    }
    void posunFigurky(int pocetPoli);   //posun figurky
    void presunZDomceku();              //presun figurky na hraciu dosku
    void vyradenieFigurky();            //presun figurky naspat do domceku
};


#endif //CLOVECEPOSEM_FIGURKA_H
