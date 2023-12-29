//
// Created by 2karo on 27. 12. 2023.
//

#ifndef CLOVECEPOSEM_HRA_H
#define CLOVECEPOSEM_HRA_H


#include "../Objekty/Hrac.h"
#include "../Objekty/HraciaDoska.h"

class Hra {
private:
    int pocetHracov;
    std::vector<Hrac> hraci;
    HraciaDoska hraciaDoska;
    Hrac aktualnyTah;

public:
    void zacniHru();
    void spravTah();
    void ukonciHru();
    void ukazVysledok();
};


#endif //CLOVECEPOSEM_HRA_H
