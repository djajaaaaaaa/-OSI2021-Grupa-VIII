#include "Administrator.h"
#include "Operater.h"
#include "Kontrolor.h"
#include "Sef.h"
#include <set>
#include <iostream>
#include <algorithm>

Administrator::Administrator(string ime, string lozinka) : Korisnik(ime, lozinka, 'A')
{

}


void Administrator::kreirajNalog(std::set<std::shared_ptr<Korisnik>>& set) // da li samo dodavanje u set ili i u datoteku
{
	fstream fin;
	fin.open("korisnici.dat", ios::binary || ios::in || ios::app);

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
		dozvoljenoDodavanje(ime, tip1, set);
	}
	catch (const std::exception& e) 
	{
		std::cout << e.what() << std::endl;
	}
	
	
	// da li izbjeci ovo grananje i napraviti konstruktor korisnik pa upisati u fajl (da ne bude apstraktna klasa)?
	if (tip1 == 'a' || tip1 == 'A')
	{
		Administrator novi(ime, lozinka);
		set.emplace(std::make_shared<Korisnik>(novi));
	}
	else if (tip1 == 'k' || tip1 == 'K')
	{
		Kontrolor novi(ime, lozinka);
		set.emplace(std::make_shared<Korisnik>(novi));
	}
	else if (tip1 == 'o' || tip1 == 'O')
	{
		Operater novi(ime, lozinka);
		set.emplace(std::make_shared<Korisnik>(novi));
	}
	else
	{
		Sef novi(ime, lozinka);
		set.emplace(std::make_shared<Korisnik>(novi));
	}
	
	
	
}

void Administrator::dozvoljenoDodavanje(string username, char tip, std::set<std::shared_ptr<Korisnik>>& set)
{
	if (tip != 'a' && tip != 'A' && tip != 'k' && tip != 'K' && tip != 'o' && tip != 'O' && tip != 's' && tip != 'S')
		throw std::invalid_argument("Nevalidan tip!");
	int countS = 0, countA = 0;
	
	for (auto it = set.begin(); it != set.end(); it++)
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

void Administrator::obrisiNalog(std::set<std::shared_ptr<Korisnik>>& set)
{
	string ime; 
	std::cout << "Unesi korisnicko ime: ";
	std::cin >> ime;
	std::set<std::shared_ptr<Korisnik> >::iterator it;

	for (it = set.begin(); it != set.end(); ++it)
	{
		if ((*it)->getIme() == ime)
		{
			set.erase(it);
			std::cout << "Korisnik pronadjen i obrisan!" << std::endl;
			break;
		}
	}

}


void Administrator::suspenzijaNaloga(std::set<std::shared_ptr<Korisnik>>& set)
{
	char flag;
	do
	{
		std::cout << "Suspenzija ili ukidanje suspenzije?(1/0)";
		std::cin >> flag;

	} while (flag != '1' && flag != '0');

	string ime; 
	std::cout << "Unesi korisnicko ime naloga: ";
	std::cin >> ime;
	std::set<std::shared_ptr<Korisnik>>::iterator it;

	for (it = set.begin(); it != set.end(); ++it)
	{
		if ((*it)->getIme() == ime)
		{
			if (flag == '1')
			{
				(*it)->suspenduj();
				std::cout << "Korisnik suspendovan!" << std::endl;
				break;
			}
			else
			{
				(*it)->ukloniSuspenziju();
				std::cout << "Suspenzija uklonjena!" << std::endl;
				break;
			}

		}
	}
	
	if (it == set.end())
		std::cout << "Korisnik nije pronadjen!" << std::endl;
}