#pragma once
#include <string>
#include <iomanip>
#include <iostream>
using namespace std;

class Let
{
private:
	string sifra;
	string odlazak;
	string dolazak;
	string vrijemePolaska;
	string vrijemeDolaska;
	string datum;
	string opis;
	string brojMjesta;
	string brojSlobodnihMjesta;
	string status;

public:
	Let(string, string, string, string, string, string, string, string, string);
	string getSifra()const
	{
		return sifra;
	}
	string getStatus()const
	{
		return status;
	}
	string getDatum() const
	{
		return datum;
	}
	string getBrSlobMjesta() const
	{
		return brojSlobodnihMjesta;
	}

	void printInfo() const
	{
		std::cout << this->sifra << std::setw(8) << this->odlazak << " - " << this->dolazak << std::setw(8)
			<< this->datum << std::setw(8) << this->vrijemePolaska << " - " << this->vrijemeDolaska << std::setw(8)
			<< this->status << std::endl;
	}

	friend class Kontrolor;
};