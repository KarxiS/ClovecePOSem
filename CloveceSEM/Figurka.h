#pragma once

#include "Policko.h"
class Policko;
class Figurka {
private:
    char znak;
    int suradnicaX;
    int suradnicaY;
    int spawnX;
    int spawnY;
    void setSuradnicaX(int x);
    void setSuradnicaY(int y);
    Policko* aktualnePolicko;
public:
    Figurka(char parZnak, int x, int y);
    char getZnak();
    int getSuradnicaX();
    int getSuradnicaY();
    Figurka& setXY(int x, int y);
    Figurka vyhodFigurku();
    void posunSa(int oKolko);


    Policko *getAktualnePolicko() const;

    Figurka& setAktualnePolicko(Policko *aktualnePolickoL);


    Policko *startovaciePolicko;

    void setStartovaciePolicko(Policko* policko);
};

