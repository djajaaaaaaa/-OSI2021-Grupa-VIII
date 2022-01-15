#include <iostream>
#include <filesystem>
#include "Sef.h"
namespace fs = std::filesystem;


Sef::Sef(string ime, string lozinka) : Korisnik(ime, lozinka, 'S')
{

}

void Sef::pregledRezervacija() const
{
	fstream datoteka;
	datoteka.open("rezervacije.txt", ios::in); // relativna putanja
	ispisDatoteke(datoteka);

}

void Sef::ispisDatoteke(std::fstream& datoteka) const
{
	if (!datoteka)
		exit(1);
	string linija;
	while (getline(datoteka, linija))
		std::cout << linija << std::endl;
}

void Sef::mjesecniIzvjestaj(std::vector<Let>& letovi) const
{
	//datum je formata dd.mm.gggg, znaci znamo tacne pozicije i broj dijelova stringa za poredjenje
	char mjesec[2];
	do
	{
		std::cout << "Unesi mjesec za pregled izvjestaja: (u formatu broja mjeseca - 0x)" << std::endl;
		std::cin >> mjesec; // podrazumijeva se tekuca godina
	} while (mjesec[0] != '0' &&  mjesec[0] != '1');

	for (auto it = letovi.begin(); it != letovi.end(); ++it)
	{
		string temp;
		temp = it->getDatum();
		if (it->getStatus() == "sletio")
		{
			if (temp[3] == mjesec[0] && temp[4] == mjesec[1])
				//it->printLet(); // skontati jos sta ide u izvjestaj
		}

	}
}

void Sef::sedmicniIzvjestaj(std::vector<Let>& letovi) const
{
	string sedmica1; string sedmica2;
	std::cout << "Unesi datum pocetka sedmice za pregled izvjestaja: (u formatu dd.mm.gggg) " << std::endl;
	std::cin >> sedmica1;
	std::cout << "Unesi datum kraja sedmice za pregled izvjestaja: (u formatu dd.mm.gggg) " << std::endl;
	std::cin >> sedmica2; // dodati provjere na nekorektnost unesenog datuma
	
	for (auto it = letovi.begin(); it != letovi.end(); ++it)
	{
		string temp;
		temp = it->getDatum();
		if (it->getStatus() == "sletio") // mjesec se podudara ili sa jednom ili sa drugom sedmicom sigurno
		{
			if (temp[3] == sedmica1[3] && temp[4] == sedmica1[4] || temp[3] == sedmica2[3] && temp[4] == sedmica2[4])
			{
				if (temp[0] > sedmica1[0] && temp[0] < sedmica2[0]) // vrijedi da je izmedju te sdvije sedmice
					//it->printLet();
				else if (temp[0] == sedmica1[0] && temp[0] == sedmica2[0] && temp[1] > sedmica1[1] && temp[1] < sedmica2[1])
					//it->printLet();
			}
		}
	}

}

void Sef::dnevniIzvjestaj(std::vector<Let>& letovi) const
{
	string datum;
	std::cout << "Unesi datum za pregled izvjestaja: (u formatu dd.mm.gggg) " << std::endl;
	std::cin >> datum;
	for (auto it = letovi.begin(); it != letovi.end(); ++it)
	{
		string temp;
		temp = it->getDatum();
		if (it->getStatus() == "sletio")
			if (datum == temp) // podrazumijeva se da je pravilno unesen da su  u istim formatima
				//it->printLet(); // skontati jos sta ide u izvjestaj
	}
	
}

