#pragma once
#include <string>
#include <vector>
#include "Kocka.h"
#include "Policko.h"

class Hrac {
private:
    std::string meno;
    char id;
public:
    std::vector<Policko> figurky;
    bool jeSkonceny;

public:
    Hrac(std::string paMeno, char paId);
    Hrac() = default;

    void nastavFigurky();
    int hodKockou(Kocka kocka);                                
    void spravPosun(Policko zvolenaFigurka, int pocetPoli);
    void vypisInfo();
    int getId();
};

