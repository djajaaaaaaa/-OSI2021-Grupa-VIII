#include <iostream>
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


int main()
{
    initDat();
	string tip, ime, lozinka;
	bool succes;
	do
	{
		succes = prijava(tip, ime, lozinka);
	} while (!succes);


	if (tip == "O")
	{
		string opcija;
		do
		{
			cout << "Izaberite zeljenu opciju (unesite odgovarajuce slovo) " << endl;
			cout << "A) Pregled rezervacija" << endl;
			cout << "B) Otvaranje rezervacije" << endl;
			cout << "C) Pregled odbijenih rezervacija" << endl;
			cout << "D) Pregled odobrenih rezervacija" << endl;
			cout << "E) Kraj" << endl;
			cin >> opcija;
			 
			if (opcija == "A")
			{
				// operater.spisakRezervacija();
			}
			else if (opcija == "B")
			{
				// operater.otvaranjeRezervacije();
			}
			else if (opcija == "C")
			{
				// operater.odbijeneRezervacije();   
			}
			else if (opcija == "D")
			{
				// operater.oodbreneRezervacije();
			}
			else
			{
				cout << "Nepoznata opcija!" << endl;
			}

		} while (opcija != "E");
	}

	else if (tip == "K")
	{
		string opcija;
		do
		{
			cout << "Izaberite zeljenu opciju (unesite odgovarajuce slovo) " << endl;
			cout << "A) Kreiranje leta" << endl;
			cout << "B) Mijenjanje statusa leta" << endl;
			cout << "C) Prikaz informacija o letu" << endl;
			cout << "D) Otkazivanje leta" << endl;
			cout << "E) Kraj" << endl;
			cin >> opcija;

			if (opcija == "A")
			{
				// kontrolor.kreirajLet()
			}
			else if (opcija == "B")
			{
				// kontrolor.izmjenaStatusa()
			}
			else if (opcija == "C")
			{
				// kontrolor.informacijeLet()
			}
			else if (opcija == "D")
			{
				// kontrolor.otkazivanjeLeta()
			}
			else
			{
				cout << "Nepoznata opcija!" << endl;
			}

		} while (opcija != "E");
	}

	else if (tip == "S")
	{
		string opcija;
		do
		{
			cout << "Izaberite zeljenu opciju (unesite odgovarajuce slovo) " << endl;
			cout << "A) Pregled izvjestaja" << endl;
			cout << "B) Pregled rezervacija" << endl;
			cout << "C) Kraj" << endl;
			cin >> opcija;

			if (opcija == "A")
			{
				string opcija1;
				cout << "Odaberite vrstu izvjestaja (unesite odgovarajuce slovo) " << endl;
				cout << "A) Dnevni" << endl;
				cout << "B) Sedmicni" << endl;
				cout << "C) Mjesecni" << endl;
				
				if (opcija1 == "A")
				{
					// sef.dnevniIzvjestaj()
				}
				else if (opcija1 == "B")
				{
					// sef.sedmicniIzvjestaj()
				}
				else if (opcija1 == "C")
				{
					// sef.mjesecniizvjestaj()
				}
				else
				{
					cout << "Nepoznata opcija!" << endl;
				}
			}
			else if (opcija == "B")
			{
				// sef.pregledRezervacija()
			}
			else
			{
				cout << "Nepoznata opcija!" << endl;
			}

		} while (opcija != "C");
	}

	else if (tip == "A")
	{
		Administrator trenutni(ime, lozinka);
		string opcija;
		do
		{
			cout << "Izaberite zeljenu opciju (unesite odgovarajuce slovo) " << endl;
			cout << "A) Kreiranje naloga" << endl;
			cout << "B) Brisanje naloga" << endl;
			cout << "C) Suspendovanje naloga" << endl;
			cout << "D) Kraj" << endl;
			cin >> opcija;

			if (opcija == "A")
			{
				trenutni.kreirajNalog();
			}
			else if (opcija == "B")
			{
				// administrator.brisanjeNaloga()
			}
			else if (opcija == "C")
			{
				// administrator.suspendovanejNaloga()
			}
			else
			{
				cout << "Nepoznata opcija!" << endl;
			}

		} while (opcija != "D");
		
	}
	else
	{
	     cout << "Greska! Nepostojeci tip naloga!" << endl;
    }

    return 0;
}

