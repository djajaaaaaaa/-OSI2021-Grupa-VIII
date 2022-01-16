#include "Administrator.h"
#include "Operater.h"
#include "Kontrolor.h"
#include "Sef.h"
#include <set>
#include <iostream>
#include <algorithm>

Administrator::Administrator(string ime, string lozinka, char susp) : Korisnik(ime, lozinka, 'A', susp)
{

}


void Administrator::kreirajNalog(std::vector<std::shared_ptr<Korisnik>>& vector) // da li samo dodavanje u set ili i u datoteku
{
	fstream fin;
	fin.open("korisnici.dat", ios::binary | ios::in | ios::app);

	string ime;string lozinka;
	char tip1;

	std::cout << "Korisnicko ime: ";
	std::cin >> ime;
	std::cout << "Lozinka: ";
	std::cin >> lozinka;
	std::cout << "Tip naloga: ";
	std::cin >> tip1;

	try
	{
		dozvoljenoDodavanje(ime, tip1, vector);
	}
	catch (const std::exception& e) 
	{
		std::cout << e.what() << std::endl;
	}
	
	
	
	if (tip1 == 'a' || tip1 == 'A')
	{
		Administrator novi(ime, lozinka);
		vector.push_back(std::make_shared<Korisnik>(novi));
	}
	else if (tip1 == 'k' || tip1 == 'K')
	{
		Kontrolor novi(ime, lozinka);
		vector.push_back(std::make_shared<Korisnik>(novi));
	}
	else if (tip1 == 'o' || tip1 == 'O')
	{
		Operater novi(ime, lozinka);
		vector.push_back(std::make_shared<Korisnik>(novi));
	}
	else
	{
		Sef novi(ime, lozinka);
		vector.push_back(std::make_shared<Korisnik>(novi));
	}
	

}

void Administrator::dozvoljenoDodavanje(string username, char tip, std::vector<std::shared_ptr<Korisnik>>& vector)
{
	if (tip != 'a' && tip != 'A' && tip != 'k' && tip != 'K' && tip != 'o' && tip != 'O' && tip != 's' && tip != 'S')
		throw std::invalid_argument("Nevalidan tip!");
	int countS = 0, countA = 0;
	
	for (auto it = vector.begin(); it != vector.end(); it++)
	{
		if ((*it)->getIme() == username)
			throw std::invalid_argument("Korisnicko ime vec postoji!");
	}

	for (auto it = vector.begin(); it != vector.end(); it++)
	{
		if ((*it)->getTip() == 'S')
			countS++;
		else if ((*it)->getTip() == 'A')
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

void Administrator::obrisiNalog(std::vector<std::shared_ptr<Korisnik>>& vector)
{
	string ime; 
	do
	{
		std::cout << "Unesi korisnicko ime: ";
		std::cin >> ime;
	} while (ime == this->getIme());

	std::vector<std::shared_ptr<Korisnik> >::iterator it;

	for (it = vector.begin(); it != vector.end(); ++it)
	{
		if ((*it)->getIme() == ime)
		{
			vector.erase(it);
			std::cout << "Korisnik pronadjen i obrisan!" << std::endl;
			break;
		}
	}
}


void Administrator::suspenzijaNaloga(std::vector<std::shared_ptr<Korisnik>>& vector)
{
	char flag;
	do
	{
		std::cout << "Suspenzija ili ukidanje suspenzije?(1/0)";
		std::cin >> flag;

	} while (flag != '1' && flag != '0');

	string ime; 
	do
	{
		std::cout << "Unesi korisnicko ime naloga: ";
		std::cin >> ime;
	} while (ime == this->getIme());

	std::vector<std::shared_ptr<Korisnik>>::iterator it;
	it = std::find_if(vector.begin(), vector.end(), [ime](std::shared_ptr<Korisnik> k) {return (*k).getIme() == ime;});
	if (it == vector.end())
	{
		std::cout << "Nije pronadjen korisnik sa zadatim imenom!" << std::endl;
		return;
	}

	
	if (flag == '1')
		(*it)->suspenduj();
	else
		(*it)->ukloniSuspenziju();


	

}
