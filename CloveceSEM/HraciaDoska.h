#pragma once
#include <string>
#include <vector>
#include "Figurka.h"
#include "Hrac.h"
#include "Policko.h"

class HraciaDoska {
private:
    std::vector<std::vector<Policko>> hraciePole;
    int pocitadlo_cesta = 10;

public:
    HraciaDoska();
    void inicializaciaHraciehoPola();
    void pridajHraca(Hrac& hrac);
    void vytvorCestu(int i, int j, int noveI, int noveJ);
    void vytvorDomceky(int xStart, int yStart, int xEnd, int yEnd, int hrac);
    Policko& getSpawn(char hrac);
    void nastavSpawnPoint();
    void zobrazHraciePole();
    void zobrazHraciePoleDebugCesty();
    Policko *getPolicko(int x, int y);
    std::string getHraciePole();
};

