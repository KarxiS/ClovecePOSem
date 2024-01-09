#pragma once
#include <vector>
#include "HraciaDoska.h"
#include "Hrac.h"

class Hra {
private:
    std::vector<Hrac> hraci;
    HraciaDoska hraciaDoska;
    Kocka kocka;
    int aktualnyHrac;

public:
    Hra();
    void zapisHraca(Hrac& hrac);
    void zacniHru();
    void spravTah(int hrac, int cisloFigurky, int oKolko);
    bool jeHracVitaz(Hrac hrac);
    std::string ukazVysledok();
    void odpisHraca(int playerId);
    char getVolnePlayerID();
};

