#include <iostream>
#include <set>
#include <memory>
#include "Administrator.h"
#include "Kontrolor.h"
#include "Operater.h"
#include "Sef.h"

void initDat()
{
    ofstream fout("korisnici.dat", ios::out | ios::binary);
    Administrator admin1("Marko", "marko123");
    Administrator admin2("Janko", "janko123");
    Kontrolor kontrolor1("Srdjan", "srdjan123");
    Kontrolor kontrolor2("Stefan", "stefan123");
    Operater operater1("Uros", "uros123");
    Operater operater2("Milos", "milos123");
    Sef sef1("Sofija", "sofija123");
    Sef sef2("Atos", "atos123");

    admin1.upisiuFajl(fout);
    admin2.upisiuFajl(fout);
    kontrolor1.upisiuFajl(fout);
    kontrolor2.upisiuFajl(fout);
    operater1.upisiuFajl(fout);
    operater2.upisiuFajl(fout);
    sef1.upisiuFajl(fout);
    sef2.upisiuFajl(fout);

    fout.close();
}

bool prijava(string& tip, string& imeNaloga, string& sifraNaloga)
{

	fstream fin;
	fin.open("korisnici.dat", ios::binary);

	string ime;char ime1[21];string lozinka;char lozinka1[21];
	char tip1;
	char suspenzija;
	int count = 0;
	cout << "Unesite korisnicko ime"
		<< ": ";
	cin >> ime;
	cout << "Unesite lozinku"
		<< ": ";
	cin >> lozinka;

	while (!fin.eof()) {
		fin.read((char*)ime1, sizeof(char[21]));
		fin.read((char*)lozinka1, sizeof(char[21]));
		fin.read(&tip1, sizeof(char));
		fin.read(&suspenzija, sizeof(int));
		string imeString(ime1);
		string lozinkaString(lozinka1);

		if (imeString == ime) {
			count = 1;
			if (lozinkaString == lozinka)
			{
				cout << "Prijava uspjesna!\n";
				imeNaloga = ime1;
				sifraNaloga = lozinka1;
				tip = tip1;
				if (suspenzija == 1) // suspendovan je pa se ne moze prijaviti, baciti izuzetak  
					return false;
				fin.close();
				return true;
			}
			else
			{
				cout << "Pogresna lozinka!\n";
				fin.close();
				return false;
			}
		}
	}
	if (count == 0)
		cout << "korisnik nije nadjen\n";
	fin.close();
	return false;
}

Korisnik& prijavaSet(string username, string lozinka, std::set<std::shared_ptr<Korisnik>>& set)
{
	auto it = std::find_if(set.begin(), set.end(), [username](std::shared_ptr<Korisnik> k) {return (*k).getIme() == username;});
	if (it == set.end())
		throw std::exception("Korisnik ne postoji.");

	if ((*it)->isSuspended() == true) 
		throw std::exception("Korisnik suspendovan.");

	if ((*it)->getLozinka() != lozinka)
		throw std::exception("Pogresna lozinka");

	return **it;

}


void ucitajKorisnike(std::set<std::shared_ptr<Korisnik>>& set, std::ifstream& fajl)
{
	Korisnik temp;
	while (!fajl.eof())
	{
		temp.ucitajizFajla(fajl);
		if (temp.getTip() == 'A')
		{
			Administrator novi(temp.getIme(), temp.getLozinka());
			set.emplace(std::make_shared<Korisnik>(novi));
		}
		else if (temp.getTip() == 'K')
		{
			Kontrolor novi(temp.getIme(), temp.getLozinka());
			set.emplace(std::make_shared<Korisnik>(novi));
		}
		else if (temp.getTip() == 'S')
		{
			Sef novi(temp.getIme(), temp.getLozinka());
			set.emplace(std::make_shared<Korisnik>(novi));
		}
		else
		{
			Operater novi(temp.getIme(), temp.getLozinka());
			set.emplace(std::make_shared<Korisnik>(novi));
		}
	}

	fajl.close();

}

void azurirajBazu(std::set<std::shared_ptr<Korisnik>>& set)
{
	ofstream fajl;
	fajl.open("korisnici.dat", ios::binary || ios::out);

	for (auto it = set.begin(); it != set.end(); it++)
		(*it)->upisiuFajl(fajl);
}


int main()
{
	ifstream ucitavanje;
	ucitavanje.open("korisnici.dat", ios::binary || ios::in);
	std::set<std::shared_ptr<Korisnik> > korisnici;
	ucitajKorisnike(korisnici, ucitavanje);
	string tip, ime, lozinka;
	
	// treba obezbijediti 5 pokusaja ili koliko smo vec naveli u specifikaciji
	std::cout << "Unesi korisnicko ime:" << std::endl;
	std::cin >> ime;
	std::cout << "Unesi lozinku:" << std::endl;
	std::cin >> lozinka;
	
	auto ulogovan = prijavaSet(ime, lozinka, korisnici); 

	bool succes;
	//do
	//{
		//succes = prijava(tip, ime, lozinka);
	//} while (!succes);

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
				//ulogovani.spisakRezervacija();
			}
			else if (opcija == 'B')
			{
				// operater.otvaranjeRezervacije();
			}
			else if (opcija == 'C')
			{
				// operater.odbijeneRezervacije();   
			}
			else if (opcija == 'D')
			{
				// operater.oodbreneRezervacije();
			}
			else
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
				ulogovani.kreirajLet();
			}
			else if (opcija == 'B')
			{
				ulogovani.izmjenaStatusa();
			}
			else if (opcija == 'C')
			{
				ulogovani.informacijeLet();
			}
			else if (opcija == 'D')
			{
				ulogovani.otkazivanjeLeta();
			}
			else
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
					ulogovani.dnevniIzvjestaj();
				}
				else if (opcija1 == 'B')
				{
					ulogovani.sedmicniIzvjestaj();
				}
				else if (opcija1 == 'C')
				{
					ulogovani.mjesecniIzvjestaj();
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
			else
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
			else
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

