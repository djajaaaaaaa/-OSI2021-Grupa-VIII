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
	void suspenzijaNaloga();
	void dozvoljenoDodavanje(string username, char tip);
};

void obrisiLinijuIzDatoteke(std::istream&, std::ostream&);
