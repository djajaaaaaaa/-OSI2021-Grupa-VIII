#include <vector>
#include <sstream>
#include <cstring>
#include <fstream>
#include <filesystem>
#include "Let.h"
#include "Korisnik.h"

class Operater : public Korisnik
{
public:
	Operater(string, string);
	void spisakRezervacija() const;
	void otvaranjeRezervacije(std::vector<Let>&);
	void odobriRezervaciju(string, std::vector<Let>&, string);
	void otkaziRezervaciju(string) const;
	void odbijeneRezervacije() const;
	void odobreneRezervacije() const;
private:
	void azurirajRaspored(std::vector<Let>&);
};