#include "Figurka.h"

Figurka::Figurka(char parZnak, int x, int y)
{
	this->znak = parZnak;
	this->suradnicaX = x;
	this->suradnicaY = y;
    this->spawnX=x;
    this->spawnY=y;
}

char Figurka::getZnak()
{
	return this->znak;
}

int Figurka::getSuradnicaX()
{
	return this->suradnicaX;
}

int Figurka::getSuradnicaY()
{
	return this->suradnicaY;
}

void Figurka::setSuradnicaX(int x) {
    this->suradnicaX=x;
}

Figurka Figurka::setXY(int x, int y) {

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
