#include "Figurka.h"

Figurka::Figurka(char parZnak, int x, int y)
{
	this->znak = parZnak;
	this->suradnicaX = x;
	this->suradnicaY = y;
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
