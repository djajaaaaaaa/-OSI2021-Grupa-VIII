#pragma once
#include "Vrijeme.h"
#include "Datum.h"
#include <string>
using namespace std;

class Let
{
private:
	string sifra;
	string odlazak;
	string dolazak;
	Vrijeme vrijemePolaska;
	Vrijeme vrijemeDolaska;
	Datum datum;
	string opis;
	int brojMjesta;
	int brojSlobodnihMjesta;

public:
	Let(string, string, string, Vrijeme, Vrijeme, Datum, string, int, int);
};
