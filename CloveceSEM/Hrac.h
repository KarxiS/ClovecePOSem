#pragma once
#include <string>
#include <vector>
#include "Kocka.h"
#include "Policko.h"

class Hrac {
private:
    std::string meno;
    char id;
    Policko vybrataFigurka;
public:
    std::vector<Policko> figurky;
    bool jeSkonceny;

public:
    Hrac(std::string paMeno, char paId);
    Hrac() = default;

    void nastavFigurky();
    int hodKockou(Kocka kocka);
    bool vyberFigurku();
    Policko& getVybrataFigurka();
    void vypisInfo();
    int getId();
};

