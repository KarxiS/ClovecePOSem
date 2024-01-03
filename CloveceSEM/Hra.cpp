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

void Hra::spravTah()
{
    Hrac& hracNaTahu = hraci.at(0);
    //vykonanie akcie hraca
    int padnuteCislo = hracNaTahu.hodKockou(this->kocka);
    //hracNaTahu.spravPosun(hracNaTahu.figurky.at(rand()%4), padnuteCislo);
    Policko& policko = *hraciaDoska.getPolicko(1,4);
    Figurka& figurka = hracNaTahu.figurky[0];
    figurka.setAktualnePolicko(&policko);
    Hrac& hracNaTahu2 = hraci.at(1);
    Policko& policko2 = *hraciaDoska.getPolicko(4,4);
    Figurka& figurka2 = hracNaTahu2.figurky[1];
    figurka2.setAktualnePolicko(&policko2);

    figurka.posunSa(3);
    hraciaDoska.zobrazHraciePole();


    hraciaDoska.zobrazHraciePole();
    //aktualizacia hraca pre dalsie kolo
    this->aktualnyHrac = (this->aktualnyHrac + 1) % hraci.size();
}

void Hra::ukazVysledok()
{
    hraciaDoska.zobrazHraciePole();
}

