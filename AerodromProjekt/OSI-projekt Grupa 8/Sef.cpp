#include <iostream>
#include <filesystem>
#include <cctype>
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
	string mjesec;
	std::cout << "Unesi mjesec za pregled izvjestaja: (u formatu mm.gggg)" << std::endl;
	std::cin >> mjesec;
	

	for (auto it = letovi.begin(); it != letovi.end(); ++it)
	{
		string temp;
		temp = it->getDatum();
		if (it->getStatus() == "sletio")
		{
			if (mjesec.substr(3, 4) == temp.substr(6, 4) && mjesec[0] == temp[3] && mjesec[1] == temp[4])
				it->printInfo();
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
		if (it->getStatus() == "sletio") 
		{
			if (temp.substr(6, 4) == sedmica1.substr(6, 4) || temp.substr(6, 4) == sedmica2.substr(6, 4))
			{
				if (temp.substr(3, 2) == sedmica1.substr(3, 2) || temp.substr(3, 2) == sedmica2.substr(3, 2))
				{
					if (temp[0] > sedmica1[0] && temp[0] < sedmica2[0]) 
						it->printInfo();
					else if (temp[0] == sedmica1[0] && temp[0] == sedmica2[0] && temp[1] > sedmica1[1] && temp[1] < sedmica2[1])
						it->printInfo();
				}
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
			if (datum == temp) 
				it->printInfo(); 
	}
	
}

bool provjeraUnesenogDatuma(string datum) // datum treba da bude unesen u formatu dd.mm.gggg
{
	
	auto checkDate = [](string& str) -> bool
	{
		for (int i = 0; i < 10; i++)
		{
			if (i != 2 && i != 5)
				if (!isdigit(str[i]))
					return false;
		}

		if (str[2] != '.' && str[5] != '.')
			return false;

		return true;
	};

	if (datum.size() != 10)
		return false;
	else if (checkDate(datum) == false)
		return false;
	else if (datum[0] == '3' && datum[1] > '1')
		return false;
	else if (datum[3] == '1' && datum[4] > '2')
		return false;

	return true;
}