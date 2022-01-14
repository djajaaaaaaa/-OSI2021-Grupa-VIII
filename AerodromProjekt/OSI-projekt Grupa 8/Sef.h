#pragma once
#include <fstream>
#include "Korisnik.h"

class Sef : public Korisnik
{
public:
	Sef(string, string);

	void pregledRezervacija() const;
	void sedmicniIzvjestaj() const;
	void mjesecniIzvjestaj() const;
	void dnevniIzvjestaj() const;
	void ispisDatoteke(std::fstream&) const;
};
