//
// Created by andre on 29. 12. 2023.
//

#ifndef CLOVECEPOSEM_HRACIADOSKA_H
#define CLOVECEPOSEM_HRACIADOSKA_H
#include <string>
#include <vector>
#include "Figurka.h"
#include "Hrac.h"

class HraciaDoska {
private:
    std::vector<Figurka> hraciePole;

public:
    HraciaDoska(){
        inicializaciaHraciehoPola();
    }

    void inicializaciaHraciehoPola();    //nastav hracie policka
    void zobrazHraciePole();             //zobrazenie pozicii figuriek hracov
};


#endif //CLOVECEPOSEM_HRACIADOSKA_H
