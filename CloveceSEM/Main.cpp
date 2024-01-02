#include <iostream>
#include <thread>
#include "HraciaDoska.h"
#include "Hra.h"


//zdielane data medzi vlaknami - Hra
struct Data{
    Hra hra;
};

//producent - kocka, ktora dava padnute cislo;
void dajCislo(Data* data){

}

//konzument - hrac, ktory vykona akciu s padnutym cislom;
void spravTah(Data* data){

}


int main()
{
    /*
    srand(time(nullptr));
    Data data;

    Hrac hrac1("Jozef", '1');
    Hrac hrac2("Matus", '2');
    Hrac hrac3("Kiko", '3');
    Hrac hrac4("Rasto", '4');
    data.hra.zapisHraca(hrac1);
    data.hra.zapisHraca(hrac2);
    data.hra.zapisHraca(hrac3);
    data.hra.zapisHraca(hrac4);

    std::thread KOCKA(dajCislo, &data);
    std::thread PLAYER1(spravTah, &data);
    std::thread PLAYER2(spravTah, &data);
    std::thread PLAYER3(spravTah, &data);
    std::thread PLAYER4(spravTah, &data);

    PLAYER1.join();
    PLAYER2.join();
    PLAYER3.join();
    PLAYER4.join();

    data.hra.zacniHru();
    return 0;
     */


    srand(time(nullptr));

    Hrac hrac1("Jozef", '1');
    Hrac hrac2("Matus", '2');
    Hrac hrac3("Kiko", '3');
    Hrac hrac4("Rasto", '4');
    Hra hra;
    hra.zapisHraca(hrac1);
    hra.zapisHraca(hrac2);
    hra.zapisHraca(hrac3);
    hra.zapisHraca(hrac4);

    hra.zacniHru();
    hra.ukazVysledok();
    return 0;
}
