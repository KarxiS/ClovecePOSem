#include "HraciaDoska.h"
#include <iostream>


HraciaDoska::HraciaDoska() : hraciePole(11, std::vector<Policko>(11)) {
    
}


void HraciaDoska::inicializaciaHraciehoPola() {
    
    for (int i = 0; i < 11; ++i) {
        for (int j = 0; j < 11; ++j) {
            hraciePole[i][j] = Policko();
        }
    }

    hraciePole[5][5] = Policko();
    this->vytvorCestu(10, 4, 5, 4);
    this->vytvorCestu(6, 0, 6, 4);
    this->vytvorCestu(6, 0, 3, 0);
    this->vytvorCestu(4, 0, 4, 4);
    this->vytvorCestu(4, 4, -1, 4);
    this->vytvorCestu(0, 4, 0, 7);
    this->vytvorCestu(0, 6, 5, 6);
    this->vytvorCestu(4, 6, 4, 11);
    this->vytvorCestu(4, 10, 6, 10);
    this->vytvorCestu(6, 10, 6, 5);
    this->vytvorCestu(6, 6, 11, 6);
    this->vytvorCestu(10, 6, 10, 4);
}


void HraciaDoska::pridajHraca(Hrac& hrac)
{
    for (Figurka& figurka : hrac.figurky) {
        char znak = figurka.getZnak();
        int x = figurka.getSuradnicaX();
        int y = figurka.getSuradnicaY();
        hraciePole[x][y] = znak;
    }
}

void HraciaDoska::vytvorCestu(int i, int j, int noveI, int noveJ) {
    
    if (i == noveI) {
        // Horizontálna cesta
        int krok = (noveJ > j) ? 1 : -1;
        for (int jj = j; jj != noveJ; jj += krok) {
            hraciePole[i][jj] = Policko().setZnak('-');
        }
    }
    else if (j == noveJ) {
        // Vertikálna cesta
        int krok = (noveI > i) ? 1 : -1;
        for (int ii = i; ii != noveI; ii += krok) {
            hraciePole[ii][j] = Policko().setZnak('-');
        }
    }
}

void HraciaDoska::zobrazHraciePole() {
    for (int i = 0; i < 11; ++i) {
        for (int j = 0; j < 11; ++j) {
            std::cout << hraciePole[i][j].getZnak() << " ";
        }
        std::cout << std::endl;
    }
}