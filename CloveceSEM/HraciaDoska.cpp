#include "HraciaDoska.h"
#include <iostream>
#include <iomanip>


HraciaDoska::HraciaDoska() : hraciePole(11, std::vector<Policko>(11)) {
    
}


void HraciaDoska::inicializaciaHraciehoPola() {
    
    for (int i = 0; i < 11; ++i) {
        for (int j = 0; j < 11; ++j) {
            hraciePole[i][j] = Policko();
        }
    }

    hraciePole[5][5] = Policko();
    this->vytvorCestu(4, 10, 4, 5);
    this->vytvorCestu(3, 6, 0, 6);
    this->vytvorCestu(0, 6, 0, 3);
    this->vytvorCestu(1, 4, 4, 4);
    this->vytvorCestu(4, 4, 4, -1);
    this->vytvorCestu(4, 0, 7, 0);
    this->vytvorCestu(6, 0, 6, 5);
    this->vytvorCestu(6, 4, 11, 4);
    this->vytvorCestu(10, 4, 10, 6);
    this->vytvorCestu(10, 6, 5, 6);
    this->vytvorCestu(6, 6, 6, 11);
    this->vytvorCestu(6, 10, 4, 10);
    this->vytvorDomceky(1,5,4,5);
    this->vytvorDomceky(9,5,6,5);
    this->vytvorDomceky(5,1,5,4);
    this->vytvorDomceky(5,9,5,6);
    this->nastavSpawnPoint();
}

void HraciaDoska::nastavSpawnPoint()
{
    this->hraciePole[4][10].setSpawn(1);
    this->hraciePole[0][4].setSpawn(2);
    this->hraciePole[6][0].setSpawn(3);
    this->hraciePole[10][6].setSpawn(4);
}
void HraciaDoska::pridajHraca(Hrac& hrac)
{
    for (Figurka& figurka : hrac.figurky) {
        char znak = figurka.getZnak();
        int x = figurka.getSuradnicaX();
        int y = figurka.getSuradnicaY();
        hraciePole[x][y].setZnak(znak);
    }
}

void HraciaDoska::vytvorCestu(int i, int j, int noveI, int noveJ) {
    
    if (i == noveI) {
        // Vertikálna cesta
        int krok = (noveJ > j) ? 1 : -1;
        for (int jj = j; jj != noveJ; jj += krok) {
            hraciePole[jj][i] = Policko().setZnak('-').setCislo(pocitadlo_cesta++);
        }
    }
    else if (j == noveJ) {
        // Horizontálna cesta
        int krok = (noveI > i) ? 1 : -1;
        for (int ii = i; ii != noveI; ii += krok) {
            hraciePole[j][ii] = Policko().setZnak('-').setCislo(pocitadlo_cesta++);
        }
    }
}
void HraciaDoska::vytvorDomceky(int xStart, int yStart, int xEnd, int yEnd) {

    int smerX = (xStart < xEnd) ? 1 : -1;
    int smerY = (yStart < yEnd) ? 1 : -1;
    int pocitadloDomcek = 0;
    if(xStart == xEnd){
        // Vertikálna cesta
        for (int y = yStart; y != yEnd + smerY; y += smerY) {
            hraciePole[y][xStart] = Policko().setZnak('X').setCislo(pocitadloDomcek++);
        }
    }
    if(yStart == yEnd){
        // Horizontalna cesta
        for (int x = xStart; x != xEnd + smerX; x += smerX) {
            hraciePole[yStart][x] = Policko().setZnak('X').setCislo(pocitadloDomcek++);
        }
    }
}

void HraciaDoska::zobrazHraciePole() {
    std::cout << "*********VypisHry**********"<<std::endl;
    for (int i = 0; i < 11; ++i) {
        for (int zvacsenieLoop = 0; zvacsenieLoop < 1; ++zvacsenieLoop) {
            for (int j = 0; j < 11; ++j) {

                std::cout <<  std::setw(2)<<hraciePole[i][j].getZnak()  << "\033[31m | \033[0m";
            }
            std::cout << std::endl;
        }


    }
}


void HraciaDoska::zobrazHraciePoleDebugCesty() {
    std::cout << "*********Debug**********"<<std::endl;
    for (int i = 0; i < 11; ++i) {
        for (int zvacsenieLoop = 0; zvacsenieLoop < 1; ++zvacsenieLoop) {
            for (int j = 0; j < 11; ++j) {

                std::cout <<  std::setw(2)<<hraciePole[i][j].getCislo()  << "\033[31m | \033[0m";
            }
            std::cout << std::endl;
        }


    }
}
