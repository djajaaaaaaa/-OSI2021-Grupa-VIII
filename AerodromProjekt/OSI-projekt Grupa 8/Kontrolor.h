#pragma once
#include <string>
#include <fstream>
#include "Korisnik.h"
#include "Vrijeme.h"
#include "Datum.h"

class Kontrolor : public Korisnik
{
public:
	Kontrolor(string, string);

	void kreirajLet();
	void izmjenaStatusa();
	void informacijeLet();
	void otkazivanjeLeta();

private:
	bool dodajLetURaspored(Datum, Vrijeme);
};
