#include "Hra.h"
#include <iostream>

Hra::Hra()
{
    this->aktualnyHrac = 0;
    this->jeKoniec = false;
}

void Hra::zapisHraca(Hrac& hrac)
{
    if (hraci.size() < 4) {
        hraci.push_back(hrac);
    }
    else {
        std::cout << "V hre su zapojeni len prvi 4 hraci." << std::endl;
    }

}

void Hra::zacniHru()
{
    hraciaDoska.inicializaciaHraciehoPola();
    for (int i = 0; i < hraci.size(); ++i) {
        hraciaDoska.pridajHraca(hraci.at(i));
    };
    hraciaDoska.zobrazHraciePole();

    hraciaDoska.zobrazHraciePoleDebugCesty();
    /*
    do {
        this->spravTah();
        hraciaDoska.zobrazHraciePole();
    } while (!this->jeKoniec);
    */

}

void Hra::spravTah(int hrac, int cisloFigurky, int oKolko)
{
    Hrac& hracNaTahu = hraci.at(hrac);
    //vykonanie akcie hraca

    Figurka& figurka = hracNaTahu.figurky[cisloFigurky-1];

    if(figurka.getStartovaciePolicko()==figurka.getAktualnePolicko()&& oKolko==6){
        Policko& policko = hraciaDoska.getSpawn(hracNaTahu.getId());
        figurka.setAktualnePolicko(&policko);
        return;
    }
    //hracNaTahu.spravPosun(hracNaTahu.figurky.at(rand()%4), padnuteCislo);
    Policko& policko = hraciaDoska.getSpawn(hracNaTahu.getId());
    figurka.posunSa(oKolko);
    //aktualizacia hraca pre dalsie kolo
    this->aktualnyHrac = (this->aktualnyHrac + 1) % hraci.size();
}

void Hra::ukazVysledok()
{
    hraciaDoska.zobrazHraciePole();
}

