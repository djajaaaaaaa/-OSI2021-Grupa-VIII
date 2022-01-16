#include "Let.h"

Let::Let(string sifra, string odlazak, string dolazak, string vrijemePolaska, string vrijemeDolaska, string datum, string opis, string brojMjesta, string brojSlobodnihMjesta, string status) :
	sifra(sifra), odlazak(odlazak), dolazak(dolazak), vrijemePolaska(vrijemePolaska), vrijemeDolaska(vrijemeDolaska), datum(datum), opis(opis), brojMjesta(brojMjesta), brojSlobodnihMjesta(brojSlobodnihMjesta), status(status)
{

}

void Let::printInfo() const
{
	std::cout << this->sifra << std::setw(15) << this->odlazak << " - " << this->dolazak << std::setw(25)
		<< this->datum << std::setw(30) << this->vrijemePolaska << " - " << this->vrijemeDolaska << std::setw(24)
		<< this->status << std::endl;
}