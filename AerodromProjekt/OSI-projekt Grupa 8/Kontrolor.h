#pragma once
#include <string>
#include <fstream>
#include "Korisnik.h"
#include "Let.h"

class Kontrolor : public Korisnik
{
public:
	Kontrolor(string, string);

	void kreirajLet();
	void izmjenaStatusa();
	void informacijeLet();
	void otkazivanjeLeta();

private:
	bool dodajLetURaspored(Let&);
	bool pretragaLetaZaInf(string);
	void upisiLet(Let&);
	void zamijeniDatoteke();
};

