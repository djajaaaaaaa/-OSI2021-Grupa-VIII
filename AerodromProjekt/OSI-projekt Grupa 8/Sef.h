#pragma once
#include "Korisnik.h"

class Sef : public Korisnik
{
public:
	Sef(string, string);

	void pregledRezervacija();
	void sedmicniIzvjestaj();
	void mjesecniIzvjestaj();
	void dnevniIzvjestaj();
};
