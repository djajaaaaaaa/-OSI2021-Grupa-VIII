#pragma once
#include "Korisnik.h"
#include <string>
#include <set>
using std::string;

class Administrator : public Korisnik
{
public:
	Administrator(string, string);
	
	void kreirajNalog(std::set<std::shared_ptr<Korisnik>>& set);
	void obrisiNalog(std::set<std::shared_ptr<Korisnik>>& set);
	void suspenzijaNaloga(std::set<std::shared_ptr<Korisnik>>& set);
	void dozvoljenoDodavanje(string username, char tip, std::set<std::shared_ptr<Korisnik>>& set);
};

