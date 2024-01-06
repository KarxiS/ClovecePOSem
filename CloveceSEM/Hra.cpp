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
    //zobrazenie hracieho pola, tesne pred zacatim hry
    hraciaDoska.zobrazHraciePole();

    int hrac;
    int cisloFigurky;
    int oKolko;
    Hrac hracPoVykonaniTahu;

    int cisloKola=1;
    do {
        std::cout << std::endl;
        std::cout << "--------------------------Kolo " << cisloKola << " --------------------------\n";

        //v metode spravTah sa aktualizuje dalsi hrac
        hrac = this->aktualnyHrac;
        oKolko = this->kocka.hodKockou();
        std::cout << this->hraci.at(hrac).getMeno() << "(" << this->hraci.at(hrac).getId() << ")" <<", ktoru figurku(1-4) chcete posunut o " << oKolko << " :" << std::endl;
        std::cin >> cisloFigurky;
        if(cisloFigurky < 1 || cisloFigurky > 4){
            std::cout << "Zadali ste nespravne cislo! skuste znova";
            std::cin >> cisloFigurky;
        }

        //vykonanie tahu hracom na rade
        this->spravTah(hrac, cisloFigurky, oKolko);
        hraciaDoska.zobrazHraciePole();
        hracPoVykonaniTahu = this->hraci.at((this->aktualnyHrac - 1 + hraci.size()) % hraci.size());

        cisloKola++;
    } while (!hracPoVykonaniTahu.maFigurkyCiel());

    this->jeKoniec= true;
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

    Policko& policko = hraciaDoska.getSpawn(hracNaTahu.getId());
    figurka.posunSa(oKolko);
    //aktualizacia hraca pre dalsie kolo
    this->aktualnyHrac = (this->aktualnyHrac + 1) % hraci.size();
}

std::string Hra::ukazVysledok()
{
    return hraciaDoska.getHraciePole();
}

