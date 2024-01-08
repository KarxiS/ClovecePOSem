#pragma once
#include <vector>
#include "HraciaDoska.h"
#include "Hrac.h"

class Hra {
private:
    HraciaDoska hraciaDoska;
    Kocka kocka;
    int aktualnyHrac;
public:
    bool jeKoniec;
    std::vector<Hrac> hraci;
public:

    Hra();
    void zapisHraca(Hrac& hrac);
    void zacniHru();
    void spravTah(int hrac, int cisloFigurky, int oKolko);

    std::string ukazVysledok();



    void odpisHraca(int playerId);
    char getVolnePlayerID();
};

