#pragma once
#include "Korisnik.h"
#include <filesystem>
#include <sstream>
#include "Let.h"

class Operater : public Korisnik
{
public:
	Operater(string, string);
	void spisakRezervacija() const;
	void otvaranjeRezervacije(std::vector<Let>&) const;
	void odobriRezervaciju(string) const;
	void otkaziRezervaciju(string) const;
	void odbijeneRezervacije() const;
	void odobreneRezervacije() const;
};