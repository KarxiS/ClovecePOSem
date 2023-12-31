//
// Created by 2karo on 31. 12. 2023.
//

#include "Policko.h"


Policko::Policko(int cislo, char znak) {
    this->znakovaReprezentacia=znak;
    this->cislo=cislo;


}

Policko Policko::setCislo(int cislo) {
    this->cislo=cislo;
    return *this;
}

int Policko::getCislo() {
    return this->cislo;
}

char Policko::getZnak() {
    return this->znakovaReprezentacia;
}

Policko Policko::setZnak(char znak) {
    this->znakovaReprezentacia=znak;
    return *this;
}

Policko Policko::setSpawn(Hrac hrac) {
    this->hracSpawn=hrac.getId();

    return *this;
}
