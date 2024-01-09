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
    char hracDomcekVystup='0';
    bool hore=false;
    bool dole = false;
    bool doprava = false;
    bool dolava = false;
    Policko* dalsie;
    Figurka* aktualnaFigurka;
    Policko* domcek;

public:
    Policko(int cislo=-1, char znak=' ');
    char getZnak();
    Policko& setZnak(char znak);
    int getCislo();
    Policko& setCislo(int cislo);
    Policko *getDomcek() const;
    void setDomcek(Policko *domcek);
    Figurka *getAktualnaFigurka() const;
    void setAktualnaFigurka(Figurka *aktualnaFigurka);
    Policko &setFigurka(Figurka* figurka);

    bool isJeDomcekSpawn() const;
    void setJeDomcekSpawn(bool jeDomcekSpawn);
    bool isEndDomcek();

    char getHracDomcekVystup() const;

    Policko *getDalsie() const;
    void setDalsie(Policko* dalsieLocal);

    Policko& setDomcekVstup(char hrac);
    Policko& odomkniSmer(int smerX, int smerY);
    bool isHore();
    bool isDole();
    bool isDolava();
    bool isDoprava();
};


#endif //CLOVECEPOSEM_POLICKO_H
