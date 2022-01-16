#pragma once
#include <string>
#include <iostream>
#include <iomanip>
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
	Let(string, string, string, string, string, string, string, string, string, string status = "nijePoletio");
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

	void printInfo() const;

	friend class Kontrolor;
};