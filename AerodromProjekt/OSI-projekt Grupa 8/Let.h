#pragma once
#include <string>
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
	string getStatus()const
	{
		return status;
	}
	friend class Kontrolor;
};