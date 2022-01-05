#include "Administrator.h"
#include <iostream>

Administrator::Administrator(string ime, string lozinka) : Korisnik(ime, lozinka, 'A')
{

}


void Administrator::kreirajNalog()
{
	fstream fin;
	fin.open("korisnici.dat", ios::binary);

	string ime;char ime1[21];string lozinka;char lozinka1[21];
	char tip1;

	std::cout << "Korisnicko ime: ";
	std::cin >> ime;
	std::cout << "Lozinka: ";
	std::cin >> lozinka;
	std::cout << "Tip naloga: ";
	std::cin >> tip1;

	//ako je tip sef, potrebno je izvrsiti provjeru da li vec postoje 3 sefa u bazi podataka

	// u zavisnosti od tipa, naoraviti konstruktor i iskoristiti funkciju naloga korisnik za upis u fajl?
}