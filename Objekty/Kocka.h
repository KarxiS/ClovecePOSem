//
// Created by andre on 29. 12. 2023.
//

#ifndef CLOVECEPOSEM_KOCKA_H
#define CLOVECEPOSEM_KOCKA_H
#include <cstdlib>
#include <ctime>

class Kocka {
private:

public:
    inline int hodKockou(){
        return (rand() % 6) + 1;    //simulacia hodu kockou, cisla od 1-6
    };
};


#endif //CLOVECEPOSEM_KOCKA_H
