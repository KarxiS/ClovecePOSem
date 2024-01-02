#include "Hrac.h"
#include <iostream>

Hrac::Hrac(std::string paMeno, int paId)
{
	this->meno = paMeno;
	this->id = paId;
	this->jeSkonceny = false;
    this->nastavFigurky();
}

void Hrac::nastavFigurky()
{
    this->figurky.clear();
    char pom=(char)this->id;
    switch (pom) {
        case '1':
            this->figurky.push_back(Policko(-1, pom, 10, 0));
            this->figurky.push_back(Policko(-1, pom, 10, 1));
            this->figurky.push_back(Policko(-1, pom, 9, 0));
            this->figurky.push_back(Policko(-1, pom, 9, 1));
            break;

        case '2':
            this->figurky.push_back(Policko(-1, pom, 0, 0));
            this->figurky.push_back(Policko(-1, pom, 0, 1));
            this->figurky.push_back(Policko(-1, pom, 1, 0));
            this->figurky.push_back(Policko(-1, pom, 1, 1));
            break;

        case '3':
            this->figurky.push_back(Policko(-1, pom, 0, 9));
            this->figurky.push_back(Policko(-1, pom, 0, 10));
            this->figurky.push_back(Policko(-1, pom, 1, 9));
            this->figurky.push_back(Policko(-1, pom, 1, 10));
            break;

        case '4':
            this->figurky.push_back(Policko(-1, pom, 9, 9));
            this->figurky.push_back(Policko(-1, pom, 9, 10));
            this->figurky.push_back(Policko(-1, pom, 10, 9));
            this->figurky.push_back(Policko(-1, pom, 10, 10));
            break;

        default:
            std::cout << "Vyskytla sa chyba pri nastatovani figurok.";
            break;
    }
}

int Hrac::hodKockou(Kocka kocka)
{
    return kocka.hodKockou();
}

void Hrac::spravPosun(Policko zvolenaFigurka, int pocetPoli)
{

}

void Hrac::vypisInfo()
{
    std::cout << "Meno hraca: " << this->meno << ", id hraca: " << this->id << std::endl;
}

int Hrac::getId() {
    return this->id;
}
