#pragma once
#include <string>
#include <vector>
#include "Figurka.h"
#include "Kocka.h"

class Hrac {
private:
    std::string meno;
    char id;
public:
    std::vector<Figurka> figurky;
    Hrac(std::string paMeno, char paId);
    Hrac() = default;

    std::string getMeno();
    char getId();
    void nastavFigurky();
    bool maFigurkyCiel();
    void vypisInfo();
};

