#include <iostream>
#include <filesystem>
#include "Sef.h"
namespace fs = std::filesystem;


Sef::Sef(string ime, string lozinka) : Korisnik(ime, lozinka, 'S')
{

}

void Sef::pregledRezervacija() const
{
	namespace fs = filesystem;
	fs::path path = filesystem::current_path() / "rezervacije";
	fstream file;

	int i = 0;
	for (auto const& entry : fs::directory_iterator(path))
	{
		string dat = entry.path().string();
		file.open(dat, ios::in);
		ispisDatoteke(file);
		std::cout << std::endl;
			file.close();
	}


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

	std::cout << "Sifra leta:" << std::setw(10) << "Odlazak:" << " - " << "Dolazak:" << std::setw(20)
		<< "Datum:" << std::setw(30) << "Vrijeme polaska:" << " - " << "Vrijeme dolaska:" << std::setw(15)
		<< "Status:" << std::endl;

	for (auto it = letovi.begin(); it != letovi.end(); ++it)
	{
		string temp;
		temp = it->getDatum();
		if (it->getStatus() == "sletio")
		{
			if (mjesec.substr(0, 2) == temp.substr(3, 2) && mjesec.substr(3, 4) == temp.substr(6, 4))
				it->printInfo();
		}

	}

}

void Sef::sedmicniIzvjestaj(std::vector<Let>& letovi) const
{
	string sedmica1; string sedmica2;
	do
	{
		std::cout << "Unesi datum pocetka sedmice za pregled izvjestaja: (u formatu dd.mm.gggg) " << std::endl;
		std::cin >> sedmica1;
		std::cout << "Unesi datum kraja sedmice za pregled izvjestaja: (u formatu dd.mm.gggg) " << std::endl;
		std::cin >> sedmica2; // dodati provjere na nekorektnost unesenog datuma
	} while (provjeraUnesenogDatuma(sedmica1) == false && provjeraUnesenogDatuma(sedmica2) == false
		&& sedmica1 > sedmica2);

	std::cout << "Sifra leta:" << std::setw(10) << "Odlazak:" << " - " << "Dolazak:" << std::setw(20)
		<< "Datum:" << std::setw(30) << "Vrijeme polaska:" << " - " << "Vrijeme dolaska:" << std::setw(15)
		<< "Status:" << std::endl;

	for (auto it = letovi.begin(); it != letovi.end(); ++it)
	{
		string temp;
		temp = it->getDatum();
		if (it->getStatus() == "sletio")
		{
			if (temp.substr(6, 4) == sedmica1.substr(6, 4) || temp.substr(6, 4) == sedmica2.substr(6, 4))
			{
				if (sedmica1.substr(3, 2) == sedmica2.substr(3, 2))
				{
					if (temp.substr(0, 2) >= sedmica1.substr(0, 2) && temp.substr(0, 2) <= sedmica2.substr(0, 2))
						it->printInfo();
				}
				else if (sedmica1.substr(3, 2) < sedmica2.substr(3, 2))
				{
					if (temp.substr(3, 2) == sedmica1.substr(3, 2))
					{
						if (temp.substr(0, 2) >= sedmica1.substr(0, 2) && temp.substr(0, 2) >= sedmica2.substr(0, 2))
							it->printInfo();
					}
					else if (temp.substr(3, 2) == sedmica2.substr(3, 2))
					{
						if (temp.substr(0, 2) <= sedmica1.substr(0, 2) && temp.substr(0, 2) <= sedmica2.substr(0, 2))
							it->printInfo();
					}


				}

			}
		}
	}

}

void Sef::dnevniIzvjestaj(std::vector<Let>& letovi) const
{
	string datum;
	do
	{
		std::cout << "Unesi datum za pregled izvjestaja: (u formatu dd.mm.gggg.) " << std::endl;
		std::cin >> datum;
	} while (provjeraUnesenogDatuma(datum) == false);

	std::cout << "Sifra leta:" << std::setw(10) << "Odlazak:" << " - " << "Dolazak:" << std::setw(20)
		<< "Datum:" << std::setw(30) << "Vrijeme polaska:" << " - " << "Vrijeme dolaska:" << std::setw(15)
		<< "Status:" << std::endl;

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
		for (int i = 0; i < 11; i++)
		{
			if (i != 2 && i != 5 && i != 10)
				if (!isdigit(str[i]))
					return false;
		}

		if (str[2] != '.' && str[5] != '.' && str[10] != '.')
			return false;

		return true;
	};

	if (datum.size() != 11)
		return false;
	else if (checkDate(datum) == false)
		return false;
	else if (datum[0] == '3' && datum[1] > '1')
		return false;
	else if (datum[3] == '1' && datum[4] > '2')
		return false;

	return true;
}
