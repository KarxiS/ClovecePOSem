//
// Created by 2karo on 31. 12. 2023.
//

#include "Policko.h"


Policko::Policko(int cislo, char znak, int x, int y) {
    this->cislo=cislo;
    this->znakovaReprezentacia=znak;
    this->suradnicaX=x;
    this->suradnicaY=y;
}

Policko& Policko::setCislo(int cislo) {
    this->cislo=cislo;
    return *this;
}

int Policko::getCislo() {
    return this->cislo;
}

char Policko::getZnak() {
    return this->znakovaReprezentacia;
}

Policko& Policko::setZnak(char znak) {
    if(znak=='X'){
        this->jeDomcekEnd=true;
    }else{
        this->jeDomcekEnd=false;
    }

    this->znakovaReprezentacia=znak;
    return *this;
}

Policko& Policko::setSpawn(int hrac) {

    this->hracDomcekVystup=hrac;
    this->jeDomcekSpawn=true;
    return *this;
}

Policko& Policko::odomkniSmer(int smerX, int smerY) {
    if(smerX==1){
        this->doprava=true;
    }
    if(smerX==-1){
        this->dolava=true;
    }
    if(smerY==1){
        this->dole=true;
    }
    if(smerY==-1){
        this->hore=true;
    }
    return *this;
}

int Policko::getSuradnicaX() {
    return this->suradnicaX;
}

int Policko::getSuradnicaY() {
    return this->suradnicaY;
}
