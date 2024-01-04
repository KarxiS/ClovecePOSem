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
    bool jeSkonceny;

public:
    Hrac(std::string paMeno, char paId);
    Hrac() = default;

    void nastavFigurky();
    int hodKockou(Kocka kocka);
    void spravPosun(Figurka zvolenaFigurka, int pocetPoli);
    void vypisInfo();
    char getId();
};

