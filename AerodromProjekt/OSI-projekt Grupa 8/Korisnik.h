#pragma once
#include <string>
#include <exception>
#include <fstream>
#include <iostream>
using namespace std;

class Korisnik {
	char ime[21] = {};
	char lozinka[21] = {};
	char tip;
	char suspendovan; // podrazumijevano nije suspendovan
public:
	Korisnik();
	Korisnik(string ime, string lozinka, char tip, char susp = '0'); // ako se ne navede onda je 0, a moze se i navesti
	string getIme() const;
	string getLozinka() const;
	char getTip() const;
	void upisiuFajl(ostream&) const;
	void ucitajizFajla(ifstream&) const;
	bool isSuspended();
	char getSuspenzija();
	void suspenduj();
	void ukloniSuspenziju();
};
