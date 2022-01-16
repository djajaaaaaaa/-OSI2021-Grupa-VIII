#include <iostream>
#include <set>
#include <memory>
#include <string>
#include <cstring>
#include <sstream>
#include "Administrator.h"
#include "Kontrolor.h"
#include "Operater.h"
#include "Sef.h"
#include "Let.h"
#include "Exceptions.h"
#include <vector>

Korisnik& prijavaSet(string username, string lozinka, std::vector<std::shared_ptr<Korisnik>>& vector)
{
	auto it = std::find_if(vector.begin(),vector.end(), [username](std::shared_ptr<Korisnik> k) {return (*k).getIme() == username;});
	if (it == vector.end())
		throw KorisnikNePostoji("Korisnik ne postoji.");

	if ((*it)->isSuspended() == true) 
		throw KorisnikSuspendovan("Korisnik suspendovan.");

	if ((*it)->getLozinka() != lozinka)
		throw NeispravnaLozinka("Pogresna lozinka");

	return **it;
}


void ucitajKorisnike(std::vector<std::shared_ptr<Korisnik>>& vector, std::ifstream& fajl)
{
	Korisnik temp;
	while (!fajl.eof())
	{
		temp.ucitajizFajla(fajl);
		if (temp.getTip() == 'A')
		{
			Administrator novi(temp.getIme(), temp.getLozinka(), temp.getSuspenzija());
			vector.push_back(std::make_shared<Korisnik>(novi));
		}
		else if (temp.getTip() == 'K')
		{
			Kontrolor novi(temp.getIme(), temp.getLozinka(), temp.getSuspenzija());
			vector.push_back(std::make_shared<Korisnik>(novi));
		}
		else if (temp.getTip() == 'S')
		{
			Sef novi(temp.getIme(), temp.getLozinka(), temp.getSuspenzija());
			vector.push_back(std::make_shared<Korisnik>(novi));
		}
		else if (temp.getTip() == 'O')
		{
			Operater novi(temp.getIme(), temp.getLozinka(), temp.getSuspenzija());
			vector.push_back(std::make_shared<Korisnik>(novi));
		}
	}
	fajl.close();
	vector.pop_back();
}

void azurirajBazu(std::vector<std::shared_ptr<Korisnik>>& vector)
{
	ofstream fajl;
	fajl.open("korisnici.dat", ios::binary | ios::out);

	for (auto it = vector.begin(); it != vector.end(); it++)
		(*it)->upisiuFajl(fajl);
}

void ucitajLetove(std::vector<Let>& letovi, ifstream& fin)
{
	vector<string> row;
	string line, word;
	while (!fin.eof())
	{
		row.clear();
		getline(fin, line);
		stringstream str(line);
		while (getline(str, word, ',')) {

			row.push_back(word);
		}
		if (!(row.empty()))
		{
			Let load(row[0], row[1], row[2], row[3], row[4], row[5], row[6], row[7], row[8], row[9]);
			letovi.push_back(load);
		}
	}
}

int main()
{
	ifstream ucitavanje;
	ucitavanje.open("korisnici.dat", ios::binary | ios::in);
	std::vector<std::shared_ptr<Korisnik> > korisnici;
	ucitajKorisnike(korisnici, ucitavanje);
	string tip, ime, lozinka;
	
	bool prijavaFlag = false;
	int i = 0;
	Korisnik ulogovan;

	do
	{
		try
		{
			std::cout << "Unesi korisnicko ime:" << std::endl;
			std::cin >> ime;
			std::cout << "Unesi lozinku:" << std::endl;
			std::cin >> lozinka;
			ulogovan = prijavaSet(ime, lozinka, korisnici);

			prijavaFlag = true;
		}
		catch (KorisnikNePostoji& e)
		{
			i++;
			std::cout << e.what() << std::endl;

		}
		catch (KorisnikSuspendovan& k)
		{
			i++;
			std::cout << k.what() << std::endl;
		}
		catch (NeispravnaLozinka& n)
		{
			i++;
			std::cout << n.what() << std::endl;
		}

	} while (prijavaFlag == false && i < 5);

	std::vector<Let> letovi;
	ifstream fin;
	fin.open("raspored.txt", ios::in);
	ucitajLetove(letovi, fin);

	if (ulogovan.getTip() == 'O')
	{
		Operater& ulogovani = static_cast<Operater&>(ulogovan);
		char opcija;
		do
		{
			cout << "Izaberite zeljenu opciju (unesite odgovarajuce slovo) " << endl;
			cout << "A) Pregled rezervacija" << endl;
			cout << "B) Otvaranje rezervacije" << endl;
			cout << "C) Pregled odbijenih rezervacija" << endl;
			cout << "D) Pregled odobrenih rezervacija" << endl;
			cout << "E) Kraj" << endl;
			cin >> opcija;

			if (opcija == 'A')
			{
				ulogovani.spisakRezervacija();
			}
			else if (opcija == 'B')
			{
				ulogovani.otvaranjeRezervacije(letovi);
			}
			else if (opcija == 'C')
			{
				ulogovani.odbijeneRezervacije();   
			}
			else if (opcija == 'D')
			{
				ulogovani.odobreneRezervacije();
			}
			else if(opcija != 'E')
			{
				cout << "Nepoznata opcija!" << endl;
			}

		} while (opcija != 'E');
	}

	else if (ulogovan.getTip() == 'K')
	{
		Kontrolor& ulogovani = static_cast<Kontrolor&>(ulogovan);
		char opcija;
		do
		{
			cout << "Izaberite zeljenu opciju (unesite odgovarajuce slovo) " << endl;
			cout << "A) Kreiranje leta" << endl;
			cout << "B) Mijenjanje statusa leta" << endl;
			cout << "C) Prikaz informacija o letu" << endl;
			cout << "D) Otkazivanje leta" << endl;
			cout << "E) Kraj" << endl;
			cin >> opcija;

			if (opcija == 'A')
			{
				ulogovani.kreirajLet(letovi);
			}
			else if (opcija == 'B')
			{
				ulogovani.izmjenaStatusa(letovi);
			}
			else if (opcija == 'C')
			{
				ulogovani.informacijeLet(letovi);
			}
			else if (opcija == 'D')
			{
				ulogovani.otkazivanjeLeta(letovi);
			}
			else if(opcija != 'E')
			{
				cout << "Nepoznata opcija!" << endl;
			}

		} while (opcija != 'E');
	}

	else if (ulogovan.getTip() == 'S')
	{
		Sef& ulogovani = static_cast<Sef&>(ulogovan);
		char opcija;
		do
		{
			cout << "Izaberite zeljenu opciju (unesite odgovarajuce slovo) " << endl;
			cout << "A) Pregled izvjestaja" << endl;
			cout << "B) Pregled rezervacija" << endl;
			cout << "C) Kraj" << endl;
			cin >> opcija;

			if (opcija == 'A')
			{
				char opcija1;
				cout << "Odaberite vrstu izvjestaja (unesite odgovarajuce slovo) " << endl;
				cout << "A) Dnevni" << endl;
				cout << "B) Sedmicni" << endl;
				cout << "C) Mjesecni" << endl;
				cin >> opcija1;

				if (opcija1 == 'A')
				{
					ulogovani.dnevniIzvjestaj(letovi);
				}
				else if (opcija1 == 'B')
				{
					ulogovani.sedmicniIzvjestaj(letovi);
				}
				else if (opcija1 == 'C')
				{
					ulogovani.mjesecniIzvjestaj(letovi);
				}
				else
				{
					cout << "Nepoznata opcija!" << endl;
				}
			}
			else if (opcija == 'B')
			{
				ulogovani.pregledRezervacija();
			}
			else if(opcija != 'C')
			{
				cout << "Nepoznata opcija!" << endl;
			}

		} while (opcija != 'C');
	}

	else if (ulogovan.getTip() == 'A')
	{
		Administrator& ulogovani = static_cast<Administrator&>(ulogovan);
		char opcija;
		do
		{
			cout << "Izaberite zeljenu opciju (unesite odgovarajuce slovo) " << endl;
			cout << "A) Kreiranje naloga" << endl;
			cout << "B) Brisanje naloga" << endl;
			cout << "C) Suspendovanje naloga" << endl;
			cout << "D) Kraj" << endl;
			cin >> opcija;

			if (opcija == 'A')
			{
				ulogovani.kreirajNalog(korisnici);
			}
			else if (opcija == 'B')
			{
				ulogovani.obrisiNalog(korisnici);
			}
			else if (opcija == 'C')
			{
				ulogovani.suspenzijaNaloga(korisnici);
			}
			else if(opcija != 'D')
			{
				cout << "Nepoznata opcija!" << endl;
			}

		} while (opcija != 'D');

	}
	else
	{
		cout << "Greska! Nepostojeci tip naloga!" << endl;
	}

	azurirajBazu(korisnici);
    return 0;
}

