#include "Hra.h"
#include <iostream>

Hra::Hra()
{
	this->aktualnyHrac = 0;
	this->jeKoniec = false;
}

void Hra::zapisHraca(Hrac& hrac)
{
	if (hraci.size() < 4) {
		hraci.push_back(hrac);
	}
	else {
		std::cout << "V hre su zapojeni len prvi 4 hraci." << std::endl;
	}
	
}

void Hra::zacniHru()
{
	hraciaDoska.inicializaciaHraciehoPola();
	for (int i = 0; i < hraci.size(); ++i) {
		hraciaDoska.pridajHraca(hraci.at(i));
	};
	hraciaDoska.zobrazHraciePole();
    this->spravTah();




    //hraciaDoska.zobrazHraciePoleDebugCesty();
    /*
	do {
		this->spravTah();
		hraciaDoska.zobrazHraciePole();

	} while (!this->jeKoniec);
    */
	
}

void Hra::spravTah()
{
	Hrac hracNaTahu = hraci.at(aktualnyHrac);
    std::cout << "Hrac na rade: " << hracNaTahu.getId() - 48 << std::endl;

	int padnuteCislo = hracNaTahu.hodKockou(this->kocka);
    std::cout << "Padnute cislo: " << padnuteCislo << std::endl;

	//aktualizacia hraca pre dalsie kolo	
	this->aktualnyHrac = (this->aktualnyHrac + 1) % hraci.size();
}

void Hra::ukazVysledok()
{

}

