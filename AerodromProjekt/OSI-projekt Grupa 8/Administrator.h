#pragma once
#include "Korisnik.h"

class Administrator : public Korisnik
{
public:
	Administrator(string, string);
	
	void kreirajNalog();
	void obrisiNalog();
	void suspendujNalog();
};
