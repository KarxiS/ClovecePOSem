#pragma once
#include <string>
#include <vector>
#include "Figurka.h"
#include "Hrac.h"
#include "Policko.h"

class HraciaDoska {
private:


    std::vector<std::vector<Policko>> hraciePolePolicko;
    int pocitadlo_cesta = 10;
    std::vector<std::vector<Policko>> hraciePole;
public:
    HraciaDoska();

    void inicializaciaHraciehoPola();
    void pridajHraca(Hrac& hrac);
    void vytvorCestu(int i, int j, int noveI, int noveJ);
    void vytvorDomceky(int xStart, int yStart, int xEnd, int yEnd, int hrac);
    void zobrazHraciePole();
    void zobrazHraciePoleDebugCesty();

    void nastavSpawnPoint();

    Policko *getPolicko(int x, int y);
};

