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
	int brojMjesta;
	int brojSlobodnihMjesta;

public:
	Let(string, string, string, string, string, string, string, int, int);
	friend class Kontrolor;
};