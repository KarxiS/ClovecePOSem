#include "Hrac.h"
#include <iostream>

Hrac::Hrac(std::string paMeno, char paId)
{
    this->meno = paMeno;
    this->id = paId;

    this->nastavFigurky();
}

void Hrac::nastavFigurky()
{

    this->figurky.clear();

    if (this->id == '0') {
        this->figurky.push_back(Figurka(id, 10, 0).setPoradie(1));
        this->figurky.push_back(Figurka(id, 10, 1).setPoradie(2));
        this->figurky.push_back(Figurka(id, 9, 0).setPoradie(3));
        this->figurky.push_back(Figurka(id, 9, 1).setPoradie(4));
    }
    else if (this->id == '1') {
        this->figurky.push_back(Figurka(id, 0, 0).setPoradie(1));
        this->figurky.push_back(Figurka(id, 0, 1).setPoradie(2));
        this->figurky.push_back(Figurka(id, 1, 0).setPoradie(3));
        this->figurky.push_back(Figurka(id, 1, 1).setPoradie(4));
    }
    else if (this->id == '2') {
        this->figurky.push_back(Figurka(id, 0, 9).setPoradie(1));
        this->figurky.push_back(Figurka(id, 0, 10).setPoradie(2));
        this->figurky.push_back(Figurka(id, 1, 9).setPoradie(3));
        this->figurky.push_back(Figurka(id, 1, 10).setPoradie(4));
    }
    else if (this->id == '3') {
        this->figurky.push_back(Figurka(id, 9, 9).setPoradie(1));
        this->figurky.push_back(Figurka(id, 9, 10).setPoradie(2));
        this->figurky.push_back(Figurka(id, 10, 9).setPoradie(3));
        this->figurky.push_back(Figurka(id, 10, 10).setPoradie(4));
    }
}

void Hrac::vypisInfo()
{
    std::cout << "meno hraca: " << this->meno << "id hraca: " << this->id <<std::endl;
}

char Hrac::getId() {
    return this->id;
}

std::string Hrac::getMeno() {
    return this->meno;
}

bool Hrac::maFigurkyCiel(){

    //prejdenie hracovych figurok, ci su v cieli
    for (Figurka figurka : this->figurky) {

        if(figurka.getAktualnePolicko()== nullptr){
            return false;
        }
        Policko* policko = figurka.getAktualnePolicko();
        if(!policko->isEndDomcek()){
            return false;
        }
    }
    return true;
}
