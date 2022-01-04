#pragma once
#include <string>
#include <exception>
#include <fstream>
using namespace std;

class Korisnik {
	char ime[21] = {};
	char lozinka[21] = {};
	char tip;
public:
	Korisnik();
	Korisnik(string ime, string lozinka, char tip);
	string getIme() const;
	char getTip() const;
	void upisiuFajl(ostream&) const;
	void ucitajizFajla(ifstream&) const;
	virtual ~Korisnik() = 0
	{};
};
