#include "Figurka.h"

Figurka::Figurka(char parZnak, int x, int y)
{
    this->znak = parZnak;
    this->suradnicaX = x;
    this->suradnicaY = y;
    this->spawnX=x;
    this->spawnY=y;
    this->aktualnePolicko= nullptr;
}

char Figurka::getZnak()
{
    return this->znak;
}

int Figurka::getSuradnicaX()
{
    return this->suradnicaX;
}

Policko *Figurka::getAktualnePolicko() const {
    return aktualnePolicko;
}

Figurka& Figurka::setAktualnePolicko(Policko* aktualnePolickoL) {
    if(this->aktualnePolicko!= nullptr){
        this->aktualnePolicko->setFigurka(nullptr);
    }

    if(aktualnePolickoL->getAktualnaFigurka()!= nullptr){
        aktualnePolickoL->getAktualnaFigurka()->vyhodFigurku();
    }

    this->aktualnePolicko = aktualnePolickoL;
    aktualnePolickoL->setAktualnaFigurka(this);
    return *this;
}

int Figurka::getSuradnicaY()
{
    return this->suradnicaY;
}

void Figurka::setSuradnicaX(int x) {
    this->suradnicaX=x;
}

Figurka& Figurka::setXY(int x, int y) {

    this->setSuradnicaX(x);
    this->setSuradnicaY(y);
    return *this;
}

void Figurka::setSuradnicaY(int y) {
    this->suradnicaY=y;
}

Figurka Figurka::vyhodFigurku() {
    // Set the current square to null
    this->aktualnePolicko->setFigurka(nullptr);
    this->aktualnePolicko = nullptr;

    // Set the figurine's current square to its starting square
    this->aktualnePolicko = this->startovaciePolicko;
    this->aktualnePolicko->setFigurka(this);
    return *this;
}

void Figurka::posunSa(int oKolko) {
    Policko* localPolicko = this->aktualnePolicko;
    Policko* finalPolicko = this->aktualnePolicko;

    for (int i = 0; i < oKolko; ++i) {

        if (finalPolicko == nullptr || finalPolicko->getDalsie() == nullptr) {
            return;
        }


        else if (finalPolicko->getDomcek() != nullptr && finalPolicko->getDomcek()->getHracDomcekVystup() == this->getZnak()) {
            this->aktualnePolicko = finalPolicko->getDomcek();
            finalPolicko = finalPolicko->getDomcek();
            this->aktualnePolicko->setFigurka(this);
            localPolicko->setFigurka(nullptr);
            continue;

        }
        finalPolicko=finalPolicko->getDalsie();


    }
    //ak final policko je niekto, pojdeme naspat na local

    if(finalPolicko->getAktualnaFigurka()!= nullptr &&finalPolicko->getAktualnaFigurka()->getZnak()!=this->getZnak()) {
        finalPolicko->getAktualnaFigurka()->vyhodFigurku();
    }

    if(finalPolicko->getAktualnaFigurka()!= nullptr &&finalPolicko->getAktualnaFigurka()->getZnak()==this->getZnak()) {
        return;
    }


    aktualnePolicko->setFigurka(nullptr);
    aktualnePolicko = finalPolicko;
    aktualnePolicko->setFigurka(this);



}

void Figurka::setStartovaciePolicko(Policko* policko) {
    this->startovaciePolicko=policko;
}
