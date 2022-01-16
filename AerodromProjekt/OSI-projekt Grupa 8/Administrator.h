#pragma once
#include "Korisnik.h"
#include <string>
#include <vector>
using std::string;

class Administrator : public Korisnik
{
public:
	Administrator(string, string);
	
	void kreirajNalog(std::vector<std::shared_ptr<Korisnik>>& );
	void obrisiNalog(std::vector<std::shared_ptr<Korisnik>>&);
	void suspenzijaNaloga(std::vector<std::shared_ptr<Korisnik>>& );
	void dozvoljenoDodavanje(string username, char tip, std::vector<std::shared_ptr<Korisnik>>& set);
};

