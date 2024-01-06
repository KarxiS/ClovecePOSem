#include "Hrac.h"
#include <iostream>

Hrac::Hrac(std::string paMeno, char paId)
{
    this->meno = paMeno;
    this->id = paId;
    this->jeSkonceny = false;
    this->nastavFigurky();
}

void Hrac::nastavFigurky()
{

    this->figurky.clear();

    if (this->id == '1') {
        this->figurky.push_back(Figurka(id, 10, 0));
        this->figurky.push_back(Figurka(id, 10, 1));
        this->figurky.push_back(Figurka(id, 9, 0));
        this->figurky.push_back(Figurka(id, 9, 1));
    }
    else if (this->id == '2') {
        this->figurky.push_back(Figurka(id, 0, 0));
        this->figurky.push_back(Figurka(id, 0, 1));
        this->figurky.push_back(Figurka(id, 1, 0));
        this->figurky.push_back(Figurka(id, 1, 1));
    }
    else if (this->id == '3') {
        this->figurky.push_back(Figurka(id, 0, 9));
        this->figurky.push_back(Figurka(id, 0, 10));
        this->figurky.push_back(Figurka(id, 1, 9));
        this->figurky.push_back(Figurka(id, 1, 10));
    }
    else if (this->id == '4') {
        this->figurky.push_back(Figurka(id, 9, 9));
        this->figurky.push_back(Figurka(id, 9, 10));
        this->figurky.push_back(Figurka(id, 10, 9));
        this->figurky.push_back(Figurka(id, 10, 10));
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
