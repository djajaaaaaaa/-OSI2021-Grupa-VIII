#include "Administrator.h"
#include <iostream>

Administrator::Administrator(string ime, string lozinka) : Korisnik(ime, lozinka, 'A')
{

}


void Administrator::kreirajNalog()
{
	fstream fin;
	fin.open("korisnici.dat", ios::in);

	string ime;char ime1[21];string lozinka;char lozinka1[21];
	char tip1;

	std::cout << "Korisnicko ime: ";
	std::cin >> ime;
	std::cout << "Lozinka: ";
	std::cin >> lozinka;
	std::cout << "Tip naloga: ";
	std::cin >> tip1;

	try
	{
		dozvoljenoDodavanje(ime, tip1);
	}
	catch (const std::exception& e) 
	{
		std::cout << e.what() << std::endl;
	}
	
	Korisnik novi(ime, lozinka, tip1);
	novi.upisiuFajl(fin);
	
}

void Administrator::dozvoljenoDodavanje(string username, char tip)
{
	int countS = 0, countA = 0;
	string ime;char ime1[21];string lozinka;char lozinka1[21];
	char tip1;
	fstream fin;
	fin.open("korisnici.dat", ios::in);

	while (!fin.eof())
	{
		fin.read((char*)ime1, sizeof(char[21]));
		fin.read((char*)lozinka1, sizeof(char[21]));
		fin.read(&tip1, sizeof(char));
		if (ime1 == username)
			throw std::exception("Korisnicko ime vec postoji!"); // druga vrsta exceptiona, definisati
		if (tip1 == 'S')
			countS++;
		else if (tip1 == 'A')
			countA++;
	}

	if (tip == 'S')
	{
		if (countS == 3)
			throw std::exception("Prekoracen broj naloga!");
	}
	else if (tip == 'A')
	{
		if (countA == 2)
			throw std::exception("Prekoracen broj naloga!");
	}
}

void Administrator::obrisiNalog()
{
	
}