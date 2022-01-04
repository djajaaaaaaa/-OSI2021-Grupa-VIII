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
	fin.open("korisnici.dat", ios::in);

	string ime;char ime1[21];string lozinka;char lozinka1[21];
	char tip1;
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
    return 0;
}

