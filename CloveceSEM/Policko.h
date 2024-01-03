//
// Created by 2karo on 31. 12. 2023.
//

#ifndef CLOVECEPOSEM_POLICKO_H
#define CLOVECEPOSEM_POLICKO_H


#include "Figurka.h"

class Figurka;

class Policko {
private:
    char znakovaReprezentacia=' ';
    int cislo = -1;
    bool jeDomcekEnd=false;
    bool jeDomcekSpawn=false;
    int hracDomcekVystup=0;
    bool hore=false;
    bool dole = false;
    bool doprava = false;
    bool dolava = false;
    Policko* dalsie;
    Figurka* aktualnaFigurka;
public:
    Policko *getDalsie() const;

public:
    Policko(int cislo=-1, char znak=' ');
    char getZnak();
    Policko& setZnak(char znak);
    int getCislo();
    Policko& setCislo(int cislo);
    Policko& setSpawn(int hrac);
    Policko& odomkniSmer(int smerX, int smerY);
    bool isSpawnDomcek();
    bool isHore();
    bool isDole();
    bool isDolava();
    bool isDoprava();

    Figurka *getAktualnaFigurka() const;

    void setAktualnaFigurka(Figurka *aktualnaFigurka);

    bool isEndDomcek();

    void setDalsie(Policko* dalsieLocal);


    Policko &setFigurka(Figurka* figurka);
};


#endif //CLOVECEPOSEM_POLICKO_H
