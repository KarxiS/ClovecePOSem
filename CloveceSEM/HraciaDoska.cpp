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
    this->vytvorCestu(4, 10, 4, 6);
    this->vytvorCestu(4, 6, 0, 6);
    this->vytvorCestu(0, 6, 0, 4);
    this->vytvorCestu(0, 4, 4, 4);
    this->vytvorCestu(4, 4, 4, 0);
    this->vytvorCestu(4, 0, 6, 0);
    this->vytvorCestu(6, 0, 6, 4);
    this->vytvorCestu(6, 4, 10, 4);
    this->vytvorCestu(10, 4, 10, 6);
    this->vytvorCestu(10, 6, 6, 6);
    this->vytvorCestu(6, 6, 6, 10);
    this->vytvorCestu(6, 10, 4, 10);
    this->vytvorDomceky(1,5,4,5,'2');
    this->vytvorDomceky(9,5,6,5,'4');
    this->vytvorDomceky(5,1,5,4,'1');
    this->vytvorDomceky(5,9,5,6,'3');
    this->nastavSpawnPoint();
}

void HraciaDoska::nastavSpawnPoint()
{
    this->hraciePole[10][4].setDomcekVstup('3').setZnak('S').setJeDomcekSpawn(true);
    this->hraciePole[4][0].setDomcekVstup('2').setZnak('S').setJeDomcekSpawn(true);
    this->hraciePole[0][6].setDomcekVstup('1').setZnak('S').setJeDomcekSpawn(true);
    this->hraciePole[6][10].setDomcekVstup('4').setZnak('S').setJeDomcekSpawn(true);
}

Policko* HraciaDoska::getPolicko(int x,int y) {
    return &this->hraciePole[y][x];
}
void HraciaDoska::pridajHraca(Hrac& hrac)
{
    for (Figurka& figurka : hrac.figurky) {
        char znak = figurka.getZnak();
        int x = figurka.getSuradnicaX();
        int y = figurka.getSuradnicaY();
        figurka.setAktualnePolicko(&hraciePole[y].at(x));
        figurka.setStartovaciePolicko(&hraciePole[y].at(x));
    }
}

void HraciaDoska::vytvorCestu(int i, int j, int noveI, int noveJ) {

    if (i == noveI) {
        // Vertikálna cesta
        int krok = (noveJ > j) ? 1 : -1;
        for (int jj = j; jj != noveJ; jj += krok) {
            hraciePole[jj][i] = Policko().setZnak('-').setCislo(pocitadlo_cesta++).odomkniSmer(0,krok);
            hraciePole[jj][i].setDalsie(&hraciePole[jj+krok][i]);
            if(hraciePole[jj][i].getCislo()==19) {
                hraciePole[jj][i].odomkniSmer(1,0);
            }

            if(hraciePole[jj][i].getCislo()==39) {
                hraciePole[jj][i].odomkniSmer(-1,0);
            }

        }
    }
    else if (j == noveJ) {
        // Horizontálna cesta
        int krok = (noveI > i) ? 1 : -1;
        for (int ii = i; ii != noveI; ii += krok) {
            hraciePole[j][ii] = Policko().setZnak('-').setCislo(pocitadlo_cesta++).odomkniSmer(krok,0);
            hraciePole[j][ii].setDalsie(&hraciePole[j][ii+krok]);
            if(hraciePole[j][ii].getCislo()==49) {
                hraciePole[j][ii].odomkniSmer(0,-1);
            }

            if(hraciePole[j][ii].getCislo()==29) {
                hraciePole[j][ii].odomkniSmer(0,1);
            }




        }
    }
}
void HraciaDoska::vytvorDomceky(int xStart, int yStart, int xEnd, int yEnd, int hrac) {

    int smerX = (xStart < xEnd) ? 1 : -1;
    int smerY = (yStart < yEnd) ? 1 : -1;
    int pocitadloDomcek = 0;
    if(xStart == xEnd){

        // Vertikálna cesta

        for (int y = yStart; y != yEnd + smerY; y += smerY) {
            hraciePole[y][xStart] = Policko().setZnak('X').setCislo(pocitadloDomcek++).odomkniSmer(0,
                                                                                                   smerY).setDomcekVstup(
                    hrac);

            hraciePole[y][xStart].setDalsie(&hraciePole[y+smerY][xStart]);

        }

        hraciePole[yEnd ][xStart].setDalsie(nullptr);



        hraciePole[yStart-smerY][xStart].setDomcek(&hraciePole[yStart][xStart]);
    }
    if(yStart == yEnd){
        // Horizontalna cesta

        for (int x = xStart; x != xEnd + smerX; x += smerX) {
            hraciePole[yStart][x] = Policko().setZnak('X').setCislo(pocitadloDomcek++).odomkniSmer(smerX,
                                                                                                   0).setDomcekVstup(
                    hrac);


            hraciePole[yStart][x].setDalsie(&hraciePole[yStart][x+smerX]);

        }

        hraciePole[yStart ][xEnd].setDalsie(nullptr);

        hraciePole[yStart][xStart-smerX].setDomcek(&hraciePole[yStart][xStart]);
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


std::string HraciaDoska::getHraciePole() {
    std::string result;
    for (int i = 0; i < 11; ++i) {
        for (int j = 0; j < 11; ++j) {
            result += hraciePole[i][j].getZnak();
            result += " | ";
        }
        result += "\n";
    }
    return result;
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

Policko &HraciaDoska::getSpawn(char hrac) {
    for (int i = 0; i < hraciePole.size(); i++) {
        for (int j = 0; j < hraciePole[i].size(); j++) {
            if (hraciePole[i][j].isJeDomcekSpawn() &&hraciePole[i][j].getHracDomcekVystup() == hrac ) {
                return hraciePole[i][j];
            }
        }

    }
}
