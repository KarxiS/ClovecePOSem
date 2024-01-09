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
    Policko* aktualnePolicko;
    Policko *startovaciePolicko;
    int poradie;

private:
    void setSuradnicaX(int x);
    void setSuradnicaY(int y);

public:
    Figurka(char parZnak, int x, int y);
    char getZnak();
    int getSuradnicaX();
    int getSuradnicaY();
    Policko* getAktualnePolicko() const;
    Figurka& setAktualnePolicko(Policko *aktualnePolickoL);
    Policko *getStartovaciePolicko() const;
    void setStartovaciePolicko(Policko* policko);
    int getPoradie() const;
    Figurka& setPoradie(int poradie);

    Figurka vyhodFigurku();
    void posunSa(int oKolko);
    Figurka& setXY(int x, int y);

};

