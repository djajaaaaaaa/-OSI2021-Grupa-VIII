#include "Let.h"

Let::Let(string sifra, string odlazak, string dolazak, string vrijemePolaska, string vrijemeDolaska, string datum, string opis, string brojMjesta, string brojSlobodnihMjesta, string status) :
	sifra(sifra), odlazak(odlazak), dolazak(dolazak), vrijemePolaska(vrijemePolaska), vrijemeDolaska(vrijemeDolaska), datum(datum), opis(opis), brojMjesta(brojMjesta), brojSlobodnihMjesta(brojSlobodnihMjesta), status(status)
{

}

void Let::printInfo() const
{
	std::cout << this->sifra << std::setw(8) << this->odlazak << " - " << this->dolazak << std::setw(8)
		<< this->datum << std::setw(8) << this->vrijemePolaska << " - " << this->vrijemeDolaska << std::setw(8)
		<< this->status << std::endl;
}