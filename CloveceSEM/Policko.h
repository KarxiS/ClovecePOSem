//
// Created by 2karo on 31. 12. 2023.
//

#ifndef CLOVECEPOSEM_POLICKO_H
#define CLOVECEPOSEM_POLICKO_H

class Policko {
private:
    char znakovaReprezentacia;
    int cislo;
    int suradnicaX;
    int suradnicaY;
    int hracDomcekVystup=0;
public:
    bool jeDomcekEnd=false;
    bool jeDomcekSpawn=false;
    bool vHre=false;

    bool hore=false;
    bool dole = false;
    bool doprava = false;
    bool dolava = false;
public:
    Policko(int cislo=-1, char znak=' ', int x=0, int y=0);
    char getZnak();
    Policko& setZnak(char znak);
    int getCislo();
    Policko& setCislo(int cislo);
    int getSuradnicaX();
    int getSuradnicaY();
    Policko& setSpawn(int hrac);
    Policko& odomkniSmer(int smerX, int smerY);
};


#endif //CLOVECEPOSEM_POLICKO_H
