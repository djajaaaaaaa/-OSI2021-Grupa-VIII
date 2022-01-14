#pragma once
#include <string>
#include <fstream>
#include "Korisnik.h"
#include "Let.h"
#include <vector>

class Kontrolor : public Korisnik
{
public:
	Kontrolor(string, string);

	void kreirajLet(std::vector<Let>&);
	void izmjenaStatusa(std::vector<Let>&);
	void informacijeLet();
	void otkazivanjeLeta();

private:
	bool dodajLetURaspored(Let&, std::vector<Let>&);
	bool pretragaLetazaInf(string);
	void upisiLet(Let&);
	void pretragaLeta(string);
	void zamijeniDatoteke();
};

