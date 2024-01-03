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

public:
    HraciaDoska();
    std::vector<std::vector<Policko>> hraciePole;
    void inicializaciaHraciehoPola();
    void pridajHraca(Hrac& hrac);
    void vytvorCestu(int i, int j, int noveI, int noveJ);
    void vytvorDomceky(int xStart, int yStart, int xEnd, int yEnd);
    void zobrazHraciePole();
    void zobrazHraciePoleDebugCesty();

    void nastavSpawnPoint();

    Policko *getPolicko(int x, int y);
};
