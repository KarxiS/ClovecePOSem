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
    this->setXY(this->spawnX,this->spawnY);
    return *this;
}

void Figurka::posunSa(int oKolko) {
    for (int i = 0; i < oKolko; ++i) {

        if(aktualnePolicko!= nullptr){
            Policko* dalsie =aktualnePolicko->getDalsie();
            aktualnePolicko->setFigurka(nullptr);
            aktualnePolicko=dalsie;
            aktualnePolicko->setFigurka(this);
        }



    }
}
