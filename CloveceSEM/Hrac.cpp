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
    switch (this->id) {
        case '1':
            this->figurky.push_back(Policko(-1, this->id, 10, 0));
            this->figurky.push_back(Policko(-1, this->id, 10, 1));
            this->figurky.push_back(Policko(-1, this->id, 9, 0));
            this->figurky.push_back(Policko(-1, this->id, 9, 1));
            break;

        case '2':
            this->figurky.push_back(Policko(-1, this->id, 0, 0));
            this->figurky.push_back(Policko(-1, this->id, 0, 1));
            this->figurky.push_back(Policko(-1, this->id, 1, 0));
            this->figurky.push_back(Policko(-1, this->id, 1, 1));
            break;

        case '3':
            this->figurky.push_back(Policko(-1, this->id, 0, 9));
            this->figurky.push_back(Policko(-1, this->id, 0, 10));
            this->figurky.push_back(Policko(-1, this->id, 1, 9));
            this->figurky.push_back(Policko(-1, this->id, 1, 10));
            break;

        case '4':
            this->figurky.push_back(Policko(-1, this->id, 9, 9));
            this->figurky.push_back(Policko(-1, this->id, 9, 10));
            this->figurky.push_back(Policko(-1, this->id, 10, 9));
            this->figurky.push_back(Policko(-1, this->id, 10, 10));
            break;

        default:
            std::cout << "Vyskytla sa chyba pri nastatovani figurok.\n";
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
