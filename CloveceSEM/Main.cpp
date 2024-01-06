#include <iostream>
#include <thread>
#include "HraciaDoska.h"
#include "Hra.h"

int main()
{
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
    return 0;
}
