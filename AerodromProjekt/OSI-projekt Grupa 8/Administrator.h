#pragma once
#include "Korisnik.h"
#include <string>
using std::string;

class Administrator : public Korisnik
{
public:
	Administrator(string, string);
	
	void kreirajNalog();
	void obrisiNalog();
	void suspendujNalog();
	void dozvoljenoDodavanje(string username, char tip);
};
