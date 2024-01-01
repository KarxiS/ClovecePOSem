//
// Created by 2karo on 31. 12. 2023.
//

#include "Policko.h"


Policko::Policko(int cislo, char znak) {
    this->znakovaReprezentacia=znak;
    this->cislo=cislo;


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

bool Policko::isSpawnDomcek(){
    return this->jeDomcekSpawn;
}

bool Policko::isEndDomcek(){
    return this->jeDomcekEnd;
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

bool Policko::isHore() {
    return this->hore;
}

bool Policko::isDole() {
    return this->dole;
}

bool Policko::isDolava() {
    return this->dolava;
}

bool Policko::isDoprava() {
    return this->doprava;
}
