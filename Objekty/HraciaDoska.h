#pragma once
#include <string>
#include <vector>
#include "Figurka.h"
#include "Hrac.h"

class HraciaDoska {
private:

    std::vector<std::vector<char>> hraciePole;

public:
    HraciaDoska();

    void inicializaciaHraciehoPola();
    void pridajHraca(Hrac& hrac);
    void vytvorCestu(int i, int j, int noveI, int noveJ);
    void zobrazHraciePole();             
};

