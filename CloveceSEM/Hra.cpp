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
    Policko& policko = hraciaDoska.getSpawn(hracNaTahu.getId());
    Figurka& figurka = hracNaTahu.figurky[0];
    figurka.setAktualnePolicko(&policko);


    Hrac& hracNaTahu2 = hraci.at(1);
    Policko& policko2 = hraciaDoska.getSpawn(hracNaTahu2.getId());
    Figurka& figurka2 = hracNaTahu2.figurky[0];
    figurka2.setAktualnePolicko(&policko2);

    figurka2.posunSa(10);
    figurka2.posunSa(40);
    ;



    hraciaDoska.zobrazHraciePole();


    hraciaDoska.zobrazHraciePole();
    //aktualizacia hraca pre dalsie kolo
    this->aktualnyHrac = (this->aktualnyHrac + 1) % hraci.size();
}

void Hra::ukazVysledok()
{
    hraciaDoska.zobrazHraciePole();
}

