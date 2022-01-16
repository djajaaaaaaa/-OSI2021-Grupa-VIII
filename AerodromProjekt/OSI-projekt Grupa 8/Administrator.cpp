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
		if ((*it)->getIme() == username)
			throw std::invalid_argument("Korisnicko ime vec postoji!");
	}

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
	do
	{
		std::cout << "Unesi korisnicko ime: ";
		std::cin >> ime;
	} while (ime == this->getIme());

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
	do
	{
		std::cout << "Unesi korisnicko ime naloga: ";
		std::cin >> ime;
	} while (ime == this->getIme());

	std::set<std::shared_ptr<Korisnik>>::iterator it;
	it = std::find_if(set.begin(), set.end(), [ime](std::shared_ptr<Korisnik> k) {return (*k).getIme() == ime;});
	if (it == set.end())
	{
		std::cout << "Nije pronadjen korisnik sa zadatim imenom!" << std::endl;
		return;
	}

	string name = (*it)->getIme();
	string loz = (*it)->getLozinka();
	char tip = (*it)->getTip();

	set.erase(it);

	if (tip == 'A')
	{
		Administrator novi(ime, loz);
		if (flag == '1')
			novi.suspenduj();
		else
			novi.ukloniSuspenziju();
		set.emplace(std::make_shared<Korisnik>(novi));
	}
	else if (tip == 'S')
	{
		Sef novi(ime, loz);
		if (flag == '1')
			novi.suspenduj();
		else
			novi.ukloniSuspenziju();
		set.emplace(std::make_shared<Korisnik>(novi));
	}
	else if (tip == 'K')

	{
		Kontrolor novi(ime, loz);
		if (flag == '1')
			novi.suspenduj();
		else
			novi.ukloniSuspenziju();
		set.emplace(std::make_shared<Korisnik>(novi));
	}
	else if (tip == 'O')
	{
		Operater novi(ime, loz);
		if (flag == '1')
			novi.suspenduj();
		else
			novi.ukloniSuspenziju();
		set.emplace(std::make_shared<Korisnik>(novi));
	}


}
