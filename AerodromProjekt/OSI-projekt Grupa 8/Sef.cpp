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

void Sef::mjesecniIzvjestaj() const
{
	string mjesec;
	std::cout << "Unesi mjesec za pregled izvjestaja: " << std::endl;
	std::cin >> mjesec;

	fstream datoteka;
	datoteka.open(".\\Izvjestaji\\Mjesecni\\" + mjesec + ".txt", ios::in);
	ispisDatoteke(datoteka);
}

void Sef::sedmicniIzvjestaj() const
{
	string sedmica;
	std::cout << "Unesi sedmicu za pregled izvjestaja: " << std::endl;
	std::cin >> sedmica;
	fstream datoteka;
	datoteka.open(".\\Izvjestaji\\Sedmicni\\" + sedmica + ".txt", ios::in);
	ispisDatoteke(datoteka);
}

void Sef::dnevniIzvjestaj() const
{
	string dan;
	std::cout << "Unesi dan za pregled izvjestaja: " << std::endl;
	std::cin >> dan;
	generisiDIzvjestaj();
	fstream datoteka;
	datoteka.open(".\\Izvjestaji\\Dnevni\\" + dan + ".txt", ios::in);
	ispisDatoteke(datoteka);
}

