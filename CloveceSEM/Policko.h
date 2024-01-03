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
    char hracDomcekVystup=0;
public:
    int getHracDomcekVystup() const;

private:
    bool hore=false;
    bool dole = false;
    bool doprava = false;
    bool dolava = false;
    Policko* dalsie;
    Figurka* aktualnaFigurka;
    Policko* domcek;
public:
    Policko *getDomcek() const;

    void setDomcek(Policko *domcek);

public:
    Policko *getDalsie() const;

public:
    Policko(int cislo=-1, char znak=' ');
    char getZnak();
    Policko& setZnak(char znak);
    int getCislo();
    Policko& setCislo(int cislo);
    Policko& setSpawn(char hrac);
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
